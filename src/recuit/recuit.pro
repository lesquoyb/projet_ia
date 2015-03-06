TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gelement.cpp \
    vector2d.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    pelement.h \
    exception.h \
    gelement.h \
    sommet.h \
    arete.h \
    graphe.h \
    test_gelement.h \
    testpelement.h \
    vector2d.h \
    algebre_lineaire.h \
    recuit_simule.h \
    tools_math.h \
    recuit_simule_d1.h \
    test_recuit_simule_d1.h \
    test_recuit_simule_d2.h \
    recuit_simule_d2.h \
    vrai_test.h

