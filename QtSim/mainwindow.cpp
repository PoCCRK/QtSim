#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QtSim");
    QDir dir(QDir::currentPath());
    dir.cdUp();
    msgLabel = new QLabel(ui->statusBar);
    msgLabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addWidget(msgLabel);
    model = new QStandardItemModel(ui->treeView);
    newdialog = new NewDialog(this);
    detailDialog = new DetailDialog(this);
    extractDialog = new ExtractDialog(this);
    menu = new QMenu(this);
    menu->addAction(ui->actionDetail);
    task = new Sim();
    thread = new QThread();
    task->moveToThread(thread);
    ui->doSSim->setEnabled(false);
    ui->doTSim->setEnabled(false);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    newdialog->setEnvironment(QString("%1/input").arg(dir.absolutePath()), QString("%1/output").arg(dir.absolutePath()), QString("%1/temp").arg(dir.absolutePath()),
                              QStringLiteral("-paTsu"), QString("%1/bin").arg(dir.absolutePath()), QString("%1/workspace").arg(dir.absolutePath()));
    newdialog->setSim(5, 10, 4, 8, 1, 1);
    task->setEnvironment(QString("%1/input").arg(dir.absolutePath()), QString("%1/output").arg(dir.absolutePath()), QString("%1/temp").arg(dir.absolutePath()),
                         QStringLiteral("-paTsu"), QString("%1/bin").arg(dir.absolutePath()), QString("%1/workspace").arg(dir.absolutePath()));
    task->setSim(5, 10, 4, 8, 1, 1);

    QObject::connect(task, &Sim::SimRunning, msgLabel, &QLabel::setText);
    QObject::connect(task, &Sim::SimFail, this, &MainWindow::whenSimFail);

    QObject::connect(newdialog, &NewDialog::giveEnvironment, task, &Sim::setEnvironment);
    QObject::connect(newdialog, &NewDialog::giveSim, task, &Sim::setSim);
    QObject::connect(task, &Sim::TSimDetailComplete, this, &MainWindow::whenTSimDetailComplete);

    QObject::connect(task, &Sim::ProjectListMade, this, &MainWindow::setProjectList);
    QObject::connect(task, &Sim::SSimComplete, this, &MainWindow::setSSim);
    QObject::connect(task, &Sim::TSimComplete, this, &MainWindow::setTSim);

    QObject::connect(ui->doSSim, &QPushButton::clicked, task, &Sim::doSSim);
    QObject::connect(ui->doTSim, &QPushButton::clicked, task, &Sim::doTSim);
    QObject::connect(this, &MainWindow::doTSimDetail, task, &Sim::doTSimDetail);
    QObject::connect(extractDialog, &ExtractDialog::doExtract, task, &Sim::extract);

    model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("project")
                                     << QStringLiteral("tsim") << QStringLiteral("tsim target")
                                     << QStringLiteral("ssim") << QStringLiteral("ssim target"));
    ui->treeView->setModel(model);
    thread->start();
}

MainWindow::~MainWindow()
{
    thread->requestInterruption();
    thread->quit();
    thread->wait();
    delete newdialog;
    delete detailDialog;
    delete menu;
    delete task;
    delete thread;
    delete model;
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    switch( QMessageBox::question(this, tr("Exit"),
        tr("Do you really want to close QtSim?"),
        tr("Yes"), tr("No"),
        0, 1 ) )
    {
    case 0:
        close();
        break;
    case 1:
    default:
        break;
    }
}

void MainWindow::on_actionNew_triggered()
{
    newdialog->exec();
}

void MainWindow::setProjectList(QList<Node*>* project_list)
{
    // I know that it is not ideal here.
    model->clear();
    model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("project")
                                     << QStringLiteral("tsim") << QStringLiteral("tsim target")
                                     << QStringLiteral("ssim") << QStringLiteral("ssim target"));
    if (!project_list->isEmpty())
    {
        ui->doSSim->setEnabled(false);
        ui->doTSim->setEnabled(false);
        QStandardItem* itemProject;
        for (Node* n : *project_list)
        {
            itemProject =  new QStandardItem(n->getNodeData().fileName());
            model->appendRow(itemProject);
        }
        ui->doSSim->setEnabled(true);
        ui->doTSim->setEnabled(true);
    }
}
void MainWindow::setSSim(QList<float>* ssim_list, QList<QFileInfo>* ssimf_list)
{
    for (int i=0; i<model->rowCount(); i++)
    {
        model->setItem(i, 3, new QStandardItem(QString::number(ssim_list->at(i), 'f', 0)));
        model->setItem(i, 4, new QStandardItem(ssimf_list->at(i).fileName()));
    }
}
void MainWindow::setTSim(QList<float>* tsim_list, QList<QFileInfo>* tsimf_list)
{
    for (int i=0; i<model->rowCount(); i++)
    {
        model->setItem(i, 1, new QStandardItem(QString::number(tsim_list->at(i), 'f', 0)));
        model->setItem(i, 2, new QStandardItem(tsimf_list->at(i).fileName()));
    }
}

void MainWindow::whenSimFail(const QString& failmsg)
{
    QMessageBox::warning(this, tr("SimFail"), failmsg);
}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    if (index.isValid())
      menu->exec(QCursor::pos());
}

void MainWindow::on_actionDetail_triggered()
{
    if (task->tsimf_list == nullptr || task->tsimf_list->isEmpty())
        QMessageBox::warning(this, tr("Detail"), tr("Please do TSim first."));
    else{
        QModelIndex currentIndex = ui->treeView->currentIndex();
        QString project_name = model->item(currentIndex.row(), 0)->text();
        emit doTSimDetail(project_name);
    }
}

void MainWindow::whenTSimDetailComplete(const QString& s)
{
    detailDialog->appendText(s);
    detailDialog->exec();
}

void MainWindow::on_doTSim_clicked()
{
    ui->doTSim->setEnabled(false);
}

void MainWindow::on_doSSim_clicked()
{
    ui->doSSim->setEnabled(false);
}

void MainWindow::on_actionClean_triggered()
{
    switch( QMessageBox::question(this, tr("Clean"),
            QString("Do you really delete all files in temp dir and output dir?\n"
                    "Which are:\n%1\n%2").arg(task->getTemp()).arg(task->getOutput()),
        tr("Yes"), tr("No"),
        0, 1 ) )
    {
    case 0:
        task->clean();
        break;
    case 1:
    default:
        break;
    }
}

void MainWindow::on_actionExtract_triggered()
{
    extractDialog->exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("About"),
            tr("Contact Liang DaHao for support: 353984017@qq.com"));
}
