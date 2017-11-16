#include <QPushButton>
#include <QVBoxLayout>
#include "getkeycode.h"

getKeyCode::getKeyCode(QWidget *parent)
: QWidget(parent)
{
    setupUi();
}

getKeyCode::~getKeyCode()
{
}

void getKeyCode::setupUi()
{
    setWindowTitle(tr("Get Key Codes"));

    centerLabel = new QLabel(tr("Please Press Key"));
    QPushButton *okButton = new QPushButton(tr(" OK "));
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *mLay = new QVBoxLayout;
    mLay->addWidget(centerLabel);
    mLay->addWidget(okButton);

    setLayout(mLay);
    resize(200,120);
    this->setFocus();
}


void getKeyCode::keyPressEvent(QKeyEvent *event)
{

    switch(event->key()){
        case Qt::Key_Up:
            centerLabel->setText(tr("Press ?"));
            break;
        case Qt::Key_Left:
            centerLabel->setText(tr("Press ?"));
            break;
        case Qt::Key_Right:
            centerLabel->setText(tr("Press ?"));
            break;
        case Qt::Key_Down:
            centerLabel->setText(tr("Press ?"));
            break;
        case Qt::Key_0:
            centerLabel->setText(tr("Press 0"));
            break;
    }
    QString str;
    str.setNum(event->key());
//    centerLabel->setText(str);
}
