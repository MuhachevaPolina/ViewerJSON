#include <src/json-viewer/AppViewer.h>

AppViewer::AppViewer(QWidget* parent) : QWidget(parent)
{
  resize(1200, 800);

  m_quitButton = new QPushButton("exit", this);

  // m_treeModel = new JSONTreeItemModel;
  m_textEditor = new JSONTextEdit;

  m_layout = new QVBoxLayout;

  m_jsonLayout = new QHBoxLayout;
  m_jsonLayout->addWidget(m_textEditor);

  m_layout->addLayout(m_jsonLayout);
  m_layout->addWidget(m_quitButton);
  setLayout(m_layout);

  connect(m_quitButton, &QPushButton::clicked, this, &AppViewer::close);
}
