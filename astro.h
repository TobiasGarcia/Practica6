#ifndef ASTRO_H
#define ASTRO_H

#include <QGraphicsPixmapItem>
#include <QDebug>

class Astro: public QGraphicsPixmapItem {
private:
    short radio;

public:
    Astro(short _radio);

};

#endif // ASTRO_H
