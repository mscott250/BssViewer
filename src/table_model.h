#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include "bank_transaction_list.h"

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent, BankTransactionList *transactions);
    ~TableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    BankTransactionList * transactions;
};

#endif // TABLE_MODEL_H
