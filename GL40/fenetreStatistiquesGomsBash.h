#ifndef FENETRESTATISTIQUESGOMSBASH_H
#define FENETRESTATISTIQUESGOMSBASH_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextDocument>
#include <QComboBox>

#include <QtCharts>

#include <vector>

#include "statistiquesGomsBash.h"

using namespace std;
using namespace QtCharts;

class FenetreStatistiquesGomsBash : public QWidget {
    Q_OBJECT

private:

    QTableView *tableauResultats;
    QStandardItemModel *modeleTableau;
    QPushButton *recommencer;
    QPushButton *retourMenu;
    QPushButton *quitter;
    vector<vector<StatistiquesGomsBash>> statsGomsBash;
    QHBoxLayout *layoutSuperieur;
    QChartView *chartView;

    double tempsTotalReel;
    double tempsTotalGoms;

public:

    explicit FenetreStatistiquesGomsBash(QWidget *parent = 0);
    FenetreStatistiquesGomsBash(vector<vector<StatistiquesGomsBash>> statistiquesGomsBash, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    void calcul(vector<StatistiquesGomsBash> statistiquesGomsBash);
    QChart* createLineChart(vector<StatistiquesGomsBash> statistiquesGomsBash) const;

public slots:

    void quitterApplication();
    void retournerMenu();
    void changerEnregistrement(int index);

};

#endif // FENETRESTATISTIQUESGOMSBASH_H
