#include "fenetreTestGomsClics.h"

FenetreTestGomsClics::FenetreTestGomsClics(int profondeur, QWidget *parent, double parametre1, double parametre2, double parametre3): QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    info = new QLabel("Dans ce test, vous devez double-cliquer le bouton correct (en vert).", this);
    info->setGeometry(290, 390, 1280, 100);
    info->setFont(QFont("Arial", 18, -1, true));

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
    info->hide();

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
    grille[boutonActif]->setStyleSheet(QString("background-color : Green; border-width : 2px; border-style : outline; color : white;"));
    grille[boutonActif]->setText("CELUI-CI");

    setLayout(gridLayout);
    chronometre->start();

}

void FenetreTestGomsClics::changer() {

    if (selectionne) { // 2eme clic

        // On enlève l'ancien
        grille[boutonActif]->setStyleSheet(QString(""));
        grille[boutonActif]->setDown(false);
        grille[boutonActif]->setDisabled(true);
        grille[boutonActif]->setText("Pas ici");

        // Ajout aux stats :
        statistiquesGomsClics.push_back(StatistiquesGomsClics(param2, param1, param3, boutonActif, chronometre->elapsed()));

        // On met un nouveau
        boutonActif = qrand()%16;
        grille[boutonActif]->setEnabled(true);
        grille[boutonActif]->setStyleSheet(QString("background-color : Green; border-width : 2px; border-style : outline; color : white;"));
        grille[boutonActif]->setText("CELUI-CI");
        selectionne = false;

        chronometre->restart();
        nombreClicsCourant++;

    }

    else {

        grille[boutonActif]->setDown(true);
        selectionne = true;

    }

    if (nombreClicsCourant == nombreC) { // Fin

        emit sequenceFin(statistiquesGomsClics);

    }
}
