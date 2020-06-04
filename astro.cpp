#include "astro.h"
#include <QDebug>

Astro::Astro(short _radio) {
    initialize(_radio);
}

void Astro::initialize(short _radio) {

    radio = _radio;
    setOffset(-30, -30); //Esto hay que cambiarlo según la imágen
    setPixmap(QPixmap(":/resources/astros/sun.png"));
}
