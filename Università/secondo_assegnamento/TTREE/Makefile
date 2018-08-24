################################
#
#     Makefile Progetto Recupero AA 2017/18
#    
################################


# file da consegnare
# modificare se si aggiungono file
FILE_DA_CONSEGNARE=ttree.c

# preferenze compilatore e flag di compilazione
CC=clang
# compilazione 
CFLAGS= -Wall -pedantic -g

obj = ttree.o ttree_d.o

# phony targets
.PHONY: cleanall test1 test2 test3 test4 test5 consegna 


ttree1 : 01test.o $(obj)
	clang $(obj) 01test.o -o ttree1 -lm

ttree2 : 02test.o $(obj)
	clang $(obj) 02test.o -o ttree2 -lm

ttree3 : 03test.o $(obj)
	clang $(obj) 03test.o -o ttree3 -lm

ttree4 : 04test.o $(obj)
	clang $(obj) 04test.o -o ttree4 -lm

ttree5 : 05test.o $(obj)
	clang $(obj) 05test.o -o ttree5 -lm

ttree6 : 06test.o $(obj)
	clang $(obj) 06test.o -o ttree6 -lm
	
ttree7 : 07test.o $(obj)
	clang $(obj) 07test.o -o ttree7 -lm

ttree8 : 08test.o $(obj)
	clang $(obj) 08test.o -o ttree8 -lm

ttree.o: ttree.c ttree.h 
ttree_d.o: ttree_d.c ttree.h 
01test.o: 01test.c ttree.h   
02test.o: 02test.c ttree.h   
03test.o: 03test.c ttree.h   
04test.o: 04test.c ttree.h   
05test.o: 05test.c ttree.h
06test.o: 06test.c ttree.h
07test.o: 07test.c ttree.h   
08test.o: 08test.c ttree.h

cleanall: 
	-rm -f *.o *~ ./core ttree?


test1:
	make cleanall
	make ttree1
	-rm -f out1.txt
	./ttree1 | tee out1.txt
	diff out1.txt DATI/out1.check.txt
	@echo "********** Test1 superato!"

test2: 
	make cleanall
	make ttree2
	-rm -f out2.txt
	./ttree2 | tee out2.txt
	@echo "********** Test2 superato!"


test3: 
	make cleanall
	make ttree3
	-rm -f out3.txt
	./ttree3 | tee out3.txt
	@echo "********** Test3 superato!"


test4: 
	make cleanall
	make ttree4
	-rm -f out4?.txt
	./ttree4 
	diff out41.txt out42.txt
	@echo "********** Test4 superato!"
	

test5: 
	make cleanall
	make ttree5
	-rm -f out5.txt out5.txt.sorted
	./ttree5 | tee out5.txt
	diff DATI/out5.check.txt out5.txt
	@echo "********** Test5 superato!"


test6: 
	make cleanall
	make ttree6
	-rm -f out6.txt out6.txt.sorted
	./ttree6 | tee out6.txt
	sort -n out6.txt > out6.txt.sorted 
	diff DATI/out6.check.txt out6.txt.sorted
	@echo "********** Test6 superato!"
	
test7: 
	make cleanall
	make ttree7
	-rm -f out7.txt
	./ttree7 | tee out7.txt 
	sort -n out7.txt > out7.txt.sorted 
	diff DATI/out7.check.txt out7.txt.sorted 
	@echo "********** Test7 superato!"

test8: 
	make cleanall
	make ttree8
	-rm -f out8.txt
	./ttree8 | tee out8.txt 
	sort -n out8.txt > out8.txt.sorted
	diff DATI/out8.check.txt out8.txt.sorted
	@echo "********** Test8 superato!"

consegna:
	make cleanall
	make test1
	make test2
	make test3
	make test4
	make test5
	make test6
	make test7
	make test8
	./gruppo-check.pl < gruppo.txt
	tar -cvf $(USER)-pr.tar ./gruppo.txt  $(FILE_DA_CONSEGNARE) 
	@echo "********** TAR creato inviare in allegato a una mail al docente del proprio corso insieme a nome, cognome,  numero di matricola dei componenti del gruppo"
