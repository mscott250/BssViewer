#ifndef BANK_TRANSACTION_LIST_H
#define BANK_TRANSACTION_LIST_H

#include "bank_transaction.h"

#include <deque>

class BankTransactionList {
public:
    ~BankTransactionList();

    void add(BankTransaction * transaction);
    BankTransaction * get(int index);
    int size();
private:
    std::deque<BankTransaction *> transactions;
};

#endif // BANK_TRANSACTION_LIST_H
