#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>

namespace Ui {
class settingswindow;
}

class settingswindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit settingswindow(QWidget *parent = 0);
    ~settingswindow();
    void print(QString outputMessage);
    void clear_window();

    struct settingswindow
    {
        double mazeSize{0};
        double cellSize{0};
        double wallHeight{0};
        double wallWidth{0};
    };

private:
    Ui::settingswindow *ui;
};

#endif // SETTINGSWINDOW_H
