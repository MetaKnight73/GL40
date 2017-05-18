#ifndef STATISTIQUESFITTS_H
#define STATISTIQUESFITTS_H

#include <QTime>
#include <QPointF>
#include <math.h>
#include <iostream>

class StatistiquesFitts {
private:
    // Position initiale
    QPointF positionInitiale;

    // Position du bouton
    QPointF positionBouton;

    // Distance
    double distance;

    // Largeur du bouton
    int largeurBouton;

    // Temps de déplacement souris
    int tempsDeplacementSouris;

    // Paramètres Fitts
    double parametre1;
    double parametre2;

    // Temps Fitts
    double tempsFitts;

public:
    StatistiquesFitts();
    StatistiquesFitts(QPointF positionInit, QPointF positionBout, int largeurB, int tempsDeplacementS, double param1, double param2);

    // Méthodes de calcul
    void calculTempsFitts();
    void calculDistance(); 

    QPointF getPositionInitiale();
    QPointF getPositionBouton();
    double getDistance();
    int getLargeurBouton();
    int getTempsDeplacementSouris();
    double getTempsFitts();
    double getParametre1();
    double getParametre2();

};

#endif
