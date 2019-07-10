#ifndef EXTRACTDIALOG_H
#define EXTRACTDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class ExtractDialog;
}

class ExtractDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExtractDialog(QWidget *parent = 0);
    ~ExtractDialog();

signals:
    void doExtract(const QString&, const QString&, const QString&);

private slots:
    void on_inputToolButton_clicked();

    void on_outputToolButton_clicked();

    void on_ExtractDialog_accepted();

private:
    Ui::ExtractDialog *ui;
};

#endif // EXTRACTDIALOG_H
