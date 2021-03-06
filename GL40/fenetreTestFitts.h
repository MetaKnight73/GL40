#ifndef FENETRETESTFITTS_H
#define FENETRETESTFITTS_H

#include <QWidget>
#include <QPushButton>
#include <QPoint>
#include <QTime>
#include <QMouseEvent>
#include <QLayout>
#include <QLabel>

#include <vector>

#include "statistiquesFitts.h"
#include "fenetrePrincipale.h"

using namespace std;

class FenetreTestFitts : public QWidget {
    Q_OBJECT

private:

    // Variables générales
    int nombreC;
    int nombreClicsCourant;
    double param1, param2;
    bool sourisBougeeDebut;

    // Vecteur contenant les valeurs récoltées lors du test
    vector<StatistiquesFitts> statistiquesFitts;

    // Widgets Qt
    QPushButton *bouton;
    QLabel *info;
    QTime *chronometre;

public:

    explicit FenetreTestFitts(int nombreClics, QWidget *parent = 0, double param1 = 0, double param2 = 0);
    void mouseMoveEvent(QMouseEvent *);
    void retournerMenu();

signals:

    void sequenceFin(vector<StatistiquesFitts>);

public slots:

    void deplacerBoutonClic();
    void keyPressEvent(QKeyEvent *event);

};

#endif

