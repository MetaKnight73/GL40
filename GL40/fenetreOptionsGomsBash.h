#ifndef FENETREOPTIONSGOMSBASH_H
#define FENETREOPTIONSGOMSBASH_H

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QBoxLayout>

class FenetreOptionsGomsBash : public QDialog
{
    Q_OBJECT
private:

    // Paramètres Goms-Keystroke
    int parametre1;
    double parametre2;

    // Layout
    QGridLayout *layout;
    QHBoxLayout *layoutUsers;
    QHBoxLayout *layoutValiderAnnuler;

    // Spinners
    QSpinBox *spinLongRep; //Longueur répertoire
    QSpinBox *spinParam1;
    QDoubleSpinBox *spinParam2; // Nombre de répertoire à parcourir

    // Labels
    QLabel *label1;
    QLabel *label2;
    QLabel *labelMots;

    // Boutons
    QPushButton *start;
    QPushButton *cancel;
    QPushButton *userNormal;
    QPushButton *userExpert;

public:

    explicit FenetreOptionsGomsBash(QWidget *parent = 0);
    int getLongRep();
    int getParametre1();
    double getParametre2();

public slots:

    void restoreDefaultValues();
    void restoreExpertValues();
    void onChange();
};

#endif // FENETREOPTIONSGOMSBASH_H
