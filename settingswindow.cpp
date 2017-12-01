#include "settingswindow.h"
#include "ui_settingswindow.h"

settingswindow::settingswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingswindow)
{
    ui->setupUi(this);
}

settingswindow::~settingswindow()
{
    delete ui;
}

void settingswindow::print(QString outputMessage)
{
    ui->outputPlainText->setPlainText(outputMessage);
}

void settingswindow::clear_window()
{
    ui->outputPlainText->clear();
}

double settingswindow::getMazeSize()
{
    return mmazeSize;
}

double settingswindow::getCellSize()
{
    return mNumcells;
}

//std::vector<std::string> settingswindow::getMazeAbilities()
//{
//    return mazeAbilities;
//}

bool settingswindow::applySettings()
{
    return applied;
}

void settingswindow::setSettings(std::vector<double> values)
{

}

std::vector<double> settingswindow::getSettings()
{
    mMazeSettings.push_back(mmazeSize);
    mMazeSettings.push_back(mNumcells);
    return mMazeSettings;
}

void settingswindow::on_pushButton_3_clicked()
{
    applied = false;
    //settingswindow.close();
}

void settingswindow::on_ApplyPushButton_clicked()
{
    close();
}

void settingswindow::on_horizontalSlider_valueChanged(int value)
{
    switch (value) {
    case 0:
        mNumcells = 10;
        break;
    case 1:
        mNumcells = 20;
        break;
    case 2:
        mNumcells = 30;
        break;
    case 3:
        mNumcells = 40;
        break;
    case 4:
        mNumcells = 50;
        break;
    case 5:
        mNumcells = 60;
        break;
    case 6:
        mNumcells = 70;
        break;
    case 7:
        mNumcells = 80;
        break;
    case 8:
        mNumcells = 90;
        break;
    case 9:
        mNumcells = 100;
    default:
        //mNumcells = 60;
        break;
    }
    ui->lineEdit_2->setText(QString::number(mNumcells));
}

void settingswindow::on_lineEdit_textEdited(const QString &arg1)
{
    mmazeSize =  arg1.toDouble();

}

void settingswindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    mNumcells = arg1.toDouble();
}

void settingswindow::on_horizontalSlider_actionTriggered(int action)
{
//    switch (action) {
//    case 0:
//        mNumcells = 10;
//        break;
//    case 1:
//        mNumcells = 20;
//        break;
//    case 5:
//        mNumcells = 60;
//        break;
//    case 10:
//        mNumcells = 100;
//    default:
//        mNumcells = 60;
//        break;
//    }
//    ui->lineEdit_2->setText(QString::number(mNumcells));
}
