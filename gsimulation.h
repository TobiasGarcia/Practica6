#ifndef GSIMULATION_H
#define GSIMULATION_H

#include <QGraphicsView>
#include <QTableWidget>
#include <fstream>
#include <QTimer>
#include <math.h>
#include "astro.h"

//Esta clase modela la simulación. Decidí hacerla que heredara la clase QGraphicsView en lugar
//de QGraphicsScene para que los límites del QGraphicsView donde se presentará la escena
//puedieran ser definidos desde dentro de la clase.

//Implementamos la siguiente función en lugar de sencillamente usar QString::number(),
//ésto es con el propósito de poder recuperar el decimal y la potencia de diez del
//número escrito en el formato de notación científica dentro de str.

void str2double(QString str, double &dec, short &ten_pow);

class GSimulation: public QGraphicsView {

    Q_OBJECT

private:

    //La variable dt corresponde al valor de T dentro de las fórmulas para calcular las componentes de
    //la velocidad y la posición. Éste valor es convencionalmente pequeño para obtener una buena simulación y,
    //aunque no lo parezca a primera vista, como las dimensiones son de 16000 x 16000 unidades,
    //el valor de la variable dt sí es relativamente pequeño para éste caso.

    float dt = 12;
    QBrush *brush;
    std::string data_str;
    QList<Astro*> astros;
    QGraphicsScene *scene;

    //Utilizamos doubles no tanto para almacenar un número grande, sino para poder almacenar
    //numeros de diversas magnitudes que poseen varias cifras significativas.

    //Nota: Como se mencionó, tomaremos el valor de G (la constante de gravitación universal)
    //idénticamente como 1.

    double G = 1, a_aux, cube_dist;

    //El siguiente vector contendrá la información de toda la simulación, ésto es sencillamente
    //para poder optimizar los cálculos a la hora de llevarla a cabo. Utilizando éste vector
    //estamos sectorizando toda la información necesaria en un mismo bloque dentro de la
    //memoria, en lugar de tenerla distribuida en diferentes direcciones dentro de los
    //objetos de la clase Astro.

    //Cada elemento es un arreglo de 7 doubles que almacena la información de uno los astro;
    //el primer y segundo dato son las aceleraciones en x e y respectivamente, el tercer y cuarto
    //dato son las componentes de la velocidad en x e y respectivamente, el quinto y sexto dato las
    //posiciones en x e y respectivamente, y el último dato es la masa del astro en cuestión.

    std::vector<std::array<double, 7>> data; //ax, ay, vx, vy, x, y, m

public:
    bool started;
    short simu_num;
    std::fstream file;
    QTimer *update_timer;

    void delete_astro(short index);
    void stop_simulation(QTableWidget *table);
    void start_simulation(QTableWidget *table);
    void add_astro(double x0, double y0, short radio);
    void update_astro(short index, double x0, double y0, short radio);
    GSimulation(short x, short y, QWidget *parent);
    ~GSimulation();

public slots:
    void move();

};

#endif // GSIMULATION_H
