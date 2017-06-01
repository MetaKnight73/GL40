#include "fenetreTestGomsBash.h"
#include <QDebug>

FenetreTestGomsBash::FenetreTestGomsBash(int longRep, QWidget *parent, double tempsM, int tailleChemin) : QWidget(parent)
{
    srand(time(NULL));

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    // On initialise les paramètres
    tempsMental= tempsM;
    nbRep = tailleChemin;
    longueurMaxRep = longRep;
    nombreMotsValidesCourant = 0;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    //On crée le layout
    layout = new QGridLayout;

    zoneSaisie = new QLineEdit;
    labelZoneSaisie = new QLabel;

    // Connexions
    connect(bouton, SIGNAL(clicked()), this, SLOT(lancerTest()));
    connect(zoneSaisie, SIGNAL(returnPressed()), this, SLOT(checkWord()));
    connect(this, SIGNAL(sequenceFinGoms(vector<StatistiquesGomsBash>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsBash(vector<StatistiquesGomsBash>)));

}

char* FenetreTestGomsBash::genererMotCourant(int longueur) {

    //srand(time(NULL)); seed effectuer dans le constructeur

    unsigned int length = (rand() % longueur) + 1;
    char* str = new char[length];

    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (unsigned int n = 0; n < length; n++) {
        int key = rand() % (int) (sizeof charset - 1);
        str[n] = charset[key];
    }
    str[length] = '\0';
    return str;

}

void FenetreTestGomsBash::lancerTest() {

    // On fait disparaître le bouton
    bouton->hide();

    layoutZoneSaisie = new QVBoxLayout;

    //On génère le chemin aléatoire
    char* chemin = new char[longueurMaxRep*nbRep];//On créer une chaîne de la taille Nombre de répertoire x Longueur max d'un répertoire
    chemin[0] = '\0';

    for(int i=0; i < nbRep; ++i)
    {
        strcat(chemin,genererMotCourant(longueurMaxRep));
        strcat(chemin,"/");
    }

    cheminCourant = new QLabel(QString(chemin), this, 0);
    cheminCourant->setFont(QFont("Arial Black", 12));
    labelZoneSaisie->setText(QString("Parcourez le chemin ci-dessus via la commande bash \"cd repertoire\". \"Entrée\" pour valider."));
    labelZoneSaisie->setFont(QFont("Arial", 20, -1, true));
    zoneSaisie->setMaximumHeight(50);
    zoneSaisie->setMinimumHeight(50);
    zoneSaisie->setMaximumWidth(700);
    zoneSaisie->setMinimumWidth(700);
    zoneSaisie->setFont(QFont("Arial Black", 24));

    layoutZoneSaisie->addWidget(labelZoneSaisie, 0, Qt::AlignLeft);
    layoutZoneSaisie->addWidget(zoneSaisie, 0, Qt::AlignCenter);

    layout->addWidget(cheminCourant, 0, 0, 1, 1, Qt::AlignCenter);
    layout->addLayout(layoutZoneSaisie, 1, 0, 1, 1, Qt::AlignCenter);

    setLayout(layout);

    chronometre->start();

    zoneSaisie->setFocus();

}

void FenetreTestGomsBash::checkWord() {

    QString texteZoneSaisie = zoneSaisie->text();
    QStringList listTexteMotCourant = cheminCourant->text().split("/",QString::SkipEmptyParts); // on découpe la chaine contenant le chemin en list de QString
    QString texteMotCourant;

    if(!listTexteMotCourant.isEmpty())
    {
        texteMotCourant = listTexteMotCourant.takeFirst(); //on prend le premier élement de la liste qui est le nom du répertoire
        texteMotCourant = QString("cd ") + texteMotCourant; //on ajoute la commande au début du QString
    }

    int x = QString::compare(texteZoneSaisie, texteMotCourant, Qt::CaseSensitive);
    if(!x) {

        nombreMotsValidesCourant++;
        statistiquesGomsBash.push_back(StatistiquesGomsBash(tempsMental, texteMotCourant.length(), chronometre->elapsed()));
        if(nombreMotsValidesCourant < nbRep) {

            zoneSaisie->clear();
            cheminCourant->setText(listTexteMotCourant.join("/"));
            chronometre->restart();

        }

        else {

            emit sequenceFinGoms(statistiquesGomsBash);

        }

    }

}