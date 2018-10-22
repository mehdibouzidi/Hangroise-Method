#ifndef LIAISONS_H
#define LIAISONS_H

#include <QWidget>
#include <QPainter>
#include <vector>

class Liaisons : public QWidget
{
public:
    Liaisons(QWidget *parent,std::vector<std::vector<int> > const& coor,int vide);

    void paintEvent(QPaintEvent *e);
private:
    std::vector<std::vector<int> > coordonnees;
    int vide;
};

#endif // LIAISONS_H
