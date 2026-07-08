#pragma once

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
  void deleteChild(int childIdx);

  void setNodeData(std::string key, std::string value);
  std::pair<std::string, std::string> getNodeData();

  enum class Type  // remove
  {
    String,
    Array,
    Object
  };

  Type getValueType();

 private:
  std::vector<std::shared_ptr<JSONTreeNode>> m_nodeChildren;

  std::pair<std::string, std::string> m_nodeData;  // rewrite to QJsonArray and QJsonValue
  Type m_valueType;
};