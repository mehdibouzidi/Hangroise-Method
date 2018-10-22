#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

using namespace std;

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    ui->centralwidget->setFixedSize(1280,720);

    /****************   Boutons ****************/
    parcourirBtn = new QPushButton("Parcourir");
    parcourirBtn->setFixedWidth(110);
    parcourirBtn->setIcon(QIcon("search3.png"));
    executerBtn     = new QPushButton("Exécuter");
    executerBtn->setFixedWidth(110);
    executerBtn->setEnabled(false);
    executerBtn->setIcon(QIcon("power115.png"));
   /****************   Espaces de Textes ****************/
    parcourirEdit  = new QLineEdit;
    parcourirEdit->setReadOnly(true);
    nombreDeLignes  = new QSpinBox;
    nombreDeLignes->setMinimum(1);

    /****************   Groupages ****************/
    QGroupBox *groupeBoxIllustration = new QGroupBox("Affectation");
    QGroupBox *groupeBoxInsertion     = new QGroupBox("Insertion");

    /****************   Widgets ****************/
    illustration    = new QWidget;
    illustration->setFixedSize(750,720);
    QWidget *widgetFontome   = new QWidget;
    widgetFontome->setFixedHeight(400);

    /****************   Tableau ****************/
    tableau = new QTableView;
    tableau->setFixedWidth(550);
    tab=new QStandardItemModel;
    tab->setRowCount(nombreDeLignes->text().toInt());
    tab->setColumnCount(nombreDeLignes->text().toInt());
    tableau->setModel(tab);

    /****************   Layouts   ****************/
    QGridLayout *layoutGeneral      = new QGridLayout;
    QHBoxLayout *layoutIllustration = new QHBoxLayout;
    QVBoxLayout *layoutDroite       = new QVBoxLayout;
    QHBoxLayout *layoutExecution            = new QHBoxLayout;
    QHBoxLayout *layoutParcourir            = new QHBoxLayout;


    layoutIllustration->addWidget(illustration);
    groupeBoxIllustration->setLayout(layoutIllustration);

    layoutParcourir->addWidget(parcourirEdit);
    layoutParcourir->addWidget(parcourirBtn);

    layoutExecution->addWidget(nombreDeLignes);
    layoutExecution->addWidget(executerBtn);

    layoutDroite->addWidget(tableau);
    layoutDroite->addLayout(layoutExecution);
    layoutDroite->addLayout(layoutParcourir);
    groupeBoxInsertion->setLayout(layoutDroite);

    layoutGeneral->addWidget(groupeBoxIllustration,0,0,2,1,Qt::AlignCenter);
    layoutGeneral->addWidget(widgetFontome,0,1,1,1,Qt::AlignCenter);
    layoutGeneral->addWidget(groupeBoxInsertion,1,1,1,1,Qt::AlignCenter);

    connect(parcourirBtn,SIGNAL(clicked()),this,SLOT(parcourir()));
    connect(nombreDeLignes,SIGNAL(valueChanged(int)),this,SLOT(variationTableau(int)));
    connect(executerBtn,SIGNAL(clicked()),this,SLOT(execution()));
    ui->centralwidget->setLayout(layoutGeneral);


}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}





void FenetrePrincipale::parcourir()
{
    executerBtn->setEnabled(true);
    QString fichier=QFileDialog::getOpenFileName(this, "Recherche de la matrice des couts",QString(),"Text (*.txt)");
    parcourirEdit->setText(fichier);

    vector<Case> vect,init;
    int j(0),k(0);
    QString mot("");
    QString caract("");
    QString ligne("");

    /***** Lecture de la matrice depuis le fichier *****/
    QFile *matriceTxt=new QFile(fichier);
    if (!matriceTxt->open(QIODevice::ReadOnly | QIODevice::Text))
           return;

    while (!matriceTxt->atEnd())
    {
        ligne = matriceTxt->readLine();
       // nombreDeLignes->setValue(ligne.size());
        for(int i=0;i<ligne.size();i++)
        {

            while(ligne[i] != ' ' && i<ligne.size() )
            {
               mot.push_back(ligne[i]);
               i++;
            }

            if(mot != "")
            {
            vect.push_back(Case(mot.toInt()));
            tab->setItem(j,k,new QStandardItem(mot));
            k++;
            }
            mot="";

        }

        matriceCouts.push_back(vect);
        vect=init;
         j++; k=0;

    }
    nombreDeLignes->setValue(tab->columnCount());


}

void FenetrePrincipale::variationTableau(int i)
{
    tab->setRowCount(i);
    tab->setColumnCount(i);
}
/***** Combinaison des Phases *****/

