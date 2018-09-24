#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QDockWidget>
#include"myfunction.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitializeVar();
    do_setCenterWidget(m_view);
    showMaximized();
    statusBar()->showMessage("case load",3000);

    ui->actionGCP_Associate->setEnabled(false);
    ui->actionTrajectory_Optimization->setEnabled(false);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(onOpen()));

    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(onSave()));
    connect(ui->actionBlack,SIGNAL(triggered()),this,SLOT(onBackGround_black()));
    connect(ui->actionWhite,SIGNAL(triggered()),this,SLOT(onBackGround_white()));
    connect(ui->actionGCP_Import,SIGNAL(triggered()),this,SLOT(onGCPImport()));
    connect(ui->actionGCP_Associate,SIGNAL(triggered()),this,SLOT(onGCPAssociate()));
    connect(ui->actionPretreatment,SIGNAL(triggered()),this,SLOT(onPretreatment()));
    connect(ui->actionTrajectory_Optimization,SIGNAL(triggered()),this,SLOT(onTrajectoryOptimization()));
}
void MainWindow::InitializeVar()
{
    m_view=new myVtkWidget;
    move[0]=0;move[1]=0;move[2]=0;
}
void MainWindow::do_setCenterWidget(QWidget *viewer)
{
    this->setCentralWidget(viewer);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onOpen()
{
    QFileDialog dlg;
    dlg.setFileMode(QFileDialog::ExistingFiles);
    //dlg.setNameFilter(tr("PCD Files(*.pcd);;Las Files(*.las);;Trajectory(*.hpr)"));
    QString filter=tr("PCD Files(*.pcd);;Las Files(*.las);;Trajectory(*.hpr)");
    QStringList fileNamePathList=dlg.getOpenFileNames(this,tr("Get file Path"),QDir::currentPath(),filter);
    for(int i=0;i<fileNamePathList.size();++i)
    {
        QFileInfo fileinfo=QFileInfo(fileNamePathList.at(i));
        QString m_strPathName=fileinfo.absoluteFilePath();//文件的绝对路径
        QString m_strFileExt=fileinfo.suffix();//文件扩展名
        QString m_strFileName=fileinfo.fileName();
        if(m_strFileExt=="hpr")
        {
            v_TrajectoryPoints.clear();
            v_TrajectoryPoints=TrajectoryRead(m_strPathName.toStdString(),move[0],move[1],move[2]);
            m_view->DrawPoint(Trajectory2PCL(v_TrajectoryPoints,500),m_strFileName.toStdString());
        }
    }
}
void MainWindow::onSave()
{
    QFileDialog dlg;
    QString fileNamePath=dlg.getSaveFileName(this,tr("set file name"),QDir::currentPath());
    TrajectorySave(fileNamePath.toStdString(),v_TrajectoryPoints,move[0],move[1],move[2]);
}

void MainWindow::onBackGround_black()
{
    m_view->SetBackGround(0,0,0);
}
void MainWindow::onBackGround_white()
{
    m_view->SetBackGround(255,255,255);
}

void MainWindow::onBackGround_select()
{

}
void MainWindow::onCoordinate()
{
    m_view->DrawCoordinate();
}
void MainWindow::onGCPImport()
{
    QFileDialog dlg;
    QString fileName=dlg.getOpenFileName(this,tr("Import GCP"),QDir::currentPath());
    GCPData.clear();
    GCPData=TrajectoryRead(fileName.toStdString(),move[0],move[1],move[2]);
    for(size_t i=0;i<GCPData.size();++i)
    {
        GCPData[i].isControl=true;
    }
    m_view->DrawPoint(Trajectory2PCL(GCPData),"GCP");
    m_view->ChangePointSize(3,"GCP");
    ui->actionGCP_Associate->setEnabled(true);
}

void MainWindow::onGCPAssociate()
{
    //GCP与轨迹进行关联
    double GPSTime_min=v_TrajectoryPoints[0].GPSTime;
    int index=0;
    for(size_t i=0;i<GCPData.size();++i)
    {
        index=ceil((GCPData[i].GPSTime-GPSTime_min)/0.005);
        GCPIndex.push_back(index);
        v_TrajectoryPoints[index].isControl=true;
    }
    //将控制点和对应轨迹点连线，表明偏差情况
    m_view->DrawLine(GCPData,v_TrajectoryPoints,GCPIndex,"error");

}

void MainWindow::onPretreatment()
{
    //预处理，计算两个历元间差值
    for(size_t i=0;i<v_TrajectoryPoints.size()-1;++i)
    {
        TrajectoryPoint tmp;
        tmp=v_TrajectoryPoints[i+1]-v_TrajectoryPoints[i];
        v_DTraj.push_back(tmp);
    }
}
#include<g2o/types/slam3d/edge_se3_pointxyz.h>
#include<g2o/types/slam3d/vertex_pointxyz.h>
#include<g2o/core/optimization_algorithm_levenberg.h>
#include<g2o/solvers/cholmod/linear_solver_cholmod.h>
#include<g2o/core/block_solver.h>
void MainWindow::onTrajectoryOptimization()
{
    //创建线性求解器
    g2o::BlockSolverX::LinearSolverType* linearSolver=new g2o::LinearSolverCholmod<g2o::BlockSolverX::PoseMatrixType>();
    //创建线性求解器的块
    g2o::BlockSolverX* blockSolver=new g2o::BlockSolverX(linearSolver);
    //创建优化算法
    g2o::OptimizationAlgorithmLevenberg* algorithm=new g2o::OptimizationAlgorithmLevenberg(blockSolver);
    //轨迹优化
    for(size_t i=0;i<v_TrajectoryPoints.size();++i)
    {
        //遍历轨迹点，将轨迹点转换为g2o的定点，并构建边
        g2o::VertexSE3 ver;
        //如果为控制点，
    }
}
