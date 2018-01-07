#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "bank_transaction_list.h"

#include <string>

class FileParser {
public:
    BankTransactionList * parse(const std::string& fileName);
private:
    static const std::string PURCHASE_TRANSACTION_TYPE;
    static const std::string REFUND_TRANSACTION_TYPE;

    void parseRecords(BankTransactionList *transaction, std::ifstream& file);
    BankTransaction * parseRecord(const std::string& transactionData, const std::string& supplementaryTransactionData);
    const std::string parseCurrency(const std::string& transactionData);
    float parseAmount(const std::string& transactionData, const std::string& currency);
    const BankTransactionMarker parseTransactionType(const std::string& transactionData);
    const std::string parseOrderCode(const std::string& supplementaryTransactionData);

    float parseAmountString(const std::string& amount);
};

#endif /* FILEPARSER_H */
