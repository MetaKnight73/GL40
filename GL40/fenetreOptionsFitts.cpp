#include "fenetreOptionsFitts.h"

FenetreOptionsFitts::FenetreOptionsFitts(QWidget *parent) : QDialog(parent) {

    // On assigne une taille fixe de fenêtre à 400x200
    setFixedSize(450, 200);

    // Layouts de la fenêtre
    layout = new QGridLayout;
    layout->setHorizontalSpacing(5);
    layout->setColumnMinimumWidth(0, 15);
    layout->setColumnMinimumWidth(1, 15);
    layout->setColumnMinimumWidth(2, 70);
    layout->setColumnMinimumWidth(3, 15);
    layoutUsers = new QHBoxLayout;
    layoutValiderAnnuler = new QHBoxLayout;

    // Labels de la fenêtre
    label1 = new QLabel;
    label2 = new QLabel;
    label3 = new QLabel;
    labelClics = new QLabel;

    // Spinners
    spinParam1 = new QDoubleSpinBox;
    spinParam2 = new QDoubleSpinBox;
    spinNbClics = new QSpinBox;
    spinNbClics->setAlignment(Qt::AlignCenter);
    spinNbClics->setFixedWidth(210);
    spinParam1->setFixedWidth(110);
    spinParam1->setAlignment(Qt::AlignCenter);
    spinParam2->setFixedWidth(120);
    spinParam2->setAlignment(Qt::AlignCenter);

    // Assignation des textes des labels
    label1->setText("T = ");
    label2->setText("+");
    label3->setText(" x log(D/L + 0.5) ");
    labelClics->setText("Nombre de clics à réaliser : ");

    // On gère les valeurs du spinner 1
    spinParam1->setMinimum(0);
    spinParam1->setMaximum(10);
    spinParam1->setSingleStep(0.01);
    spinParam1->setValue(1.03);

    // On gère les valeurs du spinner 2
    spinParam2->setMinimum(0.01);
    spinParam2->setMaximum(10);
    spinParam2->setSingleStep(0.01);
    spinParam2->setValue(0.1);

    // On gère les valeurs du spinner du nombre de clics
    spinNbClics->setMinimum(0);
    spinNbClics->setMaximum(1000);
    spinNbClics->setSingleStep(10);
    spinNbClics->setValue(10);

    // Textes de boutons
    start = new QPushButton("Valider");
    start->setFixedHeight(40);
    start->setStyleSheet(QString("background-color: #32CD32; border: 1px solid black; border-radius: 2px;"));

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
    layout->addWidget(label2, 0, 2, 1, 1, Qt::AlignCenter);
    layout->addWidget(spinParam2, 0, 3);
    layout->addWidget(label3, 0, 4);
    layout->addWidget(labelClics, 1, 0, 1, 4);
    layout->addWidget(spinNbClics, 1, 3);
    layout->addLayout(layoutUsers, 2, 0, 1, 6, 0);
    layout->addLayout(layoutValiderAnnuler, 3, 0, 1, 6, 0);

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

}

void FenetreOptionsFitts::restoreDefaultValues() {

    spinParam1->setValue(1.03);
    spinParam2->setValue(0.1);
    userExpert->setDown(false);
    userExpert->setEnabled(true);

}

void FenetreOptionsFitts::restoreExpertValues() {

    spinParam1->setValue(0.9);
    spinParam2->setValue(0.1);
    userNormal->setDown(false);
    userNormal->setEnabled(true);

}

void FenetreOptionsFitts::onChange() {

    double param1 = spinParam1->value();
    double param2 = spinParam2->value();

    if(param1 == (double)1.03) {

        if(param2 == (double)0.1) {

            userNormal->setDown(true);
            userNormal->setDisabled(true);

        }

        else {

            userNormal->setDown(false);
            userNormal->setEnabled(true);

        }
    }

    else if(param1 == (double)0.9) {

        if(param2 == (double)0.1) {

            userExpert->setDown(true);
            userExpert->setDisabled(true);

        }

        else {

            userExpert->setDown(false);
            userExpert->setEnabled(true);

        }
    }

    else {

        userNormal->setDown(false);
        userExpert->setDown(false);
        userNormal->setEnabled(true);
        userExpert->setEnabled(true);

    }

}

int FenetreOptionsFitts::getNbClics() {

    return spinNbClics->value();

}

double FenetreOptionsFitts::getParametre1() {

    return spinParam1->value();

}

double FenetreOptionsFitts::getParametre2() {

    return spinParam2->value();

}

