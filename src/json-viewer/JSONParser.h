#pragma once

#include <src/json-viewer/JSONTreeNode.h>

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue> 

class JSONParser
{
public:
  void setJsonDocument();
  void parseJsonDocument();
  std::shared_ptr<JSONTreeNode> getTreeNode();

private:
  void parseJsonValue(const QJsonValue& val, std::shared_ptr<JSONTreeNode> curNode, int depth, int idxInLayer, bool isArrayElem, QString key);

  QJsonDocument m_document;
  std::shared_ptr<JSONTreeNode> m_rootNode;
};