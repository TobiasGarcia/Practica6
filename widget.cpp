#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {

    ui->setupUi(this);
    setFixedSize(1000, 702);

    gsimulation = new GSimulation(0, 0, this);
}

Widget::~Widget() {
    delete gsimulation;
    delete ui;
}

