QT += quick quickcontrols2
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000 # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
     guiapplication.cpp \
     trainings.cpp

HEADERS += \
     guiapplication.h \
     trainings.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android{
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
DISTFILES += \
     android/AndroidManifest.xml \
     android/gradle/wrapper/gradle-wrapper.jar \
     android/gradlew \
     android/res/values/libs.xml \
     android/build.gradle \
     android/gradle/wrapper/gradle-wrapper.properties \
     android/gradlew.bat
}

ios {
    QMAKE_INFO_PLIST = ios/Info.plist

    fontFiles.files = $$files(fonts/*.ttf)
    fontFiles.path = fonts
    QMAKE_BUNDLE_DATA += fontFiles

    app_launch_images.files = $$PWD/ios/LaunchScreen.xib $$files($$PWD/ios/LaunchImage*.png)
    QMAKE_BUNDLE_DATA += app_launch_images


    ios_icon.files = $$files($$PWD/ios/AppIcon*.png)
    QMAKE_BUNDLE_DATA += ios_icon

DISTFILES += \
    ios/Assets.xcassets \
    ios/Info.plist \
    ios/LaunchScreen.xib
}
