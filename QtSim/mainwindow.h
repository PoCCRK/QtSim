#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "node.h"
#include "sim.h"
#include "newdialog.h"
#include "extractdialog.h"
#include "detaildialog.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QThread>
#include <QString>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QModelIndex>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void doTSimDetail(const QString&);

public slots:
    void setProjectList(QList<Node*>* project_list);
    void setSSim(QList<float>* ssim_list, QList<QFileInfo>* ssimf_list);
    void setTSim(QList<float>* tsim_list, QList<QFileInfo>* tsimf_list);
    void whenSimFail(const QString& failmsg);
    void whenTSimDetailComplete(const QString& s);

private slots:

    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void on_doTSim_clicked();

    void on_doSSim_clicked();

    void on_actionClean_triggered();

    void on_actionDetail_triggered();

    void on_actionExtract_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    Sim* task;
    QThread* thread;
    QLabel* msgLabel;
    QStandardItemModel* model;
    NewDialog* newdialog;
    DetailDialog* detailDialog;
    ExtractDialog* extractDialog;
    QMenu* menu;
};

#endif // MAINWINDOW_H
