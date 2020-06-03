#include "astro.h"
#include <QDebug>

Astro::Astro(short _radio)  : radio(_radio) {

    setOffset(-30, -30); //Esto hay que cambiarlo según la imágen
    setPixmap(QPixmap(":/resources/sun.png"));
}

//void Astro::update_trajectory() {

//    a[0] = 0;
//    a[1] = 0;

//    for (unsigned short i = 0; i < data_ptr->size(); i++) {
//        if (id != i) {
//            a_aux = (*data_ptr)[i][2]/pow(pow(r[0] - (*data_ptr)[i][0], 2) + pow(r[1] - (*data_ptr)[i][1], 2), 1.5);
//            a[0] += a_aux*((*data_ptr)[i][0] - r[0]);
//            a[1] += a_aux*((*data_ptr)[i][1] - r[1]);
//        }
//    }

//    a[0] = G*a[0];
//    a[1] = G*a[1];

//    v[0] = v[0] + T*a[0];
//    v[1] = v[1] + T*a[1];

//    r[0] = r[0] + T*v[0];
//    r[1] = r[1] + T*v[1];

//    setPos(r[0]*(700./16000.), -r[1]*(700./16000.));
//}
