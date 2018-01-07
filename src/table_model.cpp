#include "table_model.h"

#include <stdexcept>

TableModel::TableModel(QObject *parent, BankTransactionList * records)
    : QAbstractTableModel(parent) {
    this->transactions = records;
}

TableModel::~TableModel() {
    delete transactions;
}

int TableModel::rowCount(const QModelIndex & /*parent*/) const {
    return transactions->size();
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const {
    return 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {

    BankTransaction * transaction = this->transactions->get(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return QString::fromStdString(transaction->getFormattedAmount());
        case 1:
            return QString::fromStdString(transaction->getCurrency());
        case 2:
            switch (transaction->getMarker()) {
                case BankTransactionMarker::PURCHASE:
                    return QString::fromStdString("PURCHASE");
                case BankTransactionMarker::REFUND:
                    return QString::fromStdString("REFUND");
                default:
                    throw std::invalid_argument("Unknown bank transaction marker");
            }

        case 3:
            return QString::fromStdString(transaction->getIdentificationNumber());
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
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

