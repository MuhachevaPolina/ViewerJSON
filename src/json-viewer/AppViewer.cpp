#include <src/json-viewer/AppViewer.h>

AppViewer::AppViewer(QWidget* parent): QWidget(parent) 
{
  this->resize(1200, 800);
  
  this->m_quitButton = new QPushButton("exit", this);

  connect(this->m_quitButton, &QPushButton::clicked, this, &AppViewer::close);
}

