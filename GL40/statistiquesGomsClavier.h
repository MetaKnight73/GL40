#ifndef STATISTIQUESGOMSCLAVIER_H
#define STATISTIQUESGOMSCLAVIER_H

#include <QTime>
#include <math.h>

class StatistiquesGomsClavier {

private:

    // Paramètres Goms
    double tempsM, tempsP, tempsK;
    double numbouton;

    // Temps Goms
    double tempsGoms, tempsGomsReal;

public:

    StatistiquesGomsClavier();
    StatistiquesGomsClavier(double tM, double tP, double tK, double numBout, int tempsGomsReal);

    // Méthodes de calcul
    void calculTempsGoms();

    double getTempsGoms();
    double getTempsM();
    double getTempsP();
    double getTempsK();
    double getNumBouton();
    double getTempsReal();

};

#endif // STATISTIQUESGOMSCLAVIER_H
