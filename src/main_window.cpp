#include "main_window.h"
#include "file_parser.h"
#include "parse_exception.h"

#include <iostream>

#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QApplication>

MainWindow::MainWindow()
{
    openFileAction = new QAction("&Open", this);
    quitAction = new QAction("&Quit", this);

    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(quitAction);

    table_view = new QTableView;
    table_view->setStyleSheet("QTableView::item { border: 0px; padding: 5px;}");
    table_view->horizontalHeader()->setStretchLastSection(true);

    table_model = nullptr;

    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    setCentralWidget(table_view);
    setWindowTitle("BSS Viewer");
}

void MainWindow::openFile() {

    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*.*)");
    if (fileName != "") {
        LoadFile(fileName.toStdString());
    }
}

void MainWindow::quit() {
    qApp->quit();
}

void MainWindow::LoadFile(const std::string& file_name)
{
    FileParser file_parser;
    try {
        ParsedRecords * records = file_parser.Parse(file_name);
        UpdateTable(records);
    } catch (ParseException& e) {
        QMessageBox errorMessage;
        errorMessage.setText(e.what());
        errorMessage.setWindowTitle("Error loading file");
        errorMessage.exec();
    }
}

void MainWindow::UpdateTable(ParsedRecords * records) {

    // avoid memory leaks when opening multiple files in one session, by clearing any previously opened file
    delete table_model;

    table_model = new TableModel(0, records);
    table_view->setModel(table_model);
    table_view->resizeColumnsToContents();
    table_view->resizeRowsToContents();
}
