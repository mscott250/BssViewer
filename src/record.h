#ifndef RECORD_H
#define RECORD_H

#include "bank_transaction_marker.h"

#include <string>

class Record {

public:
    Record(float amount,
           const std::string& currency,
           BankTransactionMarker bankTransactionMarker,
           const std::string& identificationNumber);

    float GetAmount() const;
    const std::string GetFormattedAmount() const;
	const std::string& GetCurrency() const;
    const BankTransactionMarker GetBankTransactionMarker() const;
    const std::string& GetIdentificationNumber() const;
private:
	float amount;
    std::string currency;
    BankTransactionMarker bankTransactionMarker;
    std::string identificationNumber;
};

#endif /* RECORD_H */
