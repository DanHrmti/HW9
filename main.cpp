#include <iostream>
#include "input.h"
#include "string.h"
#include "field.h"
#include "port.h"
#include "ip.h"

int main(int argc, char **argv) {

	if (check_args(argc, argv)) {
		return -1;
	}

	String input_rule(argv[1]);

	String *parsed_rule;
	size_t size; /* should be 2 */
	input_rule.split("=", &parsed_rule, &size);

	/* create field to check type */
	Field gen_rule(parsed_rule[0].trim());


	/* create Ip/Port according to type, set range values and parse */
	if (gen_rule.get_type() == IP) {
		Ip   rule(parsed_rule[0].trim());
		rule.set_value(parsed_rule[1].trim());
		parse_input(rule);
	} else if (gen_rule.get_type() == PORT) {
		Port rule(parsed_rule[0].trim());
		rule.set_value(parsed_rule[1].trim());
		parse_input(rule);
	}

	delete[] parsed_rule;
	return 0;
}