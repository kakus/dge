# Links box2d lib to your project
# 27.04.2013 Kamil Misiowiec

unix:!macx: LIBS += -L$$PWD/lib/Box2D_v2.2.1-build/Box2D/ -lBox2D

INCLUDEPATH += $$PWD/lib/Box2D_v2.2.1/
DEPENDPATH += $$PWD/lib/Box2D_v2.2.1/

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/Box2D_v2.2.1-build/Box2D/libBox2D.a
