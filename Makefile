objects = Main.o Analyzer.o Item.o Symbol.o Parser.o

Main: ${objects}
	g++ -o Main ${objects}

Main.o: Main.cpp Analyzer.h Item.h Symbol.h Parser.h
	g++ -c Main.cpp

Analyzer.o: Analyzer.cpp Analyzer.h Symbol.h Item.h
	g++ -c Analyzer.cpp

Item.o: Item.cpp Item.h
	g++ -c Item.cpp

Symbol.o: Symbol.cpp Symbol.h
	g++ -c Symbol.cpp

Parser.o: Parser.cpp Parser.h Item.h
	g++ -c Parser.cpp

.PHONY : clean
clean:
	del *.o *.exe
