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

RESOURCES += qml.qrc

ios {

    QMAKE_INFO_PLIST = ios/Info.plist

    fontFiles.files = $$files(fonts/*.ttf)
    fontFiles.path = fonts
    QMAKE_BUNDLE_DATA += fontFiles

    app_launch_images.files = $$files($$PWD/ios/LaunchImages/LaunchImage*.png)
    QMAKE_BUNDLE_DATA += app_launch_images

    QMAKE_ASSET_CATALOGS += ios/Images.xcassets

DISTFILES += \
    ios/Images.xcassets \
    ios/Info.plist


#    HEADERS += ios/IntentHandler.h
#    OBJECTIVE_SOURCES += ios/IntentHandler.m
}


android {
    QT += androidextras

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    DISTFILES += \
        android/AndroidManifest.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew \
        android/gradlew.bat \
        android/res/values/libs.xml \

    OTHER_FILES += \
        android/src/ru/roc/dems/NotificationClient.java \


}

OTHER_FILES += \
    qml/*.qml \
