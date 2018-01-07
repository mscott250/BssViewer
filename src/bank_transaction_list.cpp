#include "bank_transaction_list.h"

BankTransactionList::~BankTransactionList() {
    for (auto const & transaction : this->transactions) {
        delete transaction;
    }
}

void BankTransactionList::add(BankTransaction * transaction) {
    this->transactions.push_back(transaction);
}

BankTransaction * BankTransactionList::get(int index) {
    return this->transactions.at(index);
}

int BankTransactionList::size() {
    return this->transactions.size();
}
