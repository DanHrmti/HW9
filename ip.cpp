#include "string.h"
#include "ip.h"

#define MASK_SEGMENT 2
#define SEGMENTS 4
#define BITS_IN_INT 32

/**
 * @brief Trasform string which contains ip address to int as specified in HW
 * @param val The string which contains the ip address
 * @return unsigned int which represents the ip address
 */
unsigned int ip_to_int(String val) {
	val = val.trim();
	String *segments;
	size_t size;
	val.split(".", &segments, &size);
	if (size != SEGMENTS) { /* should never happen */
		delete[] segments;
		return 0;
	}

	unsigned int ip = (segments[0].to_integer() << 24) |
	                  (segments[1].to_integer() << 16) |
	                  (segments[2].to_integer() << 8) |
	                  (segments[3].to_integer());

	delete[] segments;
	return ip;
}

/**
 * @brief Constructor of IP
 * @calls protected constructor of field with type IP
 */
Ip::Ip(String pattern) : Field(pattern, IP) {}

/**
 * @brief Set the allowed low and high values for ip address according to  
 			the rule which is defined by val.
 * @param val The string which defines the rule
 * @return Return true if succeded, otherwise false.
 */
bool Ip::set_value(String val) {
	/* divide val to ip and mask */
	val = val.trim();
	String *rule_segments;
	size_t size;
	val.split("/", &rule_segments, &size);
	if (size != 2) {
		delete[] rule_segments;
		return false;
	}


	/* create ip and mask defined by rule*/
	unsigned int ip = ip_to_int(rule_segments[0]);
	unsigned int mask;

	int shift_value = BITS_IN_INT - rule_segments[1].to_integer();
	if (shift_value == BITS_IN_INT) {
		mask = 0;
	} else {
		mask = ( ((unsigned int)(~0)) >> shift_value) << (shift_value);
	}
	
	/* set unsigned integer values of range */
	low  = ip & mask;
	high = low | (~mask);

	delete[] rule_segments;
	return true;
}

/**
 * @brief Check whether String val represents ip address which complies with 
 			the rule.
 * @param val The string which represents ip address to check
 * @return Return true if this complies with the rule, otherwise false.
 */
bool Ip::match_value(String val) const {

	unsigned int value = ip_to_int(val);

	if (value >= low && value <= high) {
		return true;
	} else {
		return false;
	}
}