#ifndef STATISTIQUESGOMSCLICS_H
#define STATISTIQUESGOMSCLICS_H

#include <QTime>
#include <math.h>
#include <iostream>

class StatistiquesGomsClics {
private:
    // Paramètres Goms
    double tempsM, tempsP, tempsK;
    double numbouton;

    // Temps Goms
    double tempsGoms, tempsGomsReal;

public:
    StatistiquesGomsClics();
    StatistiquesGomsClics(double tM, double tP, double tK, double numBout, int tempsGomsReal);

    // Méthodes de calcul
    void calculTempsGoms();

    double getTempsGoms();
    double getTempsM();
    double getTempsP();
    double getTempsK();
    double getNumBouton();
    double getTempsReal();

};

#endif // STATISTIQUESGOMSCLICS_H
