#include "table_model.h"

#include <stdexcept>

TableModel::TableModel(QObject *parent, ParsedRecords * records)
    : QAbstractTableModel(parent)
{
    this->records = records;
}

TableModel::~TableModel() {
    delete records;
}

int TableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return records->GetRecordCount();
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
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
            switch (row_record->GetBankTransactionMarker()) {
                case BankTransactionMarker::PURCHASE:
                    return QString::fromStdString("PURCHASE");
                case BankTransactionMarker::REFUND:
                    return QString::fromStdString("REFUND");
                default:
                    throw std::invalid_argument("Unknown bank transaction marker");
            }

        case 3:
            return QString::fromStdString(row_record->GetIdentificationNumber());
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
                return QString("Marker");
            case 3:
                return QString("Identification Number");
            }
        }
    }
    return QVariant();
}

