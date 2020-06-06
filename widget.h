#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsScene>
#include <QTableWidget>
#include <QWidget>
#include "astro.h"
#include "gsimulation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {

    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_up_btn_clicked();
    void on_add_btn_clicked();
    void on_del_btn_clicked();
    void on_play_btn_clicked();
    void on_stop_btn_clicked();
    void on_pause_btn_clicked();
    void on_table_w_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::Widget *ui;
    GSimulation *gsimulation;

    void set_up_table(QTableWidget *table);
    void reset_values();
};
#endif // WIDGET_H
