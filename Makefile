compile:
	gcc -std=c11 -g -Wall -Wshadow -pedantic -Wvla -Werror *.c -lm
clean:
	rm output*
	rm a.out
test%: compile
	./a.out inputs/test$* output$*
	diff output$* expected/expected$*

all: test1 test2 test3 test4 test5
