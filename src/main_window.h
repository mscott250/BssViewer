#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "table_model.h"
#include "parsed_records.h"

#include <QMainWindow>
#include <QTableView>
#include <QMenu>
#include <QAction>

#include <string>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    QMenu *fileMenu;

    QAction *openFileAction;

    QTableView *table_view;

    TableModel *table_model;

    void LoadFile(const std::string& file_name);
    void UpdateTable(ParsedRecords *records);

private slots:
    void openFile();
};

#endif // MAIN_WINDOW_H
