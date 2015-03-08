TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gelement.cpp \
    valuedata.cpp \
    vector2d.cpp \
    connexion.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    algebre_lineaire.h \
    arete.h \
    exception.h \
    gelement.h \
    graphe.h \
    pelement.h \
    recuit_simule.h \
    recuit_simule_d1.h \
    recuit_simule_d2.h \
    sommet.h \
    test_gelement.h \
    test_recuit_simule_d1.h \
    test_recuit_simule_d2.h \
    testpelement.h \
    tools_math.h \
    valuedata.h \
    vector2d.h \
    vrai_test.h \
    connexion.h

