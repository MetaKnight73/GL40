#ifndef STATISTIQUESGOMSCLAVIER_H
#define STATISTIQUESGOMSCLAVIER_H

#include <QTime>
#include <math.h>
#include <QDateTime>

class StatistiquesGomsClavier {

private:

    // Paramètres Goms
    double tempsM, tempsK;
    int deplacementX, deplacementY;
    double numbouton;

    // Temps Goms
    double tempsGoms, tempsGomsReal;

    // Date et heure de l'enregistrement
    QDateTime date;

public:

    StatistiquesGomsClavier();
    StatistiquesGomsClavier(double tM, double tK, int deplacementX, int deplacementY, double numBout, int tempsGomsReal);

    // Méthodes de calcul
    void calculTempsGoms();
    void calculTempsGomsFirst();

    double getTempsGoms();
    double getTempsM();
    double getTempsK();
    int getDeplacementX();
    int getDeplacementY();
    double getNumBouton();
    double getTempsReal();
    QDateTime getDate();
    void setDate(); // currentDate();

};

#endif
