DEFS = -D WATCHING
all: bin/server bin/client
run: all
	bin/server &
	bin/client 
build: all
bin/server: obj/server.o
	gcc obj/server.o -o bin/server

obj/server.o: src/server.c
	gcc -c $(DEFS) src/server.c -o obj/server.o

bin/client: obj/client.o
	gcc obj/client.o -o bin/client

obj/client.o: src/client.c
	gcc -c $(DEFS) src/client.c -o obj/client.o

clean:
	rm -rv obj
	mkdir -v obj
	rm -rv bin
	mkdir -v bin

rebuild: clean build
