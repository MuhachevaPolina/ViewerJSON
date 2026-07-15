#include <src/json-viewer/JSONTreeNode.h>

#include <QDebug>

JSONTreeNode::JSONTreeNode() {}

void JSONTreeNode::setChild(std::shared_ptr<JSONTreeNode> child, int childIdx)
{
  if(childIdx < m_nodeChildren.size())
  {
    m_nodeChildren[childIdx] = child;
  }
  else if(childIdx == m_nodeChildren.size())
  {
    m_nodeChildren.push_back(child);
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

void JSONTreeNode::setNodeData(std::string key, std::string value)
{
  m_nodeData.first = key;
  m_nodeData.second = value;
}

std::pair<std::string, std::string> JSONTreeNode::getNodeData()
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