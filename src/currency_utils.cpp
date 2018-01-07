#include "currency_utils.h"

#include <stdexcept>

float CurrencyUtils::parseAmount(std::string& amount) {

    if (amount.size() <= CurrencyUtils::SCALE) {
		throw std::invalid_argument(
                "'" + amount + "' shorter than scale " + std::to_string(CurrencyUtils::SCALE));
	}

    unsigned int insertPosition = amount.size() - CurrencyUtils::SCALE;
    std::string amountAsFloat = amount.insert(insertPosition, 1, '.');

    return std::stof(amountAsFloat);
}
