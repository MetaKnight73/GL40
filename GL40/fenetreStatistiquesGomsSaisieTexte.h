#ifndef FENETRESTATISTIQUESGOMSSAISIETEXTE_H
#define FENETRESTATISTIQUESGOMSSAISIETEXTE_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextDocument>

#include <QtCharts>

#include <vector>

#include "statistiquesGomsSaisieTexte.h"

using namespace std;
using namespace QtCharts;

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
    FenetreStatistiquesGomsSaisieTexte(vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte, QWidget *parent = 0);
    QPushButton* getBoutonRecommencer();
    QChart* createLineChart(vector<StatistiquesGomsSaisieTexte> statistiquesGomsSaisieTexte) const;

public slots:

    void quitterApplication();
    void retournerMenu();

};

#endif
