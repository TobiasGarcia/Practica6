#include "astro.h"
#include <QDebug>

Astro::Astro(float x0, float y0, float vx0, float vy0, float _m, float _radio) {

    m = _m;
    radio = _radio;

    setOffset(-30, -30);
    setPixmap(QPixmap(":/resources/sun.png"));

    r[0] = x0;
    r[1] = y0;

    v[0] = vx0;
    v[1] = vy0;

    setPos(r[0]*(700./16000.), -r[1]*(700./16000.));
}
