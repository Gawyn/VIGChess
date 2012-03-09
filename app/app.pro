TEMPLATE	= app
LANGUAGE	= C++

#CONFIG	+= qt warn_on release opengl
QT += opengl
INCLUDEPATH+=../widget 

LIBS += ../widget/libpluginGLWidget.so

HEADERS	+= Principal.h \

SOURCES	+= Principal.cpp \
	main.cpp 


TARGET = PracticaVIG

FORMS	= Principal.ui

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


