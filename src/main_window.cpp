#include "main_window.h"
#include "file_parser.h"
#include "parse_exception.h"

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

    tableView = new QTableView;
    tableView->setStyleSheet("QTableView::item { border: 0px; padding: 5px;}");
    tableView->horizontalHeader()->setStretchLastSection(true);

    tableModel = nullptr;

    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    setCentralWidget(tableView);
    setWindowTitle("BSS Viewer");
}

void MainWindow::openFile() {

    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*.*)");
    if (fileName != "") {
        loadFile(fileName.toStdString());
    }
}

void MainWindow::quit() {
    qApp->quit();
}

void MainWindow::loadFile(const std::string& fileName)
{
    FileParser fileParser;
    try {
        BankTransactionList *transactions = fileParser.parse(fileName);
        updateTable(transactions);
        setWindowTitle(QString::fromStdString("BSS Viewer - " + fileName));
    } catch (ParseException& e) {
        QMessageBox errorMessage;
        errorMessage.setText(e.what());
        errorMessage.setWindowTitle("Error loading file");
        errorMessage.exec();
    }
}

void MainWindow::updateTable(BankTransactionList *transactions) {

    // avoid memory leaks when opening multiple files in one session, by clearing any previously opened file
    delete tableModel;

    tableModel = new TableModel(0, transactions);
    tableView->setModel(tableModel);
    tableView->resizeColumnsToContents();
    tableView->resizeRowsToContents();
}
