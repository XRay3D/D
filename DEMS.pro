# 1.0 - 1.4

QT += quick location positioning bluetooth sql network

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000 # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    bt/bluetoothbaseclass.cpp \
    bt/devicefinder.cpp \
    bt/devicehandler.cpp \
    bt/deviceinfo.cpp \
    bt/skiprotokol.cpp \
    db/database.cpp \
    db/listmodel.cpp \
    db/training.cpp \
    guiapplication.cpp \
    networkcontroller.cpp \
    notificationclient.cpp \
    vibrationclient.cpp \
    shareutils/applicationui.cpp \
#    shareutils/main.cpp \
    shareutils/shareutils.cpp


HEADERS += \
    bt/bluetoothbaseclass.h \
    bt/devicefinder.h \
    bt/devicehandler.h \
    bt/deviceinfo.h \
    bt/skiprotokol.h \
    db/database.h \
    db/listmodel.h \
    db/training.h \
    guiapplication.h \
    networkcontroller.h \
    notificationclient.h \
    vibrationclient.h \
    shareutils/applicationui.h \
    shareutils/shareutils.h

RESOURCES += qml.qrc

ios {

    QMAKE_INFO_PLIST = ios/Info.plist

    QMAKE_IOS_DEPLOYMENT_TARGET = 10.0

    fontFiles.files = $$files(fonts/*.ttf)
    fontFiles.path = fonts
    QMAKE_BUNDLE_DATA += fontFiles

    app_launch_images.files = $$files($$PWD/ios/LaunchImages/LaunchImage*.png)
    QMAKE_BUNDLE_DATA += app_launch_images

    QMAKE_ASSET_CATALOGS += ios/Images.xcassets

    DISTFILES += \
        ios/Images.xcassets \
        ios/Info.plist

    HEADERS += \
        ios/QtAppDelegate.h \
        ios/QtAppDelegate-C-Interface.h \
        shareutils/ios/docviewcontroller.h \
        shareutils/ios/iosshareutils.h \

    OBJECTIVE_SOURCES += \
        ios/QtAppDelegate.mm \
        ios/src/iosshareutils.mm \
        ios/src/docviewcontroller.mm

    # Please do not modify the following two lines. Required for deployment.
    include(ios/qtquick2applicationviewer/qtquick2applicationviewer.pri)
    qtcAddDeployment()

}


android {
    QT += androidextras
    SOURCES += shareutils/android/androidshareutils.cpp
    HEADERS += shareutils/android/androidshareutils.h
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    OTHER_FILES += \

    DISTFILES += \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat
}

OTHER_FILES += \
    qml/*.qml \

DISTFILES += \
    android/src/ru/roc/dems/DemsActivity.java \
    android/src/ru/roc/dems/utils/QSharePathResolver.java \
    android/src/ru/roc/dems/utils/QShareUtils.java


