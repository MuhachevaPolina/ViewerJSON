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
  JSONTreeNode(JSONTreeNode* parent);

  void setChild(std::shared_ptr<JSONTreeNode> child, int clildIdx);
  std::shared_ptr<JSONTreeNode> getChild(int childIdx);
  int getChildrenAmount();
  void deleteChild(int childIdx);

  void setNodeData(QString key, QString value);
  std::pair<QString, QString> getNodeData();

  QJsonValue::Type getValueType();
  void setValueType(QJsonValue::Type valType);

  int getIdxAmongParentNodeChildren();
  void setIdxAmongParentNodeChildren(int idx);
  JSONTreeNode* getParent();
  void setParent(JSONTreeNode* parentNode);

 private:
  std::vector<std::shared_ptr<JSONTreeNode>> m_nodeChildren;
  JSONTreeNode* m_nodeParent;

  std::pair<QString, QString> m_nodeData;  // use "[size]" for arrays and "{size}" for objects value
  QJsonValue::Type m_valueType;

  int m_idxAmongParentNodeChildren;
};

// one string key-value per node 