main: main.o system.o
	g++ -g -Wall -Wextra -Werror -o main main.o system.o
main.o:	./main.cpp
	gcc -O2 -g -Wall -Wextra -Werror -c ./main.cpp
system.o:	./system.cpp
	gcc -O2 -g -Wall -Wextra -Werror -c ./system.cpp
clean:
	rm -f -r main main.o system.o
rebuild:
	rm -f -r main main.o system.o
	make