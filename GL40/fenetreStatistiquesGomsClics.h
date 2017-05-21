#ifndef FENETRESTATISTIQUESGOMSCLICS_H
#define FENETRESTATISTIQUESGOMSCLICS_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextDocument>
#include <QBoxLayout>

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

    double tempsTotalReel;
    double tempsTotalGoms;

public:

    explicit FenetreStatistiquesGomsClics(QWidget *parent = 0);
    FenetreStatistiquesGomsClics(vector<StatistiquesGomsClics> statistiquesGomsClics, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    QChart* createLineChart(vector<StatistiquesGomsClics> statistiquesGomsClics) const;

public slots:

    void quitterApplication();
    void retournerMenu();

};

#endif
