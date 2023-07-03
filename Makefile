lib_version = 1.1.0-rc.1

all:
	make clean
	mkdir -p ./build
	gcc -Wall -Wextra -fpic -c lifo_int.c -o build/libgdlifo.$(lib_version).o -lgdalloc
	gcc -Wall -Wextra -shared -o build/libgdlifo.$(lib_version).so build/libgdlifo.$(lib_version).o
	cp lifo_int.h build/gdlifo.h

test:
	make clean
	mkdir -p build
	gcc -g -Wall -Wextra -lgdalloc -lcriterion main.c lifo_int.c -o build/main
	./build/main

install:
	rm -rf /usr/lib64/libgdlifo.$(lib_version).so /usr/lib64/libgdlifo.1.so /usr/lib64/libgdlifo.so
	rm -rf /usr/include/gdlifo.h
	cp build/libgdlifo.$(lib_version).so /usr/lib64/libgdlifo.$(lib_version).so
	ln -s /usr/lib64/libgdlifo.$(lib_version).so /usr/lib64/libgdlifo.1.so
	ln -s /usr/lib64/libgdlifo.$(lib_version).so /usr/lib64/libgdlifo.so
	cp build/gdlifo.h /usr/include/gdlifo.h

uninstall:
	rm -rf /usr/lib64/libgdlifo.* /usr/include/gdlifo.h

clean:
	rm -rf ./build
