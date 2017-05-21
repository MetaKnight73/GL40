#include "fenetreTestGomsClics.h"

FenetreTestGomsClics::FenetreTestGomsClics(int profondeur, QWidget *parent, double parametre1, double parametre2, double parametre3): QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    // On initialise les paramètres
    param1 = parametre1;
    param2 = parametre2;
    param3 = parametre3;
    nombreC = profondeur;
    nombreClicsCourant = 0;
    selectionne = false;
    boutonActif = 0;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    // Connexions
    connect(bouton, SIGNAL(clicked()), this, SLOT(demarrer()));
    connect(this, SIGNAL(sequenceFin(vector<StatistiquesGomsClics>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsClics(vector<StatistiquesGomsClics>)));

}

void FenetreTestGomsClics::demarrer() {

    bouton->hide();
    chronometre->start();

    // Création layout
    QGridLayout *gridLayout = new QGridLayout(this);

    // Création des boutons
    for (int i = 0; i < 16; ++i) {

        grille[i] = new QPushButton("Pas ici", this);
        grille[i]->setFixedSize(80,80);
        grille[i]->setDisabled(true);
        connect(grille[i], SIGNAL(clicked()), this, SLOT(changer()));

        gridLayout->addWidget(grille[i], i%4, i/4);

    }

    // Choix d'un bouton actif
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    boutonActif = qrand()%16;
    grille[boutonActif]->setEnabled(true);
    grille[boutonActif]->setText("Celui-ci");

    setLayout(gridLayout);

}

void FenetreTestGomsClics::changer() {

    if (selectionne) { //2eme clic

        // On enlève l'ancien
        grille[boutonActif]->setDown(false);
        grille[boutonActif]->setDisabled(true);
        grille[boutonActif]->setText("Pas ici");

        // Ajout aux stats :
        statistiquesGomsClics.push_back(StatistiquesGomsClics(param2, param1, param3, boutonActif, chronometre->elapsed()));

        // On met un nouveau
        boutonActif = qrand()%16;
        grille[boutonActif]->setEnabled(true);
        grille[boutonActif]->setText("Celui-ci");
        selectionne = false;

        chronometre->restart();
        nombreClicsCourant++;

    }

    else {

        grille[boutonActif]->setDown(true);
        selectionne = true;

    }

    if (nombreClicsCourant == nombreC) { // fin

        emit sequenceFin(statistiquesGomsClics);

    }
}
