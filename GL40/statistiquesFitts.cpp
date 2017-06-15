#include "statistiquesFitts.h"

StatistiquesFitts::StatistiquesFitts() { }

StatistiquesFitts::StatistiquesFitts(QPointF positionInit, QPointF positionBout, int largeurB, int tempsDeplacementS, double param1, double param2) : positionInitiale(positionInit), positionBouton(positionBout), largeurBouton(largeurB), tempsDeplacementSouris(tempsDeplacementS), parametre1(param1), parametre2(param2) { }

void StatistiquesFitts::calculDistance() {

    distance = sqrt(pow((positionBouton.x() - positionInitiale.x()), 2) + pow((positionBouton.y() - positionInitiale.y()), 2));

}

void StatistiquesFitts::calculTempsFitts() {

    tempsFitts =  parametre1 + parametre2*log2((distance/(double)largeurBouton + 0.5));

}

QPointF StatistiquesFitts::getPositionInitiale() {

    return positionInitiale;

}

QPointF StatistiquesFitts::getPositionBouton() {

    return positionBouton;

}

double StatistiquesFitts::getDistance() {

    return distance;

}

int StatistiquesFitts::getLargeurBouton() {

    return largeurBouton;

}

int StatistiquesFitts::getTempsDeplacementSouris() {

    return tempsDeplacementSouris;

}

double StatistiquesFitts::getTempsFitts() {

    return tempsFitts;

}

double StatistiquesFitts::getParametre1() {

    return parametre1;

}

double StatistiquesFitts::getParametre2() {

    return parametre2;

}

void StatistiquesFitts::setDate(){
    date = QDateTime::currentDateTime();
}

QDateTime StatistiquesFitts::getDate(){
    return date;
}




