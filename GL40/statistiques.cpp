#include "statistiques.h"

Statistiques::Statistiques() { }

Statistiques::Statistiques(QPointF positionInit, QPointF positionBout, int largeurB, int tempsDeplacementS, double param1, double param2) : positionInitiale(positionInit), positionBouton(positionBout), largeurBouton(largeurB), tempsDeplacementSouris(tempsDeplacementS), parametre1(param1), parametre2(param2) { }

void Statistiques::calculDistance() {
    distance = sqrt(pow((positionBouton.x() - positionInitiale.x()), 2) + pow((positionBouton.y() - positionInitiale.y()), 2));
}

void Statistiques::calculTempsFitts() {
    tempsFitts =  parametre1 + parametre2*log2((distance/(double)largeurBouton + 0.5));
}

QPointF Statistiques::getPositionInitiale() {
    return positionInitiale;
}

QPointF Statistiques::getPositionBouton() {
    return positionBouton;
}

double Statistiques::getDistance() {
    return distance;
}

int Statistiques::getLargeurBouton() {
    return largeurBouton;
}

int Statistiques::getTempsDeplacementSouris() {
    return tempsDeplacementSouris;
}

double Statistiques::getTempsFitts() {
    return tempsFitts;
}

double Statistiques::getParametre1() {
    return parametre1;
}

double Statistiques::getParametre2() {
    return parametre2;
}




