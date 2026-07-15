#include <src/json-viewer/JSONParser.h>

#include <vector>

void JSONParser::setJsonDocument()
{
  QString jsonInString = QString::fromUtf8(R"json(
{
  "course": "Computer science",
  "students": [
    {
      "name": "Иван",
      "age": 25
    },
    {
      "name": "Петр",
      "age": 27
    },
    {
      "name": "Софья",
      "age": 35
    }
  ]
}
)json");

  QJsonParseError parseError;
  *m_document = QJsonDocument::fromJson(jsonInString.toUtf8(), &parseError);

  if (parseError.error != QJsonParseError::NoError)
  {
    qDebug() << parseError.errorString();
  }
}

void JSONParser::parseJsonDocument()
{
  
}

void JSONParser::parseJsonValue(const QJsonValue& val, std::shared_ptr<JSONTreeNode> node, int depth, int idxInLayer, bool isArrayElem)
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
    else if(isArrayElem)
    {
      node->setNodeData(std::to_string(idxInLayer), "{" + std::to_string(childrenAmount) + "}");
    }
    else
    {

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