#include "file_parser.h"
#include "currency_utils.h"
#include "parse_exception.h"

#include <iostream>
#include <fstream>

const std::string FileParser::PURCHASE_TRANSACTION_TYPE = "0";
const std::string FileParser::REFUND_TRANSACTION_TYPE = "5";

BankTransactionList * FileParser::parse(const std::string& fileName) {

    BankTransactionList * transactions = nullptr;

    std::ifstream file(fileName);
	if (file.is_open()) {

        transactions = new BankTransactionList;
        try {
            parseRecords(transactions, file);
        } catch (...) {
            delete transactions;
            file.close();
            throw;
        }
	} else {
        throw ParseException("Unable to open '" + fileName + "'");
	}

    return transactions;
}

void FileParser::parseRecords(BankTransactionList * transactions, std::ifstream& file) {

    int lineNumber = 0;
    std::string line;
    BankTransaction * parsedTransaction;
    while (std::getline(file, line)) {

        lineNumber++;

        if (line.size() < 2) {
            throw ParseException("Unable to parse line " + std::to_string(lineNumber) + " : no record type present");
        }

        std::string recordType = line.substr(0, 2);
        if (recordType == "15") {

            std::string supplementaryLine;
            std::getline(file, supplementaryLine);

            try {
                parsedTransaction = parseRecord(line, supplementaryLine);
            }
            catch (ParseException& e) {
                throw ParseException("Unable to parse line " + std::to_string(lineNumber) + " : " + e.what());
            }

            transactions->add(parsedTransaction);

            lineNumber++;
        }
    }
}

BankTransaction * FileParser::parseRecord(const std::string& transactionData,
                                          const std::string& supplementaryTransactionData) {

    std::string currency = parseCurrency(transactionData);

    float amount = parseAmount(transactionData, currency);

    BankTransactionMarker transactionType = parseTransactionType(transactionData);
    if (transactionType == BankTransactionMarker::REFUND) {
        amount = amount * -1;
    }

    std::string orderCode = parseOrderCode(supplementaryTransactionData);

    return new BankTransaction {amount, currency, transactionType, orderCode};
}

const std::string FileParser::parseCurrency(const std::string& transactionData) {

    std::string localCurrencyCode = transactionData.substr(76, 3);
    std::string settlementCurrencyCode = transactionData.substr(89, 3);

    if (localCurrencyCode.empty()) {
		return "GBP";
	}

    if (settlementCurrencyCode.empty()) {
        throw ParseException("No settlement currency, but local currency present");
    }
    if (localCurrencyCode == "GBP") {
        throw ParseException("Local currency set to GBP");
    }
    if (localCurrencyCode != settlementCurrencyCode) {
        throw ParseException("Local and settlement currencies are different");
    }

    return localCurrencyCode;
}

float FileParser::parseAmount(const std::string& transactionData, const std::string& currency) {

    std::string localValue = transactionData.substr(67,  9);
    std::string transactionValue = transactionData.substr(33, 11);
    std::string settlementValue = transactionData.substr(80, 9);

    if (localValue.empty()) {
        return CurrencyUtils::parseAmount(transactionValue);
	} else {

        if (settlementValue.empty()) {
            throw ParseException("No settlement value, but a local one present");
		}

        if (localValue != settlementValue) {
            throw ParseException("Local and settlement values are different");
		}

        return CurrencyUtils::parseAmount(localValue);
	}
}

const BankTransactionMarker FileParser::parseTransactionType(const std::string& transactionData) {

    std::string transactionType = transactionData.substr(56, 1);
    if (transactionType == FileParser::PURCHASE_TRANSACTION_TYPE) {
        return BankTransactionMarker::PURCHASE;
    } else if (transactionType == FileParser::REFUND_TRANSACTION_TYPE) {
        return BankTransactionMarker::REFUND;
	} else {
        throw ParseException("Unsupported transaction type " + transactionType);
	}
}

const std::string FileParser::parseOrderCode(const std::string& supplementaryTransactionData) {

    std::string orderCode = supplementaryTransactionData.substr(30, 20);
    if (orderCode.empty()) {
        throw ParseException("No order code present");
    }

    return orderCode;
}
