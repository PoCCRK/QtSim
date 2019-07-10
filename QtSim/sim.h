#ifndef SIM_H
#define SIM_H

#include "node.h"
#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QString>
#include <QRegExp>
#include <QList>
#include <QDateTime>
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <QtAlgorithms>

class Sim : public QObject
{
    Q_OBJECT

public:
    explicit Sim(QObject *parent = nullptr);
    ~Sim();
    static const int C;
    static const int CPP;
    static const int JAVA;
    static const int LISP;
    static const int M2;
    static const int MIRA;
    static const int PASC;
    static const int TEXT;
    QList<Node*>* project_list;
    QList<float>* ssim_list;
    QList<QFileInfo>* ssimf_list;
    QList<float>* tsim_list;
    QList<QFileInfo>* tsimf_list;
    QString getTemp();
    QString getOutput();

signals:
    void SimFail(const QString&);
    void SimRunning(const QString&);
    void ProjectListMade(QList<Node*>*);
    void SSimComplete(QList<float>*, QList<QFileInfo>*);
    void TSimComplete(QList<float>*, QList<QFileInfo>*);
    void TSimDetailComplete(const QString&);

public slots:
    void extract(const QString& option, const QString& input, const QString& output);
    void makeProjectList();
    void computeSSim(QList<Node*>* input_list);
    void computeTSim(QList<Node*>* input_list);
    void doSSim();
    void doTSim();
    void clean();
    void setEnvironment(QString inpute_directory, QString output_directory, QString temp_directory,
                        QString sim_options, QString bin, QString workspace);
    void setSim(int dir_weight, int file_weight, int same_dir_name,
                int same_file_name, int same_file_size, int same_file_time);
    void doTSimDetail(const QString& project_name);

private:
    QDateTime date_time;
    QString bin;
    QString workspace;
    QString input_directory;
    QString output_directory;
    QString temp_directory;
    QString sim_options;
    QProcess* process;
    int dir_weight;
    int file_weight;
    int same_dir_name;
    int same_file_name;
    int same_file_size;
    int same_file_time;
    float computeSSimSub1(Node* s, Node* d);
    float computeSSimSub2(Node* s, Node* d);
    QFileInfoList toSrcList(Node* n);
    void deleFolder(QString path);
};

#endif // SIM_H
