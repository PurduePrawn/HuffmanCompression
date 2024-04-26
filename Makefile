compile:
	gcc -std=c11 -g -Wall -Wshadow -pedantic -Wvla -Werror *.c -lm

test%: compile
	./a.out inputs/test$* output$*
	diff output$* expected/expected$*

all: test1 test2 test3 test4 test5

debug%: compile
	-gdb ./a.out inputs/test$* output$*
	lldb ./a.out inputs/test$* output$*


memcheck%: compile
	-valgrind ./a.out inputs/test$* output$*
	leaks --atExit -- ./a.out inputs/test$* output$*

clean:
	rm output*
	rm a.out
