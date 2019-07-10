#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDialog(QWidget *parent = 0);
    ~NewDialog();

signals:
    void giveEnvironment(QString, QString, QString, QString, QString, QString);
    void giveSim(int, int, int, int, int, int);

public slots:
    void setEnvironment(QString inpute_directory, QString output_directory, QString temp_directory,
                        QString sim_options, QString bin, QString workspace);

    void setSim(int dir_weight, int file_weight, int same_dir_name,
                int same_file_name, int same_file_size, int same_file_time);

private slots:
    void on_inputToolButton_clicked();

    void on_outputToolButton_clicked();

    void on_tempToolButton_clicked();

    void on_workspaceToolButton_clicked();

    void on_NewDialog_accepted();

private:
    Ui::NewDialog *ui;
};

#endif // NEWDIALOG_H




