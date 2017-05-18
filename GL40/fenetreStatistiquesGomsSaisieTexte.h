#ifndef FENETRESTATISTIQUESGOMSSAISIETEXTE_H
#define FENETRESTATISTIQUESGOMSSAISIETEXTE_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <vector>
#include <QPushButton>
#include <QFileDialog>
#include <QTextDocument>
#include <QtCharts>
#include <fstream>
#include <iostream>
#include "statistiquesGomsSaisieTexte.h"

using namespace std;

class FenetreStatistiquesGomsSaisieTexte : public QWidget {
    Q_OBJECT
private:
    QTableView *tableauResultats;
    QStandardItemModel *modeleTableau;
    QPushButton *recommencer;
    QPushButton *retourMenu;
    QPushButton *quitter;

    double tempsTotalReel;
    double tempsTotalGoms;

public:
    explicit FenetreStatistiquesGomsSaisieTexte(QWidget *parent = 0);
    FenetreStatistiquesGomsSaisieTexte(std::vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    QChart* createLineChart(vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte) const;

public slots:
    void quitterApplication();
    void retournerMenu();

};

#endif
