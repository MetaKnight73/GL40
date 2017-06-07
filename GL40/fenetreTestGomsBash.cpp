#include "fenetreTestGomsBash.h"

FenetreTestGomsBash::FenetreTestGomsBash(int longRep, QWidget *parent, double tempsM, int tailleChemin) : QWidget(parent) {

    srand(time(NULL));

    // Bouton pour lancer le test
    bouton = new QPushButton("Commencer", this);
    bouton->setGeometry(515, 310, 250, 100);

    info = new QLabel("Dans ce test, vous devez saisir la commande \"cd\" suivie du premier nom de répertoire affiché puis appuyer sur \"Entrée\".", this);
    info->setGeometry(0, 390, 1280, 100);
    info->setFont(QFont("Arial", 18, -1, true));

    // On initialise les paramètres
    tempsMental= tempsM;
    nbRep = tailleChemin;
    longueurMaxRep = longRep;
    nombreMotsValidesCourant = 0;

    // Chronomètre pour le calcul des temps
    chronometre = new QTime;

    // On crée le layout
    layout = new QGridLayout;

    zoneSaisie = new QLineEdit;
    labelZoneSaisie = new QLabel;

    bouton->setFocus();
    bouton->setDefault(true);

    // Connexions
    connect(bouton, SIGNAL(clicked()), this, SLOT(lancerTest()));
    connect(zoneSaisie, SIGNAL(returnPressed()), this, SLOT(checkWord()));
    connect(this, SIGNAL(sequenceFinGoms(vector<StatistiquesGomsBash>)), this->parent(), SLOT(afficheFenetreStatistiquesGomsBash(vector<StatistiquesGomsBash>)));

}

char* FenetreTestGomsBash::genererMotCourant(int longueur) {

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

void FenetreTestGomsBash::lancerTest() {

    // On fait disparaître le bouton
    bouton->hide();
    info->hide();

    layoutZoneSaisie = new QVBoxLayout;

    //On génère le chemin aléatoire
    char* chemin = new char[longueurMaxRep * nbRep]; //On crée une chaîne de la taille Nombre de répertoire x Longueur max d'un répertoire
    chemin[0] = '\0';

    for(int i = 0; i < nbRep; ++i) {
        strcat(chemin, genererMotCourant(longueurMaxRep));
        if(i != nbRep - 1) {
            strcat(chemin, "/");
        }
    }

    cheminCourant = new QLabel(QString(chemin), this, 0);
    cheminCourant->setFont(QFont("Arial Black", 24));
    labelZoneSaisie->setText(QString("Parcourez le chemin ci-dessus via la commande bash \"cd repertoire\". \"Entrée\" pour valider."));
    labelZoneSaisie->setFont(QFont("Arial", 18, -1, true));
    zoneSaisie->setMaximumHeight(50);
    zoneSaisie->setMinimumHeight(50);
    zoneSaisie->setMaximumWidth(700);
    zoneSaisie->setMinimumWidth(700);
    zoneSaisie->setFont(QFont("Arial Black", 24));

    layoutZoneSaisie->addWidget(labelZoneSaisie, 0, Qt::AlignLeft);
    layoutZoneSaisie->addWidget(zoneSaisie, 0, Qt::AlignCenter);

    layout->addWidget(cheminCourant, 0, 0, 1, 1, Qt::AlignCenter);
    layout->addLayout(layoutZoneSaisie, 1, 0, 1, 1, Qt::AlignCenter);

    setLayout(layout);

    chronometre->start();

    zoneSaisie->setFocus();

}

void FenetreTestGomsBash::checkWord() {

    QString texteZoneSaisie = zoneSaisie->text();
    QStringList listTexteMotCourant = cheminCourant->text().split("/", QString::SkipEmptyParts); // On découpe la chaine contenant le chemin en list de QString
    QString texteMotCourant;

    if(!listTexteMotCourant.isEmpty()) {

        texteMotCourant = listTexteMotCourant.takeFirst(); // On prend le premier élement de la liste qui est le nom du répertoire
        texteMotCourant = QString("cd ") + texteMotCourant; // On ajoute la commande au début du QString

    }

    int x = QString::compare(texteZoneSaisie, texteMotCourant, Qt::CaseSensitive);
    if(!x) {

        nombreMotsValidesCourant++;
        statistiquesGomsBash.push_back(StatistiquesGomsBash(tempsMental, texteMotCourant.length(), chronometre->elapsed()));
        if(nombreMotsValidesCourant < nbRep) {

            zoneSaisie->clear();
            cheminCourant->setText(listTexteMotCourant.join("/"));
            chronometre->restart();

        }

        else {

            emit sequenceFinGoms(statistiquesGomsBash);

        }

    }

}
