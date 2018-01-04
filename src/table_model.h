#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include "parsed_records.h"

#include <QAbstractTableModel>

#include <list>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent, ParsedRecords * records);
    ~TableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    ParsedRecords * records;
};

#endif // TABLE_MODEL_H
