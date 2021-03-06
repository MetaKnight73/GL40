#ifndef FENETREOPTIONSGOMSCLAVIER_H
#define FENETREOPTIONSGOMSCLAVIER_H

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QBoxLayout>

class FenetreOptionsGomsClavier : public QDialog
{
    Q_OBJECT

public:

    // Paramètres Goms-Clics
    double parametre1, parametre2;

    // Layout
    QGridLayout *layout;
    QHBoxLayout *layoutUsers;
    QHBoxLayout *layoutValiderAnnuler;

    // Spinners
    QSpinBox *spinProfondeur;
    QDoubleSpinBox *spinParam1;
    QDoubleSpinBox *spinParam2;

    // Labels
    QLabel *label1;
    QLabel *label2;
    QLabel *labelProfondeur;
    QLabel *labelRetourDepart;

    // Boutons
    QPushButton *start;
    QPushButton *cancel;
    QPushButton *userNormal;
    QPushButton *userExpert;

    // CheckBox
    QCheckBox *cbRetourDepart;

public:

    explicit FenetreOptionsGomsClavier(QWidget *parent = 0);
    int getProfondeur();
    double getParametre1();
    double getParametre2();
    bool getRetourDepart();

public slots:

    void restoreDefaultValues();
    void restoreExpertValues();
    void onChange();
};

#endif
