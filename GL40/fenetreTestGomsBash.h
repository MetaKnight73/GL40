#ifndef FENETRETESTGOMSBASH_H
#define FENETRETESTGOMSBASH_H

#include <QWidget>
#include <QPushButton>
#include <QTime>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QLayout>
#include <QList>

#include <vector>
#include <time.h>

#include "statistiquesGomsBash.h"

using namespace std;

class FenetreTestGomsBash : public QWidget {
    Q_OBJECT

private:

    // Variables générales
    int longueurMaxRep;
    int nombreMotsValidesCourant;
    double tempsMental;
    int nbRep;
    QGridLayout *layout;
    QVBoxLayout *layoutZoneSaisie;
    QLabel *cheminCourant, *labelZoneSaisie;
    QLineEdit *zoneSaisie;

    // Vecteur contenant les valeurs récoltées lors du test
    vector<StatistiquesGomsBash> statistiquesGomsBash;

    // Widgets Qt
    QPushButton *bouton;
    QTime *chronometre;

public:

    explicit FenetreTestGomsBash(int longRep, QWidget *parent = 0, double tempsM = 0, int tailleChemin = 0);
    char* genererMotCourant(int longueur);

signals:

    void sequenceFinGoms(vector<StatistiquesGomsBash>);

public slots:

    void lancerTest();
    void checkWord();
};

#endif // FENETRETESTGOMSBASH_H
