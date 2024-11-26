CC = g++ -fdiagnostics-color=always
FLAGS = -std=c++17 -g -O3 -Wall -I.

FLAGS += -fopenmp

OPENMP_FLAGS = -fopenmp

LIBS = -pthread

BUILD = build
OBJ = build/obj

GRAPH = graph
MATCH = matching
UTILS = utils
BUILD_TOOLS = build/tools

IEDYN = $(MATCH)/Iedyn
GRAPHFLOW = $(MATCH)/GraphFlow
SYMBI = $(MATCH)/SymBi
SJ_TREE = $(MATCH)/SJTree
TURBOFLUX = $(MATCH)/TurboFlux
PARRALLEL = $(MATCH)/Parrallel

all : dir $(BUILD)/csm

dir: $(OBJ)

$(OBJ) :
	mkdir -p $(OBJ)

#################### start ####################

$(BUILD)/csm: $(OBJ)/main.o \
		$(OBJ)/matching.o \
		$(OBJ)/sj_tree.o $(OBJ)/graphflow.o \
		$(OBJ)/turboflux.o $(OBJ)/symbi.o \
		$(OBJ)/iedyn.o \
		$(OBJ)/parrallel.o \
		$(OBJ)/graph.o $(OBJ)/induced_graph.o \
		$(OBJ)/globals.o 
		
	$(CC) $(FLAGS) $(OBJ)/main.o \
		$(OBJ)/matching.o \
		$(OBJ)/sj_tree.o $(OBJ)/graphflow.o \
		$(OBJ)/turboflux.o $(OBJ)/symbi.o \
		$(OBJ)/iedyn.o $(OBJ)/parrallel.o \
		$(OBJ)/graph.o $(OBJ)/induced_graph.o \
		$(OBJ)/globals.o \
		-o $(BUILD)/csm $(LIBS)

$(OBJ)/main.o: $(MATCH)/main.cpp \
		$(UTILS)/CLI11.hpp \
		$(UTILS)/globals.h $(UTILS)/types.h \
		$(GRAPH)/graph.h \
		$(SJ_TREE)/sj_tree.h $(GRAPHFLOW)/graphflow.h \
		$(TURBOFLUX)/turboflux.h $(SYMBI)/symbi.h \
		$(IEDYN)/iedyn.h \
		$(PARRALLEL)/parrallel.h
	$(CC) -c $(FLAGS) $(MATCH)/main.cpp -o $(OBJ)/main.o

#################### matching ####################

$(OBJ)/iedyn.o: $(IEDYN)/iedyn.cpp \
		$(UTILS)/types.h $(UTILS)/globals.h \
		$(GRAPH)/graph.h \
		$(MATCH)/matching.h \
		$(IEDYN)/iedyn.h
	$(CC) -c $(FLAGS) $(IEDYN)/iedyn.cpp \
		-o $(OBJ)/iedyn.o

$(OBJ)/symbi.o: $(SYMBI)/symbi.cpp \
		$(UTILS)/types.h $(UTILS)/globals.h \
		$(GRAPH)/graph.h \
		$(MATCH)/matching.h \
		$(SYMBI)/symbi.h
	$(CC) -c $(FLAGS) $(SYMBI)/symbi.cpp \
		-o $(OBJ)/symbi.o

$(OBJ)/turboflux.o: $(TURBOFLUX)/turboflux.cpp \
		$(UTILS)/types.h $(UTILS)/globals.h \
		$(GRAPH)/graph.h \
		$(MATCH)/matching.h \
		$(TURBOFLUX)/turboflux.h
	$(CC) -c $(FLAGS) $(TURBOFLUX)/turboflux.cpp \
		-o $(OBJ)/turboflux.o

$(OBJ)/graphflow.o: $(GRAPHFLOW)/graphflow.cpp \
		$(UTILS)/types.h $(UTILS)/utils.h \
		$(UTILS)/globals.h \
		$(GRAPH)/graph.h \
		$(MATCH)/matching.h \
		$(GRAPHFLOW)/graphflow.h
	$(CC) -c $(FLAGS) $(GRAPHFLOW)/graphflow.cpp \
		-o $(OBJ)/graphflow.o

$(OBJ)/sj_tree.o: $(SJ_TREE)/sj_tree.cpp \
		$(UTILS)/types.h $(UTILS)/globals.h \
		$(GRAPH)/graph.cpp $(GRAPH)/induced_graph.h \
		$(MATCH)/matching.h \
		$(SJ_TREE)/sj_tree.h
	$(CC) -c $(FLAGS) $(SJ_TREE)/sj_tree.cpp \
		-o $(OBJ)/sj_tree.o

$(OBJ)/parrallel.o: $(PARRALLEL)/parrallel_symbi.cpp \
		$(UTILS)/types.h $(UTILS)/globals.h \
		$(GRAPH)/graph.cpp $(GRAPH)/induced_graph.h \
		$(MATCH)/matching.h \
		$(PARRALLEL)/parrallel.h
	$(CC) -c $(FLAGS)  $(PARRALLEL)/parrallel_symbi.cpp \
		-o $(OBJ)/parrallel.o

$(OBJ)/matching.o: $(MATCH)/matching.cpp \
		$(UTILS)/types.h \
		$(GRAPH)/graph.h \
		$(MATCH)/matching.h
	$(CC) -c $(FLAGS) $(MATCH)/matching.cpp \
		-o $(OBJ)/matching.o

#################### graph ####################

$(OBJ)/graph.o: $(GRAPH)/graph.cpp \
		$(UTILS)/types.h $(UTILS)/utils.h \
		$(GRAPH)/graph.h
	$(CC) -c $(FLAGS) $(GRAPH)/graph.cpp \
		-o $(OBJ)/graph.o

$(OBJ)/induced_graph.o: $(GRAPH)/induced_graph.cpp \
		$(UTILS)/types.h \
		$(GRAPH)/induced_graph.h $(GRAPH)/graph.h
	$(CC) -c $(FLAGS) $(GRAPH)/induced_graph.cpp \
		-o $(OBJ)/induced_graph.o

#################### utils ####################

$(OBJ)/globals.o: $(UTILS)/globals.cpp $(UTILS)/globals.h
	$(CC) -c $(FLAGS) $(UTILS)/globals.cpp \
		-o $(OBJ)/globals.o

#################### end ####################

.PHONY: clean

clean: 
	rm -r ${BUILD}/obj
	rm ${BUILD}/csm