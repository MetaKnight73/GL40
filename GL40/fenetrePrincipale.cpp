#include "fenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent) {

    // Taille fixe à 1280x720
    setFixedSize(1280, 720);

    // Layout de la page
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(25);

    // Widget central de la page
    QWidget *middle = new QWidget;
    middle->setLayout(layout);
    setCentralWidget(middle);

    // Label du titre
    QLabel *label = new QLabel("Loi de Fitts et Goms-Keystroke");
    label->setFont(QFont("Arial Black", 32));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    // Label de l'énoncé
    QLabel *label2 = new QLabel("Ceci est un programme permettant d'effectuer des tests afin de comparer les résultats théoriques de plusieurs tests connus tels que la loi de Fitts et Goms-Keystroke avec les valeurs récoltées manuellement lors de ces tests.");
    label2->setWordWrap(true);
    label2->setAlignment(Qt::AlignCenter);

    layout->addWidget(label2);

    // Bouton servant à lancer l'application (la partie fitts)
    btnFitts = new QPushButton("Loi de Fitts");
    btnFitts->setFixedSize(350, 75);
    layout->addWidget(btnFitts, 0, Qt::AlignCenter);

    // Bouton servant à lancer l'application (la partie goms 1)
    btnGoms1 = new QPushButton("Goms-Keystroke (saisie de texte)");
    btnGoms1->setFixedSize(350, 75);
    layout->addWidget(btnGoms1, 0, Qt::AlignCenter);

    // Bouton servant à lancer l'application (la partie goms 2)
    btnGoms2 = new QPushButton("Goms-Keystroke (clics)");
    btnGoms2->setFixedSize(350, 75);
    layout->addWidget(btnGoms2, 0, Qt::AlignCenter);

    // Bouton servant à lancer l'application (la partie goms 3)
    btnGoms3 = new QPushButton("Goms-Keystroke (version bash)");
    btnGoms3->setFixedSize(350, 75);
    layout->addWidget(btnGoms3, 0, Qt::AlignCenter);

    // Bouton servant à lancer l'application (la partie goms 4)
    btnGoms4 = new QPushButton("Goms-Keystroke (flèches)");
    btnGoms4->setFixedSize(350, 75);
    layout->addWidget(btnGoms4, 0, Qt::AlignCenter);

    // Menu bar au sommet
    menuFile = menuBar()->addMenu("Fichier");

    // Actions de la barre
    nouveau = new QMenu("Nouveau", this);
    newFitts = new QAction("Loi de Fitts", nouveau);
    nouveau->addAction(newFitts);
    newGoms1 = new QAction("Goms-Keystroke avec saisie de texte", nouveau);
    nouveau->addAction(newGoms1);
    newGoms2 = new QAction("Goms-Keystroke avec clics", nouveau);
    nouveau->addAction(newGoms2);
    newGoms3 = new QAction("Goms-Keystroke avec saisie du chemin", nouveau);
    nouveau->addAction(newGoms3);
    newGoms4 = new QAction("Goms-Keystroke avec les flèches", nouveau);
    nouveau->addAction(newGoms4);

    about = new QAction("À propos de nous", this);
    fermer = new QAction("Quitter", this);

    menuFile->addMenu(nouveau);
    menuFile->insertSeparator(newFitts);
    menuFile->addAction(about);
    menuFile->addAction(fermer);

    // On initialise ici les fenêtres des options pour les paramètres de l'application
    fenetreOptionsFitts = new FenetreOptionsFitts;
    fenetreOptionsGomsSaisieTexte = new FenetreOptionsGomsSaisieTexte;
    fenetreOptionsGomsClics = new FenetreOptionsGomsClics;
    fenetreOptionsGomsBash = new FenetreOptionsGomsBash;
    fenetreOptionsGomsClavier = new FenetreOptionsGomsClavier;

    // Les connexions
    connect(newFitts, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsFitts()));
    connect(newGoms1, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));
    connect(newGoms2, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsClics()));
    connect(newGoms3, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsBash()));
    connect(newGoms4, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsClavier()));

    connect(btnFitts, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsFitts()));
    connect(btnGoms1, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));
    connect(btnGoms2, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClics()));
    connect(btnGoms3, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsBash()));
    connect(btnGoms4, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClavier()));

    connect(about, SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(fermer, SIGNAL(triggered()), this, SLOT(close()));

}

// Méthode appelée pour l'affichage de la fenêtre avec les paramètres de l'application
void FenetrePrincipale::afficheFenetreOptionsFitts() {

    fenetreOptionsFitts->setModal(true);

    // Si on clique sur valider dans la fenêtre d'options, on va ouvrir la fenêtre avec le test
    if(fenetreOptionsFitts->exec() == QDialog::Accepted) {

        setCentralWidget(new FenetreTestFitts(fenetreOptionsFitts->getNbClics(), this, fenetreOptionsFitts->getParametre1(), fenetreOptionsFitts->getParametre2()));

    }

}

