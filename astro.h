#ifndef ASTRO_H
#define ASTRO_H

#include <QGraphicsPixmapItem>
#include <math.h>

//#define G 1
//#define T 0.05 //Segundos
//#define WIDTH
//#define HEIGHT

class Astro: public QObject, public QGraphicsPixmapItem {

    Q_OBJECT

private:
    float v[2], a[2], dist, m, radio; //Floats para utilizar notación científica
    //std::array<float, 400> tail

public:
    float r[2];

    Astro(float x0, float y0, float vx0, float vy0, float _m, float _radio);

};

#endif // ASTRO_H
