#include "fenetrePrincipale.h"

    vector<vector<StatistiquesFitts>> FenetrePrincipale::statsFitts;
    vector<vector<StatistiquesGomsClavier>> FenetrePrincipale::statsGomsClavier;
    vector<vector<StatistiquesGomsClics>> FenetrePrincipale::statsGomsClics;
    vector<vector<StatistiquesGomsSaisieTexte>> FenetrePrincipale::statsGomsTexte;
    vector<vector<StatistiquesGomsBash>> FenetrePrincipale::statsGomsBash;

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
    label2->setFont(QFont("Arial", 18, -1, true));
    label2->setWordWrap(true);
    label2->setAlignment(Qt::AlignCenter);
    layout->addWidget(label2);

    QFrame* line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setMaximumWidth(1260);
    line->setMinimumWidth(1260);
    layout->addWidget(line);

    QVBoxLayout *colonne = new QVBoxLayout;
    colonne->setSpacing(25);

    // Bouton servant à lancer l'application (la partie fitts)
    QHBoxLayout *fittsLayout = new QHBoxLayout;
    fittsLayout->setSpacing(0);
    btnFitts = new QPushButton("Loi de Fitts");
    btnFitts->setStyleSheet(QString("font-weight: bold; font-size: 16px; text-align: center; font-style: italic;"));
    btnFitts->setFixedSize(350, 75);
    fittsLayout->addWidget(btnFitts);
    // Bouton servant à lancer l'application (historique pour la partie fitts)
    btnFittsHisto = new QPushButton();
    btnFittsHisto->setIcon(QIcon(":histo"));
    btnFittsHisto->setFixedSize(75, 75);
    fittsLayout->addWidget(btnFittsHisto);
    // Bouton Info
    btnFittsInfo = new QPushButton();
    btnFittsInfo->setIcon(QIcon(":info"));
    btnFittsInfo->setFixedSize(75, 75);
    fittsLayout->addWidget(btnFittsInfo);

    // Bouton servant à lancer l'application (la partie goms 1)
    QHBoxLayout *gomsTextLayout = new QHBoxLayout;
    gomsTextLayout->setSpacing(0);
    btnGoms1 = new QPushButton("Goms-Keystroke (saisie de texte)");
    btnGoms1->setStyleSheet(QString("font-weight: bold; font-size: 16px; text-align: center; font-style: italic;"));
    btnGoms1->setFixedSize(350, 75);
    gomsTextLayout->addWidget(btnGoms1);
    // Bouton servant à lancer l'application (historique pour la partie goms 1)
    btnGoms1Histo = new QPushButton();
    btnGoms1Histo->setIcon(QIcon(":histo"));
    btnGoms1Histo->setFixedSize(75, 75);
    gomsTextLayout->addWidget(btnGoms1Histo);
    // Bouton Info
    btnGoms1Info = new QPushButton();
    btnGoms1Info->setIcon(QIcon(":info"));
    btnGoms1Info->setFixedSize(75, 75);
    gomsTextLayout->addWidget(btnGoms1Info);

    // Bouton servant à lancer l'application (la partie goms 2)
    QHBoxLayout *gomsClicsLayout = new QHBoxLayout;
    gomsClicsLayout->setSpacing(0);
    btnGoms2 = new QPushButton("Goms-Keystroke (clics)");
    btnGoms2->setStyleSheet(QString("font-weight: bold; font-size: 16px; text-align: center; font-style: italic;"));
    btnGoms2->setFixedSize(350, 75);
    gomsClicsLayout->addWidget(btnGoms2);
    // Bouton servant à lancer l'application (historique pour la partie goms 2)
    btnGoms2Histo = new QPushButton();
    btnGoms2Histo->setIcon(QIcon(":histo"));
    btnGoms2Histo->setFixedSize(75, 75);
    gomsClicsLayout->addWidget(btnGoms2Histo);
    // Bouton Info
    btnGoms2Info = new QPushButton();
    btnGoms2Info->setIcon(QIcon(":info"));
    btnGoms2Info->setFixedSize(75, 75);
    gomsClicsLayout->addWidget(btnGoms2Info);

    // Bouton servant à lancer l'application (la partie goms 3)
    QHBoxLayout *gomsBashLayout = new QHBoxLayout;
    gomsBashLayout->setSpacing(0);
    btnGoms3 = new QPushButton("Goms-Keystroke (version bash)");
    btnGoms3->setFixedSize(350, 75);
    btnGoms3->setStyleSheet(QString("font-weight: bold; font-size: 16px; text-align: center; font-style: italic;"));
    gomsBashLayout->addWidget(btnGoms3);
    // Bouton servant à lancer l'application (historique pour la partie goms 3)
    btnGoms3Histo = new QPushButton();
    btnGoms3Histo->setIcon(QIcon(":histo"));
    btnGoms3Histo->setFixedSize(75, 75);
    gomsBashLayout->addWidget(btnGoms3Histo);
    // Bouton Info
    btnGoms3Info = new QPushButton();
    btnGoms3Info->setIcon(QIcon(":info"));
    btnGoms3Info->setFixedSize(75, 75);
    gomsBashLayout->addWidget(btnGoms3Info);

    // Bouton servant à lancer l'application (la partie goms 4)
    QHBoxLayout *gomsFlecheLayout = new QHBoxLayout;
    gomsFlecheLayout->setSpacing(0);
    btnGoms4 = new QPushButton("Goms-Keystroke (flèches)");
    btnGoms4->setFixedSize(350, 75);
    btnGoms4->setStyleSheet(QString("font-weight: bold; font-size: 16px; text-align: center; font-style: italic;"));
    gomsFlecheLayout->addWidget(btnGoms4);
    // Bouton servant à lancer l'application (historique pour la partie goms 4)
    btnGoms4Histo = new QPushButton();
    btnGoms4Histo->setIcon(QIcon(":histo"));
    btnGoms4Histo->setFixedSize(75, 75);
    gomsFlecheLayout->addWidget(btnGoms4Histo);
    // Bouton Info
    btnGoms4Info = new QPushButton();
    btnGoms4Info->setIcon(QIcon(":info"));
    btnGoms4Info->setFixedSize(75, 75);
    gomsFlecheLayout->addWidget(btnGoms4Info);

    colonne->addLayout(fittsLayout);
    colonne->addLayout(gomsTextLayout);
    colonne->addLayout(gomsClicsLayout);
    colonne->addLayout(gomsBashLayout);
    colonne->addLayout(gomsFlecheLayout);
    colonne->setContentsMargins(0, 0, 0, 25);
    colonne->setAlignment(Qt::AlignCenter);

    layout->addLayout(colonne);

    QFrame* line2 = new QFrame;
    line2->setFrameShape(QFrame::HLine);
    line2->setMaximumWidth(1260);
    line2->setMinimumWidth(1260);
    layout->addWidget(line2);

    quitter = new QPushButton("Quitter");
    quitter->setFixedSize(300, 35);
    quitter->setStyleSheet("QPushButton {"
                           "border-bottom: 4px solid #bb0000;"
                           "border-radius: 10px;"
                           "font-size: 14px;"
                           "text-align: center;"
                           "font-weight: bold;"
                           "color: #FFF;"
                           "background-color: #E74C3C;"
                           "border-bottom: 4px solid #BD3E31;"
                       "}"
                       "QPushButton:pressed {"
                           "border-bottom: 1px solid #BD3E31;"
                       "}");
    layout->addWidget(quitter, 0, Qt::AlignCenter);

    // Menu bar au sommet
    menuFile = menuBar()->addMenu("Fichier");

    // Actions de la barre
    nouveau = new QMenu("Nouveau", this);
    newFitts = new QAction("Loi de Fitts", nouveau);
    newFitts->setShortcut(QKeySequence(tr("Ctrl+1")));
    nouveau->addAction(newFitts);
    newGoms1 = new QAction("Goms-Keystroke avec saisie de texte", nouveau);
    newGoms1->setShortcut(QKeySequence(tr("Ctrl+2")));
    nouveau->addAction(newGoms1);
    newGoms2 = new QAction("Goms-Keystroke avec clics", nouveau);
    newGoms2->setShortcut(QKeySequence(tr("Ctrl+3")));
    nouveau->addAction(newGoms2);
    newGoms3 = new QAction("Goms-Keystroke avec saisie du chemin", nouveau);
    newGoms3->setShortcut(QKeySequence(tr("Ctrl+4")));
    nouveau->addAction(newGoms3);
    newGoms4 = new QAction("Goms-Keystroke avec les flèches", nouveau);
    newGoms4->setShortcut(QKeySequence(tr("Ctrl+5")));
    nouveau->addAction(newGoms4);

    historique = new QMenu("Historique", this);
    histoFitts = new QAction("Loi de Fitts", historique);
    histoFitts->setShortcut(QKeySequence(tr("Alt+1")));
    historique->addAction(histoFitts);
    histoGoms1 = new QAction("Goms-Keystroke avec saisie de texte", historique);
    histoGoms1->setShortcut(QKeySequence(tr("Alt+2")));
    historique->addAction(histoGoms1);
    histoGoms2 = new QAction("Goms-Keystroke avec clics", historique);
    histoGoms2->setShortcut(QKeySequence(tr("Alt+3")));
    historique->addAction(histoGoms2);
    histoGoms3 = new QAction("Goms-Keystroke avec saisie du chemin", historique);
    histoGoms3->setShortcut(QKeySequence(tr("Alt+4")));
    historique->addAction(histoGoms3);
    histoGoms4 = new QAction("Goms-Keystroke avec les flèches", historique);
    histoGoms4->setShortcut(QKeySequence(tr("Alt+5")));
    historique->addAction(histoGoms4);

    about = new QAction("À propos de nous", this);
    about->setShortcut(QKeySequence(tr("Ctrl+A")));
    fermer = new QAction("Quitter", this);
    fermer->setShortcut(QKeySequence(tr("Ctrl+Q")));

    menuFile->addMenu(nouveau);
    menuFile->insertSeparator(newFitts);
    menuFile->addMenu(historique);
    menuFile->insertSeparator(histoFitts);
    menuFile->addAction(about);
    menuFile->addAction(fermer);

    // On initialise ici les fenêtres des options pour les paramètres de l'application
    fenetreOptionsFitts = new FenetreOptionsFitts;
    fenetreOptionsGomsSaisieTexte = new FenetreOptionsGomsSaisieTexte;
    fenetreOptionsGomsClics = new FenetreOptionsGomsClics;
    fenetreOptionsGomsBash = new FenetreOptionsGomsBash;
    fenetreOptionsGomsClavier = new FenetreOptionsGomsClavier;

    initHistoriquesBoutons();

    // Les connexions
    connect(newFitts, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsFitts()));
    connect(newGoms1, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));
    connect(newGoms2, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsClics()));
    connect(newGoms3, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsBash()));
    connect(newGoms4, SIGNAL(triggered()), this, SLOT(afficheFenetreOptionsGomsClavier()));

    connect(histoFitts, SIGNAL(triggered()), this, SLOT(afficheFenetreStatistiquesFitts()));
    connect(histoGoms1, SIGNAL(triggered()), this, SLOT(afficheFenetreStatistiquesGomsSaisieTexte()));
    connect(histoGoms2, SIGNAL(triggered()), this, SLOT(afficheFenetreStatistiquesGomsClics()));
    connect(histoGoms3, SIGNAL(triggered()), this, SLOT(afficheFenetreStatistiquesGomsBash()));
    connect(histoGoms4, SIGNAL(triggered()), this, SLOT(afficheFenetreStatistiquesGomsClavier()));

    connect(btnFittsHisto, SIGNAL(clicked(bool)), this, SLOT(afficheFenetreStatistiquesFitts()));
    connect(btnGoms1Histo, SIGNAL(clicked(bool)), this, SLOT(afficheFenetreStatistiquesGomsSaisieTexte()));
    connect(btnGoms2Histo, SIGNAL(clicked(bool)), this, SLOT(afficheFenetreStatistiquesGomsClics()));
    connect(btnGoms3Histo, SIGNAL(clicked(bool)), this, SLOT(afficheFenetreStatistiquesGomsBash()));
    connect(btnGoms4Histo, SIGNAL(clicked(bool)), this, SLOT(afficheFenetreStatistiquesGomsClavier()));

    connect(btnFitts, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsFitts()));
    connect(btnGoms1, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));
    connect(btnGoms2, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClics()));
    connect(btnGoms3, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsBash()));
    connect(btnGoms4, SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClavier()));

    connect(btnFittsInfo, SIGNAL(clicked()), this, SLOT(afficheInfosFitts()));
    connect(btnGoms1Info, SIGNAL(clicked()), this, SLOT(afficheInfosGoms1()));
    connect(btnGoms2Info, SIGNAL(clicked()), this, SLOT(afficheInfosGoms2()));
    connect(btnGoms3Info, SIGNAL(clicked()), this, SLOT(afficheInfosGoms3()));
    connect(btnGoms4Info, SIGNAL(clicked()), this, SLOT(afficheInfosGoms4()));

    connect(about, SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(fermer, SIGNAL(triggered()), this, SLOT(close()));
    connect(quitter, SIGNAL(clicked(bool)), this, SLOT(close()));

}

