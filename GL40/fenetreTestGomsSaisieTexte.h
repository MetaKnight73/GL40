#ifndef FENETRETESTGOMSSAISIETEXTE_H
#define FENETRETESTGOMSSAISIETEXTE_H

#include <QWidget>
#include <QPushButton>
#include <QTime>
#include <QWidget>
#include <QLabel>
#include <iostream>
#include <vector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include "statistiquesGomsSaisieTexte.h"

class FenetreTestGomsSaisieTexte : public QWidget {
    Q_OBJECT
private:
    // Variables générales
    int nombreM;
    int nombreMotsValidesCourant;
    double tempsMental, longueurMax;
    QGridLayout *layout;
    QVBoxLayout *layoutZoneSaisie;
    QLabel *motCourant, *labelZoneSaisie;
    QLineEdit *zoneSaisie;

    // Vecteur contenant les valeurs récoltées lors du test
    std::vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte;

    // Widgets Qt
    QPushButton *bouton;
    QTime *chronometre;

public:
    explicit FenetreTestGomsSaisieTexte(int nombreMots, QWidget *parent = 0, double tempsM = 0, double longueurMax = 0);
    char* genererMotCourant(double longueur);

signals:
    void sequenceFinGoms(std::vector<StatistiquesGomsSaisieTexte>);

public slots:
    void lancerTest();
    void checkWord();

};

#endif
