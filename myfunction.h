#ifndef MYFUNCTION_H
#define MYFUNCTION_H
#include<QDebug>
#include<pcl/point_cloud.h>
#include<pcl/point_types.h>
#include<Eigen/Dense>
#include"tracjectory.h"
typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

//【轨迹点转化为pcl点】
PointCloudT::Ptr Trajectory2PCL(std::vector<TrajectoryPoint> Data)
{
    PointCloudT::Ptr cloud(new PointCloudT);
    for(size_t i=0;i<Data.size();i++)
    {
        PointT tmp;
        tmp.x=Data[i].Easting;
        tmp.y=Data[i].Northing;
        tmp.z=Data[i].Hell;
        if(Data[i].isControl)
        {
            tmp.r=255;
            tmp.g=0;
            tmp.b=0;
        }
        else
        {
            tmp.r=0;
            tmp.g=0;
            tmp.b=255;
        }
        cloud->points.push_back(tmp);
    }
    cloud->height=1;
    cloud->width=Data.size();
    qDebug()<<"Trajectory trans done";
    return cloud;
}
//【轨迹点转化为pcl点-抽稀】
PointCloudT::Ptr Trajectory2PCL(std::vector<TrajectoryPoint> Data,int Ratio)
{
    PointCloudT::Ptr cloud(new PointCloudT);
    for(size_t i=0;i<Data.size();i+=Ratio)
    {
        PointT tmp;
        tmp.x=Data[i].Easting;
        tmp.y=Data[i].Northing;
        tmp.z=Data[i].Hell;
        if(Data[i].isControl)
        {
            tmp.r=255;
            tmp.g=0;
            tmp.b=0;
        }
        else
        {
            tmp.r=0;
            tmp.g=0;
            tmp.b=255;
        }
        cloud->points.push_back(tmp);
    }
    cloud->height=1;
    cloud->width=Data.size();
    qDebug()<<"Trajectory trans done";
    return cloud;
}

//欧拉角平移值转变换矩阵
void EulerAngle2TransformMatrix(Eigen::Matrix4d& T,TrajectoryPoint pt)
{
    Eigen::Matrix3d Rx,Ry,Rz,R;
    Rx(0,0)=1;Rx(0,1)=0;Rx(0,2)=0;
    Rx(1,0)=0;Rx(1,1)=cos(pt.Heading*M_PI/180);Rx(1,2)=-sin(pt.Heading*M_PI/180);
    Rx(2,0)=0;Rx(2,1)=sin(pt.Heading*M_PI/180);Rx(2,2)=cos(pt.Heading*M_PI/180);
    Ry<<cos(pt.Pitch*M_PI/180),0,-sin(pt.Pitch*M_PI/180),0,1,0,sin(pt.Pitch*M_PI/180),0,cos(pt.Pitch*M_PI/180);
    Rz<<cos(pt.Roll*M_PI/180),-sin(pt.Roll*M_PI/180),0,sin(pt.Roll*M_PI/180),cos(pt.Roll*M_PI/180),0,0,0,1;
    R=Rx*Ry*Rz;
    T(0,0)=R(0,0);  T(0,1)=R(0,1);  T(0,2)=R(0,2);  T(0,3)=pt.Easting;
    T(1,0)=R(1,0);  T(1,1)=R(1,1);  T(1,2)=R(0,1);  T(1,3)=pt.Northing;
    T(2,0)=R(2,0);  T(2,1)=R(2,1);  T(2,2)=R(0,2);  T(2,3)=pt.Hell;
    T(3,0)=0;       T(3,1)=0;       T(3,2)=0;       T(3,3)=1;
}
Eigen::Matrix4d transitionMatrix(Eigen::Matrix4d& matrix1,Eigen::Matrix4d& matrix2)
{
    Eigen::Matrix4d transition;
    transition=matrix2*matrix1.transpose();
    return transition;
}
#endif // MYFUNCTION_H
