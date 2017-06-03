#include "fenetreTestGomsClavier.h"
#include <QDebug>

FenetreTestGomsClavier::FenetreTestGomsClavier(int profondeur, QWidget *parent, double parametre1, double parametre2) : QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    //Texte d'informations
    info = new QLabel("Dans ce test vous devez naviguer avec les flèches et choisir le bouton adequat avec \"Entrée\" ",this);
    info->setGeometry(250, 380, 900, 100);
    info->setFont(QFont("Arial", 15, -1, true));

    // On initialise les paramètres
    param1 = parametre1;
    param2 = parametre2;
    deplacementX = 0;
    deplacementY = 0;
    nombreC = profondeur;
    nombreClicsCourant = 0;
    boutonActif = 0;
    boutonHasard = 0;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    // Connexions
    connect(bouton, SIGNAL(clicked(bool)), this, SLOT(demarrer()));
    connect(this, SIGNAL(sequenceFin(vector<StatistiquesGomsClavier>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsClavier(vector<StatistiquesGomsClavier>)));

    //On autorise l'utilisation du clavier
    setFocusPolicy(Qt::TabFocus);

    //Création du style générale du bouton (cible & courant)
    style = new QString ("background-color : Blank;"
                         "border-width : 2px;"
                         "border-style : outline;"
                         "color : black;");

}

void FenetreTestGomsClavier::demarrer() {

    bouton->hide();
    chronometre->start();
    info->hide();

    // Création layout
    QGridLayout *gridLayout = new QGridLayout(this);

    // Création des boutons
    for (int i = 0; i < 16; ++i) {

        grille[i] = new QPushButton("Pas ici", this);
        grille[i]->setFixedSize(80,80);
        grille[i]->setDisabled(true);
        grille[i]->setAttribute(Qt::WA_TransparentForMouseEvents); // Désactive clic par souris

        gridLayout->addWidget(grille[i], i%4, i/4);

    }

    // Choix d'un bouton actif
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    boutonHasard = qrand()%16;

    QString styleTemp = *style;
    grille[boutonHasard]->setText("Celui-ci");
    grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank", "Green"));//mise en forme bouton hasard

    styleTemp = *style;;
    grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank", "LightBlue"));//mise en forme bouton actif (par défaut le premier est celui en haut à gauche)

    setLayout(gridLayout);

}

void FenetreTestGomsClavier::keyPressEvent(QKeyEvent *event) {

    QString styleTemp = *style;

    if(event->isAccepted()) {

        grille[boutonActif]->setStyleSheet(""); // Efface le style du bouton qui vient d'être quitté

        switch (event->key()) {

        case Qt::Key_Right : // Si on appuie sur la flèche de droite on change de colonne => on avance de 4 dans le tableau
            {
                if((boutonActif / 4) != 3)
                    boutonActif += 4;

                break;
            }

        case Qt::Key_Left : // Appui sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                if((boutonActif / 4) != 0)
                    boutonActif -= 4;

                break;
            }

        case Qt::Key_Down : // Appui sur la flèche du bas : recule d'une colonne -4 pour l'index
            {
                if((boutonActif % 4)  != 3)
                    boutonActif += 1;

                break;
            }

        case Qt::Key_Up : // Appui sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                if((boutonActif % 4) != 0 )
                    boutonActif -= 1;

                break;
            }

        case Qt::Key_Return :
        case Qt::Key_Enter :
            {
                if (boutonActif == boutonHasard) // Si on est sur le bon bouton au moment d'appuyer sur Entrer
                {

                    // On reste à la même position
                    grille[boutonActif]->setText("Pas ici");
                    grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank", "LightBlue")); // Le bouton cible devient un simple bouton actif

                    if(nombreClicsCourant == 0) {
                        deplacementX = boutonHasard % 4;
                        deplacementY = boutonHasard / 4;
                    }

                    // Ajout aux stats
                    statistiquesGomsClavier.push_back(StatistiquesGomsClavier(param1, param2, deplacementX, deplacementY, boutonActif, chronometre->elapsed()));

                    // On met un nouveau
                    int colonneDepart = boutonHasard % 4;
                    int ligneDepart = boutonHasard / 4;
                    boutonHasard = qrand() % 16;
                    int colonneArrivee = boutonHasard % 4;
                    int ligneArrivee = boutonHasard / 4;

                    deplacementX = abs(colonneArrivee - colonneDepart);
                    deplacementY = abs(ligneArrivee - ligneDepart);

                    grille[boutonHasard]->setText("Celui-ci");
                    styleTemp = *style;
                    grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank", "Green"));

                    chronometre->restart();
                    nombreClicsCourant++;

                    if (nombreClicsCourant == nombreC) // fin
                        emit sequenceFin(statistiquesGomsClavier);

                }

                break;

            }
        case Qt::Key_Tab :
            {
                if(boutonActif != 15)
                {
                    if((boutonActif /4) == 3)
                        (boutonActif %= 4) += 1; // on retombe sur le premier bouton tout à gauche de la ligne suivante
                    else
                        boutonActif += 4;
                }
                else
                    boutonActif = 0; //on revient au premier

                break;
             }

        default : break;

        }

        styleTemp = *style;
        grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank", "Green"));

        styleTemp = *style;
        grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank", "LightBlue"));


    }
}
