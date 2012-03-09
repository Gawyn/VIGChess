#include "GLWidget.h"
#include "GLWidgetPlugin.h"
#include <QtPlugin>

GLWidgetPlugin :: GLWidgetPlugin(QObject *parent): QObject(parent)
{
  initialized = false;
}

void GLWidgetPlugin ::initialize(QDesignerFormEditorInterface * core)
{
  if (initialized) return;
  initialized = true;
}

bool GLWidgetPlugin ::isInitialized() const
{
  return initialized;
}

QWidget * GLWidgetPlugin ::createWidget(QWidget *parent)
{
  return new GLWidget(parent); // Construir el Widget
}

QString GLWidgetPlugin ::name() const
{
  return "GLWidget"; // El nom de la classe del Widget
}

QString GLWidgetPlugin ::group() const
{
  return "Meus Widgets";
}

QIcon GLWidgetPlugin ::icon() const
{
  return QIcon();
}

QString GLWidgetPlugin ::toolTip() const
{
  return "";
}

QString GLWidgetPlugin ::whatsThis() const
{
  return "";
}

bool GLWidgetPlugin ::isContainer() const
{
  return false;
}

QString GLWidgetPlugin ::domXml() const
{
  return "<widget class=\"GLWidget\" name=\"glWidget\">\n"
  " <property name=\"geometry\">\n"
  " <rect>\n"
  " <x>0</x>\n"
  " <y>0</y>\n"
  " <width>171</width>\n"
  " <height>111</height>\n"
  " </rect>\n"
  " </property>\n"
  "</widget>\n";
}

QString GLWidgetPlugin ::includeFile() const
{
  return "GLWidget.h";
}

Q_EXPORT_PLUGIN2(GLWidgetPlugin, GLWidgetPlugin)
