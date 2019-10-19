gcc -Wall -c src/client2.c
gcc -Wall -c src/string.c
gcc -Wall -c src/server2.c
gcc -Wall  -pthread -o client2.out client2.o string.o
gcc -Wall  -pthread -o server2.out server2.o
