#pragma once 

#include <QTreeView>

class JSONTreeView: public QTreeView
{
  Q_OBJECT
public:
  JSONTreeView(QWidget* parent = nullptr);
};