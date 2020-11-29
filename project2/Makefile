main: main.o 
	g++ main.o directMap.o setAssociative.o setAssocNoAlloc.o prefetch.o prefetchMiss.o -o main

main.o: main.cpp directMap.o setAssociative.o setAssocNoAlloc.o prefetch.o prefetchMiss.o
	g++ -c main.cpp

directMap.o: directMap.cpp directMap.h
	g++ -c directMap.cpp

setAssociative.o: setAssociative.cpp setAssociative.h
	g++ -c setAssociative.cpp

setAssocNoAlloc.o:setAssocNoAlloc.cpp setAssocNoAlloc.h setAssociative.h
	g++ -c setAssocNoAlloc.cpp

prefetch.o: prefetch.cpp prefetch.h setAssociative.h
	g++ -c prefetch.cpp

prefetchMiss.o: prefetchMiss.cpp prefetchMiss.h setAssociative.h
	g++ -c prefetchMiss.cpp

clean:
	rm *.o main