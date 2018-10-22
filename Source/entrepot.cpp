#include "entrepot.h"

Entrepot::Entrepot(QWidget *parent, int y)
{
    setParent(parent);
    this->y=y;
    setGeometry(602,y,48,48);
    setHidden(false);
}

void Entrepot::paintEvent(QPaintEvent *e)
{
    QPainter *painter=new QPainter(this);
    QPoint point(0,0);
    painter->drawPixmap(point,QPixmap("entrepot.png"));

}

int Entrepot::getY() const{return y;}


