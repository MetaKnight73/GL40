#include "fenetreTestGomsSaisieTexte.h"
#include <time.h>
#include <QString>
#include <QLayout>

FenetreTestGomsSaisieTexte::FenetreTestGomsSaisieTexte(int nombreMots, QWidget *parent, double parametre1, double parametre2) : QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    // On initialise les paramètres
    param1= parametre1;
    param2 = parametre2;
    nombreM = nombreMots;
    nombreMotsValidesCourant = 0;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    //On crée le layout
    layout = new QGridLayout;
    setLayout(layout);

    zoneSaisie = new QLineEdit;
    labelZoneSaisie = new QLabel(QString("Veuillez saisir le texte affiché ci-dessus puis appuyer sur Entrée"), this, 0);

    // Connexions
    connect(bouton, SIGNAL(clicked()), this, SLOT(lancerTest()));
    connect(zoneSaisie, SIGNAL(returnPressed()), this, SLOT(checkWord()));
    //connect(this, SIGNAL(sequenceFin(std::vector<StatistiquesGomsSaisieTexte>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsSaisieTexte(std::vector<StatistiquesGomsSaisieTexte>)));

}

char* FenetreTestGomsSaisieTexte::genererMotCourant(double longueur) {
    srand(time(NULL));
    unsigned int length = (rand() % (int)longueur) + 1;
    char* str = "";

    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    if (length) {
        if(length != 1) {
            --length;
        }
        for (size_t n = 0; n < length; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[length] = '\0';
    }
    return str;
}

void FenetreTestGomsSaisieTexte::lancerTest() {

    // On fait disparaître le bouton
    bouton->hide();

    //On génère le premier mot aléatoire
    motCourant = new QLabel(QString(genererMotCourant(param1)), this, 0);
    layout->addWidget(motCourant, 0, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(labelZoneSaisie, 1, 1, 1, 1, Qt::AlignBottom);
    layout->addWidget(zoneSaisie, 2, 1, 1, 1, Qt::AlignBottom);

    zoneSaisie->setFocus();
}

void FenetreTestGomsSaisieTexte::checkWord() {

    QString texteZoneSaisie = zoneSaisie->text();
    QString texteMotCourant = motCourant->text();

    int x = QString::compare(texteZoneSaisie, texteMotCourant, Qt::CaseSensitive);
    if(!x) {
        nombreMotsValidesCourant++;
        //Gérer le chrono reset + enregistrer les valeurs dans stats goms TODO
        if(nombreMotsValidesCourant < nombreM) {
            zoneSaisie->clear();
            motCourant->setText(QString(genererMotCourant(param1)));
        }
        else {
            //Ouvrir la fenêtre de stats
        }
    }

}
