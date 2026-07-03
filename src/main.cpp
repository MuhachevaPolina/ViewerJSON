#include <src/json-viewer/AppViewer.h>

#include <QApplication>
#include <QLoggingCategory>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QLoggingCategory::setFilterRules(
      "qt.*.debug=false\n"
      "default.debug=true");
  qSetMessagePattern("[%{time hh:mm:ss.zzz} %{type}] %{message}");


  AppViewer viewer;

  viewer.show();

  return app.exec();
}