#include "fenetreTestFitts.h"

FenetreTestFitts::FenetreTestFitts(int nombreClics, QWidget *parent, double parametre1, double parametre2) : QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setStyleSheet(QString("font-weight: bold; font-size: 16px; text-align: center;"));
    bouton->setGeometry(515, 310, 250, 100);

    // Texte d'informations
    info = new QLabel("Dans ce test, vous devez simplement cliquer les boutons lorsqu'ils apparaissent.", this);
    info->setGeometry(220, 390, 1280, 100);
    info->setFont(QFont("Arial", 18, -1, true));

    // On initialise les paramètres
    param1= parametre1;
    param2 = parametre2;
    nombreC = nombreClics;
    nombreClicsCourant = 0;
    sourisBougeeDebut = false;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    // On autorise la détection permanente des évènements souris, car sinon on n'aurait une détection qu'au clic
    setMouseTracking(true);

    bouton->setFocus();
    bouton->setDefault(true);

    // Connexions
    connect(bouton, SIGNAL(clicked()), this, SLOT(deplacerBoutonClic()));
    connect(this, SIGNAL(sequenceFin(vector<StatistiquesFitts>)), this->parent(), SLOT(afficheFenetreStatistiquesFitts(vector<StatistiquesFitts>)));

}

void FenetreTestFitts::mouseMoveEvent(QMouseEvent *) {

    if(sourisBougeeDebut == false && nombreClicsCourant != 0) {

        chronometre->start();

    }

    sourisBougeeDebut = true;

}

void FenetreTestFitts::keyPressEvent(QKeyEvent *event) {

    if(event->isAccepted()) {

        switch (event->key()) {

            case Qt::Key_Escape :
                retournerMenu();
            break;
        }

    }
}

void FenetreTestFitts::retournerMenu() {

    parentWidget()->close();
    FenetrePrincipale *fenetre = new FenetrePrincipale;
    fenetre->statusBar()->setSizeGripEnabled(false);
    fenetre->show();
    QRect rectangleFenetre = QApplication::desktop()->screenGeometry();
    int x = (rectangleFenetre.width()-fenetre->width()) / 2;
    int y = (rectangleFenetre.height()-fenetre->height()) / 2;
    fenetre->move(x, y);

}


void FenetreTestFitts::deplacerBoutonClic() {

    // Verification bouton rond
    QPoint mousePos = bouton->mapFromGlobal(QCursor::pos());
    if (sqrt(pow(mousePos.x()-(bouton->width()/2), 2) + pow(mousePos.y()-(bouton->height()/2), 2)) >= bouton->width()/2
            && nombreClicsCourant>0) return;

    // On change le texte du bouton qu'on va déplacer
    if(nombreClicsCourant == 0) {
        bouton->setText("CLIQUEZ ICI !");
        bouton->setDefault(false);

        info->setGeometry(524, 610, 540, 100);
        info->setStyleSheet(QString("color: red;"));
        info->setText(QString("(\"Echap\" pour quitter)"));
    }

    // On récupère le temps de départ
    QTime now = QTime::currentTime();
    qsrand(now.msec());

    // Qsrand pour reset l'aléatoire (efficace)
    // On prend une largeur aléatoire et la hauteur devient la largeur pour avoir des carrés
    int largeurBouton = qrand()%250+70;

    int x = 0;
    int y = 0;

    // On déplace le bouton selon l'axe X, jusqu'à un minimum de 0 (garanti par le test)
    int tempx = (qrand()%1280) - largeurBouton;
    if(tempx >= 0) {

        x = tempx;

    }

    // On déplace le bouton selon l'axe Y, jusqu'à un minimum de 0 (garanti par le test)
    int tempy = (qrand()%720) - largeurBouton;
    if(tempy >= 0) {

        if(tempy+largeurBouton >= 670) {

            y = 670-largeurBouton;

        }

        else {

           y = tempy;

        }

    }

    if(((tempx + largeurBouton) >= 524) && (tempx < 1064) && ((tempy + largeurBouton) >= 610)) {
        y -= 110;
    }

    // On déplace le bouton
    bouton->setGeometry(x, y, largeurBouton, largeurBouton);

    // On fait des boutons avec des coins plus ou moins arrondis (pour qu'il s'agisse de cercles plus ou moins grands)
    QString feuilleStyle = "border-radius: ";

    QString s = QString::number((largeurBouton/2)-1);
    feuilleStyle += s;
    feuilleStyle += "px; background-color: green; color: white;";

    bouton->setStyleSheet(feuilleStyle);

    // On incrémente le nombre de clics courant
    nombreClicsCourant++;

    // On récupère la position initiale
    QPoint positionInitiale = mapFromGlobal(QCursor::pos());

    // Si on est au moins au deuxième clic (soit le premier clic du test)
    if(nombreClicsCourant >= 2) {

        // On ajoute les informations dans le vecteur des stats
        statistiquesFitts.push_back(StatistiquesFitts(positionInitiale, QPoint(x, y), largeurBouton, chronometre->elapsed(), param1, param2));

    }

    // Si on est après le dernier clic
    if(nombreClicsCourant - 1 == nombreC) {

        // On calcule les valeurs nécessaires
        for(unsigned int i = 0; i < statistiquesFitts.size(); i++) {

            statistiquesFitts[i].calculDistance();
            statistiquesFitts[i].calculTempsFitts();

        }

        statistiquesFitts[0].setDate();

        emit sequenceFin(statistiquesFitts);
    }

    sourisBougeeDebut = false;

}
