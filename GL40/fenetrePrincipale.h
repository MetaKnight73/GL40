#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QGridLayout>
#include <QBoxLayout>
#include <QWidget>
#include <QLabel>

#include <vector>

#include "fenetreOptionsFitts.h"
#include "fenetreOptionsGomsSaisieTexte.h"
#include "fenetreOptionsGomsClics.h"
#include "fenetreTestFitts.h"
#include "fenetreTestGomsSaisieTexte.h"
#include "fenetreTestGomsClics.h"
#include "fenetreStatistiquesFitts.h"
#include "fenetreStatistiquesGomsSaisieTexte.h"
#include "fenetreStatistiquesGomsClics.h"

using namespace std;

class FenetrePrincipale : public QMainWindow {
    Q_OBJECT

private:

    // Menu Bar
    QMenu *menuFile;
    QMenu *nouveau;
    QAction *newFitts;
    QAction *newGoms1;
    QAction *newGoms2;
    QAction *newGoms3;
    QAction *newGoms4;
    QAction *about;
    QAction *fermer;

    // Autres
    QPushButton *btnFitts;
    QPushButton *btnRestart;
    QPushButton *btnGoms1;
    QPushButton *btnGoms2;
    QPushButton *btnGoms3;
    QPushButton *btnGoms4;

    FenetreOptionsFitts *fenetreOptionsFitts;
    FenetreOptionsGomsSaisieTexte *fenetreOptionsGomsSaisieTexte;
    FenetreOptionsGomsClics *fenetreOptionsGomsClics;

    FenetreStatistiquesFitts *fenetreStatistiquesFitts;
    FenetreStatistiquesGomsSaisieTexte *fenetreStatistiquesGomsSaisieTexte;
    FenetreStatistiquesGomsClics *fenetreStatistiquesGomsClics;

public:

    explicit FenetrePrincipale(QWidget *parent = 0);

public slots:

    void afficheFenetreOptionsFitts();
    void afficheFenetreOptionsGomsSaisieTexte();
    void afficheFenetreOptionsGomsClics();
    void afficheFenetreStatistiquesFitts(vector<StatistiquesFitts> statistiquesFitts);
    void afficheFenetreStatistiquesGomsSaisieTexte(vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte);
    void afficheFenetreStatistiquesGomsClics(vector<StatistiquesGomsClics> statistiquesGomsClics);
    void aPropos();

};

#endif
