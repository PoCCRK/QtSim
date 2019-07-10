#include "sim.h"

const int Sim::C = 1;
const int Sim::CPP = 2;
const int Sim::JAVA = 3;
const int Sim::LISP = 4;
const int Sim::M2 = 5;
const int Sim::MIRA = 6;
const int Sim::PASC = 7;
const int Sim::TEXT = 8;

Sim::Sim(QObject *parent) : QObject(parent)
{
    this->project_list = nullptr;
    this->ssim_list = nullptr;
    this->tsim_list = nullptr;
    this->ssimf_list = nullptr;
    this->tsimf_list = nullptr;
    this->date_time = QDateTime::currentDateTime();
    process = new QProcess();
}
QString Sim::getTemp()
{
    return this->temp_directory;
}
QString Sim::getOutput()
{
    return this->output_directory;
}

void Sim::setEnvironment(QString inpute_directory, QString output_directory, QString temp_directory,
                         QString sim_options, QString bin, QString workspace)
{
    this->date_time = QDateTime::currentDateTime();
    this->input_directory = inpute_directory;
    this->output_directory = output_directory;
    this->temp_directory = temp_directory;
    this->sim_options = sim_options;
    this->bin = bin;
    this->workspace = workspace;
    makeProjectList();
}

void Sim::setSim(int dir_weight, int file_weight, int same_dir_name,
                 int same_file_name, int same_file_size, int same_file_time)
{
    this->dir_weight = dir_weight;
    this->file_weight = file_weight;
    this->same_dir_name = same_dir_name;
    this->same_file_name = same_file_name;
    this->same_file_size = same_file_size;
    this->same_file_time = same_file_time;
}

void Sim::makeProjectList()
{
    QDir dir(input_directory);
    emit SimRunning(QStringLiteral("Making ProjectList."));
    if (!dir.exists(input_directory))
    {
        emit SimFail(QStringLiteral("Make project list failed. Please check your input."));
        return;
    }

    if (project_list != nullptr)
    {
        for (Node* p : *project_list)
        {
            Node::deleAll(p);
            p = nullptr;
        }
        project_list->clear();
    }
    else
        project_list = new QList<Node*>();

    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList folder_list = dir.entryInfoList();
    for (QFileInfo project : folder_list)
    {
        project_list->append(Node::createFileTree(project.absoluteFilePath()));
    }
    emit ProjectListMade(project_list);
    emit SimRunning(QStringLiteral("makeProjectList done."));
}

void Sim::computeSSim(QList<Node*>* input_list)
{
    if (ssim_list != nullptr)
        ssim_list->clear();
    else
      ssim_list = new QList<float>();
    if (ssimf_list != nullptr)
        ssimf_list->clear();
    else
        ssimf_list = new QList<QFileInfo>();
    for (int i=0; i<input_list->size(); i++)
    {
        ssim_list->append(0);
        ssimf_list->append(QFileInfo());
    }
    for (int i=0; i<input_list->size(); i++)
    {
        for (int j=0; j<input_list->size(); j++)
        {
            if (i==j)
                continue;
            float ssim = computeSSimSub1(input_list->at(i), input_list->at(j));
            ssim_list->replace(i, qMax(ssim, ssim_list->at(i)));
            if (ssim_list->at(i) == ssim && ssim != 0)
                ssimf_list->replace(i, input_list->at(j)->getNodeData());
        }
    }
    for (int i=0; i<project_list->size(); i++)
    {
        ssim_list->replace(i,
            ssim_list->at(i)*100
            / (project_list->at(i)->getDirCount()*dir_weight + project_list->at(i)->getFileCount()*file_weight));
    }
}

