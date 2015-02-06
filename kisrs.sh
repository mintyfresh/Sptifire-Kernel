#!/bin/bash

# Create file header
echo ""
echo ".file \"${3:-kisrs.asm}\""
echo ".include \"isrdef.asm\""
echo ""

# Create handler stubs
for i in `seq ${2:-0} $1`;
do
	echo "isr $i"
done

echo ""

# Create handler table
echo ".global isrTable"
echo ".type isrTable, @object"
echo "isrTable:"

# Populate table
for i in `seq ${2:-0} $1`;
do
	echo "	.long _isr$i"
done

# Null terminate
echo "	.long 0"
