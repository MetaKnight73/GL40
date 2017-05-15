#ifndef FENETRESTATISTIQUES_H
#define FENETRESTATISTIQUES_H

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
#include "statistiques.h"

using namespace std;

class FenetreStatistiques : public QWidget {
    Q_OBJECT
private:
    QTableView *tableauResultats;
    QStandardItemModel *modeleTableau;
    QPushButton *recommencer;
    QPushButton *retourMenu;
    QPushButton *quitter;

    double tempsTotalReel;
    double tempsTotalFitts;

public:
    explicit FenetreStatistiques(QWidget *parent = 0);
    FenetreStatistiques(std::vector<Statistiques> statistiques, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    QChart* createLineChart(vector<Statistiques> statistiques) const;

public slots:
    void quitterApplication();
    void retournerMenu();

};

#endif // FENETRESTATISTIQUES_H
