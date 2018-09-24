//http://tieba.baidu.com/p/4101387026
//
//【点选部分】
//https://blog.csdn.net/liang583206/article/details/73386836
//静态函数、动态函数之间关系参考：郑莉、董渊,C++程序设计（第四版）[M],清华大学出版社,2010,7:153-158
#pragma once
#include <QVTKWidget.h>
#include <vtkAutoInit.h> 
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);

#include<pcl/io/pcd_io.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include"tracjectory.h"
class vtkRenderer;
class	vtkRenderWindowInteractor;
class myVtkWidget:
	public QVTKWidget
{
	Q_OBJECT
public:
    explicit myVtkWidget(QWidget *parent = 0);
    void DrawPoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,std::string PointsID);
    void DrawLine(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,std::string LinesID);
    void DrawLine(std::vector<TrajectoryPoint> GCP,std::vector<TrajectoryPoint> v_Trajectorys,std::vector<int> GCPIdx, std::string LinesID);
    void ChangePointSize(int PointSize,std::string PointsID);
    void SetBackGround(int r,int g,int b);
    void DrawCoordinate();
private:

	vtkRenderer *ren1;
	vtkRenderWindowInteractor *iren;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
};
