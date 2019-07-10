#include "newdialog.h"
#include "ui_newdialog.h"

NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    ui->setupUi(this);
    setWindowTitle("New");
}

void NewDialog::setEnvironment(QString inpute_directory, QString output_directory, QString temp_directory,
                               QString sim_options, QString bin, QString workspace)
{
    ui->inputLineEdit->setText(inpute_directory);
    ui->outputLineEdit->setText(output_directory);
    ui->tempLineEdit->setText(temp_directory);
    ui->simOptionLineEdit->setText(sim_options);
    ui->binLineEdit->setText(bin);
    ui->workspaceLineEdit->setText(workspace);
}

void NewDialog::setSim(int dir_weight, int file_weight, int same_dir_name,
                 int same_file_name, int same_file_size, int same_file_time)
{
    ui->dirWeightSpinBox->setValue(dir_weight);
    ui->fileWeightSpinBox->setValue(file_weight);
    ui->dirNameSpinBox->setValue(same_dir_name);
    ui->fileNmaeSpinBox->setValue(same_file_name);
    ui->fileSizeSpinBox->setValue(same_file_size);
    ui->fileTimeSpinBox->setValue(same_file_time);
}


NewDialog::~NewDialog()
{
    delete ui;
}

void NewDialog::on_inputToolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("input directory"),
                                                     ui->inputLineEdit->text(), QFileDialog::DontUseNativeDialog);
    if (!path.isEmpty())
        ui->inputLineEdit->setText(path);
}

void NewDialog::on_outputToolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("output directory"),
                                                     ui->outputLineEdit->text(), QFileDialog::DontUseNativeDialog);
    if (!path.isEmpty())
        ui->outputLineEdit->setText(path);
}

void NewDialog::on_tempToolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("temp directory"),
                                                     ui->tempLineEdit->text(), QFileDialog::DontUseNativeDialog);
    if (!path.isEmpty())
        ui->tempLineEdit->setText(path);
}

void NewDialog::on_workspaceToolButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("workspace directory"),
                                                     ui->workspaceLineEdit->text(), QFileDialog::DontUseNativeDialog);
    if (!path.isEmpty())
        ui->workspaceLineEdit->setText(path);
}

void NewDialog::on_NewDialog_accepted()
{
    emit giveEnvironment(ui->inputLineEdit->text(), ui->outputLineEdit->text(), ui->tempLineEdit->text(),
                         ui->simOptionLineEdit->text(), ui->binLineEdit->text(), ui->workspaceLineEdit->text());
    emit giveSim(ui->dirWeightSpinBox->value(), ui->fileWeightSpinBox->value(), ui->dirNameSpinBox->value(),
                 ui->fileNmaeSpinBox->value(), ui->fileSizeSpinBox->value(), ui->fileTimeSpinBox->value());
}

