#ifndef FENETRESTATISTIQUESGOMSCLICS_H
#define FENETRESTATISTIQUESGOMSCLICS_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextDocument>
#include <QBoxLayout>
#include <QComboBox>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <vector>

#include "statistiquesGomsClics.h"

using namespace std;
using namespace QtCharts;

class FenetreStatistiquesGomsClics: public QWidget {
    Q_OBJECT

private:

    QTableView *tableauResultats;
    QStandardItemModel *modeleTableau;
    QPushButton *recommencer;
    QPushButton *retourMenu;
    QPushButton *quitter;
    vector<vector<StatistiquesGomsClics>> statsGomsClics;
    QHBoxLayout *layoutSuperieur;
    QChartView *chartView;

    double tempsTotalReel;
    double tempsTotalGoms;

public:

    explicit FenetreStatistiquesGomsClics(QWidget *parent = 0);
    FenetreStatistiquesGomsClics(vector<vector<StatistiquesGomsClics>> statistiquesGomsClics, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    void calcul(vector<StatistiquesGomsClics> statistiquesGomsClics);
    QChart* createLineChart(vector<StatistiquesGomsClics> statistiquesGomsClics) const;

public slots:

    void quitterApplication();
    void retournerMenu();
    void changerEnregistrement(int index);

};

#endif
