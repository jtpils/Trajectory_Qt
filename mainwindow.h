#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"MyVtkWidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void InitializeVar();
    void do_setCenterWidget(QWidget* viewer);
private slots:
    void onOpen();
    void onSave();
    void onBackGround_black();
    void onBackGround_white();
    void onBackGround_select();
    void onCoordinate();
    void onGCPImport();
    void onGCPAssociate();
    void onPretreatment();
    void onTrajectoryOptimization();
private:
    Ui::MainWindow *ui;
    myVtkWidget* m_view;
    std::vector<TrajectoryPoint> v_TrajectoryPoints;
    std::vector<TrajectoryPoint> v_DTraj;//点间差值
    std::vector<TrajectoryPoint> GCPData;
    std::vector<int> GCPIndex;
    double move[3];
};

#endif // MAINWINDOW_H
