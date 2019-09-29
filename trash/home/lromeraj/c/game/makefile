src = $(wildcard c_files/*.c)
obj = $(src:.c=.o)

main: $(obj)
	gcc -o $@ $^ -lm

run:
	./main