void Sim::computeTSim(QList<Node*>* input_list)
{
    QList<QFileInfoList> src_list;
    for (Node* n : *input_list)
        src_list.append(toSrcList(n));

    QDir TempDir(temp_directory);
    QString datetimestr = date_time.toString(QStringLiteral("yyyyMMddHHmmsszzz"));
    TempDir.mkdir(QString("%1/%2").arg(temp_directory).arg(datetimestr));
    TempDir.cd(QString("%1/%2").arg(temp_directory).arg(datetimestr));

    if (tsim_list != nullptr)
        tsim_list->clear();
    else
      tsim_list = new QList<float>();
    if (tsimf_list != nullptr)
        tsimf_list->clear();
    else
        tsimf_list = new QList<QFileInfo>();
    for (int i=0; i<input_list->size(); i++)
    {
        tsim_list->append(0);
        tsimf_list->append(QFileInfo());
    }

    for (int i=0; i<src_list.size(); i++)
    {
        QString wfile_name = QString("%1/%2.cpp").arg(TempDir.absolutePath()).arg(input_list->at(i)->getNodeData().fileName());
        QFile wfile(wfile_name);
        if (wfile.open(QIODevice::WriteOnly))
        {
            QTextStream wstream(&wfile);
            for (QFileInfo fi : src_list.at(i))
            {
                QString suf = fi.suffix();
                if (suf == QStringLiteral("c") || suf == QStringLiteral("cpp")
                 || suf == QStringLiteral("h") || suf == QStringLiteral("hpp"))
                {
                    QFile rfile(fi.absoluteFilePath());
                    if (rfile.open(QIODevice::ReadOnly))
                    {
                        QTextStream rstream(&rfile);
                        wstream << rstream.readAll();
                        rfile.close();
                    }
                }
            }
            wfile.close();
            if (wfile.open(QIODevice::ReadOnly))
            {
                QTextStream rstream(&wfile);
                if (rstream.atEnd())
                {
                    wfile.close();
                    TempDir.remove(wfile_name);
                }
                else
                {
                    wfile.close();
                }
            }
        }

        wfile_name = QString("%1/%2.java").arg(TempDir.absolutePath()).arg(input_list->at(i)->getNodeData().fileName());
        wfile.setFileName(wfile_name);
        if (wfile.open(QIODevice::WriteOnly))
        {
            QTextStream wstream(&wfile);
            for (QFileInfo fi : src_list.at(i))
            {
                QString suf = fi.suffix();
                if (suf == QStringLiteral("java"))
                {
                    QFile rfile(fi.absoluteFilePath());
                    if (rfile.open(QIODevice::ReadOnly))
                    {
                        QTextStream rstream(&rfile);
                        wstream << rstream.readAll();
                    }
                    rfile.close();
                }
            }
            wfile.close();
            if (wfile.open(QIODevice::ReadOnly))
            {
                QTextStream rstream(&wfile);
                if (rstream.atEnd())
                {
                    wfile.close();
                    TempDir.remove(wfile_name);
                }
                else
                {
                    wfile.close();
                }
            }
        }
    }


    QString cmd;
    QDir OutputDir(output_directory);
    OutputDir.mkdir(QString("%1/%2").arg(output_directory).arg(datetimestr));
    OutputDir.cd(QString("%1/%2").arg(output_directory).arg(datetimestr));

    QFile cppfile(QString("%1/cpp.txt").arg(OutputDir.absolutePath()));
    QFile javafile(QString("%1/java.txt").arg(OutputDir.absolutePath()));

    if (cppfile.open(QIODevice::WriteOnly))
    {
        QTextStream wstream(&cppfile);
        QString program = QString("\"%1/sim_c++.exe\"").arg(bin);
        QStringList arguments;
        arguments << sim_options << QString("-o \"%1/cpp.txt\"").arg(TempDir.absolutePath());
        QStringList filters;
        filters << QStringLiteral("*.cpp");
        QFileInfoList cppInfos = TempDir.entryInfoList(filters);
        emit SimRunning(QStringLiteral("sim_c++.exe is running. It might take a long time, espcially when the inputs are large in number."));
        for (QFileInfo fi : cppInfos)
        {
            cmd = program;
            for (QString s : arguments)
                cmd += QStringLiteral(" ") + s;
            cmd += QString(" \"%1\" /").arg(fi.absoluteFilePath());
            for (QFileInfo fifi : cppInfos)
            {
                if (fi == fifi)
                    continue;
                else
                {
                    cmd += QString(" \"%1\"").arg(fifi.absoluteFilePath());
                }
            }
            //qDebug() << cmd;
            process->execute(cmd);
            QFile rfile(QString("%1/cpp.txt").arg(TempDir.absolutePath()));
            if (rfile.open(QIODevice::ReadOnly))
            {
                QTextStream rstream(&rfile);
                rstream.readLine();
                rstream.readLine();
                wstream << rstream.readAll();
                rfile.close();
            }
        }
        cppfile.close();
    }

    if (javafile.open(QIODevice::WriteOnly))
    {
        QTextStream wstream(&javafile);
        QString program = QString("\"%1/sim_java.exe\"").arg(bin);
        QStringList arguments;
        arguments << sim_options << QString("-o \"%1/java.txt\"").arg(TempDir.absolutePath());
        QStringList filters;
        filters << QStringLiteral("*.java");
        QFileInfoList javaInfos = TempDir.entryInfoList(filters);
        emit SimRunning(QStringLiteral("sim_java.exe is running. It might take a long time, espcially when the inputs are large in number."));
        for (QFileInfo fi : javaInfos)
        {
            cmd = program;
            for (QString s : arguments)
                cmd += QStringLiteral(" ") + s;
            cmd += QString(" \"%1\" /").arg(fi.absoluteFilePath());
            for (QFileInfo fifi : javaInfos)
            {
                if (fi == fifi)
                    continue;
                else
                {
                    cmd += QString(" \"%1\"").arg(fifi.absoluteFilePath());
                }
            }
            //qDebug() << cmd;
            process->execute(cmd);
            QFile rfile(QString("%1/java.txt").arg(TempDir.absolutePath()));
            if (rfile.open(QIODevice::ReadOnly))
            {
                QTextStream rstream(&rfile);
                rstream.readLine();
                rstream.readLine();
                wstream << rstream.readAll();
                rfile.close();
            }
        }
        javafile.close();
    }

    if (cppfile.open(QIODevice::ReadOnly))
    {
        QTextStream rstream(&cppfile);
        QString line;
        while (!rstream.atEnd())
        {
            line = rstream.readLine();
            QStringList sl = line.split(QStringLiteral("consists for"), QString::KeepEmptyParts, Qt::CaseSensitive);
            if (sl.count() == 2)
            {
                QString file1 = sl.at(0);
                QStringList sl1 = file1.split(QStringLiteral("/"), QString::SkipEmptyParts, Qt::CaseSensitive);
                file1 = sl1.at(sl1.count()-1);
                int dot = file1.lastIndexOf(QStringLiteral("."));
                file1.remove(dot, file1.length()-dot);
                file1 = file1.trimmed();

                QString file2 = sl.at(1);
                QStringList sl2 = file2.split(QStringLiteral("/"), QString::SkipEmptyParts, Qt::CaseSensitive);
                QString tsim = sl2.at(0);
                int percent = tsim.indexOf(QStringLiteral("%"));
                tsim.remove(percent, tsim.length()-percent);
                tsim = tsim.trimmed();

                file2 = sl2.at(sl2.count()-1);
                dot = file2.lastIndexOf(QStringLiteral("."));
                file2.remove(dot, file2.length()-dot);
                file2 = file2.trimmed();

                float ftsim = tsim.toFloat();
                for (int i=0; i<input_list->size(); i++)
                {
                    if (QString::compare(file1, input_list->at(i)->getNodeData().fileName()) == 0)
                    {
                        tsim_list->replace(i, qMax(ftsim, tsim_list->at(i)));
                        if (tsim_list->at(i) == ftsim && ftsim != 0)
                        {
                            tsimf_list->replace(i, QFileInfo(QString("%1/%2").arg(input_directory).arg(file2)));
                        }
                    }
                }
            }
        }
        cppfile.close();
    }

    if (javafile.open(QIODevice::ReadOnly))
    {
        QTextStream rstream(&javafile);
        QString line;
        while (!rstream.atEnd())
        {
            line = rstream.readLine();
            QStringList sl = line.split(QStringLiteral("consists for"), QString::KeepEmptyParts, Qt::CaseSensitive);
            if (sl.count() == 2)
            {
                QString file1 = sl.at(0);
                QStringList sl1 = file1.split(QStringLiteral("/"), QString::SkipEmptyParts, Qt::CaseSensitive);
                file1 = sl1.at(sl1.count()-1);
                int dot = file1.lastIndexOf(QStringLiteral("."));
                file1.remove(dot, file1.length()-dot);
                file1 = file1.trimmed();

                QString file2 = sl.at(1);
                QStringList sl2 = file2.split(QStringLiteral("/"), QString::SkipEmptyParts, Qt::CaseSensitive);
                QString tsim = sl2.at(0);
                int percent = tsim.indexOf(QStringLiteral("%"));
                tsim.remove(percent, tsim.length()-percent);
                tsim = tsim.trimmed();

                file2 = sl2.at(sl2.count()-1);
                dot = file2.lastIndexOf(QStringLiteral("."));
                file2.remove(dot, file2.length()-dot);
                file2 = file2.trimmed();

                float ftsim = tsim.toFloat();
                for (int i=0; i<input_list->size(); i++)
                {
                    if (QString::compare(file1, input_list->at(i)->getNodeData().fileName()) == 0)
                    {
                        tsim_list->replace(i, qMax(ftsim, tsim_list->at(i)));
                        if (tsim_list->at(i) == ftsim && ftsim != 0)
                        {
                            tsimf_list->replace(i, QFileInfo(QString("%1/%2").arg(input_directory).arg(file2)));
                        }
                    }
                }
            }
        }
        javafile.close();
    }

}

