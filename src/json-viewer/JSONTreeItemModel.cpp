#include <src/json-viewer/JSONTreeItemModel.h>

#include <utility>

JSONTreeItemModel::JSONTreeItemModel(QObject* parent, const std::shared_ptr<JSONTreeNode> treeRoot): 
QAbstractItemModel(parent), m_treeRoot(treeRoot)
{}

int JSONTreeItemModel::columnCount(const QModelIndex& parent) const
{
  return 1;
}

int JSONTreeItemModel::rowCount(const QModelIndex& parent) const
{
  if(!m_treeRoot)
  {
    return 0;
  }

  if(!parent.isValid())
  {
    return 1;
  }
  else
  {
    JSONTreeNode* parentNode = static_cast<JSONTreeNode*>(parent.internalPointer());
    return parentNode->getChildrenAmount();
  }
}

QModelIndex JSONTreeItemModel::index(int row, int column, const QModelIndex& parent) const
{
  if(!m_treeRoot)
  {
    return QModelIndex();
  }

  if(!hasIndex(row, column, parent))
  {
    return QModelIndex();
  }

  if(!parent.isValid())
  {
    return createIndex(row, column, m_treeRoot.get());
  }
  else
  {
    JSONTreeNode* parentNode = static_cast<JSONTreeNode*>(parent.internalPointer());
    std::shared_ptr<JSONTreeNode> childNode = parentNode->getChild(row);
    return createIndex(row, column, childNode.get());
  }
}

QModelIndex JSONTreeItemModel::parent(const QModelIndex& child) const
{
  if(!child.isValid())
  {
    return QModelIndex();
  }

  JSONTreeNode* childNode = static_cast<JSONTreeNode*>(child.internalPointer());

  if(!childNode)
  {
    return QModelIndex();
  }

  JSONTreeNode* parentNode = childNode->getParent();

  if(!parentNode)
  {
    return QModelIndex();
  }

  if(parentNode == m_treeRoot.get())
  {
    return createIndex(0, 0, m_treeRoot.get());
  }
  else
  {
    return createIndex(parentNode->getIdxAmongParentNodeChildren(), 0, parentNode);
  }
}

QVariant JSONTreeItemModel::data(const QModelIndex& idx, int role) const
{
  if(role != Qt::DisplayRole)
  {
    return QVariant();
  }

  if(!idx.isValid())
  {
    return QVariant();
  }

  JSONTreeNode* node = static_cast<JSONTreeNode*>(idx.internalPointer());
  if(!node)
  {
    return QVariant();
  }

  std::pair<QString, QString> nodeData = node->getNodeData();
  QString strData = nodeData.first;

  if(node->getValueType() == QJsonValue::Type::Array || node->getValueType() == QJsonValue::Type::Object)
  {
    strData += " ";
  }
  else
  {
    strData += ": ";
  }

  strData += nodeData.second;

  QVariant resData = QVariant::fromValue(strData);
  return resData;
}

// unused

int JSONTreeItemModel::countNodesAmount(const std::shared_ptr<JSONTreeNode> curNode) const
{
  // recursive
  int curAmount = 0;
  if(curNode->getChildrenAmount() == 0)
  {
    return 1;
  }
  else
  {
    for(int i = 0; i < curNode->getChildrenAmount(); ++i)
    {
      curAmount += countNodesAmount(curNode->getChild(i));
    }
    return curAmount;
  }
}

int JSONTreeItemModel::countTreeHight(int prevHight, const std::shared_ptr<JSONTreeNode> curNode) const
{
  // recursive
  std::vector<int> childrenHights;
  int hight = prevHight + 1;

  if(curNode->getChildrenAmount() == 0)
  {
    return hight;
  }
  else
  {
    for(int i = 0; i < curNode->getChildrenAmount(); ++i)
    {
      childrenHights.push_back(countTreeHight(hight, curNode->getChild(i)));
    }
  }

  return *(std::max_element(childrenHights.begin(), childrenHights.end()));
}