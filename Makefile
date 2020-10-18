predictors: predictors.o alwaysTaken.o neverTaken.o table.o biPredictorSingle.o biPredictorDouble.o gshare.o tournament.o
	g++ predictors.o alwaysTaken.o neverTaken.o table.o biPredictorSingle.o biPredictorDouble.o gshare.o tournament.o -o predictors

predictors.o: predictors.cpp 
	g++ -c predictors.cpp

alwaysTaken.o: alwaysTaken.cpp alwaysTaken.h
	g++ -c alwaysTaken.cpp

neverTaken.o: neverTaken.cpp neverTaken.h
	g++ -c neverTaken.cpp

table.o: table.cpp table.h
	g++ -c table.cpp

biPredictorSingle.o: biPredictorSingle.cpp biPredictorSingle.h table.h table.cpp
	g++ -c biPredictorSingle.cpp table.cpp

biPredictorDouble.o: biPredictorDouble.cpp biPredictorDouble.h table.h table.cpp
	g++ -c biPredictorDouble.cpp table.cpp

gshare.o: gshare.cpp gshare.h table.h table.cpp
	g++ -c gshare.cpp table.cpp

tournament.o: tournament.cpp tournament.h table.h table.cpp
	g++ -c tournament.cpp table.cpp

clean:
	rm *.o predictors