float Sim::computeSSimSub1(Node* s, Node* d)
{
    int res = 0;
    res += computeSSimSub2(s, d);
    for (Node* schild : *(s->getChildren()))
    {
         res += computeSSimSub1(schild, d);
    }
    return res;
}

float Sim::computeSSimSub2(Node* s, Node* d)
{
    float res = 0.0;
    QFileInfo f1 = s->getNodeData();
    QFileInfo f2 = d->getNodeData();
    //if ( f1.isDir() && f2.isFile() )
    //    res = 0.0;
    //if ( f1.isFile() && f2.isDir() )
    //    res = 0.0;
    if ( f1.isDir() && f2.isDir() )
    {
        QString s1 = f1.fileName().simplified().trimmed();
        QString s2 = f2.fileName().simplified().trimmed();
        if ( QString::compare(s1, s2, Qt::CaseInsensitive) == 0 )
            res += same_dir_name;
    }
    if ( f1.isFile() && f2.isFile() )
    {
        QString s1 = f1.fileName().simplified().trimmed();
        QString s2 = f2.fileName().simplified().trimmed();
        if ( QString::compare(s1, s2, Qt::CaseInsensitive) == 0 )
            res += same_file_name;
        QDateTime t1 = f1.lastModified();
        QDateTime t2 = f2.lastModified();
        if ( qAbs(t1.daysTo(t2)) <= 1 )
            res += same_file_time;
        if (qMax(f1.size(),f2.size()) != 0 &&
                qMin(f1.size(),f2.size()) / qMax(f1.size(),f2.size()) > 0.95 )
            res += same_file_size;
    }
    for (Node* dchild : *(d->getChildren()))
    {
      res = qMax(computeSSimSub2(s, dchild), res);
      if (f1.isFile() && res==same_file_name+same_file_size+same_file_time)
          return res;
      if (f1.isDir() && res==same_dir_name)
          return res;
    }
    return res;
}

