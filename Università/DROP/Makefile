################################
#
#     Makefile PROGETTO RECUPERO AA 2016/17
#    
################################


# file da consegnare
FILE_DA_CONSEGNARE=drop.c myrand.c file.c main.c
# nome file che contiene la relazione
FILE_RELAZIONE=relazione.pdf

# preferenze compilatore e flag di compilazione
CC=gcc
# compilazione senza attesa
#CFLAGS= -Wall -pedantic -g
# compilazione con attesa
CFLAGS= -Wall -pedantic -g -DWAIT

obj = drop.o myrand.o drop_docenti.o file.o

# phony targets
.PHONY: cleanall test1 test2 test3 test4 test5 test6 consegna 

drop: main.o $(obj)
	gcc $(obj) main.o -o drop -lm

drop1 : test_one.o $(obj)
	gcc $(obj) test_one.o -o drop1 -lm

drop2 : test_two.o $(obj)
	gcc $(obj) test_two.o -o drop2 -lm

drop3 : test_three.o  $(obj)
	gcc $(obj) test_three.o -o drop3 -lm

drop4 : test_four.o $(obj)
	gcc $(obj) test_four.o -o drop4 -lm

drop5 : test_five.o $(obj)
	gcc $(obj) test_five.o -o drop5 -lm

drop6 : test_six.o $(obj)
	gcc $(obj) test_six.o -o drop6 -lm

myrand.o: myrand.c myrand.h 
drop.o: drop.c drop.h myrand.h 
file.o: file.c file.h
main.o: main.c drop.h file.h myrand.h
drop_docenti.o:drop_docenti.c drop.h
test_one.o: test_one.c drop.h 
test_two.o: test_two.c drop.h myrand.h
test_three.o: test_three.c drop.h 
test_four.o: test_four.c drop.h 
test_five.o: test_five.c drop.h myrand.h 
test_six.o: test_six.c drop.h myrand.h file.h

cleanall: 
	-rm -f *.o *~ ./core drop1 drop2 drop3 drop4 drop5 drop6 drop


test1:
	make drop1
	./drop1 
	@echo "********** Test1 superato!"

test2: 
	make drop2
	./drop2 
	@echo "********** Test2 superato!"


test3:
	cp DATA/out_test3.check .
	make cleanall
	make drop3
	./drop3 
	diff out_test3.txt out_test3.check
	@echo "********** Test3 superato!"

test4:
	cp DATA/out_test4.check .
	make cleanall
	make drop4
	./drop4 
	diff out_test4.txt out_test4.check
	@echo "********** Test4 superato!"

test5:
	make cleanall
	make drop5
	./drop5
	@echo "********** Test5 superato!"

test6:
	cp DATA/data6.txt .
	make cleanall
	make drop6
	./drop6
	diff out_test6_1.txt  out_test6_2.txt
	@echo "********** Test6 superato!"

SUBJECT=info17: consegna progetto di recupero
consegna:
	make cleanall
	make test1
	make test2
	make test3
	make test4
	make test5
	make test6
	./gruppo-check.pl < gruppo.txt
	tar -cvf $(USER)-pr.tar ./gruppo.txt  $(FILE_DA_CONSEGNARE) $(FILE_RELAZIONE)
	@echo "********** TAR creato inviare in allegato a una mail a \nsusanna.pelagatti@unipi.it insieme a nome, cognome,  numero di matricola dei componenti del gruppo con oggetto \"$(SUBJECT)\""
