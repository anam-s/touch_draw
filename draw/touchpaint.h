#ifndef TOUCHPAINT_H
#define TOUCHPAINT_H
#include <QWidget>

namespace Ui {
    class touchPaint;
}

class touchPaint : public QWidget
{
    Q_OBJECT

public:
    explicit touchPaint(QWidget *parent = 0);
    ~touchPaint();

private:
    Ui::touchPaint *ui;
};

#endif // TOUCHPAINT_H
