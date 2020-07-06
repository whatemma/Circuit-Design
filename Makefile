truthtable: truthtable.c
	gcc -lm -g -Wall -Werror -fsanitize=address -o truthtable truthtable.c
clean:
	rm -f truthtable
