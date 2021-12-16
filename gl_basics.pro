QT = gui
QT += widgets
QT += opengl
equals(QT_MAJOR_VERSION, 6) {
    QT += openglwidgets
}
CONFIG += c++11

unix {
    LIBS += -lGLU
}

win32 {
    LIBS += -lglu32 -lopengl32
}

SOURCES += main.cpp \
    my_app.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
