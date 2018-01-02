#include "file_parser.h"
#include "currency_utils.h"
#include "parse_exception.h"

#include <iostream>
#include <fstream>

const std::string FileParser::PURCHASE_TRANSACTION_TYPE = "0";
const std::string FileParser::REFUND_TRANSACTION_TYPE = "5";

ParsedRecords * FileParser::Parse(const std::string& file_name) {

    ParsedRecords * records = NULL;

	std::ifstream file(file_name);
	if (file.is_open()) {

        records = new ParsedRecords;
        try {
            ParseRecords(records, file);
        } catch (...) {
            delete records;
            file.close();
            throw;
        }
	} else {
        throw ParseException("Unable to open '" + file_name + "'");
	}

    return records;
}

void FileParser::ParseRecords(ParsedRecords * records, std::ifstream& file) {

    int line_number = 0;
    std::string line;
    Record * parsed_record;
    while (std::getline(file, line)) {

        line_number++;

        if (line.size() < 2) {
            throw ParseException("Unable to parse line " + std::to_string(line_number) + " : no record type present");
        }

        std::string record_type = line.substr(0, 2);
        if (record_type == "15") {

            std::string supplementary_line;
            std::getline(file, supplementary_line);

            try {
                parsed_record = ParseRecord(line, supplementary_line);
            }
            catch (ParseException& e) {
                throw ParseException("Unable to parse line " + std::to_string(line_number) + " : " + e.what());
            }

            records->AddRecord(parsed_record);

            line_number++;
        }
    }
}

Record * FileParser::ParseRecord(const std::string& transaction_data,
                                 const std::string& supplementary_transaction_data) {

	std::string currency = ParseCurrency(transaction_data);

    float amount = ParseAmount(transaction_data, currency);

    std::string transaction_type = ParseTransactionType(transaction_data);
    if (transaction_type == FileParser::REFUND_TRANSACTION_TYPE) {
        amount = amount * -1;
    }

	std::string order_code = ParseOrderCode(supplementary_transaction_data);

    return new Record {amount, currency, order_code};
}

const std::string FileParser::ParseCurrency(const std::string& transaction_data) {

	std::string local_currency_code = transaction_data.substr(76, 3);
	std::string settlement_currency_code = transaction_data.substr(89, 3);

	if (local_currency_code.empty()) {
		return "GBP";
	}

    if (settlement_currency_code.empty()) {
        throw ParseException("No settlement currency, but local currency present");
    }
    if (local_currency_code == "GBP") {
        throw ParseException("Local currency set to GBP");
    }
    if (local_currency_code != settlement_currency_code) {
        throw ParseException("Local and settlement currencies are different");
    }

	return local_currency_code;
}

float FileParser::ParseAmount(const std::string& transaction_data, const std::string& currency) {

	std::string local_value = transaction_data.substr(67,  9);
	std::string transaction_value = transaction_data.substr(33, 11);
	std::string settlement_value = transaction_data.substr(80, 9);

	if (local_value.empty()) {
        return CurrencyUtils::ParseAmount(transaction_value);
	} else {

		if (settlement_value.empty()) {
            throw ParseException("No settlement value, but a local one present");
		}

		if (local_value != settlement_value) {
            throw ParseException("Local and settlement values are different");
		}

        return CurrencyUtils::ParseAmount(local_value);
	}
}

const std::string FileParser::ParseTransactionType(const std::string& transaction_data) {

    std::string transaction_type = transaction_data.substr(56, 1);
    if (transaction_type == FileParser::PURCHASE_TRANSACTION_TYPE ||
            transaction_type == FileParser::REFUND_TRANSACTION_TYPE) {
        return transaction_type;
	} else {
        throw ParseException("Unsupported transaction type " + transaction_type);
	}
}

const std::string FileParser::ParseOrderCode(const std::string& supplementary_transaction_data) {

    std::string order_code = supplementary_transaction_data.substr(30, 20);
    if (order_code.empty()) {
        throw ParseException("No order code present");
    }

    return order_code;
}
