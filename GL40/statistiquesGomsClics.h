#ifndef STATISTIQUESGOMSCLICS_H
#define STATISTIQUESGOMSCLICS_H

#include <QTime>
#include <math.h>
#include <iostream>

class StatistiquesGomsClics {
private:
    // Paramètres Goms
    double tempsM;
    double profondeur;

    // Temps Goms
    double tempsGoms, tempsGomsReal;

public:
    StatistiquesGomsClics();
    StatistiquesGomsClics(double tempsM, double profondeur, int tempsGomsReal);

    // Méthodes de calcul
    void calculTempsGoms();

    double getTempsGoms();
    double getTempsM();
    double getProfondeur();
    double getTempsReal();

};

#endif // STATISTIQUESGOMSCLICS_H
