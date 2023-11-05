build: main.o query.o date.o update.o execute.o udrd.o diverse.o
	gcc -Wall main.o query.o date.o update.o execute.o udrd.o diverse.o -o tema1
	
run: tema1
	./tema1

#test: test.o update.o udrd.o execute.o date.o diverse.o query.o
#	gcc -Wall test.o update.o udrd.o execute.o date.o diverse.o query.o -o test
#
#test.o: test.c
#	gcc -Wall -c test.c

main.o: main.c
	gcc -Wall -c main.c

query.o: query.c
	gcc -Wall -c query.c

date.o: date.c
	gcc -Wall -c date.c

update.o: update.c
	gcc -Wall -c update.c

execute.o: execute.c
	gcc -Wall -c execute.c

udrd.o: udrd.c
	gcc -Wall -c udrd.c

diverse.o: diverse.c
	gcc -Wall -c diverse.c

clean: 
	rm *.o && rm tema1