#include "statistiquesGomsClics.h"

StatistiquesGomsClics::StatistiquesGomsClics() { }

StatistiquesGomsClics::StatistiquesGomsClics(double tempsMentale, double prof, int tempsR) : tempsM(tempsMentale), profondeur(prof), tempsGomsReal(tempsR) { }

void StatistiquesGomsClics::calculTempsGoms() {
    double tempsPoint = 1.1; // a parametrer
    double tempsClic = 0.1;  // a parametrer
    tempsGoms =  (profondeur+1) * (tempsM + tempsPoint + (2*tempsClic)); //Le codage est (MPK²)^(profondeur+1) sans compter les homing (on commence à la souris)
}

double StatistiquesGomsClics::getTempsGoms() {
    return tempsGoms;
}

double StatistiquesGomsClics::getTempsM() {
    return tempsM;
}

double StatistiquesGomsClics::getProfondeur() {
    return profondeur;
}

double StatistiquesGomsClics::getTempsReal() {
    return tempsGomsReal;
}
