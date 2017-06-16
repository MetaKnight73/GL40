#include "statistiquesGomsClics.h"

StatistiquesGomsClics::StatistiquesGomsClics() {}

StatistiquesGomsClics::StatistiquesGomsClics(double tM, double tP, double tK, double nB, int tempsR) : tempsM(tM), tempsP(tP), tempsK(tK), numbouton(nB), tempsGomsReal(tempsR) {}

void StatistiquesGomsClics::calculTempsGoms() {

    //Temps goms entre chaque 'repertoire'
    tempsGoms =  tempsM + tempsP + (2*tempsK); //Le codage est (MPK²)^(profondeur+1) sans compter les homing (on commence à la souris)

}

double StatistiquesGomsClics::getTempsGoms() {

    return tempsGoms;

}

double StatistiquesGomsClics::getTempsM() {

    return tempsM;

}

double StatistiquesGomsClics::getTempsP() {

    return tempsP;

}

double StatistiquesGomsClics::getTempsK() {

    return tempsK;

}

double StatistiquesGomsClics::getNumBouton() {

    return numbouton;

}

double StatistiquesGomsClics::getTempsReal() {

    return tempsGomsReal;

}

void StatistiquesGomsClics::setDate(){
    date = QDateTime::currentDateTime();
}

QDateTime StatistiquesGomsClics::getDate(){
    return date;
}
