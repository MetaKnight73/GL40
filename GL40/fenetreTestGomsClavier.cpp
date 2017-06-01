#include "fenetreTestGomsClavier.h"

FenetreTestGomsClavier::FenetreTestGomsClavier(int profondeur, QWidget *parent, double parametre1, double parametre2, double parametre3) : QWidget(parent)
{
    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    //Texte d'informations
    info = new QLabel("Dans ce test vous devez naviguer avec les flèches et choisir le bouton adequat avec \"Entrée\" ",this);
    info->setGeometry(250,380,900,100);
    info->setFont(QFont("Arial", 15, -1, true));

    // On initialise les paramètres
    param1 = parametre1;
    param2 = parametre2;
    param3 = parametre3;
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
        grille[i]->setAttribute(Qt::WA_TransparentForMouseEvents);//Désactive clic par souris

        gridLayout->addWidget(grille[i], i%4, i/4);

    }

    // Choix d'un bouton actif
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    boutonHasard = qrand()%16;
    grille[boutonHasard]->setText("Celui-ci");
    grille[boutonHasard]->setDisabled(false);//On active le bouton choisi au hasard

    grille[boutonActif]->setDisabled(false);//On active le premier bouton en haut à gauche pour le test

    setLayout(gridLayout);

}

void FenetreTestGomsClavier::keyPressEvent(QKeyEvent *event) {

    if(event->isAccepted())
    {
        switch (event->key())
        {

        case Qt::Key_Right : // Si on appuie sur la flèche de droite on change de colonne => on avance de 4 dans le tableau
            {
                if((boutonActif / 4) != 3)
                {
                    grille[boutonActif]->setEnabled(false);
                    boutonActif += 4;

                    grille[boutonActif]->setEnabled(true);
                }
                break;
            }

        case Qt::Key_Left : // Appuie sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                if((boutonActif / 4) != 0)
                {
                    grille[boutonActif]->setEnabled(false);
                    boutonActif -= 4;

                    grille[boutonActif]->setEnabled(true);
                }
                break;
            }

        case Qt::Key_Down : // Appuie sur la flèche du bas : recule d'une colonne -4 pour l'index
            {
                if((boutonActif % 4)  != 3)
                {
                    grille[boutonActif]->setEnabled(false);
                    boutonActif += 1;

                    grille[boutonActif]->setEnabled(true);
                }
                break;
             }

        case Qt::Key_Up : // Appuie sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                if((boutonActif % 4) != 0 )
                {
                    grille[boutonActif]->setEnabled(false);
                    boutonActif -= 1;

                    grille[boutonActif]->setEnabled(true);
                }
                break;
            }

        case Qt::Key_Return :
            {
                if (boutonActif == boutonHasard) //si on est sur le bon bouton au moment d'appuyer sur Entrer
                {

                // On reste à la même position
                grille[boutonActif]->setText("Pas ici");

                // Ajout aux stats :
                statistiquesGomsClavier.push_back(StatistiquesGomsClavier(param2, param1, param3, boutonActif, chronometre->elapsed()));

                // On met un nouveau
                boutonHasard = qrand()%16;
                grille[boutonHasard]->setText("Celui-ci");

                chronometre->restart();
                nombreClicsCourant++;

                }

                if (nombreClicsCourant == nombreC) // fin
                    emit sequenceFin(statistiquesGomsClavier);

            }

        default : break;

        }

        grille[boutonHasard]->setEnabled(true);//on active toujours le bouton choisi au hasard
    }
}
