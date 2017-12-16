#include "instructionsdialog.h"
#include "ui_instructionsdialog.h"

instructionsdialog::instructionsdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instructionsdialog)
{
    ui->setupUi(this);
}

instructionsdialog::~instructionsdialog()
{
    delete ui;
}

void instructionsdialog::print(QString outputMessage)
{

}

void instructionsdialog::clear_window()
{

}


void instructionsdialog::setSettings(std::vector<double> values)
{

}

std::vector<double> instructionsdialog::getSettings()
{

}


void instructionsdialog::on_pushButton_clicked()
{
    close();
}
