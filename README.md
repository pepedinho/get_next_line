compile command : 

	cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=10 -g3

valgrind command :

	 valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./a.out
