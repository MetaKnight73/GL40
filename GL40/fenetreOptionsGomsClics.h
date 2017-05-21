#ifndef FENETREOPTIONSGOMSCLICS_H
#define FENETREOPTIONSGOMSCLICS_H

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QBoxLayout>

class FenetreOptionsGomsClics : public QDialog {
    Q_OBJECT

private:

    // Paramètres Goms-Clics
    double parametre1, parametre2, parametre3;

    // Layout
    QGridLayout *layout;
    QHBoxLayout *layoutUsers;
    QHBoxLayout *layoutValiderAnnuler;

    // Spinners
    QSpinBox *spinProfondeur;
    QDoubleSpinBox *spinParam1;
    QDoubleSpinBox *spinParam2;
    QDoubleSpinBox *spinParam3;

    // Labels
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *labelProfondeur;

    // Boutons
    QPushButton *start;
    QPushButton *cancel;
    QPushButton *userNormal;
    QPushButton *userExpert;

public:

    explicit FenetreOptionsGomsClics(QWidget *parent = 0);
    int getProfondeur();
    double getParametre1();
    double getParametre2();
    double getParametre3();

public slots:

    void restoreDefaultValues();
    void restoreExpertValues();
    void onChange();

};

#endif