void FenetrePrincipale::initHistoriquesBoutons() {

    if(statsFitts.empty()) {
        btnFittsHisto->setDisabled(true);
    }
    if(statsGomsTexte.empty()) {
        btnGoms1Histo->setDisabled(true);
    }
    if(statsGomsClics.empty()) {
        btnGoms2Histo->setDisabled(true);
    }
    if(statsGomsBash.empty()) {
        btnGoms3Histo->setDisabled(true);
    }
    if(statsGomsClavier.empty()) {
        btnGoms4Histo->setDisabled(true);
    }

}

// Méthode appelée pour l'affichage de la boîte de dialogue avec les infos sur Fitts
void FenetrePrincipale::afficheInfosFitts() {

    QMessageBox::about(this->parentWidget(), "Règles exercice Fitts", "Paramétrez votre test et après avoir cliqué sur \"Commencer\",\ncliquez simplement sur les ronds quand ils apparaissent.");

}

// Méthode appelée pour l'affichage de la boîte de dialogue avec les infos sur Goms saisie texte
void FenetrePrincipale::afficheInfosGoms1() {

    QMessageBox::about(this->parentWidget(), "Règles exercice Goms-Keystroke (saisie texte)", "Paramétrez votre test et après avoir cliqué sur \"Commencer\",\nsaisissez simplement les chaînes de caractère qui apparaissent à l'écran.\nUne fois le mot saisi, appuyez sur \"Entrée\" pour passer au mot suivant.");

}

