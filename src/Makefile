CFLAGS=-Wall -Wextra -O2
LFLAGS=-lm -lraylib
OBJF=radarcore.o


radar.out: $(OBJF) main.cpp
	g++ main.cpp $(OBJF) -o radar.out $(CFLAGS) $(LFLAGS)

radarcore.o: radarcore.cpp
	g++ radarcore.cpp -o radarcore.o -c $(CFLAGS) $(LFLAGS)

clean:
	rm -f *.o *.out
