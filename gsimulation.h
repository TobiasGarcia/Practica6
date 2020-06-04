#ifndef GSIMULATION_H
#define GSIMULATION_H

#include <QGraphicsView>
#include <QTableWidget>
#include <QTimer>
#include <math.h>
#include "astro.h"

//Floats para utilizar notación científica

//No utilizamos .toDouble porque necesitamos la potencia
void str2double(QString str, double &dec, short &ten_pow);

class GSimulation: public QGraphicsView {

    Q_OBJECT

private:
    QBrush *brush;
    float dt = 12;
    double G = 1, a_aux, cube_dist;
    QList<Astro*> astros;
    QGraphicsScene *scene;
    std::vector<std::array<double, 7>> data; //ax, ay, vx, vy, x, y, m

public:
    bool started;
    QTimer *update_timer;

    GSimulation(short x, short y, QWidget *parent);
    ~GSimulation();
    void add_astro(double x0, double y0, short radio);
    void delete_astro(short index);
    void update_astro(short index, double x0, double y0, short radio);
    void start_simulation(QTableWidget *table);
    void stop_simulation(QTableWidget *table);

public slots:
    void move();

};

#endif // GSIMULATION_H
