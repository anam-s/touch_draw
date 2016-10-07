#include "widget.h"
#include "ui_widget.h"
#include <QCoreApplication>
#include <QEvent>
#include <QPainter>
#include <QColor>
#include <QList>
#include "widget.h"
#include "utilities.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_AcceptTouchEvents);
    touchColors << QColor(255, 0, 0) << QColor(0, 0, 255) << QColor(0, 255, 0) << QColor(255, 255, 0) << QColor(255, 0, 255) << QColor(0, 255, 255);

    // Default touch label:
    touchLabel = "Touch";



    void QPaintWidget::startBrush(PaintBrush &brush, QPoint position, int index, const QList<QColor> &colors)
    {
        brush.lastPosition = position;
        brush.index = index;
        brush.down = true;
        paintLine(position, position, 4, retrieveColor(colors, brush.index));
    }

    void QPaintWidget::moveBrush(PaintBrush &brush, QPoint position, const QList<QColor> &colors)
    {
        paintLine(brush.lastPosition, position, 4, retrieveColor(colors, brush.index));
        brush.lastPosition = position;
    }

    void QPaintWidget::removeBrush(PaintBrush &brush, QPoint finalPosition, const QList<QColor> &colors)
    {
        paintLine(mouseBrush.lastPosition, finalPosition, 4, retrieveColor(colors, mouseBrush.index));
        brush.down = false;
    }

    // Paints a line from "startPos" to "endPos" with thickness "radius" and color "color"
    void QPaintWidget::paintLine(QPoint startPos, QPoint endPos, int radius, QColor color)
    {
        QRect boundingBox;
        QPainter painter(&image);
        QPen pen(color);
        pen.setWidth(radius);
        painter.setPen(pen);
        painter.drawLine(startPos, endPos);
        painter.end();

        boundingBox.setLeft(min(startPos.x(), endPos.x()) - radius);
        boundingBox.setTop(min(startPos.y(), endPos.y()) - radius);
        boundingBox.setRight(max(startPos.x(), endPos.x()) + radius);
        boundingBox.setBottom(max(startPos.y(), endPos.y()) + radius);
        update(boundingBox);
    }


    bool QPaintWidget::event(QEvent *event)
    {
        QEvent::Type type = event->type();
        // Handle Qt Touch events:
        if (type == QEvent::TouchBegin || type == QEvent::TouchEnd || type == QEvent::TouchUpdate) {
            QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
            QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

            foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
                QPoint touchPos;
                  #if QT_VERSION >= 0x050000
                if (touchEvent->device()->type() == QTouchDevice::TouchPad) {
    #else
                if (touchEvent->deviceType() == QTouchEvent::TouchPad) {
    #endif
                    touchPos.setX(touchPoint.normalizedPos().x() * this->width());
                    touchPos.setY(touchPoint.normalizedPos().y() * this->height());
                } else {
                    touchPos = QPoint(touchPoint.pos().x(), touchPoint.pos().y());

                    if (touchPoint.id() == 0) {
                        if (touchPoint.state() == Qt::TouchPointPressed) {
                            mouseTouchInProgress = true;
                        } else if (touchPoint.state() == Qt::TouchPointReleased) {
                            mouseTouchInProgress = false;
                        }
                    }
                }

                switch (touchPoint.state()) {
                    case Qt::TouchPointPressed:
                        startBrush(touchBrushes[touchPoint.id()], touchPos, touchPoint.id(), touchColors);
                        break;
                    case Qt::TouchPointMoved:
                        moveBrush(touchBrushes[touchPoint.id()], touchPos, touchColors);
                        break;
                    case Qt::TouchPointReleased:
                        touchBrushes.remove(touchPoint.id());
                        if (touchBrushes.count() == 0) {
                            allTouchesReleased();
                        }
                        break;
                    default:
                        break;
                }
            }
            return true;
        }

        return QWidget::event(event);
    }

    void QPaintWidget::setTouchLabel(const QString &newLabel)
    {
        touchLabel = newLabel;
    }


}

Widget::~Widget()
{
    delete ui;
}
