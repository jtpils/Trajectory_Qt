#include "viewer.h"

Viewer::Viewer()
{
    pointColor.fromRgb(255,255,255);
    isDrawPoint=false;
    isDrawLine=true;
}
void Viewer::DrawPoint(std::vector<TrajectoryPoint> PointData)
{
    //画点
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for(size_t i=0;i<PointData.size();i+=100)
    {
        if(PointData[i].isControl==true)
        {
            //glColor3f(1.0,0,0);
            glVertex3d(PointData[i].Easting,PointData[i].Northing,PointData[i].Hell);
        }
        else
        {
            //glColor3f(pointColor.red()/255,pointColor.green()/255,pointColor.blue()/255);
            glVertex3d(PointData[i].Easting,PointData[i].Northing,PointData[i].Hell);
        }
    }
    glEnd();
}
void Viewer::DrawPoint(std::vector<PointXYZ> PointData)
{
    glPointSize(3.0);
    glBegin(GL_POINTS);
   for(size_t i=0;i<PointData.size();++i)
    {
        glVertex3d(PointData[i].x,PointData[i].y,PointData[i].z);
    }
    glEnd();
}
void Viewer::DrawLines(std::vector<TrajectoryPoint> LineData)
{
    //划线
            glBegin(GL_LINE_STRIP);
            for(size_t i=0;i<LineData.size()-1;++i)
            {
                if(LineData.size()==i)
                    break;
                glColor3f(1.0,0,0);
                glVertex3d(LineData[i].Easting,LineData[i].Northing,LineData[i].Hell);
                glVertex3d(LineData[i+1].Easting,LineData[i+1].Northing,LineData[i+1].Hell);
            }
            glEnd();
}
void Viewer::draw()
{
    if(isDrawPoint)
    {
        DrawPoint(TrajectoryPoints);
        DrawPoint(PointData);

    }
    if(isDrawLine)
    {
        DrawLines(TrajectoryPoints);
    }

}

void Viewer::init()
{
    restoreStateFromFile();
    //help();
}
