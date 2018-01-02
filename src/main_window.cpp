#include "main_window.h"
#include "file_parser.h"
#include "parse_exception.h"

#include <iostream>

#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow()
{
    table_view = new QTableView;
    table_view->setStyleSheet("QTableView::item { border: 0px; padding: 5px;}");
    table_view->horizontalHeader()->setStretchLastSection(true);

    setCentralWidget(table_view);
    setWindowTitle("BSS Viewer");
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
    table_model = new TableModel(0, records);
    table_view->setModel(table_model);
    table_view->resizeColumnsToContents();
    table_view->resizeRowsToContents();
}
