#include "detaildialog.h"
#include "ui_detaildialog.h"

DetailDialog::DetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog)
{
    ui->setupUi(this);
    setWindowTitle("Detail");
}

DetailDialog::~DetailDialog()
{
    delete ui;
}

void DetailDialog::appendText(const QString& text)
{
    ui->textBrowser->append(text);
    ui->textBrowser->moveCursor(QTextCursor::Start);
}

void DetailDialog::on_DetailDialog_finished(int result)
{
    ui->textBrowser->clear();
}
