#include "flashlight.h"
#include <bitset>


Flashlight::Flashlight(QLine line)
    :line(line)
{

}

void Flashlight::draw(QPainter *painter)
{
    painter->setPen(QPen(QBrush(QColor(0,0,0,255)), 5,  Qt::SolidLine));
    painter->drawLine(line);
}


// QPoint rotatePoint(const QPoint point, const QPoint pivot, double angle) {
//     double rad = qDegreesToRadians(angle); // угол в радианах

//     double x = point.x() - pivot.x();
//     double y = point.y() - pivot.y();

//     double xNew = x * cos(rad) - y * sin(rad);
//     double yNew = x * sin(rad) + y * cos(rad);

//     return QPoint(xNew + pivot.x(), yNew + pivot.y());
// }





QLine Flashlight::getLine() const
{
    return line;
}