// Méthode appelée pour l'affichage de la boîte de dialogue avec les infos sur Goms clics
void FenetrePrincipale::afficheInfosGoms2() {

    QMessageBox::about(this->parentWidget(), "Règles exercice Goms-Keystroke (clics)", "Paramétrez votre test et après avoir cliqué sur \"Commencer\",\ndouble-cliquez sur chaque carré affichant \"Celui-ci\" afin de passer au suivant.");

}

// Méthode appelée pour l'affichage de la boîte de dialogue avec les infos sur Goms bash
void FenetrePrincipale::afficheInfosGoms3() {

    QMessageBox::about(this->parentWidget(), "Règles exercice Goms-Keystroke (bash)", "Paramétrez votre test et après avoir cliqué sur \"Commencer\",\nsaisissez la commande \"cd\" suivie de la chaîne de caractères précédant le premier \"/\" de la chaîne affichée à l'écran, puis appuyez sur \"Entrée\" pour passer à la chaîne suivante.");

}

// Méthode appelée pour l'affichage de la boîte de dialogue avec les infos sur Goms clavier
void FenetrePrincipale::afficheInfosGoms4() {

    QMessageBox::about(this->parentWidget(), "Règles exercice Goms-Keystroke (clavier)", "Paramétrez le test et après avoir cliqué sur \"Commencer\",\ndéplacez vous d'un carré à un autre grâce aux flèches directionnelles ou la touche de tabulation afin de parvenir au carré voulu.\nLe carré courant est le carré bleu et le carré visé et le carré vert.");

}

