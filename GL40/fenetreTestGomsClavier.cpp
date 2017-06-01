#include "fenetreTestGomsClavier.h"

#include <QDebug>
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
        grille[i]->setAttribute(Qt::WA_TransparentForMouseEvents);//Désactive clic par souris

        gridLayout->addWidget(grille[i], i%4, i/4);

    }

    // Choix d'un bouton actif
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    boutonHasard = qrand()%16;

    QString styleTemp = *style;
    grille[boutonHasard]->setText("Celui-ci");
    grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank","Green"));//mise en forme bouton hasard

    styleTemp = *style;;
    grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank","LightBlue"));//mise en forme bouton actif (par défaut le premier est celui en haut à gauche)

    setLayout(gridLayout);

}

void FenetreTestGomsClavier::keyPressEvent(QKeyEvent *event) {

    QString styleTemp = *style;

    if(event->isAccepted())
    {

        grille[boutonActif]->setStyleSheet(""); //efface le style du bouton qui vient d'être quitté

        switch (event->key())
        {

        case Qt::Key_Right : // Si on appuie sur la flèche de droite on change de colonne => on avance de 4 dans le tableau
            {
                if((boutonActif / 4) != 3)
                    boutonActif += 4;

                break;
            }

        case Qt::Key_Left : // Appuie sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                if((boutonActif / 4) != 0)
                    boutonActif -= 4;

                break;
            }

        case Qt::Key_Down : // Appuie sur la flèche du bas : recule d'une colonne -4 pour l'index
            {
                if((boutonActif % 4)  != 3)
                    boutonActif += 1;

                break;
             }

        case Qt::Key_Up : // Appuie sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                if((boutonActif % 4) != 0 )
                    boutonActif -= 1;

                break;
            }

        case Qt::Key_Return :
            {
                if (boutonActif == boutonHasard) //si on est sur le bon bouton au moment d'appuyer sur Entrer
                {

                // On reste à la même position
                grille[boutonActif]->setText("Pas ici");
                grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank","LightBlue"));//le bouton cible devient un simple bouton actif

                // Ajout aux stats :
                statistiquesGomsClavier.push_back(StatistiquesGomsClavier(param2, param1, param3, boutonActif, chronometre->elapsed()));

                // On met un nouveau
                boutonHasard = qrand()%16;

                grille[boutonHasard]->setText("Celui-ci");
                styleTemp = *style;
                grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank","Green"));

                chronometre->restart();
                nombreClicsCourant++;

                }

                if (nombreClicsCourant == nombreC) // fin
                    emit sequenceFin(statistiquesGomsClavier);

            }

        default : break;

        }

        styleTemp = *style;
        grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank","Green"));

        styleTemp = *style;
        grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank","LightBlue"));


    }
}