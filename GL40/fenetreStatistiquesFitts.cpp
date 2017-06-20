#include "fenetreStatistiquesFitts.h"
#include "fenetrePrincipale.h"

FenetreStatistiquesFitts::FenetreStatistiquesFitts(QWidget *parent) : QWidget(parent) {}

FenetreStatistiquesFitts::FenetreStatistiquesFitts(vector<vector<StatistiquesFitts>> statistiquesFitts, QWidget *parent) : QWidget(parent) {

    statsFitts = statistiquesFitts;

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
    for(unsigned int i = 0; i < statsFitts.size(); ++i) {
        listeEnregistrement->addItem(statsFitts[i][0].getDate().toString(QString("d/MM/yyyy - hh:mm:ss")));
    }

    listeEnregistrement->setCurrentIndex(statsFitts.size()-1);
    listeEnregistrement->setEditable(true);
    listeEnregistrement->lineEdit()->setReadOnly(true);
    listeEnregistrement->lineEdit()->setAlignment(Qt::AlignCenter);

    QPalette *palette = new QPalette();
    const QColor *color = new QColor(225, 225, 225);
    palette->setColor(QPalette::All, QPalette::Base, *color);
    listeEnregistrement->setPalette(*palette);

    listeEnregistrement->setStyleSheet(QString("padding: 0px;"));
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
    layoutBoutons->addWidget(recommencer, 0, Qt::AlignCenter);

    // Bouton retour menu
    retourMenu = new QPushButton("Retour au menu");
    retourMenu->setFixedHeight(50);
    retourMenu->setFixedWidth(315);
    layoutBoutons->addWidget(retourMenu, 0, Qt::AlignCenter);

    // Bouton quitter
    quitter = new QPushButton("Quitter");
    quitter->setFixedHeight(50);
    quitter->setFixedWidth(315);
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
    modeleTableau->setItem(0, 0, new QStandardItem("Distance"));
    modeleTableau->setItem(0, 1, new QStandardItem("Largeur du bouton"));
    modeleTableau->setItem(0, 2, new QStandardItem("Temps Fitts (prévu)"));
    modeleTableau->setItem(0, 3, new QStandardItem("Temps réalisé (réel)"));

    tableauResultats->setColumnWidth(0, 60);
    tableauResultats->setColumnWidth(1, 130);
    tableauResultats->setColumnWidth(2, 130);
    tableauResultats->setColumnWidth(3, 130);
    tableauResultats->setMinimumWidth(453);
    tableauResultats->setMaximumWidth(453);

    layoutTableau->addWidget(tableauResultats);
    layoutTableau->setAlignment(Qt::AlignLeft);

    calcul(statsFitts[statsFitts.size()-1]); // dernier element

    // Dessin
    chartView = new QChartView(createLineChart(statsFitts[statsFitts.size()-1]), parent);
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

void FenetreStatistiquesFitts::calcul(vector<StatistiquesFitts> statistiquesFitts){
    // On initialise les temps totaux à 0
    tempsTotalReel = 0;
    tempsTotalFitts = 0;

    // On remplit le tableau au fur et à mesure avec les valeurs obtenues au préalable

    modeleTableau->setRowCount(1); // retire les anciennes donnees

    for(unsigned int i = 1; i < statistiquesFitts.size() + 1; i++) {

        modeleTableau->setItem(i, 0, new QStandardItem(QString::number(statistiquesFitts[i-1].getDistance())));
        modeleTableau->setItem(i, 1, new QStandardItem(QString::number(statistiquesFitts[i-1].getLargeurBouton())));
        modeleTableau->setItem(i, 2, new QStandardItem(QString::number(statistiquesFitts[i-1].getTempsFitts())));
        modeleTableau->setItem(i, 3, new QStandardItem(QString::number((double)statistiquesFitts[i-1].getTempsDeplacementSouris() / 1000)));

        // Calcul du temps moyen
        tempsTotalReel += (double)statistiquesFitts[i-1].getTempsDeplacementSouris() / 1000;
        tempsTotalFitts += statistiquesFitts[i-1].getTempsFitts();

    }

    modeleTableau->setItem(statistiquesFitts.size()+1, 1, new QStandardItem("Temps moyen"));
    modeleTableau->setItem(statistiquesFitts.size()+1, 2, new QStandardItem(QString::number(tempsTotalFitts / statistiquesFitts.size())));
    modeleTableau->setItem(statistiquesFitts.size()+1, 3, new QStandardItem(QString::number(tempsTotalReel / statistiquesFitts.size())));

    // Alignement central dans les cellules
    for(unsigned int i = 0; i < statistiquesFitts.size() + 2; i++) {

        for(unsigned int j = 0; j < 4; j++) {

            modeleTableau->setData(modeleTableau->index(i, j), Qt::AlignCenter, Qt::TextAlignmentRole);

        }

    }
}

QPushButton* FenetreStatistiquesFitts::getBoutonRecommencer() {

    return recommencer;

}

QChart* FenetreStatistiquesFitts::createLineChart(vector<StatistiquesFitts> statistiquesFitts) const {

    QChart *chart = new QChart();

    chart->setTitle("Comparaison des temps Fitts théorique et réalisé");

    QString nameTheorique("Temps théorique");
    QString nameReel("Temps réalisé");

    QLineSeries *serieTheorique = new QLineSeries(chart);
    QLineSeries *serieReel = new QLineSeries(chart);

    for (unsigned int i = 1; i < statistiquesFitts.size() + 1; i++) {

        serieTheorique->append(i-1, statistiquesFitts[i-1].getTempsFitts());
        serieReel->append(i-1, (double)statistiquesFitts[i-1].getTempsDeplacementSouris() / 1000);

    }

    serieTheorique->setName(nameTheorique);
    serieReel->setName(nameReel);

    chart->addSeries(serieTheorique);
    chart->addSeries(serieReel);

    chart->createDefaultAxes();

    return chart;
}

void FenetreStatistiquesFitts::quitterApplication() {

    parentWidget()->close();

}

void FenetreStatistiquesFitts::retournerMenu() {

    parentWidget()->close();
    FenetrePrincipale *fenetre = new FenetrePrincipale;
    fenetre->statusBar()->setSizeGripEnabled(false);
    fenetre->show();

}

void FenetreStatistiquesFitts::changerEnregistrement(int index){
    calcul(statsFitts[index]);
    //changer graphique
    layoutSuperieur->removeWidget(chartView);

    chartView = new QChartView(createLineChart(statsFitts[index]), parentWidget());
    chartView->setMinimumSize(830, 730);
    chartView->setMaximumSize(830, 730);
    chartView->setStyleSheet("border: 1px solid black");

    layoutSuperieur->addWidget(chartView, 0, Qt::AlignLeft);
}
