# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gnl_test.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clu <clu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 17:38:52 by clu               #+#    #+#              #
#    Updated: 2024/12/18 13:39:29 by clu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Default loop count
LOOP_COUNT=10

# Check if the number of arguments is correct
if [ $# -ne 1 ]; then
    echo "Usage: $0 <number_of_loops>"
    exit 1
fi

# Check if the provided argument is a valid number
if ! [[ $1 =~ ^[0-9]+$ ]]; then
    echo "Invalid number of loops: $1"
    exit 1
fi

# Set the loop count to the provided argument
LOOP_COUNT=$1

# Compilation for mandatory part
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=5 -o test_gnl gnl_test.c get_next_line.c get_next_line_utils.c

# Check if compilation was successful
if [ $? -ne 0 ]; then
	echo "Compilation failed for mandatory part"
	exit 1
fi

# Run tests for mandatory part
echo "Running tests for mandatory part with the assigned BUFFER_SIZE and $LOOP_COUNT loops"
echo ""

# Test with various files
./test_gnl $LOOP_COUNT

# Run Valgrind to check for memory leaks
# echo "Running Valgrind to check for memory leaks for mandatory part"
# valgrind --leak-check=full --show-leak-kinds=all -s ./test_gnl $LOOP_COUNT
# echo "Done"

# Compilation for bonus part
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=10 -o test_gnl_bonus gnl_test_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c

# Check if compilation was successful
if [ $? -ne 0 ]; then
	echo "Compilation failed for bonus part"
	exit 1
fi

# Run tests for bonus part
echo "Running tests for bonus part with the assigned BUFFER_SIZE and $LOOP_COUNT loops"
echo ""

# Test with various files
./test_gnl_bonus $LOOP_COUNT

# Run Valgrind to check for memory leaks
# echo "Running Valgrind to check for memory leaks for bonus part"
# valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./test_gnl_bonus $LOOP_COUNT
# echo "Done"
