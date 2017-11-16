#include "settingswindow.h"
#include "ui_settingswindow.h"

settingswindow::settingswindow(QWidget *parent) :
    QMainWindow(parent),
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
    return mazeSize;
}

double settingswindow::getCellSize()
{
    return cellSize;
}

//std::vector<std::string> settingswindow::getMazeAbilities()
//{
//    return mazeAbilities;
//}

bool settingswindow::applySettings()
{
    return applied;
}

void settingswindow::on_pushButton_3_clicked()
{
    applied = false;
    //settingswindow.close();
}
