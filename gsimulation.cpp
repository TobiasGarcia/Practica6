#include "gsimulation.h"

void str2double(QString str, double &dec, short &ten_pow) {

    //Almacenamos el decimal y la potencia de diez del número escrito en el formato
    //de notación científica dentro de str, en dec y ten_pow respectivamenete,
    //las cuales son variables recibidas por referencia.

    QStringList list = str.split('E');

    dec = list[0].toDouble();
    ten_pow = list[1].toInt();
}

GSimulation::GSimulation(short x, short y, QWidget *parent) : QGraphicsView(parent) {

    //La variable parent es utilizada para poder colocar el QGraphicsView dentro
    //del Widget.

    //Inicializamos la semilla para la generación de números aleatorios,
    //éstos serán utilizados en astro.cpp.

    srand(time(nullptr));

    //Establecemos las dimensiones del QGraphicsView en 702 x 702 pixeles para poder
    //colcoar una escena de 700 x 700 pixeles.

    //Nota: Según las pruebas que realicé, para poder colocar la escena perfectamente ajustada
    //al QGraphicsView, hay que sobredimensionar éste último 2 pixeles de más.

    setGeometry(x, y, 702, 702);

    //Utilizamos la variable brush para poder colocar el fondo del espacio exterior
    //al QGraphicsView.

    brush = new QBrush(QImage(":/resources/space.png"));
    brush->setTransform(QTransform().translate(-351, -351));
    setBackgroundBrush(*brush);

    scene = new QGraphicsScene;
    scene->setSceneRect(-350, -350, (width() - 2), (height() - 2));
    setScene(scene);

    update_timer = new QTimer;
    connect(update_timer, &QTimer::timeout, this, &GSimulation::move);

    //La variable started será utilizada para determinar cuando el programa
    //está haciendo los cálculos y ejecutando la simulación.

    started = false;
}

GSimulation::~GSimulation() {
    delete update_timer;
    delete brush;
    delete scene;
}

void GSimulation::add_astro(double x0, double y0, short radio) {

    //Añadimos un nuevo astro a la escena y a la lista de astros.

    Astro *astro = new Astro(radio);

    astro->setPos(x0*(700./16000.), -y0*(700./16000.));
    scene->addItem(astro);

    astros.push_back(astro);
}

void GSimulation::delete_astro(short index) {

    scene->removeItem(astros[index]);
    delete astros[index];
    astros.removeAt(index);
}

void GSimulation::update_astro(short index, double x0, double y0, short radio) {

    astros[index]->set_radio(radio);
    astros[index]->setPos(x0*(700./16000.), -y0*(700./16000.));
}

void GSimulation::start_simulation(QTableWidget *table) {

    //Este método comienza a ejecutar la simulación.

    //Los datos de diferentes simulaciones serán guardados en diferentes archivos de texto,
    //para ésto habrá un archivo llamado simu_num.txt que poseerá una sola línea con el número
    //de simulaciones realizadas hasta ahora, de ésta forma, los datos de cada simulación podrán
    //ser almacenados en los archivos de texto de nombre simulN.txt, donde N será el número de
    //la simulación correspondiente.

    //Nota: Éstos archivos de texto, junto con simu_num.txt, estarán almacenados en una carpeta
    //llamada data dentro de la carpeta donde se encuentra el .pro de éste proyecto.

    file.open("../Practica6/data/simu_num.txt", std::ios::in);
    getline(file, data_str);
    simu_num = std::stol(data_str);
    file.close();
    data_str = "";

    //El dato de simu_num.txt es almacenado en la variable simu_num. Notemos que bastaría
    //leer éste dato una única vez, no cada vez que se inicie una simulación, puesto que solamente
    //habría que aumentar el valor de simu_num para poder almacenar la información en el .txt correcto;
    //sin embergo, si el dato de simu_num.txt es modificado mientras la apliación se encuentra abierta,
    //el valor de simu_num no sería actualizado hasta cerrarla y abrirla de nuevo, por lo cual es
    //preferible leer éste dato cada vez que se comience una simulación, en busca de
    //posibles cambios.

    //Actualizamos el dato de simu_num.txt.

    file.open("../Practica6/data/simu_num.txt", std::ios::out);
    file << ++simu_num;
    file.close();

    //Creamos el archivo simulN.txt, donde N corresponde al valor leído de simu_num.txt más 1,
    //en el cual será almacenada la información de la simulación que se comenzará a ejecutar.

    //Nota: Como agregaremos una línea cada vez que actualicemos la escena, lo cual será en periodos
    //de tiempo muy cortos, preferimos no cerra el archivo cada vez, sino mantenerlo abierto
    //durante toda la simulación, y cerrarlo sólo cuando ésta sea pausada o finalizada.

    file.open("../Practica6/data/simul" + std::to_string(simu_num) + ".txt", std::ios::out);

    double mass;
    short ten_pow;

    //Inicializamos el vector data con todas las condiciones iniciales almacenadas
    //dentro del QTableWidget.

    data.resize(table->rowCount());
    for (short i = 0; i < table->rowCount(); i++) {

        //Colocamos las aceleraciones iniciales en 0 para poder usar el
        //operador += posteriormente durante el cálculo de éstas.

        data[i][0] = 0;
        data[i][1] = 0;

        //Tomamos las componente de la velocidad inicial.

        data[i][2] = table->item(i, 3)->text().toDouble();
        data[i][3] = table->item(i, 4)->text().toDouble();

        //Tomamos la posición inicial.

        data[i][4] = table->item(i, 1)->text().toDouble();
        data[i][5] = table->item(i, 2)->text().toDouble();

        //Almacenamos ésta información en el string data_str para poder agregarla
        //al final del ciclo al archivo .txt correspondiente.

        data_str.append(std::to_string(data[i][4]));
        data_str.push_back('\t');
        data_str.append(std::to_string(data[i][5]));
        data_str.push_back('\t');

        //Finalmente tomamos la masa, para luego reiniciar el ciclo de nuevo
        //para el siguiente astro dentro del QTableWidget.

        str2double(table->item(i, 5)->text(), mass, ten_pow);
        data[i][6] = mass*pow(10, ten_pow);
    }

    data_str.push_back('\n');
    file << data_str;
    data_str = "";

    //Colocamos started en true y ajustamos update_timer para que cada 20 milisegunos ejecute
    //el slot move(), el cual es el encargado de realizar los cálculos y actualizar la escena.

    started = true;
    update_timer->start(20);
}

