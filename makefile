CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -Werror -pedantic \
			-fsanitize=address,undefined -fno-omit-frame-pointer -D_FORTIFY_SOURCE=2

all: main

main: main.o menu.o ManchesterBaby.o assembler.o system.o
	$(CXX) $(CXXFLAGS) -o main main.o menu.o ManchesterBaby.o assembler.o system.o

main.o: ./main.cpp
	$(CXX) $(CXXFLAGS) -c ./main.cpp

menu.o: ./menu.cpp ./menu.h
	$(CXX) $(CXXFLAGS) -c ./menu.cpp

ManchesterBaby.o: ./ManchesterBaby.cpp ./ManchesterBaby.h
	$(CXX) $(CXXFLAGS) -c ./ManchesterBaby.cpp

assembler.o: ./assembler.cpp ./assembler.h
	$(CXX) $(CXXFLAGS) -c ./assembler.cpp

system.o: ./system.cpp ./system.h
	$(CXX) $(CXXFLAGS) -c ./system.cpp

clean:
	rm -f -r main main.o menu.o assembler.o system.o ManchesterBaby.o

rebuild: clean all