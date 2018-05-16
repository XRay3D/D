QT += quick quickcontrols2 location positioning bluetooth sql
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
    guiapplication.cpp \

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

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


#APP_FILES.files += Trainings.db

ios {
    QMAKE_INFO_PLIST = ios/Info.plist
#    QMAKE_BUNDLE_DATA += APP_FILES

    fontFiles.files = $$files(fonts/*.ttf)
    fontFiles.path = fonts
    QMAKE_BUNDLE_DATA += fontFiles

    app_launch_images.files = $$PWD/ios/LaunchScreen.xib $$files($$PWD/ios/LaunchImage*.png)
    QMAKE_BUNDLE_DATA += app_launch_images

    QMAKE_ASSET_CATALOGS += ios/Images.xcassets

DISTFILES += \
    ios/Assets.xcassets \
    ios/Info.plist \
    ios/LaunchScreen.xib

QTPLUGIN += qsqlite
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

