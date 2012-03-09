CONFIG     += designer plugin release
TARGET      = pluginGLWidget
QT         += opengl
OBJECTS_DIR = .obj
MOC_DIR     = .moc
TEMPLATE    = lib
target.path = ~/.designer/plugins/designer
INSTALLS   += target
HEADERS     =  GLWidgetPlugin.h GLWidget.h
SOURCES     =  GLWidgetPlugin.cpp GLWidget.cpp

HEADERS	+= 	Object.h \
	ObjectRef.h \
	Face.h \
	Vertex.h \
	Color.h \
	Box.h \
	Material.h \
	MaterialLib.h \
	Point.h \
        Scene.h \
        Tauler.h \
	uiLlums/boto.h \
	uiLlums/finestraLlums.h \
	uiLlums/llum.h \
	uiLlums/sliderText.h \
	uiLlums/textField.h \
	uiLlums/ui_EditorLlums.h
	

SOURCES	+= Object.cpp \
	ObjectRef.cpp \
	Face.cpp \
	Vertex.cpp \
	Color.cpp \
	Box.cpp \
	Material.cpp \
	MaterialLib.cpp \
	Point.cpp \
        Scene.cpp \
        Tauler.cpp \
	uiLlums/boto.cpp \
	uiLlums/finestraLlums.cpp \
	uiLlums/sliderText.cpp \
	uiLlums/textField.cpp

