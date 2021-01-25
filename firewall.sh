#!/bin/bash

# remove all comments, spaces and blank lines from rules arg
sed 's/#.*//g' "$1" > parsed_rules.txt
sed -in 's/ //g' parsed_rules.txt
sed -in '/^$/d' parsed_rules.txt

# save packets from stdin in a variable
packets=$(cat /dev/stdin)

# check for matching packets, each line filtering by a different rule
while read line; do
  echo "$packets" | \
  ./firewall.exe "$(echo "$line" | cut -d , -f1)" | \
  ./firewall.exe "$(echo "$line" | cut -d , -f2)" | \
  ./firewall.exe "$(echo "$line" | cut -d , -f3)" | \
  ./firewall.exe "$(echo "$line" | cut -d , -f4)" >> matching_packets.txt
done < parsed_rules.txt

# # sort and deduplicate packets that matched several rules
sort -uo matching_packets.txt matching_packets.txt
sed -in 's/ //g' matching_packets.txt
sed -in '/^$/d' matching_packets.txt

# send matching packets to stdout and delete auxilary txt files
cat matching_packets.txt
rm parsed_rules.txt matching_packets.txt