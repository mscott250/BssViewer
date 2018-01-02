#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "table_model.h"
#include "parsed_records.h"

#include <QMainWindow>
#include <QTableView>

#include <string>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void LoadFile(const std::string& file_name);

private:
    QTableView *table_view;

    TableModel *table_model;

    void UpdateTable(ParsedRecords *records);
};

#endif // MAIN_WINDOW_H
