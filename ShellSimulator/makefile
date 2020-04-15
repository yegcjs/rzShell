myShell:bin/myShell.o bin/Command.o bin/cmdManager.o bin/cat.o bin/cd.o bin/cmp.o bin/cp.o bin/install.o bin/man.o bin/wc.o bin/sh.o 
	g++ -g bin/myShell.o bin/Command.o bin/cmdManager.o bin/cat.o bin/cd.o bin/cmp.o bin/cp.o bin/install.o bin/man.o bin/wc.o bin/sh.o  -o myShell
bin/myShell.o:source/myShell.cpp source/myShell.h
	g++ -g -c source/myShell.cpp -o bin/myShell.o
bin/cmdManager.o:source/cmdManager.cpp source/cmdManager.h
	g++ -g -c source/cmdManager.cpp -o bin/cmdManager.o
bin/Command.o:source/Command.cpp source/Command.h
	g++ -g -c source/Command.cpp -o bin/Command.o
bin/cat.o:source/cat.cpp source/cat.h
	g++ -g -c source/cat.cpp -o bin/cat.o
bin/cd.o:source/cd.cpp source/cd.h
	g++ -g -c source/cd.cpp -o bin/cd.o
bin/cmp.o:source/cmp.cpp source/cmp.h
	g++ -g -c source/cmp.cpp -o bin/cmp.o
bin/cp.o:source/cp.cpp source/cp.h
	g++ -g -c source/cp.cpp -o bin/cp.o
bin/install.o:source/install.cpp source/install.h
	g++ -g -c source/install.cpp -o bin/install.o
bin/man.o:source/man.cpp source/man.h
	g++ -g -c source/man.cpp -o bin/man.o
bin/wc.o:source/wc.cpp source/wc.h
	g++ -g -c source/wc.cpp -o bin/wc.o
bin/sh.o:source/sh.cpp source/sh.h
	g++ -g -c source/sh.cpp -o bin/sh.o
clean:
	rm /bin/*.o
	rm myShell