// Méthode appelée pour paramétrer le test Fitts
void FenetrePrincipale::afficheFenetreOptionsFitts() {

    fenetreOptionsFitts->setModal(true);

    // Si on clique sur valider dans la fenêtre d'options, on va ouvrir la fenêtre avec le test
    if(fenetreOptionsFitts->exec() == QDialog::Accepted) {

        setCentralWidget(new FenetreTestFitts(fenetreOptionsFitts->getNbClics(), this, fenetreOptionsFitts->getParametre1(), fenetreOptionsFitts->getParametre2()));

    }

}

// Méthode appelée pour paramétrer le test Goms Saisie Texte
void FenetrePrincipale::afficheFenetreOptionsGomsSaisieTexte() {

    fenetreOptionsGomsSaisieTexte->setModal(true);

    // Si on clique sur valider dans la fenêtre d'options, on va ouvrir la fenêtre avec le test
    if(fenetreOptionsGomsSaisieTexte->exec() == QDialog::Accepted) {

        setCentralWidget(new FenetreTestGomsSaisieTexte(fenetreOptionsGomsSaisieTexte->getNbMots(), this, fenetreOptionsGomsSaisieTexte->getParametre2(), fenetreOptionsGomsSaisieTexte->getParametre1()));

    }

}

// Méthode appelée pour paramétrer le test Goms Clics
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

        setCentralWidget(new FenetreTestGomsClavier(fenetreOptionsGomsClavier->getProfondeur(), this, fenetreOptionsGomsClavier->getParametre1(), fenetreOptionsGomsClavier->getParametre2(), fenetreOptionsGomsClavier->getRetourDepart()));
    }

}

