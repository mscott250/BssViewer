#include "bank_transaction.h"

#include <sstream>
#include <iostream>

BankTransaction::BankTransaction(float amount,
                                 const std::string& currency,
                                 const BankTransactionMarker marker,
                                 const std::string& orderCode) {
    this->amount = amount;
    this->currency = currency;
    this->marker = marker;
    this->identificationNumber = orderCode;
}

float BankTransaction::getAmount() const {
    return this->amount;
}

const std::string BankTransaction::getFormattedAmount() const {

    std::ostringstream output;

    // set the formatting to 2 digits after the decimal point
    output.setf(std::ios::fixed, std::ios::floatfield);
    output.precision(2);

    output << this->amount;

    return output.str();
}

const std::string& BankTransaction::getCurrency() const {
    return this->currency;
}

const BankTransactionMarker BankTransaction::getMarker() const {
    return this->marker;
}

const std::string& BankTransaction::getIdentificationNumber() const {
    return this->identificationNumber;
}

