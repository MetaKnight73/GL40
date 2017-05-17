#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <vector>
#include <iostream>
#include "fenetreOptionsFitts.h"
#include "fenetreOptionsGomsSaisieTexte.h"
#include "fenetreTest.h"
#include "fenetreStatistiques.h"

class FenetrePrincipale : public QMainWindow {
    Q_OBJECT
private:
    // Menu Bar
    QMenu *menuFile;
    QMenu *nouveau;
    QAction *newFitts;
    QAction *newGoms1;
    QAction *newGoms2;
    QAction *about;
    QAction *fermer;

    // Autres
    QPushButton *btnFitts;
    QPushButton *btnRestart;
    QPushButton *btnGoms1;
    QPushButton *btnGoms2;

    FenetreOptionsFitts *fenetreOptionsFitts;
    FenetreOptionsGomsSaisieTexte *fenetreOptionsGomsSaisieTexte;
    FenetreStatistiques *fenetreStatistiques;

public:
    explicit FenetrePrincipale(QWidget *parent = 0);

public slots:
    void afficheFenetreOptionsFitts();
    void afficheFenetreOptionsGomsSaisieTexte();
    void afficheFenetreStatistiques(std::vector<Statistiques> statistiques);
    void aPropos();

};

#endif // FENETREPRINCIPALE_H
