#include "utilities.h"

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}


QColor retrieveColor(const QList<QColor> &colorList, int index)
{
    return colorList[index % colorList.count()];
}
