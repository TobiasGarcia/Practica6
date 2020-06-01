#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(1000, 702);
    ui->graphicsView->setGeometry(0, 0, 702, 702);

    scene = new QGraphicsScene;
    scene->setSceneRect(-350, -350, (ui->graphicsView->width() - 2), (ui->graphicsView->height() - 2));

    astro = new Astro(5000, 5000, 0, 0, 2, 3);
    scene->addItem(astro);

    ui->graphicsView->setScene(scene);
}

Widget::~Widget() {
    delete scene;
    delete ui;
}

