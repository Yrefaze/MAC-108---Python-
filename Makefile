
	# Variables to save time and prevent typos
CXX = g++
FLAGS = -I src/include -L src/lib
LIBS = -lmingw32 -lSDL2main -lSDL2

# main
main:
	$(CXX) $(FLAGS) main.cpp -o main $(LIBS)

# orbit
orbit:
	$(CXX) $(FLAGS) orbit.cpp -o orbit $(LIBS)

orbit2:
	$(CXX) $(FLAGS) orbit2.cpp -o orbit2 $(LIBS)
orbit3:
	$(CXX) $(FLAGS) orbit3.cpp -o orbit3 $(LIBS)
orbit4:
	$(CXX) $(FLAGS) orbit4.cpp -o orbit4 $(LIBS)	
orbit5: 
	$(CXX) $(FLAGS) orbit5.cpp -o orbit5 $(LIBS)
orbit6:
	$(CXX) $(FLAGS) orbit6.cpp -o orbit6 $(LIBS)
orbit7:
	$(CXX) $(FLAGS) orbit7.cpp -o orbit7 $(LIBS)
orbit8:
	$(CXX) $(FLAGS) orbit8.cpp -o orbit8 $(LIBS)
orbit9:
	$(CXX) $(FLAGS) orbit9.cpp -o orbit9 $(LIBS)
# default
all: main orbit