// Méthode appelée pour l'affichage de la fenêtre avec les paramètres de l'application
void FenetrePrincipale::afficheFenetreOptionsGomsSaisieTexte() {

    fenetreOptionsGomsSaisieTexte->setModal(true);

    // Si on clique sur valider dans la fenêtre d'options, on va ouvrir la fenêtre avec le test
    if(fenetreOptionsGomsSaisieTexte->exec() == QDialog::Accepted) {

        setCentralWidget(new FenetreTestGomsSaisieTexte(fenetreOptionsGomsSaisieTexte->getNbMots(), this, fenetreOptionsGomsSaisieTexte->getParametre2(), fenetreOptionsGomsSaisieTexte->getParametre1()));

    }

}

// Méthode appelée pour l'affichage de la fenêtre avec les paramètres de l'application
void FenetrePrincipale::afficheFenetreOptionsGomsClics() {

    fenetreOptionsGomsClics->setModal(true);

    // Si on clique sur valider dans la fenêtre d'options, on va ouvrir la fenêtre avec le test
    if(fenetreOptionsGomsClics->exec() == QDialog::Accepted) {

        setCentralWidget(new FenetreTestGomsClics(fenetreOptionsGomsClics->getProfondeur(), this, fenetreOptionsGomsClics->getParametre1(), fenetreOptionsGomsClics->getParametre2(), fenetreOptionsGomsClics->getParametre3()));

    }

}

//Méthode appelée pour paramétrer le test Goms Bash
void FenetrePrincipale::afficheFenetreOptionsGomsBash() {

    fenetreOptionsGomsBash->setModal(true);

    //Le test s'ouvre sur clic au bouton gauche (Accepted) dans la fenêtre d'options via le connect() au QDialog
    if(fenetreOptionsGomsBash->exec() == QDialog::Accepted) {

        setCentralWidget(new FenetreTestGomsBash(fenetreOptionsGomsBash->getLongRep(), this, fenetreOptionsGomsBash->getParametre2(),fenetreOptionsGomsBash->getParametre1()));
    }
}

//Méthode appelée pour paramétrer le test Goms Clavier
void FenetrePrincipale::afficheFenetreOptionsGomsClavier() {

    fenetreOptionsGomsClavier->setModal(true);

    //Le test s'ouvre sur clic au bouton gauche (Accepted) dans la fenêtre d'options via le connect() au QDialog
    if(fenetreOptionsGomsClavier->exec() == QDialog::Accepted) {

        setCentralWidget(new FenetreTestGomsClavier(fenetreOptionsGomsClavier->getProfondeur(), this, fenetreOptionsGomsClavier->getParametre1(), fenetreOptionsGomsClavier->getParametre2()));
    }

}

// Méthode appelée quand quand le test est fini, qui affiche la fenêtre des stats
void FenetrePrincipale::afficheFenetreStatistiquesFitts(vector<StatistiquesFitts> statistiquesFitts) {

    fenetreStatistiquesFitts = new FenetreStatistiquesFitts(statistiquesFitts);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesFitts->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsFitts()));

    setCentralWidget(fenetreStatistiquesFitts);

}

// Méthode appelée quand quand le test est fini, qui affiche la fenêtre des stats
void FenetrePrincipale::afficheFenetreStatistiquesGomsSaisieTexte(vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte) {

    fenetreStatistiquesGomsSaisieTexte = new FenetreStatistiquesGomsSaisieTexte(statistiquesGomsSaisieTexte);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsSaisieTexte->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));

    setCentralWidget(fenetreStatistiquesGomsSaisieTexte);

}

// Méthode appelée quand quand le test est fini, qui affiche la fenêtre des stats
void FenetrePrincipale::afficheFenetreStatistiquesGomsClics(vector<StatistiquesGomsClics> statistiquesGomsClics) {

    fenetreStatistiquesGomsClics = new FenetreStatistiquesGomsClics(statistiquesGomsClics);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsClics->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClics()));

    setCentralWidget(fenetreStatistiquesGomsClics);

}

void FenetrePrincipale::afficheFenetreStatistiquesGomsBash(vector<StatistiquesGomsBash> statistiquesGomsBash) {

    fenetreStatistiquesGomsBash = new FenetreStatistiquesGomsBash(statistiquesGomsBash);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsBash->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsBash()));

    setCentralWidget(fenetreStatistiquesGomsBash);

}

void FenetrePrincipale::afficheFenetreStatistiquesGomsClavier(vector<StatistiquesGomsClavier> statistiquesGomsClavier) {

    fenetreStatistiquesGomsClavier = new FenetreStatistiquesGomsClavier(statistiquesGomsClavier);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsClavier->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClavier()));

    setCentralWidget(fenetreStatistiquesGomsClavier);

}

// Méthode appelée pour l'affichage de la boîte de dialogue "A propos"
void FenetrePrincipale::aPropos() {

    QMessageBox::about(this->parentWidget(), "A propos de nous", "Ce projet a été réalisé par Nicolas Hergenroether, Kieran Molina et Vincent Yucel dans le cadre de l'UV GL40 de l'UTBM.");

}
