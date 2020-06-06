#ifndef ASTRO_H
#define ASTRO_H

#include <QGraphicsPixmapItem>

//Esta clase es con el único propósito de poder agregar una imágen a los diferentes astros
//que participan de la simulación. Toda la información, cálculo de trayectorias y
//posiciones se hace dentro de los métodos de la clase GSimulation.

class Astro: public QGraphicsPixmapItem {

    //Encapsulamos el código para inicializar el objeto dentro del método set_radio(),
    //esto es con el propósito de poder "construir" un mismo objeto varias
    //veces, sin tener que liberar y reservar memoria de nuevo.

private:
    QPixmap *image;

public:
    Astro(short radio);
    ~Astro() {delete image;};
    void set_radio(short radio);

};

#endif // ASTRO_H
