QT       += core gui opengl openglwidgets

QMAKE_CXXFLAGS += -Wa,-mbig-obj

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport printsupport opengl openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    "../"

SOURCES += \
    SerialPort.cpp \
    commandextender.cpp \
    glwidget.cpp \
    group3d.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    simpleobject3d.cpp \
    structs_cmds.cpp \
    structs_tools.cpp

HEADERS += \
    SerialPort.h \
    commandextender.h \
    glwidget.h \
    group3d.h \
    mainwindow.h \
    qcustomplot.h \
    simpleobject3d.h \
    structs_cmds.h \
    structs_tools.h \
    transformational.h \
    ../structs_cmds_commons.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lopengl32

DISTFILES +=

RESOURCES += \
    shaders.qrc \
    textures.qrc
