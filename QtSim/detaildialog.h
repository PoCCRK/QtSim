#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>

namespace Ui {
class DetailDialog;
}

class DetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetailDialog(QWidget *parent = 0);
    ~DetailDialog();

public slots:
    void appendText(const QString& text);

private slots:
    void on_DetailDialog_finished(int result);

private:
    Ui::DetailDialog *ui;
};

#endif // DETAILDIALOG_H
