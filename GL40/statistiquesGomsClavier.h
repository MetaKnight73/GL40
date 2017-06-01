#ifndef STATISTIQUESGOMSCLAVIER_H
#define STATISTIQUESGOMSCLAVIER_H

#include <QTime>
#include <math.h>

class StatistiquesGomsClavier {

private:

    // Paramètres Goms
    double tempsM, tempsK;
    int deplacementX, deplacementY;
    double numbouton;

    // Temps Goms
    double tempsGoms, tempsGomsReal;

public:

    StatistiquesGomsClavier();
    StatistiquesGomsClavier(double tM, double tK, int deplacementX, int deplacementY, double numBout, int tempsGomsReal);

    // Méthodes de calcul
    void calculTempsGoms();

    double getTempsGoms();
    double getTempsM();
    double getTempsK();
    int getDeplacementX();
    int getDeplacementY();
    double getNumBouton();
    double getTempsReal();

};

#endif
