objects = Main.o Analyzer.o Item.o Symbol.o

Main: ${objects}
	g++ -o Main ${objects} -g

Main.o: Main.cpp Analyzer.h Item.h Symbol.h
	g++ -c Main.cpp -g

Analyzer.o: Analyzer.cpp Analyzer.h Symbol.h Item.h
	g++ -c Analyzer.cpp -g

Item.o: Item.cpp Item.h
	g++ -c Item.cpp -g

Symbol.o: Symbol.cpp Symbol.h
	g++ -c Symbol.cpp -g


.PHONY : clean
clean:
	del *.o *.exe
