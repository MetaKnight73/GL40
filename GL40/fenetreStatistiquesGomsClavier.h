#ifndef FENETRESTATISTIQUESGOMSCLAVIER_H
#define FENETRESTATISTIQUESGOMSCLAVIER_H

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

#include "statistiquesGomsClavier.h"

using namespace std;
using namespace QtCharts;

class FenetreStatistiquesGomsClavier: public QWidget {
    Q_OBJECT

private:

    QTableView *tableauResultats;
    QStandardItemModel *modeleTableau;
    QPushButton *recommencer;
    QPushButton *retourMenu;
    QPushButton *quitter;
    vector<vector<StatistiquesGomsClavier>> statsGomsClavier;
    QHBoxLayout *layoutSuperieur;
    QChartView *chartView;

    double tempsTotalReel;
    double tempsTotalGoms;

public:

    explicit FenetreStatistiquesGomsClavier(QWidget *parent = 0);
    FenetreStatistiquesGomsClavier(vector<vector<StatistiquesGomsClavier>> statistiquesGomsClavier, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    void calcul(vector<StatistiquesGomsClavier> statistiquesGomsClavier);
    QChart* createLineChart(vector<StatistiquesGomsClavier> statistiquesGomsClavier) const;

public slots:

    void quitterApplication();
    void retournerMenu();
    void changerEnregistrement(int index);

};

#endif
