#ifndef FENETREOPTIONSFITTS_H
#define FENETREOPTIONSFITTS_H

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QBoxLayout>

class FenetreOptionsFitts : public QDialog {
    Q_OBJECT
private:
    // Paramètres Fitts
    double parametre1, parametre2;

    // Layout
    QGridLayout *layout;
    QHBoxLayout *layoutUsers;
    QHBoxLayout *layoutValiderAnnuler;

    // Spinners
    QSpinBox *spinNbClics;
    QDoubleSpinBox *spinParam1;
    QDoubleSpinBox *spinParam2;

    // Labels
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *labelClics;

    // Boutons
    QPushButton *start;
    QPushButton *cancel;
    QPushButton *userNormal;
    QPushButton *userExpert;

public:
    explicit FenetreOptionsFitts(QWidget *parent = 0);
    int getNbClics();
    double getParametre1();
    double getParametre2();

public slots:
    void restoreDefaultValues();
    void restoreExpertValues();
    void onChange();

};

#endif
