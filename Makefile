objects = Main.o Analyzer.o Item.o

Main: Main.o Analyzer.o Item.o
	g++ -o Main ${objects} -g

Main.o: Main.cpp Analyzer.h Item.h
	g++ -c Main.cpp -g

Analyzer.o: Analyzer.h Analyzer.cpp
	g++ -c Analyzer.cpp -g

Item.o: Item.h Item.cpp
	g++ -c Item.cpp -g

.PHONY : clean
clean:
	del *.o *.exe
