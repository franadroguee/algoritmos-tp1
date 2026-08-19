local:
	g++ -g -std=c++11 -Wall -Wconversion -Wno-sign-conversion -Werror -o tp1 *.cpp -lm
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp1
	rm tp1

docker:
	docker build --tag tp1_udesa .
	docker run tp1_udesa
