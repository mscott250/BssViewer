#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record {

public:
    Record(float amount, const std::string& currency, const std::string& orderCode);

    float GetAmount() const;
    const std::string GetFormattedAmount() const;
	const std::string& GetCurrency() const;
	const std::string& GetOrderCode() const;
private:
	float amount;
    std::string currency;
	std::string orderCode;
};

#endif /* RECORD_H */
