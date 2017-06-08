#include "fenetreTestGomsSaisieTexte.h"
#include "fenetrePrincipale.h"

FenetreTestGomsSaisieTexte::FenetreTestGomsSaisieTexte(int nombreMots, QWidget *parent, double tempsM, int longueurMaximale) : QWidget(parent) {

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    // Texte d'informations
    info = new QLabel("Dans ce test, vous devez saisir les mots apparaissant à l'écran puis appuyer sur \"Entrée\".", this);
    info->setGeometry(180, 390, 1280, 100);
    info->setFont(QFont("Arial", 18, -1, true));

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

    bouton->setFocus();
    bouton->setDefault(true);

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

void FenetreTestGomsSaisieTexte::keyPressEvent(QKeyEvent *event) {

    if(event->isAccepted()) {

        switch (event->key()) {

            case Qt::Key_Escape :
                retournerMenu();
            break;
        }

    }
}

void FenetreTestGomsSaisieTexte::retournerMenu() {

    parentWidget()->close();
    FenetrePrincipale *fenetre = new FenetrePrincipale;
    fenetre->statusBar()->setSizeGripEnabled(false);
    fenetre->show();
    QRect rectangleFenetre = QApplication::desktop()->screenGeometry();
    int x = (rectangleFenetre.width()-fenetre->width()) / 2;
    int y = (rectangleFenetre.height()-fenetre->height()) / 2;
    fenetre->move(x, y);

}

void FenetreTestGomsSaisieTexte::lancerTest() {

    // On fait disparaître le bouton
    bouton->hide();
    info->setGeometry(524, 610, 540, 100);
    info->setText(QString("(\"Echap\" pour quitter)"));
    info->setStyleSheet(QString("color: red"));

    layoutZoneSaisie = new QVBoxLayout;

    //On génère le premier mot aléatoire
    motCourant = new QLabel(QString(genererMotCourant(longueurMax)), this, 0);
    motCourant->setFont(QFont("Arial Black", 40));
    labelZoneSaisie->setText(QString("Veuillez saisir le texte affiché ci-dessus puis appuyer sur \"Entrée\"."));
    labelZoneSaisie->setFont(QFont("Arial", 18, -1, true));
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
