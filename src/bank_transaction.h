#ifndef BANK_TRANSACTION_H
#define BANK_TRANSACTION_H

#include "bank_transaction_marker.h"

#include <string>

class BankTransaction {
public:
    BankTransaction(float amount,
                    const std::string& currency,
                    BankTransactionMarker marker,
                    const std::string& identificationNumber);

    float getAmount() const;
    const std::string getFormattedAmount() const;
    const std::string& getCurrency() const;
    const BankTransactionMarker getMarker() const;
    const std::string& getIdentificationNumber() const;
private:
	float amount;
    std::string currency;
    BankTransactionMarker marker;
    std::string identificationNumber;
};

#endif /* BANK_TRANSACTION_H */
