CC = g++
DEBUG_FLAGS = -g -O0
COMP_FLAGS = -Wall -c -std=c++11 -I ./include
LINK_FLAGS = -Wall -std=c++11 -I ./include

SRC_DIR = ./src/
OBJ_DIR = ./obj/
SOURCES = $(wildcard ${SRC_DIR}*.cpp)
VAR = $(SOURCES:${SRC_DIR}%=%)
DEBUG_OBJ = $(VAR:.cpp=_d_src.o)
REL_OBJ = $(VAR:.cpp=_src.o)

LIB_SRC_DIR = ./libsrc/
LIB_OBJ_DIR = ./lib_obj/
LIB_SOURCES = $(wildcard ${LIB_SRC_DIR}*.cpp)
LIB_VAR = $(LIB_SOURCES:${LIB_SRC_DIR}%=%)
DEBUG_LIB_OBJ = $(LIB_VAR:.cpp=_d_lib.o)
REL_LIB_OBJ = $(LIB_VAR:.cpp=_lib.o)

SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx
DEBUG_LIB_FLAGS = -L ./lib ${SDL_FLAGS} -lEngine_debug
RELEASE_LIB_FLAGS = -L ./lib ${SDL_FLAGS} -lEngine_release

vpath %.hpp ${SRC_DIR} ${LIB_SRC_DIR}
vpath %.cpp ${SRC_DIR} ${LIB_SRC_DIR}
vpath %.o ${OBJ_DIR} ${LIB_OBJ_DIR}

libs: lib_debug lib_release

debug: lib_debug src_debug

release: lib_release src_release

lib_debug: ${DEBUG_LIB_OBJ}
	ar crv libEngine_debug.a ${LIB_OBJ_DIR}*.o
	mv libEngine_debug.a ./lib/
	cp ${LIB_SRC_DIR}*.hpp ./include/

lib_release: ${REL_LIB_OBJ}
	ar crv libEngine_release.a ${LIB_OBJ_DIR}*.o
	mv libEngine_release.a ./lib/
	cp ${LIB_SRC_DIR}*.hpp ./include/

%_d_lib.o: %.cpp %.hpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

%_d_lib.o: %.cpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

%_lib.o: %.cpp %.hpp
	${CC} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

%_lib.o: %.cpp
	${CC} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

src_debug: ${DEBUG_OBJ}
	${CC} $(addprefix ${OBJ_DIR},${DEBUG_OBJ}) -o debug ${DEBUG_LIB_FLAGS}

src_release: ${REL_OBJ}
	${CC} $(addprefix ${OBJ_DIR},${REL_OBJ}) -o release ${RELEASE_LIB_FLAGS}

%_d_src.o: %.cpp %.hpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%_d_src.o: %.cpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%_src.o: %.cpp %.hpp
	${CC} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%_src.o: %.cpp
	${CC} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

clean:
	rm -f ${OBJ_DIR}*.o ${LIB_OBJ_DIR}*.o ./include/* ./lib/* release debug
