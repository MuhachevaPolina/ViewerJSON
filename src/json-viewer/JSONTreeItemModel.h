#pragma once

#include <src/json-viewer/JSONTreeNode.h>

#include <QAbstractItemModel>
#include <QModelIndex>

#include <memory>

class JSONTreeItemModel: public QAbstractItemModel
{
  Q_OBJECT
public:
  JSONTreeItemModel(QObject* parent, const std::shared_ptr<JSONTreeNode> treeRoot);
  // void setTreeRoot(std::shared_ptr<JSONTreeNode> rootNode);

  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& child = QModelIndex()) const override;
  QVariant data(const QModelIndex& idx = QModelIndex(), int role = Qt::DisplayRole) const override;

private:
  const std::shared_ptr<JSONTreeNode> m_treeRoot;

  int countTreeHight(int prevHight, const std::shared_ptr<JSONTreeNode> curNode) const;
  int countNodesAmount(const std::shared_ptr<JSONTreeNode> curNode) const;
};