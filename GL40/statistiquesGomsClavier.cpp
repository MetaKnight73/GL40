#include "statistiquesGomsClavier.h"

StatistiquesGomsClavier::StatistiquesGomsClavier() {}

StatistiquesGomsClavier::StatistiquesGomsClavier(double tM, double tK, int dX, int dY, double nB, int tempsR) : tempsM(tM), tempsK(tK), deplacementX(dX), deplacementY(dY), numbouton(nB), tempsGomsReal(tempsR) {}

void StatistiquesGomsClavier::calculTempsGoms() {

    // Temps goms entre chaque 'repertoire'
    tempsGoms =  tempsM + ((deplacementX + deplacementY + 1) * tempsK); //Le codage est MK^(nbLignesEcart+nbColonnesEcart+1)

}

double StatistiquesGomsClavier::getTempsGoms() {

    return tempsGoms;

}

double StatistiquesGomsClavier::getTempsM() {

    return tempsM;

}

double StatistiquesGomsClavier::getTempsK() {

    return tempsK;

}

int StatistiquesGomsClavier::getDeplacementX() {

    return deplacementX;

}

int StatistiquesGomsClavier::getDeplacementY() {

    return deplacementY;

}

double StatistiquesGomsClavier::getNumBouton() {

    return numbouton;

}

double StatistiquesGomsClavier::getTempsReal() {

    return tempsGomsReal;

}
