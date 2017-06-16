#include "statistiquesGomsBash.h"

StatistiquesGomsBash::StatistiquesGomsBash() {}

StatistiquesGomsBash::StatistiquesGomsBash(double tempsMentale, double longueurM, int tempsR) : tempsM(tempsMentale), longueurMot(longueurM), tempsGomsReal(tempsR) {}

void StatistiquesGomsBash::calculTempsGoms() {

    tempsGoms =  tempsM + (longueurMot+1)*0.2; //Le codage est MKKKKKK... avec K^(nb de caractères + 1 (retour chariot))

}

void StatistiquesGomsBash::calculTempsGomsFirst() {

    tempsGoms =  tempsM + 0.4 + (longueurMot+1)*0.2; //Le codage est MHKKKKKK... avec K^(nb de caractères + 1 (retour chariot)) pour le premier

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

void StatistiquesGomsBash::setDate(){
    date = QDateTime::currentDateTime();
}

QDateTime StatistiquesGomsBash::getDate(){
    return date;
}
