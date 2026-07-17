#include <src/json-viewer/JSONTreeNode.h>

#include <QDebug>

JSONTreeNode::JSONTreeNode(JSONTreeNode* parent): m_nodeParent(parent), m_valueType(QJsonValue::Type::Undefined)
{}

void JSONTreeNode::setChild(std::shared_ptr<JSONTreeNode> child, int childIdx)
{
  if(child)
  {
    child->setParent(this);
  }
  else
  {
    qDebug() << "JSONTreeNode | set child problem: child is nullptr";
  }

  if(childIdx < m_nodeChildren.size())
  {
    m_nodeChildren[childIdx] = child;
    child->setIdxAmongParentNodeChildren(childIdx);
  }
  else if(childIdx == m_nodeChildren.size())
  {
    m_nodeChildren.push_back(child);
    child->setIdxAmongParentNodeChildren(childIdx);
  }
  else
  {
    qDebug() << "JSONTreeNode | set child problem: index out of range";
  }
}

std::shared_ptr<JSONTreeNode> JSONTreeNode::getChild(int childIdx)
{
  if(childIdx < m_nodeChildren.size())
  {
    return m_nodeChildren[childIdx];
  }
  else
  {
    qDebug() << "JSONTreeNode | get child problem: index out of range";
  }
}

void JSONTreeNode::deleteChild(int childIdx)
{
  if(childIdx < m_nodeChildren.size())
  {
    m_nodeChildren.erase(m_nodeChildren.begin() + childIdx);
  }
  else
  {
    qDebug() << "JSONTreeNode | delete child problem: index out of range";
  }
}

void JSONTreeNode::setNodeData(QString key, QString value)
{
  m_nodeData.first = key;
  m_nodeData.second = value;
}

std::pair<QString, QString> JSONTreeNode::getNodeData()
{
  return m_nodeData;
}

QJsonValue::Type JSONTreeNode::getValueType()
{
  return m_valueType;
}


void JSONTreeNode::setValueType(QJsonValue::Type valType)
{
  m_valueType = valType;
}

int JSONTreeNode::getChildrenAmount()
{
  return m_nodeChildren.size();
}

int JSONTreeNode::getIdxAmongParentNodeChildren()
{
  return m_idxAmongParentNodeChildren;
}

JSONTreeNode* JSONTreeNode::getParent()
{
  return m_nodeParent;
}

void JSONTreeNode::setParent(JSONTreeNode* parentNode)
{
  m_nodeParent = parentNode;
}

void JSONTreeNode::setIdxAmongParentNodeChildren(int idx)
{
  m_idxAmongParentNodeChildren = idx;
}
