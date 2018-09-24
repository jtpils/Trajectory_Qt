#ifndef VIEWER_H
#define VIEWER_H
#include<QGLViewer/qglviewer.h>
#include<tracjectory.h>
#include"DataType.h"
class Viewer : public QGLViewer
{
public:
    Viewer();
    virtual void draw();
    virtual void init();
    void DrawPoint(std::vector<TrajectoryPoint> PointData);
    void DrawPoint(std::vector<PointXYZ> PointData);
    void DrawLines(std::vector<TrajectoryPoint> LineData);
public:
    bool isDrawPoint;
    bool isDrawLine;
    std::vector<TrajectoryPoint>TrajectoryPoints;
    std::vector<PointXYZ> PointData;
    QColor pointColor;
};

#endif // VIEWER_H
