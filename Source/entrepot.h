#ifndef ENTREPOT_H
#define ENTREPOT_H

#include <QWidget>
#include <QPainter>


class Entrepot : public QWidget
{
public:
    Entrepot(QWidget *parent,int y);
    void paintEvent(QPaintEvent *e);

    int getY()const;
private:
    int y;
};

#endif // ENTREPOT_H
