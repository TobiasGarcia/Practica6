#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsScene>
#include <QWidget>
#include "astro.h"
#include "gsimulation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {

    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    GSimulation *gsimulation;
};
#endif // WIDGET_H
