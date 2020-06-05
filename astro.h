#ifndef ASTRO_H
#define ASTRO_H

#include <QGraphicsPixmapItem>
#include <time.h>

class Astro: public QGraphicsPixmapItem {

    //Dejamos el código para inicializar objeto dentro del método initialize(),
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
