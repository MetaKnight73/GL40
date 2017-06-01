#ifndef FENETRESTATISTIQUESGOMSCLAVIER_H
#define FENETRESTATISTIQUESGOMSCLAVIER_H

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

    double tempsTotalReel;
    double tempsTotalGoms;

public:

    explicit FenetreStatistiquesGomsClavier(QWidget *parent = 0);
    FenetreStatistiquesGomsClavier(vector<StatistiquesGomsClavier> statistiquesGomsClavier, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    QChart* createLineChart(vector<StatistiquesGomsClavier> statistiquesGomsClavier) const;

public slots:

    void quitterApplication();
    void retournerMenu();

};

#endif
