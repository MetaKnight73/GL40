#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>

#include "fenetrePrincipale.h"
#include "fenetreTestFitts.h"

int main(int argc, char *argv[]) {

    //Application
    QApplication app(argc, argv);

    // Codec pour l'affichage des caractères en UTF-8
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // Fenêtre principale
    FenetrePrincipale *fenetre = new FenetrePrincipale;
    fenetre->statusBar()->setSizeGripEnabled(false);

    // On centre la fenêtre dans l'écran
    QRect rectangleFenetre = QApplication::desktop()->screenGeometry();
    int x = (rectangleFenetre.width()-fenetre->width()) / 2;
    int y = (rectangleFenetre.height()-fenetre->height()) / 2;
    fenetre->move(x, y);

    // On affiche la fenêtre
    fenetre->show();

    return app.exec();

}

