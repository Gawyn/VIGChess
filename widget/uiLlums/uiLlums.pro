TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release
QT	+= opengl


HEADERS	+= llum.h \
	finestraLlums.h \
	sliderText.h \
	boto.h \
	textField.h

SOURCES	+= finestraLlums.cpp \
	sliderText.cpp \
	boto.cpp \
	textField.cpp \ 
	main.cpp 

FORMS	= EditorLlums.ui

