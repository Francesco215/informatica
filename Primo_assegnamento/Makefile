################################
#
#     Makefile Assegnamento 1 AA 2016/17
#    
################################


# file da consegnare
FILE_DA_CONSEGNARE=drop.c myrand.c

# preferenze compilatore e flag di compilazione
CC=gcc
# compilazione senza attesa
#CFLAGS= -Wall -pedantic -g
# compilazione con attesa
CFLAGS= -Wall -pedantic -g -DWAIT

obj = drop.o myrand.o

# phony targets
.PHONY: cleanall test1 test2 test3 consegna docu


drop1 : test_one.o $(obj)
	gcc $(obj) test_one.o -o drop1 -lm

drop2 : test_two.o $(obj)
	gcc $(obj) test_two.o -o drop2 -lm

drop3 : test_three.o $(obj)
	gcc $(obj) test_three.o -o drop3 -lm


myrand.o: myrand.c myrand.h 
drop.o: drop.c drop.h myrand.h
test_one.o: test_one.c drop.h myrand.h
test_two.o: test_two.c drop.h myrand.h
test_three.o: test_three.c drop.h myrand.h


cleanall: 
	-rm -f *.o *~ ./core drop1 drop2 drop3


test1:
	cp DATA/drop1.h drop.h
	make cleanall
	make drop1
	./drop1 
	@echo "********** Test1 superato!"

test2: 
	cp DATA/drop2.h drop.h
	make cleanall
	make drop2
	./drop2 
	@echo "********** Test2 superato!"

test3:
	cp DATA/drop3.h drop.h
	make cleanall
	make drop3
	./drop3 
	@echo "********** Test3 superato!"


consegna:
	make cleanall
	make test1
	make test2
	make test3
	./gruppo-check.pl < gruppo.txt
	tar -cvf $(USER)-a1.tar ./gruppo.txt  $(FILE_DA_CONSEGNARE) 
	@echo "********** TAR creato inviare in allegato a una mail a \nsusanna.pelagatti@unipi.it insieme a nome, cognome,  numero di matricola dei componenti del gruppo"
