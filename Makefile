LDFLAGS			= -lraylib -lm

main : main.c
	gcc $(CFLAGS) main.c -o main $(LDFLAGS)
clean:
	rm -f ./main
