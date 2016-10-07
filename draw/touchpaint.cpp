#include <QDebug>
#include <QMainWindow>
#include "touchpaint.h"

touchPaint::touchPaint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::touchPaint)
{
    ui->setupUi(this);
    QString windowTitle = QString("Touch Paint(") + QString(169) + QString(" touch");
    this->setWindowTitle(windowTitle);
    ui->paintWidget->setTouchLabel("Qt Touch");
}

touchPaint::~touchPaint()
{
    delete ui;
}
