#include "widget.h"
#include "ui_widget.h"

//REVISAR MAX VX Y VY

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {

    ui->setupUi(this);
    setFixedSize(1144, 702);
    setWindowTitle("Gravity Simulation");

    gsimulation = new GSimulation(0, 0, this);

    set_up_table(ui->table_w);

    ui->play_btn->setIcon(QIcon(QPixmap(":/resources/buttons/play_btn.png")));
    ui->play_btn->setIconSize(QSize(50, 50));

    ui->pause_btn->setIcon(QIcon(QPixmap(":/resources/buttons/pause_btn.png")));
    ui->pause_btn->setIconSize(QSize(50, 50));

    ui->stop_btn->setIcon(QIcon(QPixmap(":/resources/buttons/stop_btn.png")));
    ui->stop_btn->setIconSize(QSize(50, 50));
}

Widget::~Widget() {
    delete gsimulation;
    delete ui;
}

void Widget::reset_values() {

    ui->x0_double->setValue(0);
    ui->y0_double->setValue(0);
    ui->vx0_double->setValue(0);
    ui->vy0_double->setValue(0);
    ui->mass_double->setValue(1);
    ui->ten_pow->setValue(0);
    ui->radio->setValue(1);
}

void Widget::set_up_table(QTableWidget *table) {

    table->horizontalHeader()->setDefaultSectionSize(60);
    table->horizontalHeader()->setMinimumSectionSize(60);
    table->setColumnCount(7);

    table->verticalHeader()->setDefaultSectionSize(10);
    table->verticalHeader()->setVisible(false);

    QStringList headers = {"Astro", "Ini X", "Ini Y", "Ini Vx", "Ini Vy", "Mass", "Radio"};
    table->setHorizontalHeaderLabels(headers);
}


void Widget::on_add_btn_clicked() {

    if (ui->table_w->rowCount() == 0) ui->play_btn->setEnabled(true);

    short row =  ui->table_w->rowCount();
    ui->table_w->insertRow(row);
    ui->table_w->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
    ui->table_w->setItem(row, 1, new QTableWidgetItem(QString::number(ui->x0_double->value())));
    ui->table_w->setItem(row, 2, new QTableWidgetItem(QString::number(ui->y0_double->value())));
    ui->table_w->setItem(row, 3, new QTableWidgetItem(QString::number(ui->vx0_double->value())));
    ui->table_w->setItem(row, 4, new QTableWidgetItem(QString::number(ui->vy0_double->value())));
    ui->table_w->setItem(row, 5, new QTableWidgetItem(QString::number(ui->mass_double->value()) +
                                                      QString("E") + QString::number(ui->ten_pow->value())));
    ui->table_w->setItem(row, 6, new QTableWidgetItem(QString::number(ui->radio->value())));

    gsimulation->add_astro(ui->x0_double->value(), ui->y0_double->value(), ui->radio->value());

    if (row == 7) ui->add_btn->setEnabled(false);

    reset_values();

    ui->del_btn->setEnabled(false);
    ui->up_btn->setEnabled(false);

    ui->table_w->setCurrentCell(-1, 0);
}

void Widget::on_del_btn_clicked() {

    short row = ui->table_w->currentRow();
    ui->table_w->removeRow(row);

    gsimulation->delete_astro(row);

    ui->add_btn->setEnabled(true);
    ui->del_btn->setEnabled(false);
    ui->up_btn->setEnabled(false);
    if (ui->table_w->rowCount() == 0) ui->play_btn->setEnabled(false);

    for (short i = row; i < ui->table_w->rowCount(); i++) {
        ui->table_w->item(i, 0)->setText(QString::number(i + 1));
    }

    reset_values();

    ui->table_w->setCurrentCell(-1, 0);
}

void Widget::on_table_w_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) {

    Q_UNUSED(previousColumn)
    Q_UNUSED(currentColumn)

    if (!(gsimulation->started) and (currentRow != -1) and (previousRow != currentRow)) {
        ui->del_btn->setEnabled(true);
        ui->up_btn->setEnabled(true);

        double mass;
        short ten_pow;

        ui->x0_double->setValue(ui->table_w->item(currentRow, 1)->text().toDouble());
        ui->y0_double->setValue(ui->table_w->item(currentRow, 2)->text().toDouble());
        ui->vx0_double->setValue(ui->table_w->item(currentRow, 3)->text().toDouble());
        ui->vy0_double->setValue(ui->table_w->item(currentRow, 4)->text().toDouble());

        str2double(ui->table_w->item(currentRow, 5)->text(), mass, ten_pow);
        ui->mass_double->setValue(mass);
        ui->ten_pow->setValue(ten_pow);

        ui->radio->setValue(ui->table_w->item(currentRow, 6)->text().toInt());
    }
}

void Widget::on_up_btn_clicked() {

    short row = ui->table_w->currentRow();
    ui->table_w->item(row, 1)->setText(QString::number(ui->x0_double->value()));
    ui->table_w->item(row, 2)->setText(QString::number(ui->y0_double->value()));
    ui->table_w->item(row, 3)->setText(QString::number(ui->vx0_double->value()));
    ui->table_w->item(row, 4)->setText(QString::number(ui->vy0_double->value()));
    ui->table_w->item(row, 5)->setText(QString::number(ui->mass_double->value()) +
                                       QString("E") + QString::number(ui->ten_pow->value()));
    ui->table_w->item(row, 6)->setText(QString::number(ui->radio->value()));

    gsimulation->update_astro(row, ui->x0_double->value(), ui->y0_double->value(), ui->radio->value());

    reset_values();

    ui->del_btn->setEnabled(false);
    ui->up_btn->setEnabled(false);

    ui->table_w->setCurrentCell(-1, 0);
}

void Widget::on_play_btn_clicked() {

    ui->add_btn->setEnabled(false);
    ui->up_btn->setEnabled(false);
    ui->del_btn->setEnabled(false);

    ui->play_btn->setEnabled(false);
    ui->pause_btn->setEnabled(true);
    ui->stop_btn->setEnabled(true);

    if (gsimulation->started) {
        gsimulation->file.open("../Practica6/data/simul" + std::to_string(gsimulation->simu_num) + ".txt", std::ios::app);
        gsimulation->update_timer->start(20);
    }
    else gsimulation->start_simulation(ui->table_w);
}

void Widget::on_pause_btn_clicked() {

    ui->play_btn->setEnabled(true);
    ui->pause_btn->setEnabled(false);

    gsimulation->update_timer->stop();
    gsimulation->file.close();
}

void Widget::on_stop_btn_clicked() {

    ui->add_btn->setEnabled(ui->table_w->rowCount() != 8);

    ui->play_btn->setEnabled(true);
    ui->pause_btn->setEnabled(false);
    ui->stop_btn->setEnabled(false);

    ui->table_w->setCurrentCell(-1, 0);
    gsimulation->stop_simulation(ui->table_w);
}





















































