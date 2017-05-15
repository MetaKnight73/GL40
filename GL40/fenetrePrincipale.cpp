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
    newFitts = new QAction("Loi de Fitts", this);
    nouveau->addAction(newFitts);
    newGoms1 = new QAction("Goms-Keystroke avec saisie de texte", this);
    nouveau->addAction(newGoms1);
    newGoms2 = new QAction("Goms-Keystroke avec clics", this);
    nouveau->addAction(newGoms2);

    about = new QAction("À propos de nous", this);
    fermer = new QAction("Quitter", this);

    menuFile->addMenu(nouveau);
    menuFile->insertSeparator(newFitts);
    menuFile->addAction(about);
    menuFile->addAction(fermer);

    // On initialise ici la fenêtre des options pour les paramètres de l'application
    fenetreOptions = new FenetreOptions;

    // Les connexions
    connect(newFitts, SIGNAL(triggered()), this, SLOT(afficheFenetreOptions()));
    connect(about, SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(btnFitts, SIGNAL(clicked()), this, SLOT(afficheFenetreOptions()));
    connect(fermer, SIGNAL(triggered()), this, SLOT(close()));

}

// Méthode appelée pour l'affichage de la fenêtre avec les paramètres de l'application
void FenetrePrincipale::afficheFenetreOptions() {

    fenetreOptions->setModal(true);

    // Si on clique sur valider dans la fenêtre d'options, on va ouvrir la fenêtre avec le test
    if(fenetreOptions->exec() == QDialog::Accepted) {
        setCentralWidget(new FenetreTest(fenetreOptions->getNbClics(), this, fenetreOptions->getParametre1(), fenetreOptions->getParametre2()));
    }

}

// Méthode appelée quand quand le test est fini, qui affiche la fenêtre des stats
void FenetrePrincipale::afficheFenetreStatistiques(std::vector<Statistiques> statistiques) {

    fenetreStatistiques = new FenetreStatistiques(statistiques);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiques->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptions()));

    setCentralWidget(fenetreStatistiques);

}

// Méthode appelée pour l'affichage de la boîte de dialogue "A propos"
void FenetrePrincipale::aPropos() {

    QMessageBox::about(this->parentWidget(), "A propos de nous", "Ce projet a été réalisé par Nicolas Hergenroether, Kieran Molina et Vincent Yucel dans le cadre de l'UV GL40 de l'UTBM.");

}
