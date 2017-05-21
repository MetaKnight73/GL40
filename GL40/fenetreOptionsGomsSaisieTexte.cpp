#include "fenetreOptionsGomsSaisieTexte.h"

FenetreOptionsGomsSaisieTexte::FenetreOptionsGomsSaisieTexte(QWidget *parent) : QDialog(parent) {

    // On assigne une taille fixe de fenêtre à 400x200
    setFixedSize(400,200);

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
    labelMots = new QLabel;

    // Spinners
    spinParam1 = new QDoubleSpinBox;
    spinParam2 = new QDoubleSpinBox;
    spinNbMots = new QSpinBox;
    spinNbMots->setAlignment(Qt::AlignCenter);
    spinParam1->setFixedWidth(110);
    spinParam1->setAlignment(Qt::AlignCenter);
    spinParam2->setFixedWidth(110);
    spinParam2->setAlignment(Qt::AlignCenter);

    // Assignation des textes des labels
    label1->setText("Nombre de caractères maximal d'un mot : ");
    label2->setText("Temps d'activité mentale (M) : ");
    labelMots->setText("Sélectionnez le nombre de mots à saisir : ");

    // On gère les valeurs du spinner 1
    spinParam1->setMinimum(1);
    spinParam1->setMaximum(20);
    spinParam1->setSingleStep(1);
    spinParam1->setValue(10);

    // On gère les valeurs du spinner 2
    spinParam2->setMinimum(0.01);
    spinParam2->setMaximum(2);
    spinParam2->setSingleStep(0.01);
    spinParam2->setValue(1.35);

    // On gère les valeurs du spinner du nombre de clics
    spinNbMots->setMinimum(1);
    spinNbMots->setMaximum(20);
    spinNbMots->setSingleStep(1);
    spinNbMots->setValue(10);

    // Textes de boutons
    start = new QPushButton("Valider");
    start->setFixedHeight(40);
    start->setStyleSheet(QString("background-color: #32CD32; border: 1px solid black;"));

    cancel = new QPushButton("Annuler");
    cancel->setFixedHeight(40);
    cancel->setStyleSheet(QString("background-color: #DC143C; border: 1px solid black;"));

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
    layout->addWidget(labelMots, 2, 0);
    layout->addWidget(spinNbMots, 2, 1);
    layout->addLayout(layoutUsers, 3, 0, 1, 6, 0);
    layout->addLayout(layoutValiderAnnuler, 4, 0, 1, 6, 0);

    setLayout(layout);

    userNormal->setDown(true);
    userNormal->setEnabled(false);

    // Les connexions
    connect(start, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(userNormal, SIGNAL(clicked()), this, SLOT(restoreDefaultValues()));
    connect(userExpert, SIGNAL(clicked()), this, SLOT(restoreExpertValues()));
    connect(spinParam2, SIGNAL(valueChanged(double)), this, SLOT(onChange()));

}

void FenetreOptionsGomsSaisieTexte::restoreDefaultValues() {

    spinParam1->setValue(10);
    spinParam2->setValue(1.35);
    spinNbMots->setValue(10);
    userExpert->setDown(false);
    userExpert->setEnabled(true);

}

void FenetreOptionsGomsSaisieTexte::restoreExpertValues() {

    spinParam1->setValue(10);
    spinParam2->setValue(1.25);
    spinNbMots->setValue(10);
    userNormal->setDown(false);
    userNormal->setEnabled(true);

}

void FenetreOptionsGomsSaisieTexte::onChange() {

    double param2 = spinParam2->value();

    if(param2 == (double)1.35) {

        userNormal->setDown(true);
        userNormal->setDisabled(true);

    }

    else if(param2 == (double)1.25) {

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

int FenetreOptionsGomsSaisieTexte::getNbMots() {

    return spinNbMots->value();

}

double FenetreOptionsGomsSaisieTexte::getParametre1() {

    return spinParam1->value();

}

double FenetreOptionsGomsSaisieTexte::getParametre2() {

    return spinParam2->value();

}
