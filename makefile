p1: mst.cpp graph.o graph.h primsimple.o primfibheap.o prim.o prim.h fibheap.h 
	echo "compiling Minimum Spanning Tree"
	g++ -c mst.cpp
	g++ -g mst.o graph.o primsimple.o fibheap.o primfibheap.o prim.o -o mst
graph.o: graph.cpp graph.h
	echo "Compiling Graph"
	g++ -c graph.cpp 
primsimple.o: primsimple.cpp prim.h
	g++ -c primsimple.cpp
primfibheap.o: primfibheap.cpp fibheap.o prim.h fibheap.h
	g++ -c primfibheap.cpp 
fibheap.o: 
	g++ -c fibheap.cpp
prim.o: prim.cpp prim.h primsimple.cpp
	echo "Compiling Prim"
	g++ -c prim.cpp  prim.h 
clean:
	rm *o
