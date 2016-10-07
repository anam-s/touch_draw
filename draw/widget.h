#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class PaintBrush {
public:
    PaintBrush() : lastPosition(), index(0), down(false) {};

    QPoint	lastPosition;
    int		index;
    bool	down;
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QList<QColor>			mouseColors;
    QList<QColor>			touchColors;
    QImage					image;
    PaintBrush				mouseBrush;

    QMap<int, PaintBrush>	touchBrushes;
    QString					touchLabel;


protected:
    void paintEvent(QPaintEvent *event);
    bool event(QEvent *event);
    void drawText(QPainter &painter, const QString &text, int x, int y);
    void drawBrushLabel(QPainter &painter, const PaintBrush &brush, const QString &label);
    void paintLine(QPoint startPos, QPoint endPos, int radius, QColor color);

    // Renders a brush's label at its current position.
    void QPaintWidget::drawBrushLabel(QPainter &painter, const PaintBrush &brush, const QString &label)
    {
        QString text(label), indexString;
        indexString.setNum(brush.index+1);
        text.append(' ');
        text.append(indexString);

        drawText(painter, text, brush.lastPosition.x() + 8, brush.lastPosition.y() - 8);
    }


};

#endif // WIDGET_H
