QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fitts_and_Goms-Keystroke
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

win32:RC_ICONS += icons/logo.ico

SOURCES += main.cpp\
    fenetrePrincipale.cpp \
    fenetreOptionsFitts.cpp \
    fenetreOptionsGomsSaisieTexte.cpp \
    fenetreTestFitts.cpp \
    statistiquesFitts.cpp \
    fenetreStatistiquesFitts.cpp \
    fenetreTestGomsSaisieTexte.cpp \
    statistiquesGomsSaisieTexte.cpp \
    fenetreStatistiquesGomsSaisieTexte.cpp \
    fenetreOptionsGomsClics.cpp \
    statistiquesGomsClics.cpp \
    fenetreTestGomsClics.cpp \
    fenetreStatistiquesGomsClics.cpp \
    fenetreOptionsGomsClavier.cpp \
    fenetreStatistiquesGomsClavier.cpp \
    fenetreTestGomsClavier.cpp \
    statistiquesGomsClavier.cpp \
    fenetreOptionsGomsBash.cpp \
    fenetreStatistiquesGomsBash.cpp \
    statistiquesGomsBash.cpp \
    fenetreTestGomsBash.cpp

HEADERS  += \
    fenetrePrincipale.h \
    fenetreOptionsFitts.h \
    fenetreOptionsGomsSaisieTexte.h \
    fenetreTestFitts.h \
    statistiquesFitts.h \
    fenetreStatistiquesFitts.h \
    fenetreTestGomsSaisieTexte.h \
    fenetreStatistiquesGomsSaisieTexte.h \
    statistiquesGomsSaisieTexte.h \
    fenetreOptionsGomsClics.h \
    statistiquesGomsClics.h \
    fenetreTestGomsClics.h \
    fenetreStatistiquesGomsClics.h \
    fenetreOptionsGomsClavier.h \
    fenetreStatistiquesGomsClavier.h \
    fenetreTestGomsBash.h \
    statistiquesGomsClavier.h \
    fenetreOptionsGomsBash.h \
    fenetreStatistiquesGomsBash.h \
    statistiquesGomsBash.h \
    fenetreTestGomsClavier.h

RESOURCES += \
    ressources.qrc
