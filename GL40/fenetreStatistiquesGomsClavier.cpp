#include "fenetreStatistiquesGomsClavier.h"

#include <iostream>

#include "fenetrePrincipale.h"

FenetreStatistiquesGomsClavier::FenetreStatistiquesGomsClavier(QWidget *parent) : QWidget(parent) {}

FenetreStatistiquesGomsClavier::FenetreStatistiquesGomsClavier(vector<vector<StatistiquesGomsClavier>> statistiquesGomsClavier, QWidget *parent) : QWidget(parent) {
    statsGomsClavier = statistiquesGomsClavier;

    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Layout des boutons
    QHBoxLayout *layoutBoutons = new QHBoxLayout;

    //Layout supérieur
    layoutSuperieur = new QHBoxLayout;

    // Layout du tableau
    QHBoxLayout *layoutTableau = new QHBoxLayout;

    // Selection enregistrement
    QComboBox *listeEnregistrement = new QComboBox;
    for(unsigned int i=0; i<statsGomsClavier.size(); ++i){
        listeEnregistrement->addItem(statsGomsClavier[i][0].getDate().toString(QString("d/MM/yyyy - hh:mm:ss")));
    }
    listeEnregistrement->setCurrentIndex(statsGomsClavier.size()-1);
    listeEnregistrement->setEditable(true);
    listeEnregistrement->lineEdit()->setReadOnly(true);
    listeEnregistrement->lineEdit()->setAlignment(Qt::AlignCenter);

    QPalette *palette = new QPalette();
    const QColor *color = new QColor(225, 225, 225);
    palette->setColor(QPalette::All, QPalette::Base, *color);
    listeEnregistrement->setPalette(*palette);

    listeEnregistrement->setStyleSheet(QString("padding: 0px; font-size: 14px; font-weight: bold;"));
    listeEnregistrement->setFixedHeight(50);
    listeEnregistrement->setFixedWidth(300);
    for (int i = 0 ; i < listeEnregistrement->count() ; ++i) {
        listeEnregistrement->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    layoutBoutons->addWidget(listeEnregistrement);

    // Bouton recommencer
    recommencer = new QPushButton("Recommencer");
    recommencer->setFixedHeight(50);
    recommencer->setFixedWidth(315);
    recommencer->setStyleSheet("QPushButton {"
                               "border-radius: 10px;"
                               "color: #FFF;"
                               "font-size: 14px;"
                               "text-align: center;"
                               "font-weight: bold;"
                               "text-decoration: none;"
                               "background-color: #82BF56;"
                               "border-bottom: 4px solid #669644;"
                           "}"
                           "QPushButton:pressed {"
                               "border-bottom: 1px solid #669644;"
                           "}"
                           );
    layoutBoutons->addWidget(recommencer, 0, Qt::AlignCenter);

    // Bouton retour menu
    retourMenu = new QPushButton("Retour au menu");
    retourMenu->setFixedHeight(50);
    retourMenu->setFixedWidth(315);
    retourMenu->setStyleSheet("QPushButton {"
                              "border-radius: 10px;"
                              "font-size: 14px;"
                              "text-align: center;"
                              "font-weight: bold;"
                              "color: #FFF;"
                              "background-color: #F2CF66;"
                              "border-bottom: 4px solid #D1B358;"
                          "}"
                          "QPushButton:pressed {"
                              "border-bottom: 1px solid #D1B358;"
                          "}");
    layoutBoutons->addWidget(retourMenu, 0, Qt::AlignCenter);

    // Bouton quitter
    quitter = new QPushButton("Quitter l'application");
    quitter->setFixedHeight(50);
    quitter->setFixedWidth(315);
    quitter->setStyleSheet("QPushButton {"
                           "border-bottom: 4px solid #bb0000;"
                           "border-radius: 10px;"
                           "font-size: 14px;"
                           "text-align: center;"
                           "font-weight: bold;"
                           "color: #FFF;"
                           "background-color: #E74C3C;"
                           "border-bottom: 4px solid #BD3E31;"
                       "}"
                       "QPushButton:pressed {"
                           "border-bottom: 1px solid #BD3E31;"
                       "}");
    layoutBoutons->addWidget(quitter, 0, Qt::AlignCenter);

    // Initialisation du tableau final
    tableauResultats = new QTableView;
    tableauResultats->verticalHeader()->setHidden(true);
    tableauResultats->horizontalHeader()->setHidden(true);
    tableauResultats->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // On gère le modèle du tableau
    modeleTableau = new QStandardItemModel;
    tableauResultats->setModel(modeleTableau);

    // Titres des colonnes
    modeleTableau->setItem(0, 0, new QStandardItem("Colonne"));
    modeleTableau->setItem(0, 1, new QStandardItem("Ligne"));
    modeleTableau->setItem(0, 2, new QStandardItem("Temps Goms (prévu)"));
    modeleTableau->setItem(0, 3, new QStandardItem("Temps Goms (réel)"));

    tableauResultats->setColumnWidth(0, 75);
    tableauResultats->setColumnWidth(1, 75);
    tableauResultats->setColumnWidth(2, 150);
    tableauResultats->setColumnWidth(3, 150);
    tableauResultats->setMinimumWidth(453);
    tableauResultats->setMaximumWidth(453);

    layoutTableau->addWidget(tableauResultats);
    layoutTableau->setAlignment(Qt::AlignLeft);

    calcul(statsGomsClavier[statsGomsClavier.size()-1]); // dernier element

    // Dessin
    chartView = new QChartView(createLineChart(statsGomsClavier[statsGomsClavier.size()-1]), parent);
    chartView->setMinimumSize(830, 730);
    chartView->setMaximumSize(830, 730);
    chartView->setStyleSheet("border: 1px solid black");

    // Ajout des layouts
    layoutSuperieur->addLayout(layoutTableau);
    layoutSuperieur->addWidget(chartView, 0, Qt::AlignLeft);
    layout->addLayout(layoutSuperieur);
    layout->addLayout(layoutBoutons);

    connect(quitter, SIGNAL(clicked()), this, SLOT(quitterApplication()));
    connect(retourMenu, SIGNAL(clicked()), this, SLOT(retournerMenu()));
    connect(listeEnregistrement, SIGNAL(currentIndexChanged(int)), this, SLOT(changerEnregistrement(int)));

}

void FenetreStatistiquesGomsClavier::calcul(vector<StatistiquesGomsClavier> statistiquesGomsClavier){
    // On initialise les temps totaux à 0
    tempsTotalReel = 0;
    tempsTotalGoms = 0;

    modeleTableau->setRowCount(1); // retire les anciennes donnees

    // On remplit le tableau au fur et à mesure avec les valeurs obtenues au préalable
    for(unsigned int i = 1; i < statistiquesGomsClavier.size() + 1; i++) {

        if(i == 1) {
            statistiquesGomsClavier[i-1].calculTempsGomsFirst();
        }
        else {
            statistiquesGomsClavier[i-1].calculTempsGoms();
        }

        modeleTableau->setItem(i, 0, new QStandardItem(QString::number(floor(statistiquesGomsClavier[i-1].getNumBouton() / 4) + 1)));
        modeleTableau->setItem(i, 1, new QStandardItem(QString::number(fmod(statistiquesGomsClavier[i-1].getNumBouton(), 4) + 1)));
        modeleTableau->setItem(i, 2, new QStandardItem(QString::number(statistiquesGomsClavier[i-1].getTempsGoms())));
        modeleTableau->setItem(i, 3, new QStandardItem(QString::number(statistiquesGomsClavier[i-1].getTempsReal() / 1000)));

        // Calculate average times
        tempsTotalReel += ((double)statistiquesGomsClavier[i-1].getTempsReal() / 1000);
        tempsTotalGoms += statistiquesGomsClavier[i-1].getTempsGoms();

    }

    modeleTableau->setItem(statistiquesGomsClavier.size()+1, 1, new QStandardItem("Temps moyen"));
    modeleTableau->setItem(statistiquesGomsClavier.size()+1, 2, new QStandardItem(QString::number(tempsTotalGoms / statistiquesGomsClavier.size())));
    modeleTableau->setItem(statistiquesGomsClavier.size()+1, 3, new QStandardItem(QString::number(tempsTotalReel / statistiquesGomsClavier.size())));

    // Alignement central dans les cellules
    for(unsigned int i = 0; i < statistiquesGomsClavier.size() + 2; i++) {

        for(unsigned int j = 0; j < 4; j++) {

            modeleTableau->setData(modeleTableau->index(i, j), Qt::AlignCenter, Qt::TextAlignmentRole);

        }

    }
}

QPushButton* FenetreStatistiquesGomsClavier::getBoutonRecommencer() {

    return recommencer;

}

QChart* FenetreStatistiquesGomsClavier::createLineChart(vector<StatistiquesGomsClavier> statistiquesGomsClavier) const {

    QChart *chart = new QChart();

    chart->setTitle("Comparaison des temps Goms théorique et réalisé");

    QString nameTheorique("Temps théorique");
    QString nameReel("Temps réalisé");

    QLineSeries *serieTheorique = new QLineSeries(chart);
    QLineSeries *serieReel = new QLineSeries(chart);

    for (unsigned int i = 1; i < statistiquesGomsClavier.size() + 1; i++) {

        if(i == 1) {
            statistiquesGomsClavier[i-1].calculTempsGomsFirst();
        }
        else {
            statistiquesGomsClavier[i-1].calculTempsGoms();
        }

        serieTheorique->append(i-1, statistiquesGomsClavier[i-1].getTempsGoms());
        serieReel->append(i-1, (double)statistiquesGomsClavier[i-1].getTempsReal() / 1000);

    }

    serieTheorique->setName(nameTheorique);
    serieReel->setName(nameReel);

    chart->addSeries(serieTheorique);
    chart->addSeries(serieReel);

    chart->createDefaultAxes();

    return chart;
}

void FenetreStatistiquesGomsClavier::quitterApplication() {

    parentWidget()->close();

}

void FenetreStatistiquesGomsClavier::retournerMenu() {

    parentWidget()->close();
    FenetrePrincipale *fenetre = new FenetrePrincipale;
    fenetre->statusBar()->setSizeGripEnabled(false);
    fenetre->show();

}

void FenetreStatistiquesGomsClavier::changerEnregistrement(int index){
    calcul(statsGomsClavier[index]);
    //changer graphique
    layoutSuperieur->removeWidget(chartView);

    chartView = new QChartView(createLineChart(statsGomsClavier[index]), parentWidget());
    chartView->setMinimumSize(830, 730);
    chartView->setMaximumSize(830, 730);
    chartView->setStyleSheet("border: 1px solid black");

    layoutSuperieur->addWidget(chartView, 0, Qt::AlignLeft);
}
