#include "record.h"

#include <sstream>
#include <iostream>

Record::Record(float amount,
               const std::string& currency,
               const BankTransactionMarker bankTransactionMarker,
               const std::string& orderCode) {
    this->amount = amount;
    this->currency = currency;
    this->bankTransactionMarker = bankTransactionMarker;
    this->identificationNumber = orderCode;
}

float Record::GetAmount() const {
    return this->amount;
}

const std::string Record::GetFormattedAmount() const {

    std::ostringstream output;

    // set the formatting to 2 digits after the decimal point
    output.setf(std::ios::fixed, std::ios::floatfield);
    output.precision(2);

    output << this->amount;

    return output.str();
}

const std::string& Record::GetCurrency() const {
    return this->currency;
}

const BankTransactionMarker Record::GetBankTransactionMarker() const {
    return this->bankTransactionMarker;
}

const std::string& Record::GetIdentificationNumber() const {
    return this->identificationNumber;
}

