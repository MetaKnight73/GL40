#ifndef FENETRESTATISTIQUESFITTS_H
#define FENETRESTATISTIQUESFITTS_H

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

#include "statistiquesFitts.h"

using namespace std;
using namespace QtCharts;

class FenetreStatistiquesFitts : public QWidget {
    Q_OBJECT

private:

    QTableView *tableauResultats;
    QStandardItemModel *modeleTableau;
    QPushButton *recommencer;
    QPushButton *retourMenu;
    QPushButton *quitter;
    vector<vector<StatistiquesFitts>> statsFitts;
    QHBoxLayout *layoutSuperieur;
    QChartView *chartView;

    double tempsTotalReel;
    double tempsTotalFitts;

public:

    explicit FenetreStatistiquesFitts(QWidget *parent = 0);
    FenetreStatistiquesFitts(vector<vector<StatistiquesFitts>> statistiquesFitts, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    void calcul(vector<StatistiquesFitts> statistiquesFitts);
    QChart* createLineChart(vector<StatistiquesFitts> statistiquesFitts) const;

public slots:

    void quitterApplication();
    void retournerMenu();
    void changerEnregistrement(int index);

};

#endif
