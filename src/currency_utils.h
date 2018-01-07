#ifndef CURRENCY_UTILS_H_
#define CURRENCY_UTILS_H_

#include <string>

class CurrencyUtils {
public:
    static float parseAmount(std::string& amount);
private:
    static const int SCALE = 2;
};

#endif /* CURRENCY_UTILS_H_ */
