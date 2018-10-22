#ifndef USINE_H
#define USINE_H

#include <QPainter>

#include <QWidget>

class Usine : public QWidget
{
public:
    Usine(QWidget *parent, int y);

    void paintEvent(QPaintEvent *e);
    int getY()const;
private :
    int y;
};

#endif // USINE_H
