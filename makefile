all: Main.o Helper.o Interface.o Transactional_Commands.o 
	g++ Main.o Helper.o Interface.o Transactional_Commands.o

Main.o: Main.cpp
	g++ -c Main.cpp

Helper.o: Helper.cpp
	g++ -c Helper.cpp

Interface.o: Interface.cpp
	g++ -c Interface.cpp

Transactional_Commands.o: Transactional_Commands.cpp
	g++ -c Transactional_Commands.cpp

clean:
	rm Main.o Helper.o Interface.o Transactional_Commands.o

wipe:
	rm Main.o Helper.o Interface.o Transactional_Commands.o Main.cpp Helper.cpp Helper.hpp Interface.cpp Interface.hpp Transactional_Commands.cpp Transactional_Commands.hpp Common.h
