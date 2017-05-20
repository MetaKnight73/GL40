#include "fenetreTestGomsClics.h"
#include <QLayout>

FenetreTestGomsClics::FenetreTestGomsClics(int profondeur, QWidget *parent, double parametre1, double parametre2, double parametre3): QWidget(parent){

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    // On initialise les paramètres
    param1= parametre1;
    param2 = parametre2;
    param3 = parametre3;
    nombreC = profondeur;
    nombreClicsCourant = 0;
    sourisBougeeDebut = false;
    selectionne = false;
    boutonActif = 0;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    // On autorise la détection permanente des évènements souris, car sinon on n'aurait une détection qu'au clic
    setMouseTracking(true);

    // Connexions
    connect(bouton, SIGNAL(clicked()), this, SLOT(demarrer()));
    connect(this, SIGNAL(sequenceFin(std::vector<StatistiquesGomsClics>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsClics(std::vector<StatistiquesGomsClics>)));

}

void FenetreTestGomsClics::mouseMoveEvent(QMouseEvent *) {

    if(sourisBougeeDebut == false) {
        chronometre->start();
    }

    sourisBougeeDebut = true;

}

void FenetreTestGomsClics::demarrer(){
    bouton->hide();
    //création layout
    QGridLayout *gridLayout = new QGridLayout(this);

    //création des boutons
    for (int i=0; i<16; ++i){
        grille[i] = new QPushButton("pas là", this);
        grille[i]->setFixedSize(80,80);
        grille[i]->setDisabled(true);
        connect(grille[i], SIGNAL(clicked()), this, SLOT(changer()));

        gridLayout->addWidget(grille[i], i%4, i/4);
    }

    //choix d'un bouton actif
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    boutonActif = qrand()%16;
    grille[boutonActif]->setEnabled(true);
    grille[boutonActif]->setText("celui là");

    setLayout(gridLayout);

}

void FenetreTestGomsClics::changer(){
    if (selectionne){ //2eme clic
        // on enlève l'ancien
        grille[boutonActif]->setDown(false);
        grille[boutonActif]->setDisabled(true);
        grille[boutonActif]->setText("pas là");

        //ajout aux stats :
        statistiquesGomsClics.push_back(StatistiquesGomsClics(param2, param1, param3, boutonActif, chronometre->elapsed()));

        // on met un nouveau
        boutonActif = qrand()%16;
        grille[boutonActif]->setEnabled(true);
        grille[boutonActif]->setText("celui là");
        selectionne = false;

        chronometre->restart();
        ++nombreClicsCourant;
    }else{
        grille[boutonActif]->setDown(true);
        selectionne = true;
    }

    if (nombreClicsCourant-1 >= nombreC){ // fin
        emit sequenceFin(statistiquesGomsClics);
    }
}
