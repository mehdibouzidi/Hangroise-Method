#include "liaisons.h"



Liaisons::Liaisons(QWidget *parent, const std::vector<std::vector<int> > &coor, int vide)
{
    setParent(parent);
    coordonnees=coor;
    this->vide=vide;
    this->setGeometry(0,0,750,720);
    setHidden(false);
}

void Liaisons::paintEvent(QPaintEvent *e)
{

    QPainter *painter=new QPainter(this);


    int vide1;
    for(int i=0; i<coordonnees.size();i++)
    {
        vide1=(coordonnees[i][0]+1)*vide+34;
        QPoint point1(47,vide1);
        vide1=(coordonnees[i][1]+1)*vide+24;
        QPoint point2(602,vide1);
        painter->drawLine(point1,point2);
    }
}
