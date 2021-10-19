#include <math.h>
#include <time.h>
#include <QSize>
#include <QWidget>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <mutex>
#include <Thread>
#include <QDebug>
#include "polygon.hpp"

using namespace std;

polygon::polygon(const QColor &fg, const QColor &paint_col)
    :fg(fg), paint_col(paint_col)
{
}

void polygon::draw(QPainter &painter) const
{
    painter.setPen(QPen(fg));

    for (edge edge: edges)
    {
        painter.drawLine(edge.p1->x, edge.p1->y, edge.p2->x, edge.p2->y);
    }

    for (point *point : points)
    {
        QString text("(");
        text.append(QString::number(point->x));
        text.append("; ");
        text.append(QString::number(point->y));
        text.append(")");
        painter.drawText(point->x - (text.indexOf(';') + 1) * 5, point->y - 5, text);
    }
}

void polygon::find_max(int &max) const
{
    max = points[0]->x;
    for (point *p : points)
        if (p->x > max)
            max = p->x;
}

void polygon::find_min(int &min) const
{
    min = points[0]->x;
    for (point *p : points)
        if (p->x < min)
            min = p->x;
}

void polygon::find_up(int &up) const
{
    up = points[0]->y;
    for (point *p : points)
        if (p->y > up)
            up = p->y;
}

void polygon::find_down(int &down) const
{
    down = points[0]->y;
    for (point *p : points)
        if (p->y > down)
            down = p->y;
}

mutex mtx;

void polygon::draw_line(int x, int y, int max, QImage *image, QColor bg, matrix &buffer)
{
    while (x < max)
    {
        //mtx.lock();
//        if (image->pixelColor(x, y) == paint_col)
//            image->setPixelColor(x, y, bg);
//        else
//            image->setPixelColor(x, y, paint_col);
        buffer[y][x] = not buffer[y][x];
        //mtx.unlock();
        x++;
    }
}

void polygon::edges_proc(QImage *image, QColor bg, size_t start, size_t finish, int max, matrix &buffer)
{
    for (size_t i = start; i < finish; i++)
    {
        point beg(edges[i].p1), end(edges[i].p2);

        if (beg.y == end.y)
            continue;

        if (beg.y > end.y)
        {
            int tmp = beg.y;
            beg.y = end.y;
            end.y = tmp;

            tmp = beg.x;
            beg.x = end.x;
            end.x = tmp;
        }

        float ctg = (float) (end.x - beg.x) / (end.y - beg.y);

        float x = beg.x;
        int y = beg.y;

        while (y != end.y)
        {
            draw_line(round(x), y, max, image, bg, buffer);
            x += ctg;
            y += 1;
        }
    }
}

void polygon::paint(QPainter &painter, QImage *image, QColor bg, size_t th_count)
{
    int max, up;
    //int down, min;
    find_max(max);
    //find_min(min);
    find_up(up);
    //find_down(down);

    auto buffer = vector<vector<bool>>();
    for (int i = 0; i < up; i++) {
        buffer.emplace_back(max);
        for (int j = 0; j < max; j++) {
            buffer[i][j] = false;
        }
    }

    size_t edges_for_th = edges.size() / th_count;
    thread *th = new thread[th_count];

    for (size_t i = 0; i < th_count - 1; i++)
    {
        size_t start = i * edges_for_th, finish = (i + 1) * edges_for_th;
        th[i] = thread([&image, bg, start, finish, max, this, &buffer]()
                       {
                           edges_proc(image, bg, start, finish, max, buffer);
                       });
    }
    th[th_count - 1] = thread([&]()
                   {
                       edges_proc(image, bg, (th_count - 1) * edges_for_th, edges.size(), max, buffer);
                   });

    for (size_t i = 0; i < th_count; i++)
    {
        th[i].join();
    }
    delete[] th;

    for (int i = 0; i < up; i++) {
        for (int j = 0; j < max; j++) {
            if (buffer[i][j]) {
                painter.setPen(paint_col);
            }
            else {
                painter.setPen(bg);
            }
            painter.drawPoint(j, i);
        }
    }
}

void polygon::base(QPainter &painter, QImage *image, QColor bg)
{
    int max, up;
    //int down, min;
    find_max(max);
    //find_min(min);
    find_up(up);
    //find_down(down);

    auto buffer = vector<vector<bool>>();
    for (int i = 0; i < up; i++) {
        buffer.emplace_back(max);
        for (int j = 0; j < max; j++) {
            buffer[i][j] = false;
        }
    }

    edges_proc(image, bg, 0, edges.size(), max, buffer);
    for (int i = 0; i < up; i++) {
        for (int j = 0; j < max; j++) {
            if (buffer[i][j]) {
                painter.setPen(paint_col);
            }
            else {
                painter.setPen(bg);
            }
            painter.drawPoint(j, i);
        }
    }
}

double polygon::paint_time(QImage *image, size_t th_count)
{
    QImage img = QImage(image->size(), QImage::Format_RGBA64);
    QPainter painter(&img);

    int n = 50;
    qDebug() << th_count;
    clock_t clk;

    if (!th_count) {
        clk = clock();
        for (int i = 0; i < n; i++) {
            base(painter, &img, QColor(0, 0, 0));
        }
        clk = clock() - clk;
    }
    else {
        clk = clock();
        for (int i = 0; i < n; i++) {
            paint(painter, &img, QColor(0, 0, 0), th_count);
        }
        clk = clock() - clk;
    }

    return (double) clk / CLOCKS_PER_SEC / n;
}

void polygon::add_point(point *point, bool hor, bool ver)
{
    if (hor)
        point->y = points[points.size() - 1]->y;
    if (ver)
        point->x = points[points.size() - 1]->x;

    points.push_back(point);
    if (new_edge)
        edges.push_back(edge(points[points.size() - 1], points[points.size() - 2]));
    new_edge = true;
}

void polygon::add_hole()
{
    close();
    new_edge = false;
    start_pos = points.size();
}

void polygon::close()
{
    if (points.size() != edges.size())
        edges.push_back(edge(points[start_pos], points[points.size() - 1]));
}
