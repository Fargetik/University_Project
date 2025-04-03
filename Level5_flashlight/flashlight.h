#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H
#include <QLine>
#include <QPainter>

class Flashlight
{
public:
    Flashlight();

    Flashlight(QLine line);

    void draw(QPainter *painter);

    int classify(QPoint pixel, QLine lineleft, QLine lineright);

    QLine getLine() const;

protected:

    QLine line;
    const double angle = 60;

};

#endif // FLASHLIGHT_H
