#include "extractdialog.h"
#include "ui_extractdialog.h"

ExtractDialog::ExtractDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExtractDialog)
{
    ui->setupUi(this);
    ui->renameNRadioButton->click();
    setWindowTitle("Extract");
}

ExtractDialog::~ExtractDialog()
{
    delete ui;
}

void ExtractDialog::on_inputToolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("input directory"),
                   ui->inputLineEdit->text(), QFileDialog::DontUseNativeDialog);
    if (!path.isEmpty())
    {
        ui->inputLineEdit->setText(path);
        ui->outputLineEdit->setText(path);
    }
}

void ExtractDialog::on_outputToolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("output directory"),
                                                     ui->outputLineEdit->text(), QFileDialog::DontUseNativeDialog);
    if (!path.isEmpty())
        ui->outputLineEdit->setText(path);
}

void ExtractDialog::on_ExtractDialog_accepted()
{
    if (ui->inputLineEdit->text().isEmpty() || ui->outputLineEdit->text().isEmpty())
    {
        return;
    }
    QString str;
    if (ui->renameNRadioButton->isChecked())
        str = "-aou";
    else if (ui->renameERadioButton->isChecked())
        str = "-aot";
    else if (ui->skipRadioButton->isChecked())
        str = "-aos";
    else if (ui->overlayRadioButton->isChecked())
        str = "-aoa";
    emit doExtract(str, ui->inputLineEdit->text(), ui->outputLineEdit->text());
}
