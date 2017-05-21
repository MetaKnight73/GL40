#include "statistiquesGomsSaisieTexte.h"

StatistiquesGomsSaisieTexte::StatistiquesGomsSaisieTexte() {}

StatistiquesGomsSaisieTexte::StatistiquesGomsSaisieTexte(double tempsMentale, double longueurM, int tempsR) : tempsM(tempsMentale), longueurMot(longueurM), tempsGomsReal(tempsR) {}

void StatistiquesGomsSaisieTexte::calculTempsGoms() {

    tempsGoms =  tempsM + (longueurMot+1)*0.2; //Le codage est MKKKKKK... avec K^(nb de caractères + 1 (retour chariot))

}

double StatistiquesGomsSaisieTexte::getTempsGoms() {

    return tempsGoms;

}

double StatistiquesGomsSaisieTexte::getTempsM() {

    return tempsM;

}

double StatistiquesGomsSaisieTexte::getLongueurMot() {

    return longueurMot;

}

double StatistiquesGomsSaisieTexte::getTempsReal() {

    return tempsGomsReal;

}
