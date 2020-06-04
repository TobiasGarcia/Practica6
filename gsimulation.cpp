#include "gsimulation.h"

void str2double(QString str, double &dec, short &ten_pow) {

    QStringList list = str.split('E');

    dec = list[0].toDouble();
    ten_pow = list[1].toInt();
}

GSimulation::GSimulation(short x, short y, QWidget *parent) : QGraphicsView(parent) {

    //Lo del parent es para que se coloque en el QWidget, esto es pensando en la
    //portabilidad.

    setGeometry(x, y, 702, 702);

    brush = new QBrush(QImage(":/resources/space.png"));
    brush->setTransform(QTransform().translate(-351, -351));
    setBackgroundBrush(*brush);

    scene = new QGraphicsScene;
    scene->setSceneRect(-350, -350, (width() - 2), (height() - 2));

    update_timer = new QTimer;

    setScene(scene);

    connect(update_timer, &QTimer::timeout, this, &GSimulation::move);

    started = false;
}

GSimulation::~GSimulation() {
    delete update_timer;
    delete brush;
    delete scene;
}

void GSimulation::add_astro(double x0, double y0, short radio) {

    Astro *astro = new Astro(radio);
    astro->setPos(x0*(700./16000.), -y0*(700./16000.));
    scene->addItem(astro);
    astros.push_back(astro);
}

void GSimulation::delete_astro(short index) {

    scene->removeItem(astros[index]);
    astros.erase(astros.begin() + index);
}

void GSimulation::update_astro(short index, double x0, double y0, short radio) {

    astros[index]->initialize(radio);
    astros[index]->setPos(x0*(700./16000.), -y0*(700./16000.));
}

void GSimulation::start_simulation(QTableWidget *table) {

    double mass;
    short ten_pow;

    data.resize(table->rowCount());
    for (short i = 0; i < table->rowCount(); i++) {
        data[i][0] = 0;
        data[i][1] = 0;

        data[i][2] = table->item(i, 3)->text().toDouble();
        data[i][3] = table->item(i, 4)->text().toDouble();

        data[i][4] = table->item(i, 1)->text().toDouble();
        data[i][5] = table->item(i, 2)->text().toDouble();

        str2double(table->item(i, 5)->text(), mass, ten_pow);
        data[i][6] = mass*pow(10, ten_pow);
    }

    started = true;
    update_timer->start(20);
}

void GSimulation::stop_simulation(QTableWidget *table) {

    started = false;
    data.clear();

    for (short i = 0; i < table->rowCount(); i++) {
        astros[i]->setPos(table->item(i, 1)->text().toDouble()*(700./16000.),
                          -table->item(i, 2)->text().toDouble()*(700./16000.));
    }
}

void GSimulation::move() {

    for (unsigned short i = 0; i < data.size(); i++) {
        for (unsigned short j = (i + 1); j < data.size(); j++) {

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




























































