#include "MyVtkWidget.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
myVtkWidget::myVtkWidget(QWidget *parent /* = 0 */) :
QVTKWidget(parent)
{
	//变量初始化
	//QVTK的初始化
	viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
	this->ren1 = vtkRenderer::New();
	this->GetRenderWindow()->AddRenderer(ren1);
	this->iren = this->GetInteractor();
	SetRenderWindow(viewer->getRenderWindow());
	viewer->setupInteractor(GetInteractor(), GetRenderWindow());
	update();
}
void myVtkWidget::DrawPoint(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,std::string PointsID)
{
    viewer->addPointCloud(cloud,PointsID);
    viewer->resetCamera();
    update();
}
void myVtkWidget::DrawLine(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,std::string LinesID)
{
    int num=cloud->points.size();
    for(int i=0;i<num;++i)
    {
        if(i==num)
            break;
        viewer->addLine(cloud->points[i],cloud->points[i+1],LinesID);
    }
    update();
}
void myVtkWidget::DrawLine(std::vector<TrajectoryPoint> GCP, std::vector<TrajectoryPoint> v_Trajectorys, std::vector<int> GCPIdx, std::string LinesID)
{
    int num=GCP.size();
    for(int i=0;i<num;++i)
    {
        pcl::PointXYZ pt1(GCP[i].Easting,GCP[i].Northing,GCP[i].Hell),pt2(v_Trajectorys[GCPIdx[i]].Easting,v_Trajectorys[GCPIdx[i]].Northing,v_Trajectorys[GCPIdx[i]].Hell);
        viewer->addLine(pt1,pt2,0,255,0,LinesID+std::to_string(i));
    }
    update();
}
void myVtkWidget::SetBackGround(int r, int g, int b)
{
    viewer->setBackgroundColor(r,g,b);
    update();
}
void myVtkWidget::ChangePointSize(int PointSize, std::string PointsID)
{
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,PointSize,PointsID);
    update();
}
void myVtkWidget::DrawCoordinate()
{
    viewer->addCoordinateSystem(1.0);
    update();
}
