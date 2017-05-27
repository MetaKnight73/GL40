#ifndef FENETRESTATISTIQUESGOMSBASH_H
#define FENETRESTATISTIQUESGOMSBASH_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextDocument>

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

    double tempsTotalReel;
    double tempsTotalGoms;

public:

    explicit FenetreStatistiquesGomsBash(QWidget *parent = 0);
    FenetreStatistiquesGomsBash(vector<StatistiquesGomsBash> statistiquesGomsBash, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    QChart* createLineChart(vector<StatistiquesGomsBash> statistiquesGomsBash) const;

public slots:

    void quitterApplication();
    void retournerMenu();

};

#endif // FENETRESTATISTIQUESGOMSBASH_H
