#ifndef UTILITIES_H
#define UTILITIES_H

#include <QList>
#include <QColor>

int min(int a, int b);
int max(int a, int b);
QColor retrieveColor(const QList<QColor> &colorList, int index);

#endif // UTILITIES_H
