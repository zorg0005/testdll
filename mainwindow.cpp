#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "_sg_api.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // инициализация граматической бибилиотеки
  gren.Load();
}

MainWindow::~MainWindow()
{
  delete ui;
}
