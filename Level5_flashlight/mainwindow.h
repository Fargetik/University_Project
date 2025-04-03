#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:

    const double angle = 60;
    bool Flag_to_paint = false;
    QLine line;
    QLine lineleft;
    QLine lineright;

    const QList<QColor> colors = {
        QColor(Qt::gray),
        QColor(0, 128, 1), // Светло-зелёный
        QColor(Qt::green),
        QColor(Qt::blue),
        QColor(Qt::yellow)
    };

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
