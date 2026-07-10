#include <src/json-viewer/JSONParser.h>

#include <vector>

void JSONParser::parseJsonValue(const QJsonValue& val, std::shared_ptr<JSONTreeNode> node, int depth, int idxInLayer)
{
  // recursive
  if(val.isNull())
  {
    return;
  }

  node->setValueType(val.type());

  if(val.isObject())
  {
    QJsonObject obj = val.toObject();
    int childrenAmount = obj.size();

    if(depth == 0)
    {
      node->setNodeData("object", "{" + std::to_string(childrenAmount) + "}");
    }
    else
    {
      node->setNodeData(std::to_string(idxInLayer), "{" + std::to_string(childrenAmount) + "}");
    }

    QStringList keys = obj.keys(); 
    std::shared_ptr<JSONTreeNode> childNode = std::make_shared<JSONTreeNode>();

    for(int i = 0; i < childrenAmount; ++i)
    {
      node->setChild(childNode, i);
      this->parseJsonValue(obj.value(keys[i]), childNode, depth + 1, i);
      childNode = std::make_shared<JSONTreeNode>();
    }
  }
  else if(val.isArray())
  {
    QJsonArray arr = val.toArray();
    int childrenAmount = arr.size();
    std::shared_ptr<JSONTreeNode> childNode = std::make_shared<JSONTreeNode>();

    for(int i = 0; i < childrenAmount; ++i)
    {
      node->setChild(childNode, i);
      // node->setNodeData(keys[i].toStdString(), obj.value(keys[i]));
      // this->parseJsonValue(obj.value(keys[i]), ) 
      childNode = std::make_shared<JSONTreeNode>();
    }
    // this->parseJsonValue()
  }
  else
  {
    QString str = val.toString();
    int sepIdx = str.indexOf(":");

    QString key = str.left(sepIdx);
    QString value = str.mid(sepIdx + 1);

    node->setNodeData(key.toStdString(), value.toStdString());

    return;
  }
}