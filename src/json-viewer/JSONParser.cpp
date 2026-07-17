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
  QJsonValue val;

  if(m_document->isObject())
  {
    val = m_document->object();
  }
  else if(m_document->isArray())
  {
    val = m_document->array();
  }

  std::shared_ptr<JSONTreeNode> rootNode = std::make_shared<JSONTreeNode>();
  parseJsonValue(val, rootNode, 0, 0, false, QString());
  m_rootNode = rootNode;
}

void JSONParser::parseJsonValue(const QJsonValue& val, std::shared_ptr<JSONTreeNode> node, int depth, int idxInLayer, bool isArrayElem, QString key)
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
      node->setNodeData("object", QString::fromStdString("{" + std::to_string(childrenAmount) + "}"));
    }
    else if(isArrayElem)
    {
      node->setNodeData(QString::fromStdString(std::to_string(idxInLayer)), QString::fromStdString("{" + std::to_string(childrenAmount) + "}"));
    }
    else
    {
      node->setNodeData(key, QString::fromStdString("{" + std::to_string(childrenAmount) + "}"));
    }

    QStringList keys = obj.keys(); 
    std::shared_ptr<JSONTreeNode> childNode = std::make_shared<JSONTreeNode>();

    for(int i = 0; i < childrenAmount; ++i)
    {
      node->setChild(childNode, i);
      parseJsonValue(obj.value(keys[i]), childNode, depth + 1, i, false, keys[i]);
      childNode = std::make_shared<JSONTreeNode>();
    }
  }
  else if(val.isArray())
  {
    QJsonArray arr = val.toArray();
    int childrenAmount = arr.size();
    std::shared_ptr<JSONTreeNode> childNode = std::make_shared<JSONTreeNode>();

    if(depth == 0)
    {
      node->setNodeData("array", QString::fromStdString("[" + std::to_string(childrenAmount) + "]"));
    }
    else if(isArrayElem)
    {
      node->setNodeData(QString::fromStdString(std::to_string(idxInLayer)), QString::fromStdString("[" + std::to_string(childrenAmount) + "]"));
    }
    else
    {
      node->setNodeData(key, QString::fromStdString("[" + std::to_string(childrenAmount) + "]"));
    }

    for(int i = 0; i < childrenAmount; ++i)
    {
      node->setChild(childNode, i);
      parseJsonValue(arr[i], childNode, depth + 1, i, false, QString::fromStdString(std::to_string(i)));
      childNode = std::make_shared<JSONTreeNode>();
    }
  }
  else
  {
    QString str = val.toString();
    int sepIdx = str.indexOf(":");

    QString key = str.left(sepIdx);
    QString value = str.mid(sepIdx + 1);

    node->setNodeData(key, value);

    return;
  }
}

std::shared_ptr<JSONTreeNode> JSONParser::getTreeNode()
{
  return m_rootNode;
}