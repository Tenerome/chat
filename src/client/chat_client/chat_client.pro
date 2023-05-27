QT += quick
QT += widgets
QT += core
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/Socket/Socket.cpp \
    src/ftp/ftp.cpp \
    src/info/AppInfo.cpp \
    src/info/lang/En.cpp \
    src/info/lang/Lang.cpp \
    src/info/lang/Zh.cpp \
    src/md5/md5.cpp \
    src/md5/useMD5.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH +="../build-chat_client-Desktop_Qt_5_15_2_GCC_64bit-Debug/"
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        src/Socket/Socket.h \
        src/ftp/ftp.h \
        src/info/AppInfo.h \
        src/info/lang/En.h \
        src/info/lang/Lang.h \
        src/info/lang/Zh.h \
        src/info/stdafx.h \
        src/md5/md5.h \
        src/md5/useMD5.h

DISTFILES +=