void Sim::doSSim()
{
    emit SimRunning(QStringLiteral("SSim is running. It might take a long time, espcially when the inputs are large in number."));
    computeSSim(project_list);
    //QtConcurrent::run(this, &Sim::computeSSim, project_list);

    emit SimRunning(QStringLiteral("SSim done."));
    emit SSimComplete(ssim_list, ssimf_list);
}

void Sim::doTSim()
{
    emit SimRunning(QStringLiteral("TSim is running. It might take a long time, espcially when the inputs are large in number."));
    computeTSim(project_list);
    //QtConcurrent::run(this, &Sim::computeTSim, project_list);

    emit SimRunning(QStringLiteral("TSim done."));
    emit TSimComplete(tsim_list, tsimf_list);
}

QFileInfoList Sim::toSrcList(Node* n)
{
    QFileInfoList res;
    if (n->getNodeData().isFile())
    {
        QString filesuffix = n->getNodeData().suffix();
        if (filesuffix == "cpp" || filesuffix == "hpp" || filesuffix == "c" || filesuffix == "h" || filesuffix == "java")
            res.append(n->getNodeData());
    }

    for(Node* child : *(n->getChildren()))
        res.append(toSrcList(child));

    return res;
}

void Sim::clean()
{
    emit SimRunning(QStringLiteral("cleaning."));
    QDir dir(temp_directory);
    if (dir.exists())
    {
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        QFileInfoList fileList = dir.entryInfoList();
        for (QFileInfo fi : fileList)
        {
            if (fi.isFile() || fi.isSymLink())
                fi.dir().remove(fi.fileName());
            else
                deleFolder(fi.absoluteFilePath());
        }
    }

    dir.cd(output_directory);
    if (dir.exists())
    {
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        QFileInfoList fileList = dir.entryInfoList();
        for (QFileInfo fi : fileList)
        {
            if (fi.isFile() || fi.isSymLink())
                fi.dir().remove(fi.fileName());
            else
                deleFolder(fi.absoluteFilePath());
        }
    }

    emit SimRunning(QStringLiteral("clean done."));
}

