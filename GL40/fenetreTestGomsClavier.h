#ifndef FENETRETESTGOMSCLAVIER_H
#define FENETRETESTGOMSCLAVIER_H

#include <QWidget>
#include <QPushButton>
#include <QTime>
#include <QLayout>
#include <QKeyEvent>
#include <QLabel>

#include <vector>

#include "statistiquesGomsClavier.h"

using namespace std;

class FenetreTestGomsClavier : public QWidget {
    Q_OBJECT

public:

    explicit FenetreTestGomsClavier(int profondeur, QWidget *parent = 0, double param1 = 0, double param2 = 0);

    // Variables générales
    int nombreC;
    int nombreClicsCourant;
    int boutonActif, boutonHasard, deplacementX, deplacementY;
    double param1, param2;

    // Vecteur contenant les valeurs récoltées lors du test
    vector<StatistiquesGomsClavier> statistiquesGomsClavier;

    // Widgets Qt
    QPushButton *bouton;
    QPushButton *grille[16];
    QTime *chronometre;
    QLabel* info;
    QString *style;

signals:

    void sequenceFin(vector<StatistiquesGomsClavier>);

public slots:

    void demarrer();
    void keyPressEvent(QKeyEvent *event);
};

#endif
