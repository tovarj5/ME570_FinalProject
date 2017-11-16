//From http://www.qtforum.org/article/28240/how-to-get-arrow-keys.html
#ifndef GETKEYCODE_H
#define GETKEYCODE_H

#include <QWidget>
#include <QLabel>
#include <QtGui/QKeyEvent>

class getKeyCode : public QWidget
{
    Q_OBJECT

    public:
        getKeyCode(QWidget *parent = 0);
        ~getKeyCode();
        void setupUi();

    protected:
        void keyPressEvent(QKeyEvent *event);

    private:
        QLabel *centerLabel;
};

#endif // GETKEYCODE_H
