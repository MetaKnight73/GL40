#include "fenetrePrincipale.h"
#include <QGridLayout>
#include <QBoxLayout>
#include <QWidget>
#include <QLabel>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent) {

    // Taille fixe à 1280x720, envisager une adaptation
    setFixedSize(1280, 720);

    // Layout de la page
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(50);

    // Widget central de la page
    QWidget *middle = new QWidget;
    middle->setLayout(layout);
    setCentralWidget(middle);

    // Label du titre
    QLabel *label = new QLabel("Loi de Fitts et Goms-Keystroke");
    label->setFont(QFont("Arial Black", 32));
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    // Label de l'énoncé (première partie)
    QLabel *label2 = new QLabel("Ceci est un programme permettant d'effectuer des tests afin de comparer les résultats théoriques de plusieurs tests connus tels que la loi de Fitts et Goms-Keystroke avec les valeurs récoltées manuellement lors de ces tests.");
    label2->setWordWrap(true);
    label2->setAlignment(Qt::AlignCenter);

    layout->addWidget(label2);

    // Bouton servant à lancer l'application (la partie fitts)
    btnFitts = new QPushButton("Loi de Fitts");
    btnFitts->setFixedSize(400, 75);
    layout->addWidget(btnFitts, 0, Qt::AlignCenter);

    // Bouton servant à lancer l'application (la partie goms 1)
    btnGoms1 = new QPushButton("Goms-Keystroke (saisie de texte)");
    btnGoms1->setFixedSize(400, 100);
    layout->addWidget(btnGoms1, 0, Qt::AlignCenter);

    // Bouton servant à lancer l'application (la partie goms 2)
    btnGoms2 = new QPushButton("Goms-Keystroke (clics)");
    btnGoms2->setFixedSize(400, 125);
    layout->addWidget(btnGoms2, 0, Qt::AlignCenter);

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

    about = new QAction("À propos de nous", this);
    fermer = new QAction("Quitter", this);

    menuFile->addMenu(nouveau);
    menuFile->insertSeparator(newFitts);
    menuFile->addAction(about);
    menuFile->addAction(fermer);

    // On initialise ici la fenêtre des options pour les paramètres de l'application
    fenetreOptionsFitts = new FenetreOptionsFitts;
    fenetreOptionsGomsSaisieTexte = new FenetreOptionsGomsSaisieTexte;
    fenetreOptionsGomsClics = new FenetreOptionsGomsClics;

    // Les connexions
    connect(newFitts, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsFitts()));
    connect(newGoms1, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));
    connect(newGoms2, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsClics()));
    connect(about, SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(btnFitts, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsFitts()));
    connect(btnGoms1, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));
    connect(btnGoms2, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClics()));
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
        //setCentralWidget(new FenetreTestGomsClics(fenetreOptionsGomsClics->getProfondeur(), this, fenetreOptionsGomsClics->getParametre2(), fenetreOptionsGomsClics->getParametre1()));
        std::cout << "Modifier FenetrePrincipale::afficheFenetreOptionsClics() après avoir créer la classe de test GomsClics ! - ligne 118?" << std::endl;
    }

}

// Méthode appelée quand quand le test est fini, qui affiche la fenêtre des stats
void FenetrePrincipale::afficheFenetreStatistiquesFitts(std::vector<StatistiquesFitts> statistiquesFitts) {

    fenetreStatistiquesFitts = new FenetreStatistiquesFitts(statistiquesFitts);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesFitts->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsFitts()));

    setCentralWidget(fenetreStatistiquesFitts);

}

// Méthode appelée quand quand le test est fini, qui affiche la fenêtre des stats
void FenetrePrincipale::afficheFenetreStatistiquesGomsSaisieTexte(std::vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte) {

    fenetreStatistiquesGomsSaisieTexte = new FenetreStatistiquesGomsSaisieTexte(statistiquesGomsSaisieTexte);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsSaisieTexte->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));

    setCentralWidget(fenetreStatistiquesGomsSaisieTexte);

}

// Méthode appelée pour l'affichage de la boîte de dialogue "A propos"
void FenetrePrincipale::aPropos() {

    QMessageBox::about(this->parentWidget(), "A propos de nous", "Ce projet a été réalisé par Nicolas Hergenroether, Kieran Molina et Vincent Yucel dans le cadre de l'UV GL40 de l'UTBM.");

}
