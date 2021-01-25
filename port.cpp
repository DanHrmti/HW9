#include "string.h"
#include "field.h"
#include "port.h"

/**
 * @brief Constructor of Port
 * @note Uses protected constructor of Field
 */
Port::Port(String pattern) : Field(pattern, PORT) {}

/**
 * @brief Set the allowed range values for port according to the rule which 
 			is defined by val.
 * @param val The string which defines the rule
 * @return Return true if succeded, otherwise false.
 */
bool Port::set_value(String val) {
	
	/* parse string and divide to range values */
	val = val.trim();
	String *range_rule;
	size_t size;
	val.split("-", &range_rule, &size);
	if (size != 2) {
		delete[] range_rule;
		return false;
	}

	/* set integer value of range */
	range[0] = range_rule[0].to_integer();
	range[1] = range_rule[1].to_integer();

	delete[] range_rule;
	return true;
}

/**
 * @brief Check whether String val represents port address which complies with 
 			the rule.
 * @param val The string which represents ip address to check
 * @return Return true if this complies with the rule, otherwise false.
 */
bool Port::match_value(String val) const {
	val = val.trim();
	int value = val.to_integer();
	if (value >= range[0] && value <= range[1]) {
		return true;
	} else {
		return false;
	}
}