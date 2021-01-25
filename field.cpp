#include "string.h"
#include "port.h"
#include "ip.h"

/**
 * @brief Protected constructor of Field
 * @param pattern The string which defines the field and its type
 * @param type Determines what Field check in a packet: ip or port.
 * @return Field which is constructed.
 * @note can only be used by sons: Ip and Port
 */
Field::Field(String pattern, field_type type)
: pattern(pattern), type(type) {}

/**
 * @brief Constructor of Field from String class.
 * @param pattern The string from which we determine pattern and then we 
 					determine type by checking the string itself.
 * @return Field which we constructed from the string recieved.
 */
Field::Field(String pattern) {
	pattern = pattern.trim();
	this->pattern = pattern;

	if (pattern.equals("src-ip") || pattern.equals("dst-ip")) {
		this->type = IP;
	} else if (pattern.equals("src-port") || pattern.equals("dst-port")) {
		this->type = PORT;
	} else {
		this->type = GENERIC;
	}
}

/**
 * @brief Destructor of Field.
 */
Field::~Field() {}


/**
 * @brief Get the type key of class Field
 */
field_type Field::get_type() const {
	return this->type;
}

/**
 * @brief Set the allowed values according to the rule by calling set_value 
 			of the specific class (Ip or Port)
 * @param val The string which defines the rule
 * @return result of set_value of specific class, otherwise false.
 */
bool Field::set_value(String val) {
	if (this->type == IP) {
		Ip *ip = (Ip*)this;
		return ip->set_value(val);

	} else if (this->type == PORT) {
		Port *port = (Port*)this;
		return port->set_value(val);

	} else {
		return false;
	}
}

/**
 * @brief Check if val complies with the rule which is defined by set_value
 * @param val The string to check
 * @return True if val complies with the rule, False otherwise.
 */
bool Field::match_value(String val) const {
	if (this->type == IP) {
		Ip *ip = (Ip*)this;
		return ip->match_value(val);

	} else if (this->type == PORT) {
		Port *port = (Port*)this;
		return port->match_value(val);

	} else {
		return false;
	}
}

/**
 * @brief Check if string of packet complies with the rule for each case:
 			ip or port. Uses both match_value and set_value.
 * @param val The string to check if it complies with the rule.
 * @return Return true if val complies with the rule, otherwise false.
 */
bool Field::match(String packet) {
	packet = packet.trim();

	/* divide the packet to its 4 fields */
	String *packet_fields;
	size_t num_fields;
	packet.split(",", &packet_fields, &num_fields);
	if (num_fields == 0) {
		delete[] packet_fields;
		return false;
	}

	/* find relevant packet field and check for match */
	String *cur_pattern_and_value; /* of packet field */
	size_t size; /* should be 2 */

	String cur_packet_field_pattern;
	String cur_packet_field_value;

	for (size_t i=0; i < num_fields; i+=1) {
		packet_fields[i].split("=", &cur_pattern_and_value, &size);
		if (size != 2) {
			delete[] cur_pattern_and_value;
			continue;
		}

		cur_packet_field_pattern = cur_pattern_and_value[0].trim();
		cur_packet_field_value   = cur_pattern_and_value[1].trim();

		if (this->pattern.equals(cur_packet_field_pattern)) {
			if (this->match_value(cur_packet_field_value)) {
				delete[] cur_pattern_and_value;
				delete[] packet_fields;
				return true;
			}
		}
		delete[] cur_pattern_and_value;
	}

	/* if reached here, there is no match */
	delete[] packet_fields;
	return false;
}