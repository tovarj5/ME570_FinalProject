#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <QtGui>
#include <QDialog>

namespace Ui {
class settingswindow;
}

class settingswindow : public QDialog
{
    Q_OBJECT

public:

    explicit settingswindow(QWidget *parent = 0);
    ~settingswindow();
    void print(QString outputMessage);
    void clear_window();
    double getMazeSize();
    double getCellSize();
    //  std::vector<std::string> getMazeAbilities();
    bool applySettings();




private slots:
    void on_pushButton_3_clicked();

    void on_ApplyPushButton_clicked();

private:
    Ui::settingswindow *ui;
    double mazeSize{0};
    double cellSize{0};
    double wallHeight{0};
    double wallWidth{0};
    //std::vector<std::string> mazeAbilities{nullptr};
    bool applied{false};
};

#endif // SETTINGSWINDOW_H
