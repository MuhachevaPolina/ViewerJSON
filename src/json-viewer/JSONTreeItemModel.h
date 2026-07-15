#pragma once

#include <src/json-viewer/JSONTreeNode.h>

#include <QAbstractItemModel>

#include <memory>

class JSONTreeItemModel: public QAbstractItemModel
{
  Q_OBJECT
public:
  JSONTreeItemModel();
  void setTreeRoot();

private:
  std::shared_ptr<JSONTreeNode> m_treeRoot;
};