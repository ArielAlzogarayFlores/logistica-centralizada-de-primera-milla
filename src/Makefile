CC = g++

CFLAGS = -std=c++17 -O2

SRC = \
main.cpp \
utils/gap_instance.cpp \
utils/io.cpp \
utils/algorithm_runner.cpp \
heuristicas/heuristica_1.cpp \
heuristicas/heuristica_2.cpp \
heuristicas/heuristica_3.cpp\
heuristicas/heuristica_4.cpp\
heuristicas/heuristica_5.cpp\
busqueda-local/operador_1.cpp \
busqueda-local/operador_2.cpp


OBJ = $(SRC:.cpp=.o)

EXEC = gap_simulator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run:
	./$(EXEC)