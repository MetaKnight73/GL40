#include "statistiquesGomsClavier.h"

StatistiquesGomsClavier::StatistiquesGomsClavier() {}

StatistiquesGomsClavier::StatistiquesGomsClavier(double tM, double tP, double tK, double nB, int tempsR) : tempsM(tM), tempsP(tP), tempsK(tK), numbouton(nB), tempsGomsReal(tempsR) {}

void StatistiquesGomsClavier::calculTempsGoms() {

    //Temps goms entre chaque 'repertoire'
    tempsGoms =  tempsM + tempsP + (2*tempsK); //Le codage est (MPK²)^(profondeur+1) sans compter les homing (on commence à la souris)

}

double StatistiquesGomsClavier::getTempsGoms() {

    return tempsGoms;

}

double StatistiquesGomsClavier::getTempsM() {

    return tempsM;

}

double StatistiquesGomsClavier::getTempsP() {

    return tempsP;

}

double StatistiquesGomsClavier::getTempsK() {

    return tempsK;

}

double StatistiquesGomsClavier::getNumBouton() {

    return numbouton;

}

double StatistiquesGomsClavier::getTempsReal() {

    return tempsGomsReal;

}
