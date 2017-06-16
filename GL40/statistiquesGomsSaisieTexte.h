#ifndef STATISTIQUESGOMSSAISIETEXTE_H
#define STATISTIQUESGOMSSAISIETEXTE_H

#include <QTime>
#include <math.h>
#include <QDateTime>

class StatistiquesGomsSaisieTexte {

private:

    // Paramètres Goms
    double tempsM;
    double longueurMot;

    // Temps Goms
    double tempsGoms, tempsGomsReal;

    // Date et heure de l'enregistrement
    QDateTime date;

public:

    StatistiquesGomsSaisieTexte();
    StatistiquesGomsSaisieTexte(double tempsM, double longueurMot, int tempsGomsReal);

    // Méthodes de calcul
    void calculTempsGoms();
    void calculTempsGomsFirst();

    double getTempsGoms();
    double getTempsM();
    double getLongueurMot();
    double getTempsReal();
    QDateTime getDate();
    void setDate(); // currentDate();

};

#endif
