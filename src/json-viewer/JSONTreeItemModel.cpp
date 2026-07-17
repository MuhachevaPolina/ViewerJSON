#include <src/json-viewer/JSONTreeItemModel.h>

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
    return -1;
  }

  if(!parent.isValid())
  {
    return 1;
  }
  else
  {
    return countNodesAmount(m_treeRoot);
  }
}

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