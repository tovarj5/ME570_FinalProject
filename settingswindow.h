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

    explicit settingswindow( QWidget *parent = 0);

    ~settingswindow();
    void print(QString outputMessage);
    void clear_window();
    double getMazeSize();
    double getCellSize();
    //  std::vector<std::string> getMazeAbilities();
    bool applySettings();
    void setSettings(std::vector<double> values);
    std::vector<double> getSettings();



private slots:
    void on_pushButton_3_clicked();

    void on_ApplyPushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_horizontalSlider_actionTriggered(int action);

private:
    Ui::settingswindow *ui;
    std::vector<double> mMazeSettings;
    double mmazeSize{0}, mdifficulty{1};
    double mNumcells{0};
    double mwallLength{0};
//    double wallWidth{0};
    double mrestitution{0};
    //std::vector<std::string> mazeAbilities{nullptr};
    bool applied{false};
};

#endif // SETTINGSWINDOW_H
