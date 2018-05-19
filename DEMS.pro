# 1.0 - 1.4

QT += quick location positioning bluetooth sql
#QT += quickcontrols2
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
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
    guiapplication.cpp

HEADERS += \
    bt/bluetoothbaseclass.h \
    bt/devicefinder.h \
    bt/devicehandler.h \
    bt/deviceinfo.h \
    bt/skiprotokol.h \
    db/database.h \
    db/listmodel.h \
    db/training.h \
    guiapplication.h

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
}

android {

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \


}
