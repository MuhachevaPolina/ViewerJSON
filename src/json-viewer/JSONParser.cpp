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

  if(parseError.error != QJsonParseError::NoError)
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

  std::shared_ptr<JSONTreeNode> rootNode = std::make_shared<JSONTreeNode>(nullptr);
  rootNode->makeNodeRoot();
  parseJsonValue(val, rootNode, 0, 0, false, QString());
  m_rootNode = rootNode;
}

void JSONParser::parseJsonValue(const QJsonValue& val,
                                std::shared_ptr<JSONTreeNode> curNode, int depth,
                                int idxInLayer, bool isArrayElem, QString key)
{
  // recursive
  if(val.isNull())
  {
    return;
  }

  curNode->setValueType(val.type());

  if(val.isObject())
  {
    QJsonObject obj = val.toObject();
    int childrenAmount = obj.size();

    if(depth == 0)
    {
      curNode->setNodeData(
          "object",
          QString::fromStdString("{" + std::to_string(childrenAmount) + "}"));
    }
    else if(isArrayElem)
    {
      curNode->setNodeData(
          QString::fromStdString(std::to_string(idxInLayer)),
          QString::fromStdString("{" + std::to_string(childrenAmount) + "}"));
    }
    else
    {
      curNode->setNodeData(key, QString::fromStdString(
                                 "{" + std::to_string(childrenAmount) + "}"));
    }

    QStringList keys = obj.keys();
    
    std::shared_ptr<JSONTreeNode> childNode = std::make_shared<JSONTreeNode>(&(*curNode));

    for(int i = 0; i < childrenAmount; ++i)
    {
      curNode->setChild(childNode, i);
      parseJsonValue(obj.value(keys[i]), childNode, depth + 1, i, false,
                     keys[i]);
      childNode = std::make_shared<JSONTreeNode>(&(*curNode));
    }
  }
  else if(val.isArray())
  {
    QJsonArray arr = val.toArray();
    int childrenAmount = arr.size();
    std::shared_ptr<JSONTreeNode> childNode = std::make_shared<JSONTreeNode>(&(*curNode));

    if(depth == 0)
    {
      curNode->setNodeData(
          "array",
          QString::fromStdString("[" + std::to_string(childrenAmount) + "]"));
    }
    else if(isArrayElem)
    {
      curNode->setNodeData(
          QString::fromStdString(std::to_string(idxInLayer)),
          QString::fromStdString("[" + std::to_string(childrenAmount) + "]"));
    }
    else
    {
      curNode->setNodeData(key, QString::fromStdString(
                                 "[" + std::to_string(childrenAmount) + "]"));
    }

    for(int i = 0; i < childrenAmount; ++i)
    {
      curNode->setChild(childNode, i);
      parseJsonValue(arr[i], childNode, depth + 1, i, true,
                     QString::fromStdString(std::to_string(i)));
      childNode = std::make_shared<JSONTreeNode>(&(*curNode));
    }
  }
  else
  {
    QString str;
    if(val.isString())
    {
      str = val.toString();
    }
    else if(val.isDouble())
    {
      str = QString::fromStdString(std::to_string(val.toDouble()));
    }
    else if(val.isBool())
    {
      if(val.toBool())
      {
        str = "true";
      }
      else
      {
        str = "false";
      }
    }

    if(!isArrayElem)
    {
      curNode->setNodeData(key, str);
    }
    else
    {
      curNode->setNodeData(QString::fromStdString(std::to_string(idxInLayer)), str);
    }

    return;
  }
}

std::shared_ptr<JSONTreeNode> JSONParser::getTreeNode() { return m_rootNode; }