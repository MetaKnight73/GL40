#include "fenetreTestGomsClavier.h"

FenetreTestGomsClavier::FenetreTestGomsClavier(int profondeur, QWidget *parent, double parametre1, double parametre2, bool param3) : QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setStyleSheet(QString("font-weight: bold; font-size: 16px; text-align: center;"));
    bouton->setGeometry(515, 310, 250, 100);

    //Texte d'informations
    info = new QLabel("Dans ce test, vous devez naviguer avec les flèches ou la touche \"Tab\" et choisir le bouton adéquat avec \"Entrée\".", this);
    info->setGeometry(40, 390, 1280, 100);
    info->setFont(QFont("Arial", 18, -1, true));

    // On initialise les paramètres
    param1 = parametre1;
    param2 = parametre2;
    retourDepart = param3;
    deplacementX = 0;
    deplacementY = 0;
    nombreC = profondeur;
    nombreClicsCourant = 0;
    boutonActif = 0;
    boutonHasard = 0;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    //On autorise l'utilisation du clavier
    setFocusPolicy(Qt::TabFocus);

    //Création du style général du bouton (cible & courant)
    style = new QString ("background-color : Blank;"
             "border-width : 2px;"
             "border-style : outline;"
             "color : black;");

    bouton->setFocus();
    bouton->setDefault(true);

    // Connexions
    connect(bouton, SIGNAL(clicked(bool)), this, SLOT(demarrer()));
    connect(this, SIGNAL(sequenceFin(vector<StatistiquesGomsClavier>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsClavier(vector<StatistiquesGomsClavier>)));

}

void FenetreTestGomsClavier::demarrer() {

    bouton->hide();
    info->setGeometry(524, 610, 540, 100);
    info->setText(QString("(\"Echap\" pour quitter)"));
    info->setStyleSheet(QString("color: red"));

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
    grille[boutonHasard]->setText("CELUI-CI");
    grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank", "Green")); // Mise en forme bouton hasard
    grille[boutonHasard]->setStyleSheet(styleTemp.replace("black", "white"));

    styleTemp = *style;;
    grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank", "LightBlue")); // Mise en forme bouton actif (par défaut le premier est celui en haut à gauche)
    grille[boutonActif]->setStyleSheet(styleTemp.replace("black", "white"));

    setLayout(gridLayout);
    chronometre->start();

}

void FenetreTestGomsClavier::retournerMenu() {

    parentWidget()->close();
    FenetrePrincipale *fenetre = new FenetrePrincipale;
    fenetre->statusBar()->setSizeGripEnabled(false);
    fenetre->show();
    QRect rectangleFenetre = QApplication::desktop()->screenGeometry();
    int x = (rectangleFenetre.width()-fenetre->width()) / 2;
    int y = (rectangleFenetre.height()-fenetre->height()) / 2;
    fenetre->move(x, y);

}

void FenetreTestGomsClavier::keyPressEvent(QKeyEvent *event) {

    QString styleTemp = *style;

    if(event->isAccepted()) {

        switch (event->key()) {

        case Qt::Key_Right :
        case Qt::Key_Tab :    // Si on appuie sur la flèche de droite ou tab on change de colonne => on avance de 4 dans le tableau
            {
                grille[boutonActif]->setStyleSheet(""); // Efface le style du bouton qui vient d'être quitté
                if((boutonActif / 4) != 3)
                    boutonActif += 4;
                else if(boutonActif != 15)
                    boutonActif -= 11;
                else
                    boutonActif = 0;

                break;
            }

        case Qt::Key_Left : // Appui sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                grille[boutonActif]->setStyleSheet(""); // Efface le style du bouton qui vient d'être quitté
                if((boutonActif / 4) == 0 && boutonActif != 0)
                    boutonActif += 11;
                else if((boutonActif / 4) != 0)
                    boutonActif -=4;

                break;
            }

        case Qt::Key_Down : // Appui sur la flèche du bas : recule d'une colonne -4 pour l'index
            {
                grille[boutonActif]->setStyleSheet(""); // Efface le style du bouton qui vient d'être quitté
                if((boutonActif % 4)  != 3)
                    boutonActif += 1;

                break;
             }

        case Qt::Key_Up : // Appui sur la flèche de gauche : recule d'une colonne -4 pour l'index
            {
                grille[boutonActif]->setStyleSheet(""); // Efface le style du bouton qui vient d'être quitté
                if((boutonActif % 4) != 0 )
                    boutonActif -= 1;

                break;
            }

        case Qt::Key_Escape:
            {
                retournerMenu();

                break;
            }

        case Qt::Key_Return :
        case Qt::Key_Enter :
            {
                if (boutonActif == boutonHasard) // Si on est sur le bon bouton au moment d'appuyer sur Entrer
                {
                    grille[boutonActif]->setText("Pas ici");

                    if(retourDepart) {
                        // On reste à la même position
                        grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank", "LightBlue")); // Le bouton cible devient un simple bouton actif
                        grille[boutonActif]->setStyleSheet(styleTemp.replace("black", "white"));

                        deplacementX = boutonHasard % 4;
                        deplacementY = boutonHasard / 4;

                    }
                    else if(nombreClicsCourant == 0) {
                        deplacementX = boutonHasard % 4;
                        deplacementY = boutonHasard / 4;
                    }

                    // Ajout aux stats
                    statistiquesGomsClavier.push_back(StatistiquesGomsClavier(param1, param2, deplacementX, deplacementY, boutonActif, chronometre->elapsed()));

                    // On met un nouveau
                    if(retourDepart) {
                        boutonHasard = qrand() % 16;
                        grille[boutonActif]->setStyleSheet("");
                        boutonActif = 0;
                    }
                    else {
                        int colonneDepart = boutonHasard % 4;
                        int ligneDepart = boutonHasard / 4;
                        boutonHasard = qrand() % 16;
                        int colonneArrivee = boutonHasard % 4;
                        int ligneArrivee = boutonHasard / 4;

                        deplacementX = abs(colonneArrivee - colonneDepart);
                        deplacementY = abs(ligneArrivee - ligneDepart);
                    }

                    grille[boutonHasard]->setText("CELUI-CI");
                    styleTemp = *style;
                    grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank", "Green"));
                    grille[boutonHasard]->setStyleSheet(styleTemp.replace("black", "white"));

                    chronometre->restart();
                    nombreClicsCourant++;

                }

                if (nombreClicsCourant == nombreC) { // Fin
                    statistiquesGomsClavier[0].setDate();
                    emit sequenceFin(statistiquesGomsClavier);
                }

            }

        default : break;

        }

        if(event->key() != Qt::Key_Escape) {
            styleTemp = *style;
            grille[boutonHasard]->setStyleSheet(styleTemp.replace("Blank", "Green"));
            grille[boutonHasard]->setStyleSheet(styleTemp.replace("black", "white"));

            styleTemp = *style;
            grille[boutonActif]->setStyleSheet(styleTemp.replace("Blank", "LightBlue"));
            grille[boutonActif]->setStyleSheet(styleTemp.replace("black", "white"));
        }
    }
}
