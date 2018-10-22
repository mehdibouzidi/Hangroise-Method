#include "usine.h"


Usine::Usine(QWidget *parent,int y)
{
    setParent(parent);
    setGeometry(0,y,48,48);
    setHidden(false);
    this->y=y;

}

void Usine::paintEvent(QPaintEvent *e)
{
    QPainter *painter=new QPainter(this);
    QPoint point(0,0);
    painter->drawPixmap(point,QPixmap("usine.png"));

}

int Usine::getY() const{return y;}
