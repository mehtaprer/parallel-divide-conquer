CC =g++
CFLAGS= -lpthread -lrt

compile:
	$(CC) standard.cpp $(CFLAGS) -o standard
	$(CC) divide.cpp $(CFLAGS) -o divide
	$(CC) strassen.cpp $(CFLAGS) -o strassen
	$(CC) -std=c++11 pdivide.cpp $(CFLAGS) -o pdivide
	$(CC) -std=c++11 pstrassen.cpp $(CFLAGS) -o pstrassen
clean:
	rm standard divide pdivide strassen pstrassen
