#ifndef FENETRETESTGOMSSAISIETEXTE_H
#define FENETRETESTGOMSSAISIETEXTE_H

#include <QWidget>
#include <QPushButton>
#include <QTime>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QLayout>

#include <vector>
#include <time.h>

#include "statistiquesGomsSaisieTexte.h"

using namespace std;

class FenetreTestGomsSaisieTexte : public QWidget {
    Q_OBJECT

private:

    // Variables générales
    int nombreM;
    int nombreMotsValidesCourant;
    double tempsMental;
    int longueurMax;
    QGridLayout *layout;
    QVBoxLayout *layoutZoneSaisie;
    QLabel *motCourant, *labelZoneSaisie, *info;
    QLineEdit *zoneSaisie;

    // Vecteur contenant les valeurs récoltées lors du test
    vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte;

    // Widgets Qt
    QPushButton *bouton;
    QTime *chronometre;

public:

    explicit FenetreTestGomsSaisieTexte(int nombreMots, QWidget *parent = 0, double tempsM = 0, int longueurMax = 0);
    char* genererMotCourant(int longueur);

signals:

    void sequenceFinGoms(vector<StatistiquesGomsSaisieTexte>);

public slots:

    void lancerTest();
    void checkWord();

};

#endif
