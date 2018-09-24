#include"tracjectory.h"
#include<QDebug>
#include<QProgressDialog>
#include<QCoreApplication>
#include<fstream>
TrajectoryPoint::TrajectoryPoint()
{
    GPSTime=0;
    Easting=0;
    Northing=0;
    Hell=0;
    Heading=0;
    Pitch=0;
    Roll=0;
    Longitude=0;
    Latitude=0;
    TotSlpDst=0;
    isControl=false;

}
TrajectoryPoint::~TrajectoryPoint()
{

}
TrajectoryPoint TrajectoryPoint::operator +(const TrajectoryPoint& pt)
{
    TrajectoryPoint p;
    p.GPSTime=GPSTime+pt.GPSTime;
    p.Easting=Easting+pt.Easting;
    p.Northing=Northing+pt.Northing;
    p.Hell=Hell+pt.Hell;
    p.Heading=Heading+pt.Heading;
    p.Pitch=Pitch+pt.Pitch;
    p.Roll=Roll+pt.Roll;
    p.Latitude=Latitude+pt.Latitude;
    p.Longitude=Longitude+pt.Longitude;
    p.TotSlpDst=TotSlpDst+pt.TotSlpDst;
    return p;
}
TrajectoryPoint TrajectoryPoint::operator -(const TrajectoryPoint& pt)
{
    TrajectoryPoint p;
    p.GPSTime=GPSTime-pt.GPSTime;
    p.Easting=Easting-pt.Easting;
    p.Northing=Northing-pt.Northing;
    p.Hell=Hell-pt.Hell;
    p.Heading=Heading-pt.Heading;
    p.Pitch=Pitch-pt.Pitch;
    p.Roll=Roll-pt.Roll;
    p.Latitude=Latitude-pt.Latitude;
    p.Longitude=Longitude-pt.Longitude;
    p.TotSlpDst=TotSlpDst-pt.TotSlpDst;
    return p;
}
//轨迹打开
std::vector<TrajectoryPoint> TrajectoryRead(std::string filename,double& east,double& north,double& h)
{
    FILE* fp=NULL;
    fp=fopen(filename.c_str(),"r");
    if(fp==NULL)
    {
        QMessageBox::critical(NULL,QObject::tr("Error"),QObject::tr("Cannot Open Trajectory Point!"));
        fclose(fp);
    }
    std::vector<TrajectoryPoint> Trajectory;
    TrajectoryPoint tmp;
    char* tempString=new char[20];
    double m_s=0,tt=0;
    bool isCoordinateMove=false;
    if((east<0.001)&&(north<0.001)&&(h<0.001))
        isCoordinateMove=false;
    else
        isCoordinateMove=true;
    while (fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %s",&tmp.GPSTime,&tmp.Easting,&tmp.Northing,&tmp.Hell,&tmp.Heading,&tmp.Pitch,&tmp.Roll,&tmp.Longitude,&tmp.Latitude,tempString)!=EOF)
    {
        if(!isCoordinateMove)//计算平移参数
        {
            east=int(tmp.Easting/10)*10;
            north=int(tmp.Northing/10)*10;
            h=int(tmp.Hell/10)*10;
            isCoordinateMove=true;
        }
        tmp.TotSlpDstString=std::string(tempString);
        tmp.Easting=tmp.Easting-east;
        tmp.Northing=tmp.Northing-north;
        tmp.Hell=tmp.Hell-h;
        if(tempString[0]=='E')
        {
            m_s=tt;
            tmp.TotSlpDst=m_s;
        }
        else
        {
            m_s=atof(tempString);
            tmp.TotSlpDst=m_s;
            tt=m_s;
        }
        Trajectory.push_back(tmp);
    }
    fclose(fp);
    delete tempString;
    qDebug()<<Trajectory.size()<<"trajectory point read done!";
    return Trajectory;
}
std::vector<TrajectoryPoint> TrajectoryRead(std::string filename)
{
    std::vector<TrajectoryPoint> Trajectory;
    FILE* fp=NULL;
    fp=fopen(filename.c_str(),"r");
    if(fp==NULL)
    {
        QMessageBox::critical(NULL,QObject::tr("Error"),QObject::tr("Cannot Open Trajectory Point!"));
        return Trajectory;
    }
    TrajectoryPoint tmp;
    char* tempString=new char[20];
    double m_s=0,tt=0;
    bool isCoordinateMove=false;//坐标是否平移，默认为否
    double east=0,north=0,h=0;
    while (fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %s",&tmp.GPSTime,&tmp.Easting,&tmp.Northing,&tmp.Hell,&tmp.Heading,&tmp.Pitch,&tmp.Roll,&tmp.Longitude,&tmp.Latitude,tempString)!=EOF)
    {

        if(!isCoordinateMove)
        {
            east=int(tmp.Easting/10)*10;
            north=int(tmp.Northing/10)*10;
            h=int(tmp.Hell/10)*10;
            isCoordinateMove=true;
        }
        tmp.TotSlpDstString=std::string(tempString);
        tmp.Easting=(tmp.Easting-east);
        tmp.Northing=(tmp.Northing-north);
        tmp.Hell=(tmp.Hell-h);
        if(tempString[0]=='E')
        {
            m_s=tt;
            tmp.TotSlpDst=m_s;
        }
        else
        {
            m_s=atof(tempString);
            tmp.TotSlpDst=m_s;
            tt=m_s;
        }
        Trajectory.push_back(tmp);
    }
    fclose(fp);
    delete tempString;
    qDebug()<<Trajectory.size()<<"trajectory point read done!";
    return Trajectory;
}
//轨迹保存
bool TrajectorySave(std::string filename, std::vector<TrajectoryPoint> v_points, double east, double north, double h)
{
    FILE* fp=NULL;
    fp=fopen(filename.c_str(),"w+");
    if(fp==NULL)
    {
        QMessageBox::critical(NULL,QObject::tr("Error"),QObject::tr("Cannot Open Trajectory Point!"));
        fclose(fp);
        qDebug()<<"Save fail!";
        return false;
    }
    //进度对话框
    QProgressDialog dlg(QObject::tr("Save Progress"),QObject::tr("Cancle"),0,100);
    dlg.setWindowTitle(QObject::tr("Save ..."));
    size_t num=v_points.size();
    dlg.setRange(0,num);
    dlg.show();
    for(size_t i=0;i<num;++i)
    {
        fprintf(fp,"%.3lf %.3lf %.3lf %.3lf %lf %lf %lf %lf %lf %s\n",v_points[i].GPSTime,v_points[i].Easting+east,v_points[i].Northing+north,v_points[i].Hell+h,v_points[i].Heading,v_points[i].Pitch,v_points[i].Roll,v_points[i].Longitude,v_points[i].Latitude,v_points[i].TotSlpDstString.c_str());
        dlg.setValue(i);
        QCoreApplication::processEvents();
        if(dlg.wasCanceled())
            break;
    }
    fclose(fp);
    qDebug()<<"Save done!";
    return true;
}
bool TrajectorySave(std::string filename, std::vector<TrajectoryPoint> v_points)
{
    FILE* fp=NULL;
    fp=fopen(filename.c_str(),"w+");
    if(fp==NULL)
    {
        QMessageBox::critical(NULL,QObject::tr("Error"),QObject::tr("Cannot Open Trajectory Point!"));
        fclose(fp);
        qDebug()<<"Save fail!";
        return false;
    }
    //进度对话框
    QProgressDialog dlg(QObject::tr("Save Progress"),QObject::tr("Cancle"),0,100);
    dlg.setWindowTitle(QObject::tr("Save ..."));
    size_t num=v_points.size();
    dlg.setRange(0,num);
    dlg.show();
    for(size_t i=0;i<num;++i)
    {
        fprintf(fp,"%.3lf %.3lf %.3lf %.3lf %lf %lf %lf %lf %lf %s\n",v_points[i].GPSTime,v_points[i].Easting,v_points[i].Northing,v_points[i].Hell,v_points[i].Heading,v_points[i].Pitch,v_points[i].Roll,v_points[i].Longitude,v_points[i].Latitude,v_points[i].TotSlpDstString.c_str());
        dlg.setValue(i);
        QCoreApplication::processEvents();
        if(dlg.wasCanceled())
            break;
    }
    fclose(fp);
    qDebug()<<"Save done!";
    return true;
}
