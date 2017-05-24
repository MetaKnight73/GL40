#ifndef FENETREOPTIONSGOMSSAISIETEXTE_H
#define FENETREOPTIONSGOMSSAISIETEXTE_H

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QBoxLayout>

class FenetreOptionsGomsSaisieTexte : public QDialog {
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
    QSpinBox *spinNbMots;
    QSpinBox *spinParam1;
    QDoubleSpinBox *spinParam2;

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

    explicit FenetreOptionsGomsSaisieTexte(QWidget *parent = 0);
    int getNbMots();
    int getParametre1();
    double getParametre2();

public slots:

    void restoreDefaultValues();
    void restoreExpertValues();
    void onChange();

};

#endif
