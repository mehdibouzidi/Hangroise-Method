#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTableView>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <vector>
#include <iostream>
#include <QtGui>
#include <string>

#include "case.h"
#include "fonctions.h"
#include "usine.h"
#include "entrepot.h"
#include "liaisons.h"
namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

    /***** Les 5 Phases *****/
    void phase1();
    bool phase2();
    void phase3();
    void phase4();


public slots:
    void parcourir();
    void variationTableau(int i);
    void execution();

private:
    Ui::FenetrePrincipale *ui;
    QLineEdit *parcourirEdit;
    QSpinBox *nombreDeLignes;
    QPushButton *parcourirBtn;
    QPushButton *executerBtn;
    QTableView *tableau;
    QWidget *illustration;
    QStandardItemModel *tab;
    std::vector < std::vector<Case> > matriceCouts;
    std::vector <int> lignesTracees;
    std::vector <int> lignesNonTracees;
    std::vector <int> ColonnesTracees;
    std::vector <int> ColonnesNonTracees;
    std::vector <Usine*> usines;
    std::vector <Entrepot*> entrepots;
};

#endif // FENETREPRINCIPALE_H