//-----------------------    Statistiques    -----------------------//


// Méthode à appeler pour afficher les statistiques du test Fitts
void FenetrePrincipale::afficheFenetreStatistiquesFitts(){
    if (statsFitts.size() == 0) {
        QMessageBox::information(this, "Erreur", "Aucune donnée présente");
        return; // rien a afficher !
    }
    fenetreStatistiquesFitts = new FenetreStatistiquesFitts(statsFitts);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesFitts->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsFitts()));
    if(QObject::sender() == histoFitts || QObject::sender() == btnFittsHisto) fenetreStatistiquesFitts->getBoutonRecommencer()->setText("Nouvel essai");

    setCentralWidget(fenetreStatistiquesFitts);
}

// Méthode appelée pour ajouter puis afficher les statistiques du test Fitts
void FenetrePrincipale::afficheFenetreStatistiquesFitts(vector<StatistiquesFitts> statistiquesFitts) {

    statsFitts.push_back(statistiquesFitts);
    afficheFenetreStatistiquesFitts();
}

// Méthode appelée pour afficher les statistiques du test Goms Saisie Texte
void FenetrePrincipale::afficheFenetreStatistiquesGomsSaisieTexte() {
    if (statsGomsTexte.size() == 0) {
        QMessageBox::information(this, "Erreur", "Aucune donnée présente");
        return; // rien a afficher !
    }
    fenetreStatistiquesGomsSaisieTexte = new FenetreStatistiquesGomsSaisieTexte(statsGomsTexte);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsSaisieTexte->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsSaisieTexte()));
    if(QObject::sender() == histoGoms1 || QObject::sender() == btnGoms1Histo) fenetreStatistiquesGomsSaisieTexte->getBoutonRecommencer()->setText("Nouvel essai");

    setCentralWidget(fenetreStatistiquesGomsSaisieTexte);

}

