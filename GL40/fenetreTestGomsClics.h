#ifndef FENETRETESTGOMSCLICS_H
#define FENETRETESTGOMSCLICS_H


#include <QWidget>
#include <QPushButton>
#include <QPoint>
#include <QTime>
#include <QMouseEvent>
#include <QWidget>
#include <iostream>
#include <vector>
#include "statistiquesGomsClics.h"

class FenetreTestGomsClics : public QWidget {
    Q_OBJECT
private:
    // Variables générales
    int nombreC;
    int nombreClicsCourant;
    int boutonActif;
    double param1, param2, param3;
    bool sourisBougeeDebut, selectionne;

    // Vecteur contenant les valeurs récoltées lors du test
    std::vector<StatistiquesGomsClics> statistiquesGomsClics;

    // Widgets Qt
    QPushButton *bouton;
    QPushButton *grille[16];
    QTime *chronometre;

public:
    explicit FenetreTestGomsClics(int profondeur, QWidget *parent = 0, double param1 = 0, double param2 = 0, double param3 = 0);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void sequenceFin(std::vector<StatistiquesGomsClics>);

public slots:
    void demarrer();
    void changer();

};
#endif // FENETRETESTGOMSCLICS_H
