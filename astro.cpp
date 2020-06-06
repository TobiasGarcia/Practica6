#include "astro.h"

Astro::Astro(short radio) {

    //Elegimos una imágen al azar de entre las 10 disponibles para el astro
    //que está siendo agregado a la simulación.

    short image_num = rand()%10;

    if (image_num == 0) image = new QPixmap(":/resources/astros/asteroid.png");
    else if (image_num == 1) image = new QPixmap(":/resources/astros/earth.png");
    else if (image_num == 2) image = new QPixmap(":/resources/astros/jupiter.png");
    else if (image_num == 3) image = new QPixmap(":/resources/astros/mars.png");
    else if (image_num == 4) image = new QPixmap(":/resources/astros/mercury.png");
    else if (image_num == 5) image = new QPixmap(":/resources/astros/moon.png");
    else if (image_num == 6) image = new QPixmap(":/resources/astros/neptune.png");
    else if (image_num == 7) image = new QPixmap(":/resources/astros/pluto.png");
    else if (image_num == 8) image = new QPixmap(":/resources/astros/sun.png");
    else image = new QPixmap(":/resources/astros/venus.png");

    set_radio(radio);
}

void Astro::set_radio(short radio) {

    //Escalamos el radio para que sus valores dentro de la UI puedan tener un rango más amplio,
    //aunque en realidad siempre termina en un entero entre entre 10 y 85, inclusive.

    //Notmeos que 10 es el mínimo valor para el radio, ésto es con el propósito de que siempre
    //se pueda ver la imágen, ya que si permitiésemos al 1 ser el mínimo valor habrían casos
    //donde el astro estaría dentro de la simulación pero casi no se vería en lo absoluto.

    short diameter = 2*(10 + short(radio/10));
    setOffset(-diameter/2, -diameter/2);

    setPixmap((*image).scaled(diameter, diameter, Qt::KeepAspectRatio));
}
