#include "gsimulation.h"

GSimulation::GSimulation(short x, short y, QWidget *parent) : QGraphicsView(parent) {

    //Lo del parent es para que se coloque en el QWidget, esto es pensando en la
    //portabilidad.

    setGeometry(x, y, 702, 702);

    scene = new QGraphicsScene;
    scene->setSceneRect(-350, -350, (width() - 2), (height() - 2));

    update_timer = new QTimer;

    data.resize(3);

    Astro *astro = new Astro(300);
    data[0][0] = 0;
    data[0][1] = 0;

    data[0][2] = 0;
    data[0][3] = 0;

    data[0][4] = 0;
    data[0][5] = 0;

    data[0][6] = 70000;
    astro->setPos(data[0][4]*(700./16000.), -data[0][5]*(700./16000.));
    astros.push_back(astro);

    astro = new Astro(120);
    data[1][0] = 0;
    data[1][1] = 0;

    data[1][2] = 2;
    data[1][3] = 0;

    data[1][4] = 0;
    data[1][5] = -7000;

    data[1][6] = 70;
    astro->setPos(data[1][4]*(700./16000.), -data[1][5]*(700./16000.));
    astros.push_back(astro);

    astro = new Astro(100);
    data[2][0] = 0;
    data[2][1] = 0;

    data[2][2] = -1.6;
    data[2][3] = 1.2;

    data[2][4] = 4000;
    data[2][5] = 5000;

    data[2][6] = 25;
    astro->setPos(data[2][4]*(700./16000.), -data[2][5]*(700./16000.));
    astros.push_back(astro);

    for (short i = 0; i < astros.size(); i++) scene->addItem(astros[i]);

    setScene(scene);

    connect(update_timer, &QTimer::timeout, this, &GSimulation::move);
    update_timer->start(20);
}

GSimulation::~GSimulation() {
    delete update_timer;
    delete scene;
}

void GSimulation::move() {

    for (short i = 0; i < astros.size(); i++) {
        for (short j = (i + 1); j < astros.size(); j++) {

            cube_dist = pow(pow(data[i][4] - data[j][4], 2) + pow(data[i][5] - data[j][5], 2), 1.5);
            a_aux = (data[j][4] - data[i][4])/cube_dist;

            data[i][0] += a_aux*data[j][6];
            data[j][0] += -a_aux*data[i][6];

            a_aux = (data[j][5] - data[i][5])/cube_dist;

            data[i][1] += a_aux*data[j][6];
            data[j][1] += -a_aux*data[i][6];
        }

        data[i][2] = data[i][2] + dt*G*data[i][0];
        data[i][3] = data[i][3] + dt*G*data[i][1];

        data[i][4] = data[i][4] + dt*data[i][2];
        data[i][5] = data[i][5] + dt*data[i][3];

        astros[i]->setPos(data[i][4]*(700./16000.), -data[i][5]*(700./16000.));

        data[i][0] = 0;
        data[i][1] = 0;
    }
}


























































