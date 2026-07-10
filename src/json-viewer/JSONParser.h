#pragma once

#include <src/json-viewer/JSONTreeNode.h>

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue> 

class JSONParser
{
  Q_OBJECT
public:
  void getJsonDocument();
  void parseJsonValue(const QJsonValue& val, std::shared_ptr<JSONTreeNode> node, int depth, int idxInLayer);
};