void FenetrePrincipale::afficheFenetreStatistiquesGomsSaisieTexte(vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte) {
    statsGomsTexte.push_back(statistiquesGomsSaisieTexte);
    afficheFenetreStatistiquesGomsSaisieTexte();
}

// Méthode appelée pour afficher les statistiques du test Goms Clics
void FenetrePrincipale::afficheFenetreStatistiquesGomsClics() {
    if (statsGomsClics.size() == 0) {
        QMessageBox::information(this, "Erreur", "Aucune donnée présente");
        return; // rien a afficher !
    }

    fenetreStatistiquesGomsClics = new FenetreStatistiquesGomsClics(statsGomsClics);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsClics->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClics()));
    if(QObject::sender() == histoGoms2 || QObject::sender() == btnGoms2Histo) fenetreStatistiquesGomsClics->getBoutonRecommencer()->setText("Nouvel essai");

    setCentralWidget(fenetreStatistiquesGomsClics);

}

void FenetrePrincipale::afficheFenetreStatistiquesGomsClics(vector<StatistiquesGomsClics> statistiquesGomsClics) {
    statsGomsClics.push_back(statistiquesGomsClics);
    afficheFenetreStatistiquesGomsClics();
}

// Méthode appelée pour afficher les statistiques du test Goms Bash
void FenetrePrincipale::afficheFenetreStatistiquesGomsBash() {
    if (statsGomsBash.size() == 0) {
        QMessageBox::information(this, "Erreur", "Aucune donnée présente");
        return; // rien a afficher !
    }

    fenetreStatistiquesGomsBash = new FenetreStatistiquesGomsBash(statsGomsBash);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsBash->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsBash()));
    if(QObject::sender() == histoGoms3 || QObject::sender() == btnGoms3Histo) fenetreStatistiquesGomsBash->getBoutonRecommencer()->setText("Nouvel essai");

    setCentralWidget(fenetreStatistiquesGomsBash);

}

void FenetrePrincipale::afficheFenetreStatistiquesGomsBash(vector<StatistiquesGomsBash> statistiquesGomsBash) {
    statsGomsBash.push_back(statistiquesGomsBash);
    afficheFenetreStatistiquesGomsBash();
}

// Méthode appelée pour afficher les statistiques du test Goms Clavier
void FenetrePrincipale::afficheFenetreStatistiquesGomsClavier() {
    if (statsGomsClavier.size() == 0) {
        QMessageBox::information(this, "Erreur", "Aucune donnée présente");
        return; // rien a afficher !
    }

    fenetreStatistiquesGomsClavier = new FenetreStatistiquesGomsClavier(statsGomsClavier);

    // Connexion au bouton Recommencer, on réaffiche la fenêtre avec les options
    connect(fenetreStatistiquesGomsClavier->getBoutonRecommencer(), SIGNAL(clicked()), this, SLOT(afficheFenetreOptionsGomsClavier()));
    if(QObject::sender() == histoGoms4 || QObject::sender() == btnGoms4Histo) fenetreStatistiquesGomsClavier->getBoutonRecommencer()->setText("Nouvel essai");

    setCentralWidget(fenetreStatistiquesGomsClavier);

}

void FenetrePrincipale::afficheFenetreStatistiquesGomsClavier(vector<StatistiquesGomsClavier> statistiquesGomsClavier) {
    statsGomsClavier.push_back(statistiquesGomsClavier);
    afficheFenetreStatistiquesGomsClavier();
}

// Méthode appelée pour l'affichage de la boîte de dialogue "A propos"
void FenetrePrincipale::aPropos() {

    QMessageBox::about(this->parentWidget(), "A propos de nous", "Ce projet a été réalisé par Nicolas Hergenroether, Kieran Molina et Vincent Yucel dans le cadre de l'UV GL40 de l'UTBM.");

}
