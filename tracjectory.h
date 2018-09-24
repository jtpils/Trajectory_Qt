#ifndef TRACJECTORY_H
#define TRACJECTORY_H
#include<iostream>
#include<string>
#include<vector>
#include<QMessageBox>
class TrajectoryPoint
{
public:
    TrajectoryPoint();
    ~TrajectoryPoint();
    TrajectoryPoint operator +(const TrajectoryPoint& pt);
    TrajectoryPoint operator -(const TrajectoryPoint& pt);
public:
    double GPSTime;
    double Easting;
    double Northing;
    double Hell;
    double Heading;
    double Pitch;
    double Roll;
    double Longitude;
    double Latitude;
    double TotSlpDst;
    std::string TotSlpDstString;
    bool isControl;
};
std::vector<TrajectoryPoint> TrajectoryRead(std::string filename,double& east,double& north,double& h);
std::vector<TrajectoryPoint> TrajectoryRead(std::string filename);
bool TrajectorySave(std::string filename,std::vector<TrajectoryPoint> v_points,double east,double north,double h);
bool TrajectorySave(std::string filename,std::vector<TrajectoryPoint> v_points);
#endif // TRACJECTORY_H
