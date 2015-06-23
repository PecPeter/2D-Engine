CC = g++
DEBUG_FLAGS = -g -O0
COMP_FLAGS = -Wall -c -std=c++11 -I ./include
LINK_FLAGS = -Wall -std=c++11 -I ./include

SRC_DIR = ./src/
OBJ_DIR = ./obj/
SOURCES = $(wildcard ${SRC_DIR}*.cpp)
VAR = $(SOURCES:${SRC_DIR}%=%)
DEBUG_OBJ = $(VAR:.cpp=_d.o)
REL_OBJ = $(VAR:.cpp=.o)

SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lEngine_debug
BULLET_FLAGS = -lBulletCollision -lBulletDynamics -lLinearMath
LIB_FLAGS = -L ./lib ${SDL_FLAGS} ${BULLET_FLAGS}

vpath %.hpp ${SRC_DIR}
vpath %.cpp ${SRC_DIR}
vpath %.o ${OBJ_DIR}

lib_debug: 
	g++ -g -c -Wall -std=c++11 ./libsrc/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx
	ar crv libEngine_debug.a *.o
	rm -f *.o ./lib/libEngine_debug.a ./include/*.hpp
	mv libEngine_debug.a ./lib/
	cp ./libsrc/*.hpp ./include/

debug: ${DEBUG_OBJ}
	${CC} $(addprefix ${OBJ_DIR},${DEBUG_OBJ}) -o debug ${LIB_FLAGS}

release: ${REL_OBJ}
	${CC} $(addprefix ${OBJ_DIR},${REL_OBJ}) -o release ${LIB_FLAGS}

%_d.o: %.cpp %.hpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%_d.o: %.cpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%.o: %.cpp %.hpp
	${CC} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%.o: %.cpp
	${CC} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

clean:
	rm -f ${OBJ_DIR}*.o release debug
