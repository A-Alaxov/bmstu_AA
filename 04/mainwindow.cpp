#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <vector>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fg_view->set_color(QColor(Qt::white));
    ui->fg_view->set_color(QColor(Qt::black));
    ui->paint_view->set_color(QColor(Qt::green));

    ui->field->set_bg(ui->bg_view->get_color());
    ui->field->set_fg(ui->fg_view->get_color());
    ui->field->set_paint_col(ui->paint_view->get_color());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bg_button_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->bg_view->set_color(dialog.selectedColor());

    ui->field->set_bg(dialog.selectedColor());
}

void MainWindow::on_fg_button_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->fg_view->set_color(dialog.selectedColor());

    ui->field->set_fg(dialog.selectedColor());
}

void MainWindow::on_paint_button_clicked()
{
    QColorDialog dialog;
    dialog.show();
    dialog.exec();
    ui->paint_view->set_color(dialog.selectedColor());

    ui->field->set_paint_col(dialog.selectedColor());
}

void MainWindow::on_add_point_button_clicked()
{
    ui->field->add_point(ui->x_input->text().toInt(), ui->y_input->text().toInt());
}

void MainWindow::on_paint_fig_button_clicked()
{
    ui->field->finish_figure();
}

void MainWindow::on_add_hole_clicked()
{
    ui->field->add_hole();
}

void MainWindow::on_clear_clicked()
{
    ui->field->clear();
}

void MainWindow::on_time_button_clicked()
{
    ui->time->clear();
    std::ofstream out;
    out.open("../table.csv");
    if (!out.is_open()) {
        return;
    }
    out << "Len,th0,th1,th2,th4,th8,th16" << std::endl;
    for (int n = 20; n < 30; n += 250) {
        out << n;

        polygon *pol = new polygon(ui->fg_view->get_color(), ui->paint_view->get_color());
        for (int i = 0; i < n; i++) {
            point *p = new point(rand() % ui->field->width(), rand() % ui->field->height());
            pol->add_point(p, false, false);
        }
        pol->close();

        double time;
        ui->field->get_time(time, 0, pol);
        ui->time->append(QString("Потоков: 0; Время: ") + QString::number(time) + QString(" сек"));
        out << ',' << time;
        for (size_t th_count = 1; th_count < 32; th_count *= 2) {
            ui->field->get_time(time, th_count, pol);
            ui->time->append(QString("Потоков: ") + QString::number(th_count) + QString("; Время: ") + QString::number(time) + QString(" сек"));
            out << ',' << time;
        }
        out << std::endl;
        delete pol;
    }
    out.close();
}

void MainWindow::on_vertical_clicked()
{
    ui->field->set_ver();
}

void MainWindow::on_horizontal_clicked()
{
    ui->field->set_hor();
}
