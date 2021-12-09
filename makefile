main: main.o menu.o assembler.o system.o
	g++ -O2 -std=c++17 -Wno-unused-variable -Wall -Wextra -Werror -o main main.o menu.o assembler.o system.o

main.o:	./main.cpp
	g++ -O2 -std=c++17 -Wno-unused-variable -Wall -Wextra -Werror -c ./main.cpp

menu.o: ./menu.cpp ./menu.h
	g++ -O2 -std=c++17 -Wno-unused-variable -Wall -Wextra -Werror -c ./menu.cpp ./menu.h

assembler.o: ./assembler.cpp ./assembler.h
	g++ -O2 -std=c++17 -Wno-unused-variable -Wall -Wextra -Werror -c ./assembler.cpp ./assembler.h

system.o: ./system.cpp ./system.h
	g++ -O2 -std=c++17 -Wno-unused-variable -Wall -Wextra -Werror -c ./system.cpp ./system.h

clean:
	rm -f -r main main.o menu.o assembler.o system.o

rebuild:
	rm -f -r main main.o menu.o assembler.o system.o
	make