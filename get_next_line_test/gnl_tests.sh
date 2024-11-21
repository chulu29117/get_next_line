# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gnl_tests.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clu <clu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 17:38:52 by clu               #+#    #+#              #
#    Updated: 2024/11/21 18:29:06 by clu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Default loop count
LOOP_COUNT=10

# Check if a loop count is provided as an argument
if [ $# -ge 1 ]; then
	LOOP_COUNT=$1
fi

# Compilation for mandatory part
gcc -Wall -Wextra -g -D BUFFER_SIZE=5 -o test_gnl gnl_test.c get_next_line.c get_next_line_utils.c

# Check if compilation was successful
if [ $? -ne 0 ]; then
	echo "Compilation failed for mandatory part"
	exit 1
fi

# Run tests for mandatory part
echo "Running tests for mandatory part with the assigned BUFFER_SIZE"

# Test with various files
./test_gnl $LOOP_COUNT

# Run Valgrind to check for memory leaks
# echo "Running Valgrind to check for memory leaks for mandatory part"
# valgrind --leak-check=full --track-origins=yes ./test_gnl $LOOP_COUNT
# echo "Done"

# Compilation for bonus part
gcc -Wall -Wextra -g -D BUFFER_SIZE=5 -o test_gnl_bonus gnl_test_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c

# Check if compilation was successful
if [ $? -ne 0 ]; then
	echo "Compilation failed for bonus part"
	exit 1
fi

# Run tests for bonus part
echo "Running tests for bonus part with the assigned BUFFER_SIZE"

# Test with various files
./test_gnl_bonus $LOOP_COUNT

# Run Valgrind to check for memory leaks
# echo "Running Valgrind to check for memory leaks for bonus part"
# valgrind --leak-check=full --track-origins=yes ./test_gnl_bonus $LOOP_COUNT
# echo "Done"
