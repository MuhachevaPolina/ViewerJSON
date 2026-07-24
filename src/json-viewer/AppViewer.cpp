#include <src/json-viewer/AppViewer.h>

#include <src/json-viewer/JSONParser.h>

AppViewer::AppViewer(QWidget* parent) : QWidget(parent)
{
  resize(1200, 800);

  m_quitButton = new QPushButton("exit", this);

  m_textEditor = new JSONTextEdit;
  m_treeViewer = new JSONTreeView(this);

  m_treeViewer->setHeaderHidden(true);
  m_treeViewer->setHeaderHidden(true);

  m_layout = new QVBoxLayout;

  m_buttonsLayout = new QHBoxLayout;
  m_openFileButton = new QPushButton("open file", this);
  m_expandButton = new QPushButton("expand tree", this);
  m_updateTreeButton = new QPushButton("update tree", this);
  m_buttonsLayout->addWidget(m_openFileButton);
  m_buttonsLayout->addWidget(m_expandButton);
  m_buttonsLayout->addWidget(m_updateTreeButton);

  m_jsonLayout = new QHBoxLayout;
  m_jsonLayout->addWidget(m_textEditor);
  m_jsonLayout->addWidget(m_treeViewer);

  m_layout->addLayout(m_buttonsLayout);
  m_layout->addLayout(m_jsonLayout);
  m_layout->addWidget(m_quitButton);
  setLayout(m_layout);

  connect(m_quitButton, &QPushButton::clicked, this, &AppViewer::close);
  connect(m_updateTreeButton, &QPushButton::clicked, this, &AppViewer::updateTree);
}

void AppViewer::updateTree()
{
  const QString jsonText = m_textEditor->toPlainText();

  JSONParser parser;

  if(!parser.setJsonDocument(jsonText))
  {
    return;
  }

  parser.parseJsonDocument();

  std::shared_ptr<JSONTreeNode> rootNode =
      parser.getTreeNode();

  if(!rootNode)
  {
    qWarning() << "JSON tree root was not created";
    return;
  }

  auto* newModel =
      new JSONTreeItemModel(this, rootNode);

  m_treeViewer->setModel(newModel);

  if(m_treeModel)
  {
    m_treeModel->deleteLater();
  }

  m_treeModel = newModel;

  m_treeViewer->expandAll();
}
