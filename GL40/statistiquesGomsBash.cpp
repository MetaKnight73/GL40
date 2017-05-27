#include "statistiquesGomsBash.h"

StatistiquesGomsBash::StatistiquesGomsBash()
{

}

StatistiquesGomsBash::StatistiquesGomsBash(double tempsMentale, double longueurM, int tempsR) : tempsM(tempsMentale), longueurMot(longueurM), tempsGomsReal(tempsR) {}

void StatistiquesGomsBash::calculTempsGoms() {

    tempsGoms =  tempsM + (longueurMot+1)*0.2; //Le codage est MKKKKKK... avec K^(nb de caractères + 1 (retour chariot))

}

double StatistiquesGomsBash::getTempsGoms() {

    return tempsGoms;

}

double StatistiquesGomsBash::getTempsM() {

    return tempsM;

}

double StatistiquesGomsBash::getLongueurMot() {

    return longueurMot;

}

double StatistiquesGomsBash::getTempsReal() {

    return tempsGomsReal;
}
