#include <src/json-viewer/AppViewer.h>

AppViewer::AppViewer(QWidget* parent) : QWidget(parent)
{
  this->resize(1200, 800);

  this->m_quitButton = new QPushButton("exit", this);

  // this->m_treeModel = new JSONTreeItemModel;
  this->m_textEditor = new JSONTextEdit;

  this->m_layout = new QVBoxLayout;

  this->m_jsonLayout = new QHBoxLayout;
  this->m_jsonLayout->addWidget(this->m_textEditor);

  this->m_layout->addLayout(this->m_jsonLayout);
  this->m_layout->addWidget(this->m_quitButton);
  this->setLayout(this->m_layout);

  connect(this->m_quitButton, &QPushButton::clicked, this, &AppViewer::close);
}
