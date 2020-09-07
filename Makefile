CXX = clang++
ARGS = -Wall -g

all: clean Analyzer.o Main

Main: Main.o Analyzer.o
	$(CXX) $(ARGS) -o Main Main.o Analyzer.o
	
Main.o: Main.cpp Analyzer.cpp Sentence.h
	$(CXX) $(ARGS) -c Main.cpp

Analyzer.o: Analyzer.cpp Sentence.h Word.h
	$(CXX) $(ARGS) -std=c++11 -I ./boost_1_60_0/ -c Analyzer.cpp

clean: 
	rm -rf Analyzer.o Main Main.o