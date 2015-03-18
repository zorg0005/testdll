#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QtGui>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QLibrary>

#include "solarix_grammar_engine.h"

struct GrenAPI
{
 QLibrary dll;
 HFAIND hEngine;

 sol_CreateGrammarEngineEx8_Fun sol_CreateGrammarEngineEx8;
 sol_CreateGrammarEngineW_Fun sol_CreateGrammarEngineW;
 sol_DeleteGrammarEngine_Fun sol_DeleteGrammarEngine;
 sol_DeleteResPack_Fun sol_DeleteResPack;
 sol_MorphologyAnalysis8_Fun sol_MorphologyAnalysis8;
 sol_CountRoots_Fun sol_CountRoots;
 sol_GetRoot_Fun sol_GetRoot;
 sol_GetNodeContents8_Fun sol_GetNodeContents8;
 sol_GetNodeIEntry_Fun sol_GetNodeIEntry;
 sol_GetNodeVersionCount_Fun sol_GetNodeVersionCount;
 sol_GetNodeVerIEntry_Fun sol_GetNodeVerIEntry;
 sol_GetEntryClass_Fun sol_GetEntryClass;
 sol_GetClassName8_Fun sol_GetClassName8;
 sol_GetEntryName8_Fun sol_GetEntryName8;
 sol_GetNodeVerPairsCount_Fun sol_GetNodeVerPairsCount;
 sol_GetNodeVerPairCoord_Fun sol_GetNodeVerPairCoord;
 sol_GetNodeVerPairState_Fun sol_GetNodeVerPairState;
 sol_CountCoordStates_Fun sol_CountCoordStates;
 sol_GetCoordName8_Fun sol_GetCoordName8;
 sol_GetCoordStateName8_Fun sol_GetCoordStateName8;
 sol_RestoreCasing8_Fun sol_RestoreCasing8;
 sol_GetCoordType_Fun sol_GetCoordType;
 sol_GetErrorLen8_Fun sol_GetErrorLen8;
 sol_GetError8_Fun sol_GetError8;

 GrenAPI(void)
 {
  sol_CreateGrammarEngineEx8 = NULL;
  sol_CreateGrammarEngineW = NULL;
  sol_DeleteGrammarEngine = NULL;
  sol_DeleteResPack = NULL;
  sol_MorphologyAnalysis8 = NULL;
  sol_CountRoots = NULL;
  sol_GetRoot = NULL;
  sol_GetNodeContents8 = NULL;
  sol_GetNodeIEntry = NULL;
  sol_GetNodeVersionCount = NULL;
  sol_GetNodeVerIEntry = NULL;
  sol_GetEntryClass = NULL;
  sol_GetClassName8 = NULL;
  sol_GetEntryName8 = NULL;
  sol_GetNodeVerPairsCount = NULL;
  sol_GetNodeVerPairCoord = NULL;
  sol_GetNodeVerPairState = NULL;
  sol_CountCoordStates = NULL;
  sol_GetCoordName8 = NULL;
  sol_GetCoordStateName8 = NULL;
  sol_RestoreCasing8 = NULL;
  sol_GetCoordType = NULL;
  sol_GetErrorLen8 = NULL;
  sol_GetError8 = NULL;

  hEngine=NULL;
 }

