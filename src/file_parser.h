#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "parsed_records.h"

#include <string>

class FileParser {

public:
    ParsedRecords * Parse(const std::string& file_name);

private:

    static const std::string PURCHASE_TRANSACTION_TYPE;
    static const std::string REFUND_TRANSACTION_TYPE;

    void ParseRecords(ParsedRecords * records, std::ifstream& file);
    Record * ParseRecord(const std::string& transaction_data, const std::string& supplementary_transaction_data);
	const std::string ParseCurrency(const std::string& transaction_data);
    float ParseAmount(const std::string& transaction_data, const std::string& currency);
    const BankTransactionMarker ParseTransactionType(const std::string& transaction_data);
    const std::string ParseOrderCode(const std::string& supplementary_transaction_data);

    float ParseAmountString(const std::string& amount);
};

#endif /* FILEPARSER_H */
