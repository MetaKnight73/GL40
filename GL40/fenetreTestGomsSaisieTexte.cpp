#include "fenetreTestGomsSaisieTexte.h"

FenetreTestGomsSaisieTexte::FenetreTestGomsSaisieTexte(int nombreMots, QWidget *parent, double tempsM, int longueurMaximale) : QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    // On initialise les paramètres
    tempsMental= tempsM;
    longueurMax = longueurMaximale;
    nombreM = nombreMots;
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
    connect(this, SIGNAL(sequenceFinGoms(vector<StatistiquesGomsSaisieTexte>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsSaisieTexte(vector<StatistiquesGomsSaisieTexte>)));

}

char* FenetreTestGomsSaisieTexte::genererMotCourant(int longueur) {

    srand(time(NULL));
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

void FenetreTestGomsSaisieTexte::lancerTest() {

    // On fait disparaître le bouton
    bouton->hide();

    layoutZoneSaisie = new QVBoxLayout;

    //On génère le premier mot aléatoire
    motCourant = new QLabel(QString(genererMotCourant(longueurMax)), this, 0);
    motCourant->setFont(QFont("Arial Black", 40));
    labelZoneSaisie->setText(QString("Veuillez saisir le texte affiché ci-dessus puis appuyer sur Entrée"));
    labelZoneSaisie->setFont(QFont("Arial", 20, -1, true));
    zoneSaisie->setMaximumHeight(50);
    zoneSaisie->setMinimumHeight(50);
    zoneSaisie->setMaximumWidth(700);
    zoneSaisie->setMinimumWidth(700);
    zoneSaisie->setFont(QFont("Arial Black", 24));

    layoutZoneSaisie->addWidget(labelZoneSaisie, 0, Qt::AlignLeft);
    layoutZoneSaisie->addWidget(zoneSaisie, 0, Qt::AlignCenter);

    layout->addWidget(motCourant, 0, 0, 1, 1, Qt::AlignCenter);
    layout->addLayout(layoutZoneSaisie, 1, 0, 1, 1, Qt::AlignCenter);

    setLayout(layout);

    chronometre->start();

    zoneSaisie->setFocus();

}

void FenetreTestGomsSaisieTexte::checkWord() {

    QString texteZoneSaisie = zoneSaisie->text();
    QString texteMotCourant = motCourant->text();

    int x = QString::compare(texteZoneSaisie, texteMotCourant, Qt::CaseSensitive);
    if(!x) {

        nombreMotsValidesCourant++;
        statistiquesGomsSaisieTexte.push_back(StatistiquesGomsSaisieTexte(tempsMental, texteMotCourant.length(), chronometre->elapsed()));
        if(nombreMotsValidesCourant < nombreM) {

            zoneSaisie->clear();
            motCourant->setText(QString(genererMotCourant(longueurMax)));
            chronometre->restart();

        }

        else {

            emit sequenceFinGoms(statistiquesGomsSaisieTexte);

        }

    }

}