void Sim::doTSimDetail(const QString& project_name)
{
    // it looks like project_list->indexOf()
    for (int i=0; i<project_list->size(); i++)
    {
        if (QString::compare(project_name, project_list->at(i)->getNodeData().fileName())==0)
        {
            //QString s1 = project_list->at(i)->getNodeData().absoluteFilePath();
            QString s2 = tsimf_list->at(i).absoluteFilePath();
            Node* n1 = project_list->at(i);
            Node* n2 = nullptr;
            if (s2.isEmpty())
            {
                emit TSimDetailComplete("");
                break;
            }
            // Although I am sure that n2 is in project list, I am still worry about the safety here
            for (int j=0; j<project_list->size(); j++)
            {
                if (QString::compare(tsimf_list->at(i).fileName(), project_list->at(j)->getNodeData().fileName())==0)
                {
                    n2 = project_list->at(j);
                    break;
                }
            }
            /*if (n2 == nullptr)
            {
                emit TSimDetailComplete("");
                break;
            }*/
            QFileInfoList fil1 = toSrcList(n1);
            QFileInfoList fil2 = toSrcList(n2);
            QString datetimestr = date_time.toString(QStringLiteral("yyyyMMddHHmmsszzz"));
            QDir OutputDir(QString("%1/%2").arg(output_directory).arg(datetimestr));

            QString cppfilename = QString("%1/%2_detail_cpp.txt").arg(OutputDir.absolutePath()).arg(project_list->at(i)->getNodeData().fileName());
            QString cmd;
            QString program = QString("\"%1/sim_c++.exe\"").arg(bin);
            QStringList arguments;
            // -dS is important!!! Maybe there gonna be a interface in later version.
            arguments << QStringLiteral("-dS") << QString("-o \"%1\"").arg(cppfilename);
            emit SimRunning(QStringLiteral("sim_c++.exe is running. It might take a long time, espcially when the inputs are large in number."));
            cmd = program;
            for (QString s : arguments)
                cmd += QStringLiteral(" ") + s;
            QString str1;
            for (QFileInfo fi : fil1)
            {
                QString suf = fi.suffix();
                if (suf == QStringLiteral("c") || suf == QStringLiteral("cpp")
                 || suf == QStringLiteral("h") || suf == QStringLiteral("hpp"))
                    str1 += QString(" \"%1\"").arg(fi.absoluteFilePath());
            }
            QString str2;
            for (QFileInfo fi : fil2)
            {
                QString suf = fi.suffix();
                if (suf == QStringLiteral("c") || suf == QStringLiteral("cpp")
                 || suf == QStringLiteral("h") || suf == QStringLiteral("hpp"))
                    str2 += QString(" \"%1\"").arg(fi.absoluteFilePath());
            }
            if (!str1.isEmpty() && !str2.isEmpty())
            {
                cmd += str1 + QStringLiteral(" /") + str2;
                //qDebug() << cmd;
                process->execute(cmd);
                QFile rfile(cppfilename);
                if (rfile.open(QIODevice::ReadOnly))
                {
                    QTextStream rstream(&rfile);
                    emit TSimDetailComplete(rstream.readAll());
                }
            }

            QString javafilename = QString("%1/%2_detail_java.txt").arg(OutputDir.absolutePath()).arg(project_list->at(i)->getNodeData().fileName());
            program = QString("\"%1/sim_java.exe\"").arg(bin);
            arguments.clear();
            // -dS is important!!! Maybe there gonna be a interface in later version.
            arguments << QStringLiteral("-dS") << QString("-o \"%1\"").arg(javafilename);
            emit SimRunning(QStringLiteral("sim_java.exe is running. It might take a long time, espcially when the inputs are large in number."));
            cmd = program;
            for (QString s : arguments)
                cmd += QStringLiteral(" ") + s;
            str1.clear();
            for (QFileInfo fi : fil1)
            {
                QString suf = fi.suffix();
                if (suf == QStringLiteral("java"))
                    str1 += QString(" \"%1\"").arg(fi.absoluteFilePath());
            }
            str2.clear();
            for (QFileInfo fi : fil2)
            {
                QString suf = fi.suffix();
                if (suf == QStringLiteral("java"))
                    str2 += QString(" \"%1\"").arg(fi.absoluteFilePath());
            }
            if (!str1.isEmpty() && !str2.isEmpty())
            {
                cmd += str1 + QStringLiteral(" /") + str2;
                //qDebug() << cmd;
                process->execute(cmd);
                QFile rfile(javafilename);
                if (rfile.open(QIODevice::ReadOnly))
                {
                    QTextStream rstream(&rfile);
                    emit TSimDetailComplete(rstream.readAll());
                }
            }

            break;
        }
    }
    emit SimRunning(QStringLiteral("doTSimDetail done."));
}

