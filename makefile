main: ./main.cpp ./system.cpp
	g++ -g -Wall -Wextra -Werror -o main ./main.cpp ./system.cpp
clean:
	rm -f -r main