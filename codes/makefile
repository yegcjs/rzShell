default:myShell
	./myShell
debug:myShell
	gdb myShell
myShell:myShell.o cmdManager.o cmp.o cp.o Command.o cd.o wc.o cat.o sh.o man.o
	g++ -g myShell.o cmdManager.o cmp.o cp.o Command.o cd.o wc.o cat.o sh.o man.o -o myShell
myShell.o: myShell.cpp myShell.h
	g++ -g -c myShell.cpp
cmdManager.o:cmdManager.cpp cmdManager.h
	g++ -g -c cmdManager.cpp
cmp.o:cmp.cpp cmp.h
	g++ -g -c cmp.cpp
cp.o:cp.cpp cp.h
	g++ -g -c cp.cpp
cd.o:cd.cpp cd.h
	g++ -g -c cd.cpp
cat.o:cat.cpp cat.h
	g++ -g -c cat.cpp
wc.o:wc.cpp wc.h
	g++ -g -c wc.cpp
sh.o:sh.cpp sh.h
	g++ -g -c sh.cpp
man.o:man.cpp man.h
	g++ -g -c man.cpp
Command.o:Command.cpp Command.h
	g++ -g -c Command.cpp
clean:
	rm *.o
	rm myShell
