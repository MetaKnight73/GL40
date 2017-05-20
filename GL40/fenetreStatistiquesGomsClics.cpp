#include "fenetreStatistiquesGomsClics.h"
#include "fenetrePrincipale.h"
#include <QBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

using namespace QtCharts;
using namespace std;

FenetreStatistiquesGomsClics::FenetreStatistiquesGomsClics(QWidget *parent) : QWidget(parent) {}

FenetreStatistiquesGomsClics::FenetreStatistiquesGomsClics(vector<StatistiquesGomsClics> statistiquesGomsClics, QWidget *parent) : QWidget(parent) {

    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Layout des boutons
    QHBoxLayout *layoutBoutons = new QHBoxLayout;

    //Layout supérieur
    QHBoxLayout *layoutSuperieur = new QHBoxLayout;

    // Layout du tableau
    QHBoxLayout *layoutTableau = new QHBoxLayout;

    // Bouton recommencer
    recommencer = new QPushButton("Recommencer");
    recommencer->setFixedHeight(50);
    recommencer->setFixedWidth(400);
    layoutBoutons->addWidget(recommencer, 0, Qt::AlignCenter);

    // Bouton retour menu
    retourMenu = new QPushButton("Retour au menu");
    retourMenu->setFixedHeight(50);
    retourMenu->setFixedWidth(400);
    layoutBoutons->addWidget(retourMenu, 0, Qt::AlignCenter);

    // Bouton quitter
    quitter = new QPushButton("Quitter");
    quitter->setFixedHeight(50);
    quitter->setFixedWidth(400);
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
    modeleTableau->setItem(0, 0, new QStandardItem("colonne"));
    modeleTableau->setItem(0, 1, new QStandardItem("ligne"));
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

    // On initialise les temps totaux à 0
    tempsTotalReel = 0;
    tempsTotalGoms = 0;

    // On remplit le tableau au fur et à mesure avec les valeurs obtenues au préalable
    for(unsigned int i=1; i<statistiquesGomsClics.size()+1; i++) {
        statistiquesGomsClics[i-1].calculTempsGoms();

        modeleTableau->setItem(i, 0, new QStandardItem(QString::number(fmod(statistiquesGomsClics[i-1].getNumBouton(),4)+1)));
        modeleTableau->setItem(i, 1, new QStandardItem(QString::number(floor(statistiquesGomsClics[i-1].getNumBouton()/4)+1)));
        modeleTableau->setItem(i, 2, new QStandardItem(QString::number(statistiquesGomsClics[i-1].getTempsGoms())));
        modeleTableau->setItem(i, 3, new QStandardItem(QString::number(statistiquesGomsClics[i-1].getTempsReal()/1000)));

        // Calculate average times
        tempsTotalReel += ((double)statistiquesGomsClics[i-1].getTempsReal()/1000);
        tempsTotalGoms += statistiquesGomsClics[i-1].getTempsGoms();
    }

    modeleTableau->setItem(statistiquesGomsClics.size()+1, 1, new QStandardItem("Temps total"));
    modeleTableau->setItem(statistiquesGomsClics.size()+1, 2, new QStandardItem(QString::number(tempsTotalGoms)));
    modeleTableau->setItem(statistiquesGomsClics.size()+1, 3, new QStandardItem(QString::number(tempsTotalReel)));

    // Alignement central dans les cellules
    for(unsigned int i = 0; i<statistiquesGomsClics.size()+2; i++) {
        for(unsigned int j = 0; j<3; j++) {
            modeleTableau->setData(modeleTableau->index(i, j), Qt::AlignCenter, Qt::TextAlignmentRole);
        }
    }

    // Dessin
    QChartView *chartView = new QChartView(createLineChart(statistiquesGomsClics), parent);
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

}

QPushButton* FenetreStatistiquesGomsClics::getBoutonRecommencer() {
    return recommencer;
}

QChart* FenetreStatistiquesGomsClics::createLineChart(vector<StatistiquesGomsClics> statistiquesGomsClics) const {
    QChart *chart = new QChart();

    chart->setTitle("Comparaison des temps Goms théorique et réalisé");

    QString nameTheorique("Temps théorique");
    QString nameReel("Temps réalisé");

    QLineSeries *serieTheorique = new QLineSeries(chart);
    QLineSeries *serieReel = new QLineSeries(chart);

    serieTheorique->append(0, 0);
    serieReel->append(0, 0);

    for (unsigned int i=1; i<statistiquesGomsClics.size()+1; i++) {
        serieTheorique->append(i, statistiquesGomsClics[i-1].getTempsGoms());
        serieReel->append(i, (double)statistiquesGomsClics[i-1].getTempsReal()/1000);
    }

    serieTheorique->setName(nameTheorique);
    serieReel->setName(nameReel);

    chart->addSeries(serieTheorique);
    chart->addSeries(serieReel);

    chart->createDefaultAxes();

    return chart;
}

void FenetreStatistiquesGomsClics::quitterApplication() {

    parentWidget()->close();

}

void FenetreStatistiquesGomsClics::retournerMenu() {

    parentWidget()->close();
    FenetrePrincipale *fenetre = new FenetrePrincipale;
    fenetre->statusBar()->setSizeGripEnabled(false);
    fenetre->show();

}
