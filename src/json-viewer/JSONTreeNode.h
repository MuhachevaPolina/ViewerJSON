#pragma once

#include <QJsonValue>
#include <QString>

#include <memory>
#include <string>
#include <utility>
#include <vector>

class JSONTreeNode
{
 public:
  JSONTreeNode();

  void setChild(std::shared_ptr<JSONTreeNode> child, int clildIdx);
  std::shared_ptr<JSONTreeNode> getChild(int childIdx);
  int getChildrenAmount();
  void deleteChild(int childIdx);

  void setNodeData(QString key, QString value);
  std::pair<QString, QString> getNodeData();

  QJsonValue::Type getValueType();
  void setValueType(QJsonValue::Type valType);

 private:
  std::vector<std::shared_ptr<JSONTreeNode>> m_nodeChildren;

  std::pair<QString, QString> m_nodeData;  // use "[size]" for arrays and "{size}" for objects value
  QJsonValue::Type m_valueType;
};

// one string key-value per node 