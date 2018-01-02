#include "currency_utils.h"

#include <stdexcept>

float CurrencyUtils::ParseAmount(std::string& amount) {

    if (amount.size() <= CurrencyUtils::SCALE) {
		throw std::invalid_argument(
                "'" + amount + "' shorter than scale " + std::to_string(CurrencyUtils::SCALE));
	}

    unsigned int insert_position = amount.size() - CurrencyUtils::SCALE;
	std::string amount_as_float = amount.insert(insert_position, 1, '.');

	return std::stof(amount_as_float);
}
