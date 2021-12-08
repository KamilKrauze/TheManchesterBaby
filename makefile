main: main.o assembler.o system.o
	g++ -O2 -g -Wno-unused-variable -Wall -Wextra -Werror -o main main.o assembler.o system.o
main.o:	./main.cpp
	g++ -O2 -g -Wno-unused-variable -Wall -Wextra -Werror -c ./main.cpp
assembler.o: ./assembler.cpp
	g++ -O2 -g -Wno-unused-variable -Wall -Wextra -Werror -c ./assembler.cpp
system.o:	./system.cpp
	g++ -O2 -g -Wno-unused-variable -Wall -Wextra -Werror -c ./system.cpp
clean:
	rm -f -r main main.o assembler.o system.o
rebuild:
	rm -f -r main main.o assembler.o system.o
	make