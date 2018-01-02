#include "table_model.h"

TableModel::TableModel(QObject *parent, ParsedRecords * records)
    : QAbstractTableModel(parent)
{
    this->records = records;
}

int TableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return records->GetRecordCount();
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    Record * row_record = this->records->GetRecord(index.row());

    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return QString::fromStdString(row_record->GetFormattedAmount());
        case 1:
            return QString::fromStdString(row_record->GetCurrency());
        case 2:
            return QString::fromStdString(row_record->GetOrderCode());
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section,
                                Qt::Orientation orientation,
                                int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Amount");
            case 1:
                return QString("Currency");
            case 2:
                return QString("Order Code");
            }
        }
    }
    return QVariant();
}

