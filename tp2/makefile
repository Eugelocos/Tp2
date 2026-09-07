local:
	g++ -g -std=c++11 -Wall -Wconversion -Wno-sign-conversion -Werror -o tp2 *.cpp
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./tp2
	rm tp2

docker:
	docker build --tag tp2_udesa .
	docker run tp2_udesa

clean_docker:
	 bash docker_clean.sh
