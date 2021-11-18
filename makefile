main: ./main.c ./system.c
	gcc -g -Wall -Wextra -Werror -o main ./main.c ./system.c
clean:
	rm -f -r main