#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRect>
#include "flashlight.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPoint rotatePoint(const QPoint point, const QPoint pivot, double angle) {
    double rad = qDegreesToRadians(angle); // угол в радианах

    double x = point.x() - pivot.x();
    double y = point.y() - pivot.y();

    double xNew = x * cos(rad) - y * sin(rad);
    double yNew = x * sin(rad) + y * cos(rad);

    return QPoint(xNew + pivot.x(), yNew + pivot.y());
}

int classify(QLine line, QPoint pixel, QLine lineleft, QLine lineright)
{
    enum Position {
        BEHIND,
        LEFT,
        RIGHT,
        BEYOND,
        LIGHT,
    };

    QPoint p1 = line.p1();
    QPoint p2 = line.p2();
    QPoint a = p2 - p1;
    QPoint b = pixel - p1;
    QPoint bb = pixel - p2;
    if ((a.x() * b.x() + a.y() * b.y()) < 0) return BEHIND;
    if ((-a.x() * bb.x() + -a.y() * bb.y()) < 0) {
        QPoint pl1 = lineleft.p1();
        QPoint pl2 = lineleft.p2();
        QPoint pr1 = lineright.p1();
        QPoint pr2 = lineright.p2();

        QPoint al = pl1 - pl2;
        QPoint bl = pixel - pl1;

        QPoint ar = pr1 - pr2;
        QPoint br = pixel - pr1;

        if (((al.x() * bl.y() - bl.x() * al.y() >> 31) & 1) != ((ar.x() * br.y() - br.x() * ar.y() >> 31) & 1)) return LIGHT;
        return BEYOND;
    }
    if (a.x() * b.y() > b.x() * a.y()) return LEFT;
    else return RIGHT;
    return 0; // точки на линии закрасяться потом отрисовкой линией
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (Flag_to_paint) {
        QRect rect = contentsRect();
        for (int i = 0; i < rect.width(); i++) {
            for (int j = 0; j < rect.height(); j++) {
                QPoint pixel{i,j};
                painter.setPen(QPen(QBrush(colors[classify(line, pixel, lineleft, lineright)]), 1));
                painter.drawPoint(pixel);
            }
        }
        Flag_to_paint = false;
    }
    painter.setPen(QPen(QBrush(QColor(0,0,0,255)), 5,  Qt::SolidLine));
    painter.drawLine(line);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    line = QLine(event->pos(),event->pos());
    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    line = QLine(line.p1(), event->pos());
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Flag_to_paint = true;
    QPoint p1 = line.p1();
    QPoint p2 = line.p2();
    QPoint p3 = p2 + QPoint(p2.x()-p1.x(),p2.y()-p1.y());

    lineleft = QLine(p2, rotatePoint(p3, p2, -angle/2));
    lineright = QLine(p2, rotatePoint(p3, p2, angle/2));
    repaint();
}

