#pragma once

#include <src/json-viewer/JSONTextEdit.h>
#include <src/json-viewer/JSONTreeView.h>
#include <src/json-viewer/JSONTreeItemModel.h>
#include <src/json-viewer/FilesHandler.h>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class AppViewer : public QWidget
{
  Q_OBJECT
public:
  AppViewer(QWidget* parent = nullptr);

private:
  QTextEdit* m_textEditor;
  QAbstractItemModel* m_treeModel;
  QTreeView* m_treeViewer;
  FilesHandler* m_filesHandler;

  QVBoxLayout* m_layout;
  QHBoxLayout* m_jsonLayout;

  QPushButton* m_quitButton;
};