#include "fenetreOptionsGomsClics.h"

FenetreOptionsGomsClics::FenetreOptionsGomsClics(QWidget *parent) : QDialog(parent) {

    // On assigne une taille fixe de fenêtre à 400x200
    setFixedSize(450, 200);

    // Layouts de la fenêtre
    layout = new QGridLayout;
    layout->setHorizontalSpacing(5);
    layout->setColumnMinimumWidth(0, 15);
    layout->setColumnMinimumWidth(1, 15);
    layout->setColumnMinimumWidth(2, 15);
    layout->setColumnMinimumWidth(3, 15);
    layoutUsers = new QHBoxLayout;
    layoutValiderAnnuler = new QHBoxLayout;

    // Labels de la fenêtre
    label1 = new QLabel;
    label2 = new QLabel;
    label3 = new QLabel;
    labelProfondeur = new QLabel;

    // Spinners
    spinParam1 = new QDoubleSpinBox;
    spinParam2 = new QDoubleSpinBox;
    spinParam3 = new QDoubleSpinBox;
    spinProfondeur = new QSpinBox;
    spinProfondeur->setAlignment(Qt::AlignCenter);
    spinParam1->setFixedWidth(110);
    spinParam1->setAlignment(Qt::AlignCenter);
    spinParam2->setFixedWidth(110);
    spinParam2->setAlignment(Qt::AlignCenter);
    spinParam3->setFixedWidth(110);
    spinParam3->setAlignment(Qt::AlignCenter);

    // Assignation des textes des labels
    label1->setText("Temps moyen pointage (P) : ");
    label2->setText("Temps d'activité mentale (M) : ");
    label3->setText("Temps moyen frappe (K) : ");
    labelProfondeur->setText("Sélectionnez le nombre de répertoires : ");

    // On gère les valeurs du spinner 1
    spinParam1->setMinimum(0.01);
    spinParam1->setMaximum(3);
    spinParam1->setSingleStep(0.01);
    spinParam1->setValue(1.1);

    // On gère les valeurs du spinner 2
    spinParam2->setMinimum(0.01);
    spinParam2->setMaximum(2);
    spinParam2->setSingleStep(0.01);
    spinParam2->setValue(1.35);

    // On gère les valeurs du spinner 3
    spinParam3->setMinimum(0.01);
    spinParam3->setMaximum(2);
    spinParam3->setSingleStep(0.01);
    spinParam3->setValue(0.1);

    // On gère les valeurs du spinner du nombre de clics
    spinProfondeur->setMinimum(1);
    spinProfondeur->setMaximum(20);
    spinProfondeur->setSingleStep(1);
    spinProfondeur->setValue(10);

    // Textes de boutons
    start = new QPushButton("Valider");
    start->setFixedHeight(40);
    start->setStyleSheet(QString("background-color: #32CD32; border: 1px solid black;  border-radius: 2px;"));

    cancel = new QPushButton("Annuler");
    cancel->setFixedHeight(40);
    cancel->setStyleSheet(QString("background-color: #DC143C; border: 1px solid black;  border-radius: 2px;"));

    userNormal = new QPushButton("Utilisateur normal (par défaut)");
    userNormal->setFixedHeight(40);

    userExpert = new QPushButton("Utilisateur expert");
    userExpert->setFixedHeight(40);

    layoutUsers->addWidget(userNormal);
    layoutUsers->addWidget(userExpert);

    layoutValiderAnnuler->addWidget(start);
    layoutValiderAnnuler->addWidget(cancel);

    // On ajoute les éléments dans la page
    layout->addWidget(label1, 0, 0);
    layout->addWidget(spinParam1, 0, 1);
    layout->addWidget(label2, 1, 0);
    layout->addWidget(spinParam2, 1, 1);
    layout->addWidget(label3, 2, 0);
    layout->addWidget(spinParam3, 2, 1);
    layout->addWidget(labelProfondeur, 3, 0);
    layout->addWidget(spinProfondeur, 3, 1);
    layout->addLayout(layoutUsers, 4, 0, 1, 6, 0);
    layout->addLayout(layoutValiderAnnuler, 5, 0, 1, 6, 0);

    setLayout(layout);

    userNormal->setDown(true);
    userNormal->setEnabled(false);

    // Les connexions
    connect(start, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(userNormal, SIGNAL(clicked()), this, SLOT(restoreDefaultValues()));
    connect(userExpert, SIGNAL(clicked()), this, SLOT(restoreExpertValues()));
    connect(spinParam1, SIGNAL(valueChanged(double)), this, SLOT(onChange()));
    connect(spinParam2, SIGNAL(valueChanged(double)), this, SLOT(onChange()));
    connect(spinParam3, SIGNAL(valueChanged(double)), this, SLOT(onChange()));

}

void FenetreOptionsGomsClics::restoreDefaultValues() {

    spinParam1->setValue(1.1);
    spinParam2->setValue(1.35);
    spinParam3->setValue(0.1);
    spinProfondeur->setValue(10);
    userExpert->setDown(false);
    userExpert->setEnabled(true);

}

void FenetreOptionsGomsClics::restoreExpertValues() {

    spinParam1->setValue(0.9);
    spinParam2->setValue(1.25);
    spinParam3->setValue(0.08);
    spinProfondeur->setValue(10);
    userNormal->setDown(false);
    userNormal->setEnabled(true);

}

void FenetreOptionsGomsClics::onChange() {

    double param1 = spinParam1->value();
    double param2 = spinParam2->value();
    double param3 = spinParam3->value();

    if(param1 == (double)1.1 && param2 == (double)1.35 && param3 == (double)0.1) {

        userNormal->setDown(true);
        userNormal->setDisabled(true);

    }

    else if(param1 == (double)0.9 && param2 == (double)1.25 && param3 == (double)0.08) {

        userExpert->setDown(true);
        userExpert->setDisabled(true);

    }

    else {

        userNormal->setDown(false);
        userExpert->setDown(false);
        userNormal->setEnabled(true);
        userExpert->setEnabled(true);

    }

}

int FenetreOptionsGomsClics::getProfondeur() {

    return spinProfondeur->value();

}

double FenetreOptionsGomsClics::getParametre1() {

    return spinParam1->value();

}

double FenetreOptionsGomsClics::getParametre2() {

    return spinParam2->value();

}

double FenetreOptionsGomsClics::getParametre3() {

    return spinParam3->value();

}