void FenetrePrincipale::execution()
{
    int vide=(720-matriceCouts.size()*48)/matriceCouts.size();

    phase1();
    bool b(true);
    while(!phase2())
    {
        phase3();
        phase4();
    }

    vector<vector<int> > coor;
    vector<int> vect,init;
    for(int i=0; i<matriceCouts.size();i++)
        {
            for(int j=0;j<matriceCouts.size();j++)
            {
                if(matriceCouts[i][j].getValeur()==0 && matriceCouts[i][j].getEncadre())
                {vect.push_back(i);vect.push_back(j);coor.push_back(vect); vect=init;break;}
            }
        }

    Liaisons *liaison = new Liaisons(illustration,coor,vide);

    for(int i=1;i<=matriceCouts.size();i++)
    {
        Usine *usine=new Usine(illustration,i*vide);
        usines.push_back(usine);

        Entrepot *entrepot=new Entrepot(illustration,i*vide);
        entrepots.push_back(entrepot);
    }
}



/***** Les 4 Phases *****/

void FenetrePrincipale::phase1()
{
    int mini;

    for(int i=0; i<matriceCouts.size();i++)
    {   mini=minLigne(matriceCouts,i);
        for(int j=0;j<matriceCouts.size();j++)
        {
            matriceCouts[i][j]-=mini;

        }

    }

    for(int j=0; j<matriceCouts.size();j++)
    {   mini=minColonne(matriceCouts,j);
        for(int i=0;i<matriceCouts.size();i++)
        {
            matriceCouts[i][j]-=mini;
            //tab->setItem(i,j,new QStandardItem(matriceCouts[i][j].getValeur()));

        }

    }


    for(int i=0; i<matriceCouts.size();i++)
    {   mini=minLigne(matriceCouts,i);
        for(int j=0;j<matriceCouts.size();j++)
        {
            tab->setItem(i,j,new QStandardItem(QString::number(matriceCouts[i][j].getValeur())));
        }
    }
}

bool FenetrePrincipale::phase2()
{
    encadreBarre(matriceCouts);
    bool b(true);
    for(int i=0; i<matriceCouts.size() && b;i++)
    {
        b=false;
        for(int j=0; j<matriceCouts.size();j++)
        {
                if(matriceCouts[i][j].getValeur()==0 && matriceCouts[i][j].getEncadre()){b=true;}
        }

    }

return b;}

void FenetrePrincipale::phase3()
{
    vector<int> lignesMarquees,colonneMarquees;
    int ancienneTailleColonne(0),ancienneTailleLigne(0);
    bool b,B(true);

    for(int i=0;i<matriceCouts.size();i++)
    {
        b=true;
        for(int j=0;j<matriceCouts.size() && b;j++)
        {
            if(matriceCouts[i][j].getValeur()==0 && matriceCouts[i][j].getEncadre()){b=false;}

        }
        if(b){lignesMarquees.push_back(i);}
    }


    while (B)
    {
        /****************** Etape "b" ******************/
    for(int i=ancienneTailleLigne;i<lignesMarquees.size();i++)
    {
    for(int j=0;j<matriceCouts.size();j++)
     {
        if(matriceCouts[lignesMarquees[i]][j].getValeur()==0 && matriceCouts[lignesMarquees[i]][j].getBarre())
        {colonneMarquees.push_back(j);}

     }
    }
        ancienneTailleLigne=lignesMarquees.size();



        /****************** Etape "c" ******************/
    for(int j=ancienneTailleColonne;j<colonneMarquees.size() && B;j++)
    {
    for(int i=0;i<matriceCouts.size();i++)
     {
        if(matriceCouts[i][colonneMarquees[j]].getValeur()==0 && matriceCouts[i][colonneMarquees[j]].getEncadre())
        {lignesMarquees.push_back(i);}

     }
    }
    if(ancienneTailleColonne<colonneMarquees.size()){ancienneTailleColonne=colonneMarquees.size();}else{B=false;}

    }

    for(int j=0;j<matriceCouts.size() ;j++)
    {   b=true;
        for(int i=0;i<colonneMarquees.size()&& b;i++)
        {
            if(colonneMarquees[i]==j){b=false;}
        }
        if(b){ColonnesNonTracees.push_back(j); }
    }


    for(int i=0;i<colonneMarquees.size();i++)
    {
        ColonnesTracees.push_back(colonneMarquees[i]);
    }

    lignesNonTracees=lignesMarquees;

    for(int j=0;j<matriceCouts.size() ;j++)
    {   b=true;
        for(int i=0;i<lignesMarquees.size()&& b;i++)
        {
            if(lignesMarquees[i]==j){b=false;}
        }
        if(b){lignesTracees.push_back(j);}
    }

}


void FenetrePrincipale::phase4()
{
    int mini=minSpecial(matriceCouts,lignesNonTracees,ColonnesNonTracees);

    for(int i=0;i<lignesTracees.size();i++)
    {
        for(int j=0;j<ColonnesTracees.size();j++)
        {
            matriceCouts[lignesTracees[i]][ColonnesTracees[j]]+=mini;
        }
    }

    for(int i=0; i<matriceCouts.size();i++)
        {
            for(int j=0;j<matriceCouts.size();j++)
            {   if(matriceCouts[i][j].getValeur()==0){matriceCouts[i][j].setEncadre(false);matriceCouts[i][j].setBarre(false);}
                tab->setItem(i,j,new QStandardItem(QString::number(matriceCouts[i][j].getValeur())));
            }
        }
}



