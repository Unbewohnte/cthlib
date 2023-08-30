lib:
	mkdir -p build
	gcc -Wall -Werror -O2 -c src/*.c
	mv *.o build
	ar rcs build/cthlib.a build/*.o

test: clean
	gcc -Wall -Werror -O2 -static src/cthlib.c testing/test.c -o test

clean:
	rm -rf test build