void GSimulation::stop_simulation(QTableWidget *table) {

    //Finalizamos la simulación, por lo cual cerramos el archivo .txt correspondiente,
    //limpiamos el vector data y colocamos de nuevo los astros en sus posiciones iniciales.

    update_timer->stop();
    file.close();
    data.clear();
    started = false;

    for (short i = 0; i < table->rowCount(); i++) {
        astros[i]->setPos(table->item(i, 1)->text().toDouble()*(700./16000.),
                          -table->item(i, 2)->text().toDouble()*(700./16000.));
    }
}

void GSimulation::move() {

    //Este slot es el encargado de realizar los cálculos y actualizar la escena.

    //Por la simetria del problema, en lugar de para cada astro simplemente recorrer
    //los demás y calcular la aceleración que le generan, lo que hacemos es que para el
    //primer astro recorremos los demás y calculamos la aceleración que le generan, pero
    //dentro de éste mismo recorrido, cuando nos colocamos en uno de los demás astros,
    //también calculamos la aceleración que le genera el primero a éste último,
    //por lo cual, cuando pasamos a realizar el proceso sobre el segundo astro,
    //no hay necesidad de pasar por el primero pues ya calculamos la
    //aceleración que éste le genera al segundo, de ésta forma,
    //para el tercero unicamente recorremos del cuarto en
    //adelante y así sucesivamente para el resto de
    //astros del sistema.

    for (unsigned short i = 0; i < data.size(); i++) {
        for (unsigned short j = (i + 1); j < data.size(); j++) {

            //En lugar de almacenar simplemente la distancia entre los astros,
            //almacenamos de una vez su tercera potencia, pues es ésta última
            //la que necesitamos para los cálculos de las aceleraciones.

            cube_dist = pow(pow(data[i][4] - data[j][4], 2) + pow(data[i][5] - data[j][5], 2), 1.5);

            //Calculamos el factor (x - x0)/(r^3), donde r es la distancia de separación entre los astros,
            //x es la posicón del astro que genera la aceleración y x0 la del astro donde estamos haciendo
            //los cálculos; éste valor lo almacenamos en la variable a_aux, ésto es con el propósito de no
            //tener que calcularlo de nuevo, pues para la aceleración recíproca se utiliza el inverso
            //aditivo de éste factor.

            a_aux = (data[j][4] - data[i][4])/cube_dist;

            data[i][0] += a_aux*data[j][6];

            //NOTA IMPORTANTE: Notemos que a la acelarción en x del astro donde estamos
            //haciendo los cálculos le sumamos algo que aún NO es una aceleración, pues
            //multiplicamos a_aux (que correspode a (x - x0)/(r^3)) por la masa del otro
            //astro, pero aún no multiplicamos por G (la constante de gravitación universal);
            //ésto es para poder multiplicar una única vez por G luego de hacer todas las
            //sumas, puesto que se puede factorizar al ser un factor común; de ésta
            //forma nos ahorramos el tener que multiplicar por G en cada iteración
            //del ciclo interior, para pasar a hacerlo solamente una vez en cada
            //iteración del ciclo exterior.

            data[j][0] += -a_aux*data[i][6];

            //La NOTA IMPORTANTE, anteriormente descrita, aplica también para el cálculo
            //de la aceleración recíproca.

            //El procedimiento es análogo para calcular la componente de la aceleración en y.

            a_aux = (data[j][5] - data[i][5])/cube_dist;

            data[i][1] += a_aux*data[j][6];
            data[j][1] += -a_aux*data[i][6];
        }

        //Calculamos las componentes de la velocidad y multiplicamos por G como
        //mencionamos anteriormente.

        data[i][2] = data[i][2] + dt*G*data[i][0];
        data[i][3] = data[i][3] + dt*G*data[i][1];

        //Calculamos la nueva posición.

        data[i][4] = data[i][4] + dt*data[i][2];
        data[i][5] = data[i][5] + dt*data[i][3];

        //Añadimos ésta nueva información al strig data_str.

        data_str.append(std::to_string(data[i][4]));
        data_str.push_back('\t');
        data_str.append(std::to_string(data[i][5]));
        data_str.push_back('\t');

        //Actualizamos la escene y reiniciamos el valor de la aceleración en x e y
        //del astro del ciclo exterior para poder utilizar el operador += en el
        //siguiente llamado del slot move().

        astros[i]->setPos(data[i][4]*(700./16000.), -data[i][5]*(700./16000.));

        data[i][0] = 0;
        data[i][1] = 0;
    }

    //Añadimos la nueva línea al archivo .txt correspondiente.

    data_str.push_back('\n');
    file << data_str;
    data_str = "";
}