 void Load(void)
 {
  QString cd = QDir::currentPath();
  QString dll_path = cd + "/" + "solarix_grammar_engine";

  QString dll_path_test = dll_path + ".dll";
  if( !QFile().exists(dll_path_test) ) {
          qDebug() << "Библиотеки нет однако " <<dll_path_test;
        }

  dll.setFileName( dll_path );

  bool ok = dll.load();
  if( ok==false )
   {
    QString err = dll.errorString();
    qDebug() << err;
    QMessageBox msgBox;
    msgBox.setText(err);
    msgBox.exec();
    //QApplication::exit(1);
    return;
   }

   sol_CreateGrammarEngineEx8 = (sol_CreateGrammarEngineEx8_Fun)dll.resolve("sol_CreateGrammarEngineEx8");
   sol_CreateGrammarEngineW = (sol_CreateGrammarEngineW_Fun)dll.resolve("sol_CreateGrammarEngineW");
   if (!sol_CreateGrammarEngineW&&!sol_CreateGrammarEngineEx8)
      qDebug() << "функция sol_CreateGrammarEngine не определена.";
   QString xml_path = cd + "/" + "dictionary.xml";

   if( !QFile().exists(xml_path) )
    {
           qDebug() << "dictionary.xml нет в рабочей папке";
    }

   qDebug() << xml_path;
   //hEngine = sol_CreateGrammarEngineW((wchar_t*)xml_path.utf16());
   hEngine = sol_CreateGrammarEngineEx8(xml_path.toUtf8().constData(),SOL_GREN_LAZY_LEXICON);
   if( hEngine==NULL )
    {
     QMessageBox msgBox;
     msgBox.setText( QString("Could not load the dictionary ") + xml_path );
     msgBox.exec();
     QApplication::exit(1);
     //return;
    }

  sol_DeleteGrammarEngine = (sol_DeleteGrammarEngine_Fun)dll.resolve("sol_DeleteGrammarEngine");
  sol_DeleteResPack = (sol_DeleteResPack_Fun)dll.resolve("sol_DeleteResPack");
  sol_MorphologyAnalysis8 = (sol_MorphologyAnalysis8_Fun)dll.resolve("sol_MorphologyAnalysis8");
  sol_CountRoots = (sol_CountRoots_Fun)dll.resolve("sol_CountRoots");
  sol_GetRoot = (sol_GetRoot_Fun)dll.resolve("sol_GetRoot");
  sol_GetNodeContents8 = (sol_GetNodeContents8_Fun)dll.resolve("sol_GetNodeContents8");
  sol_GetNodeIEntry = (sol_GetNodeIEntry_Fun)dll.resolve("sol_GetNodeIEntry");
  sol_GetNodeVersionCount = (sol_GetNodeVersionCount_Fun)dll.resolve("sol_GetNodeVersionCount");
  sol_GetNodeVerIEntry = (sol_GetNodeVerIEntry_Fun)dll.resolve("sol_GetNodeVerIEntry");
  sol_GetEntryClass = (sol_GetEntryClass_Fun)dll.resolve("sol_GetEntryClass");
  sol_GetClassName8 = (sol_GetClassName8_Fun)dll.resolve("sol_GetClassName8");
  sol_GetEntryName8 = (sol_GetEntryName8_Fun)dll.resolve("sol_GetEntryName8");
  sol_GetNodeVerPairsCount = (sol_GetNodeVerPairsCount_Fun)dll.resolve("sol_GetNodeVerPairsCount");
  sol_GetNodeVerPairCoord = (sol_GetNodeVerPairCoord_Fun)dll.resolve("sol_GetNodeVerPairCoord");
  sol_GetNodeVerPairState = (sol_GetNodeVerPairState_Fun)dll.resolve("sol_GetNodeVerPairState");
  sol_CountCoordStates = (sol_CountCoordStates_Fun)dll.resolve("sol_CountCoordStates");
  sol_GetCoordName8 = (sol_GetCoordName8_Fun)dll.resolve("sol_GetCoordName8");
  sol_GetCoordStateName8 = (sol_GetCoordStateName8_Fun)dll.resolve("sol_GetCoordStateName8");
  sol_RestoreCasing8 = (sol_RestoreCasing8_Fun)dll.resolve("sol_RestoreCasing8");
  sol_GetCoordType = (sol_GetCoordType_Fun)dll.resolve("sol_GetCoordType");
  sol_GetErrorLen8 = (sol_GetErrorLen8_Fun)dll.resolve("sol_GetErrorLen8");
  sol_GetError8 = (sol_GetError8_Fun)dll.resolve("sol_GetError8");

  return;
 }

 ~GrenAPI(void)
 {
  if (hEngine){
      sol_DeleteGrammarEngine(hEngine);
      hEngine=NULL;
    }
  return;
 }

};

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  GrenAPI gren;
};

#endif // MAINWINDOW_H
