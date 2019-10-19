gcc -Wall -c src/client.c
gcc -Wall -c src/string.c
gcc -Wall -c src/server.c
gcc -Wall  -pthread -o client.out client.o string.o
gcc -Wall  -pthread -o server.out server.o
