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
#include "fenetreOptionsGomsBash.h"
#include "fenetreOptionsGomsClavier.h"
#include "fenetreTestFitts.h"
#include "fenetreTestGomsSaisieTexte.h"
#include "fenetreTestGomsClics.h"
#include "fenetreTestGomsBash.h"
#include "fenetreTestGomsClavier.h"
#include "fenetreStatistiquesFitts.h"
#include "fenetreStatistiquesGomsSaisieTexte.h"
#include "fenetreStatistiquesGomsClics.h"
#include "fenetreStatistiquesGomsBash.h"
#include "fenetreStatistiquesGomsClavier.h"

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
    FenetreOptionsGomsBash *fenetreOptionsGomsBash;
    FenetreOptionsGomsClavier *fenetreOptionsGomsClavier;

    FenetreStatistiquesFitts *fenetreStatistiquesFitts;
    FenetreStatistiquesGomsSaisieTexte *fenetreStatistiquesGomsSaisieTexte;
    FenetreStatistiquesGomsClics *fenetreStatistiquesGomsClics;
    FenetreStatistiquesGomsBash *fenetreStatistiquesGomsBash;
    FenetreStatistiquesGomsClavier *fenetreStatistiquesGomsClavier;

public:

    explicit FenetrePrincipale(QWidget *parent = 0);

public slots:

    void afficheFenetreOptionsFitts();
    void afficheFenetreOptionsGomsSaisieTexte();
    void afficheFenetreOptionsGomsClics();
    void afficheFenetreOptionsGomsBash();
    void afficheFenetreOptionsGomsClavier();
    void afficheFenetreStatistiquesFitts(vector<StatistiquesFitts> statistiquesFitts);
    void afficheFenetreStatistiquesGomsSaisieTexte(vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte);
    void afficheFenetreStatistiquesGomsClics(vector<StatistiquesGomsClics> statistiquesGomsClics);
    void afficheFenetreStatistiquesGomsBash(vector<StatistiquesGomsBash> statistiquesGomsBash);
    void afficheFenetreStatistiquesGomsClavier(vector<StatistiquesGomsClavier> statistiquesGomsClavier);
    void aPropos();

};

#endif
