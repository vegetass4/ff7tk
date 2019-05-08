######################################################################
#Automatically generated by qmake (2.01a) Mon Mar 26 23:01:23 2012
######################################################################

TEMPLATE= app
TARGET = ff7tkWidgetGallery
CONFIG+= c++1z
QT+= core gui xml widgets

# Input
HEADERS+=   mainwindow.h\
            ../src/data/FF7Achievements.h\
            ../src/data/FF7FieldItemList.h\
            ../src/data/FF7Item.h \
            ../src/data/FF7Location.h \
            ../src/data/FF7Materia.h\
            ../src/data/FF7Save.h\
            ../src/data/FF7SaveInfo.h\
            ../src/data/FF7Save_Types.h\
            ../src/data/FF7Text.h\
            ../src/data/SaveIcon.h\
            ../src/data/FF7Char.h\
            ../src/data/Type_FF7CHAR.h\
            ../src/data/Type_FF7CHOCOBO.h\
            ../src/data/Type_materia.h\
            ../src/formats/Archive.h \
            ../src/formats/Lgp.h\
            ../src/formats/Lgp_p.h\
            ../src/utils/LZS.h\
            ../src/utils/QLockedFile.h\
            ../src/widgets/AchievementEditor.h\
            ../src/widgets/CharEditor.h\
            ../src/widgets/CharManager.h\
            ../src/widgets/ChocoboEditor.h\
            ../src/widgets/ChocoboLabel.h\
            ../src/widgets/ChocoboManager.h \
            ../src/widgets/DialogPreview.h\
            ../src/widgets/DoubleCheckBox.h\
            ../src/widgets/ItemList.h\
            ../src/widgets/ItemPreview.h\
            ../src/widgets/ItemSelector.h\
            ../src/widgets/LocationViewer.h\
            ../src/widgets/MateriaEditor.h\
            ../src/widgets/MenuListWidget.h\
            ../src/widgets/MetadataCreator.h\
            ../src/widgets/OptionsWidget.h\
            ../src/widgets/PhsListWidget.h\
            ../src/widgets/SlotPreview.h\
            ../src/widgets/SlotSelect.h

FORMS+=     mainwindow.ui

SOURCES+=   main.cpp\
            mainwindow.cpp\
            ../src/data/FF7Achievements.cpp\
            ../src/data/FF7Char.cpp\
            ../src/data/FF7FieldItemList.cpp\
            ../src/data/FF7Item.cpp\
            ../src/data/FF7Location.cpp\
            ../src/data/FF7Materia.cpp\
            ../src/data/FF7Save.cpp\
            ../src/data/FF7SaveInfo.cpp\
            ../src/data/FF7Text.cpp\
            ../src/data/SaveIcon.cpp\
            ../src/formats/Archive.cpp\
            ../src/utils/LZS.cpp\
            ../src/utils/QLockedFile.cpp\
            ../src/formats/Lgp.cpp\
            ../src/formats/Lgp_p.cpp\
            ../src/widgets/AchievementEditor.cpp\
            ../src/widgets/CharEditor.cpp\
            ../src/widgets/CharManager.cpp\
            ../src/widgets/ChocoboEditor.cpp\
            ../src/widgets/ChocoboLabel.cpp\
            ../src/widgets/ChocoboManager.cpp\
            ../src/widgets/DialogPreview.cpp\
            ../src/widgets/DoubleCheckBox.cpp\
            ../src/widgets/ItemList.cpp\
            ../src/widgets/ItemPreview.cpp\
            ../src/widgets/ItemSelector.cpp\
            ../src/widgets/LocationViewer.cpp\
            ../src/widgets/MenuListWidget.cpp\
            ../src/widgets/MateriaEditor.cpp\
            ../src/widgets/MetadataCreator.cpp\
            ../src/widgets/OptionsWidget.cpp\
            ../src/widgets/PhsListWidget.cpp\
            ../src/widgets/SlotPreview.cpp\
            ../src/widgets/SlotSelect.cpp

RESOURCES+=\
            ../src/icons/achievements.qrc\
            ../src/icons/characters.qrc\
            ../src/icons/chocobo.qrc\
            ../src/icons/common.qrc\
            ../src/icons/items.qrc\
            ../src/icons/locations.qrc\
            ../src/icons/materia.qrc\
            ../src/icons/psxButtons.qrc

#Uncomment Below to Generate translations (currently part of black chocobo)
#TRANSLATIONS+=\
#	../src/lang/ff7tk_de.ts \
#	../src/lang/ff7tk_en.ts \
#	../src/lang/ff7tk_es.ts \
#	../src/lang/ff7tk_fr.ts \
#	../src/lang/ff7tk_jp.ts \
#	../src/lang/ff7tk_re.ts
unix:{
	#DEFINES += EnableOpenSSL	# Enable openSSL support
	#LIBS += -lcrypto		# Enable crypto lib
}
win32:{
	#Set OpenSSL include & lib paths
	#THIS MUST BE CHANGED WITH YOUR OPENSSL PATHS OR YOUR BUILD WILL FAIL!!!
	#DEFINES += EnableOpenSSL							# Enable openSSL support
	#INCLUDEPATH += C:/OpenSSL-Win32/include		# Be sure to change this to your openSSL include path
	#LIBS += -L"C:/OpenSSL-Win32/lib" -llibeay32	# Be sure to update this to your openSSL lib path
	#Prevent ms padding on packed structures on gcc compiler
	contains(QMAKE_COMPILER, gcc) {
	QMAKE_CXXFLAGS += -mno-ms-bitfields
	}
}
static:{ # everything below takes effect with CONFIG += static
	CONFIG += static
	CONFIG += staticlib # this is needed if you create a static library, not a static executable
	lessThan(QT_MAJOR_VERSION, 5): QTPLUGIN += qcncodecs qjpcodecs qtwcodecs qkrcodecs
	DEFINES += STATIC
	message("Static Build") # this is for information, that the static build is done
	TARGET = $$join(TARGET,,,-static) #this adds an s in the end, so you can seperate static build from non static build
}
# change the name of the binary, if it is build in debug mode
CONFIG(debug, debug|release) {TARGET = $$join(TARGET,,,-debug)}
