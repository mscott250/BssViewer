#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "table_model.h"
#include "bank_transaction_list.h"

#include <QMainWindow>
#include <QTableView>
#include <QMenu>
#include <QAction>

#include <string>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
private:
    QMenu *fileMenu;

    QAction *openFileAction;
    QAction *quitAction;

    QTableView *tableView;

    TableModel *tableModel;

    void loadFile(const std::string& fileName);
    void updateTable(BankTransactionList *bankTransaction);
private slots:
    void openFile();
    void quit();
};

#endif // MAIN_WINDOW_H
