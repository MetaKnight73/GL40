#ifndef FENETRETESTGOMSSAISIETEXTE_H
#define FENETRETESTGOMSSAISIETEXTE_H

#include <QWidget>
#include <QPushButton>
#include <QPoint>
#include <QTime>
#include <QMouseEvent>
#include <QWidget>
#include <QLabel>
#include <iostream>
#include <vector>
#include <QGridLayout>
#include <QLineEdit>
#include "statistiquesFitts.h"

class FenetreTestGomsSaisieTexte : public QWidget {
    Q_OBJECT
private:
    // Variables générales
    int nombreM;
    int nombreMotsValidesCourant;
    double param1, param2;
    QGridLayout *layout;
    QLabel *motCourant, *labelZoneSaisie;
    QLineEdit *zoneSaisie;

    // Vecteur contenant les valeurs récoltées lors du test
    //std::vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte;

    // Widgets Qt
    QPushButton *bouton;
    QTime *chronometre;

public:
    explicit FenetreTestGomsSaisieTexte(int nombreMots, QWidget *parent = 0, double param1 = 0, double param2 = 0);
    char* genererMotCourant(double longueur);

signals:
    //void sequenceFin(std::vector<StatistiquesGomsSaisieTexte>);

public slots:
    void lancerTest();
    void checkWord();

};

#endif