void Sim::extract(const QString& option, const QString& input, const QString& output)
{
    QDir indir(input);
    if (!indir.exists(input))
    {
        emit SimFail(QStringLiteral("Extracting failed: invalid input directory."));
        return;
    }
    QDir outdir(output);
    if (!outdir.exists(output))
    {
        emit SimFail(QStringLiteral("Extracting failed: invalid output directory."));
        return;
    }
    emit SimRunning(QStringLiteral("Extracting."));
    QFileInfoList fileList = indir.entryInfoList(QStringList()<<"*.zip", QDir::Files);
    QString outname;
    for (QFileInfo fi : fileList)
    {
        if (option == "-aoa" || option == "-aos")
        {
            // whatever it is false or not.
            outdir.mkdir(fi.baseName());
            outname = QString("%1/%2").arg(output).arg(fi.baseName());
        }
        else if (option == "-aou")
        {
            if (outdir.cd(fi.baseName()))
            {
                outdir.cdUp();
                int i = 1;
                while (outdir.cd(QString("%1_%2").arg(fi.baseName()).arg(i)))
                {
                    outdir.cdUp();
                    i++;
                }
                outdir.mkdir(QString("%1_%2").arg(fi.baseName()).arg(i));
                outname = QString("%1/%2_%3").arg(output).arg(fi.baseName()).arg(i);
            }
            else
            {
                outdir.mkdir(fi.baseName());
                outname = QString("%1/%2").arg(output).arg(fi.baseName());
            }
        }
        else if (option == "-aot")
        {
            if (outdir.cd(fi.baseName()))
            {
                outdir.cdUp();
                int i = 1;
                while (outdir.cd(QString("%1_%2").arg(fi.baseName()).arg(i)))
                {
                    outdir.cdUp();
                    i++;
                }
                outdir.rename(fi.baseName(), QString("%1_%2").arg(fi.baseName()).arg(i));
            }
            else
                outdir.mkdir(fi.baseName());
            outname = QString("%1/%2").arg(output).arg(fi.baseName());
        }
        else
            emit SimFail(QStringLiteral("Extracting failed: invalid option."));
        QString cmd = QString("\"%1/7za.exe\" x -y %2 \"%3\" \"-o%4\"").arg(bin).arg(option).arg(fi.absoluteFilePath()).arg(outname);
        //qDebug() << cmd;
        process->execute(cmd);
    }
    emit SimRunning(QStringLiteral("Extract done."));
}

void Sim::deleFolder(QString path)
{
    QDir dir(path);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    for (QFileInfo fi : fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            deleFolder(fi.absoluteFilePath());
    }
    dir.rmdir(dir.absolutePath());
}

Sim::~Sim()
{
    if (project_list != nullptr)
    {
        for (Node* p : *project_list)
        {
            Node::deleAll(p);
            p = nullptr;
        }
        delete project_list;
        project_list = nullptr;
    }
    if (ssim_list != nullptr)
    {
        delete ssim_list;
        ssim_list = nullptr;
    }
    if (tsim_list != nullptr)
    {
        delete tsim_list;
        tsim_list = nullptr;
    }
    delete process;
    process = nullptr;
}
