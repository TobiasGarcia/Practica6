#ifndef GSIMULATION_H
#define GSIMULATION_H

#include <QGraphicsView>
#include <QTimer>
#include <math.h>
#include "astro.h"

//Floats para utilizar notación científica

class GSimulation: public QGraphicsView {

    Q_OBJECT

private:
    float dt = 12;
    double G = 1, a_aux, cube_dist;
    QTimer *update_timer;
    QList<Astro*> astros;
    QGraphicsScene *scene;

public:
    std::vector<std::array<double, 7>> data; //ax, ay, vx, vy, x, y, m
    GSimulation(short x, short y, QWidget *parent);
    ~GSimulation();

    //SIMULATION BEGIN O COSAS POR EL ESTILO PARA CONECTAR CON CUALQUIER SEÑAL
public slots:
    void move();

};

#endif // GSIMULATION_H
