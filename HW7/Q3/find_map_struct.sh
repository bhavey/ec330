#!/bin/bash
echo "Total Cities:" `awk '{print $1}' map.txt | uniq | wc -l`
echo "If ETCW points to every city, this # will equal 1501:" `awk '{print $1}' map.txt | grep ETCW | wc -l`
echo "If all routes are bidirectional, this # will be double the previous #:" `cat map.txt | grep ETCW | wc -l`
echo "List of cities that point to themselves:" `awk 'substr($1,1,4)==substr($3,1,4){print $1}' map.txt`
