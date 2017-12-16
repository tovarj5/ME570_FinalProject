#ifndef INSTRUCTIONSDIALOG_H
#define INSTRUCTIONSDIALOG_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <QtGui>
#include <QDialog>

namespace Ui {
class instructionsdialog;
}

class instructionsdialog : public QDialog
{
    Q_OBJECT

public:

    explicit instructionsdialog( QWidget *parent = 0);

    ~instructionsdialog();
    void print(QString outputMessage);
    void clear_window();
    void setSettings(std::vector<double> values);
    std::vector<double> getSettings();



private slots:


    void on_pushButton_clicked();

private:
    Ui::instructionsdialog *ui;
    std::vector<double> mMazeSettings;
    double mmazeSize{0}, mdifficulty{1};
    double mNumcells{0};
    double mwallLength{0};
    double mrestitution{0};
    bool applied{false};
};

#endif // instructionsdialog_H
