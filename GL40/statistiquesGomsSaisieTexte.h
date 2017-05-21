#ifndef STATISTIQUESGOMSSAISIETEXTE_H
#define STATISTIQUESGOMSSAISIETEXTE_H

#include <QTime>
#include <math.h>

class StatistiquesGomsSaisieTexte {

private:

    // Paramètres Goms
    double tempsM;
    double longueurMot;

    // Temps Goms
    double tempsGoms, tempsGomsReal;

public:

    StatistiquesGomsSaisieTexte();
    StatistiquesGomsSaisieTexte(double tempsM, double longueurMot, int tempsGomsReal);

    // Méthodes de calcul
    void calculTempsGoms();

    double getTempsGoms();
    double getTempsM();
    double getLongueurMot();
    double getTempsReal();

};

#endif
