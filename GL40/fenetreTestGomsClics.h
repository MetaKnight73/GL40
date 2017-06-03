#ifndef FENETRETESTGOMSCLICS_H
#define FENETRETESTGOMSCLICS_H

#include <QWidget>
#include <QPushButton>
#include <QTime>
#include <QLayout>
#include <QLabel>

#include <vector>

#include "statistiquesGomsClics.h"

using namespace std;

class FenetreTestGomsClics : public QWidget {
    Q_OBJECT

private:

    // Variables générales
    int nombreC;
    int nombreClicsCourant;
    int boutonActif;
    double param1, param2, param3;
    bool selectionne;

    // Vecteur contenant les valeurs récoltées lors du test
    vector<StatistiquesGomsClics> statistiquesGomsClics;

    // Widgets Qt
    QPushButton *bouton;
    QPushButton *grille[16];
    QLabel *info;
    QTime *chronometre;

public:

    explicit FenetreTestGomsClics(int profondeur, QWidget *parent = 0, double param1 = 0, double param2 = 0, double param3 = 0);

signals:

    void sequenceFin(vector<StatistiquesGomsClics>);

public slots:

    void demarrer();
    void changer();

};

#endif
