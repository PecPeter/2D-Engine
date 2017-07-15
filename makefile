CC = g++
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -fopenmp
COMP_FLAGS = -Wall -c -std=c++14 -I ./include
LINK_FLAGS = -Wall -std=c++14 -I ./include

LIB_NAME = 2D-Engine

SRC_DIR = ./src/
OBJ_DIR = ./obj/
SOURCES := $(shell find $(SRC_DIR) -name *.cpp)
VAR = $(SOURCES:${SRC_DIR}%=%)
DEBUG_OBJ = $(VAR:.cpp=_src_d.o)
REL_OBJ = $(VAR:.cpp=_src.o)

LIB_SRC_DIR = ./libsrc/
LIB_OBJ_DIR = ./lib_obj/
LIB_SOURCES := $(shell find $(LIB_SRC_DIR) -name *.cpp)
LIB_VAR = $(LIB_SOURCES:${LIB_SRC_DIR}%=%)
DEBUG_LIB_OBJ = $(LIB_VAR:.cpp=_lib_d.o)
REL_LIB_OBJ = $(LIB_VAR:.cpp=_lib.o)

LIB_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -ltinyxml2
DEBUG_LIB_FLAGS = -L ./lib -l${LIB_NAME}_debug -lmathLib_debug ${LIB_FLAGS}
RELEASE_LIB_FLAGS = -L ./lib  -l${LIB_NAME}_release -lmathLib_release ${LIB_FLAGS}

vpath %.hpp ${SRC_DIR} ${LIB_SRC_DIR}
vpath %.cpp ${SRC_DIR} ${LIB_SRC_DIR}
vpath %.o ${OBJ_DIR} ${LIB_OBJ_DIR}

all: libs

libs: dlib rlib

debug: dlib dsrc

release: rlib rsrc

dlib: ${DEBUG_LIB_OBJ}
	ar crv lib${LIB_NAME}_debug.a $(shell find ${LIB_OBJ_DIR} -name *_lib_d.o)
	mv lib${LIB_NAME}_debug.a ./lib/
	rm -r -f ./include/${LIB_NAME}
	cp --parents $(shell find $(LIB_SRC_DIR) -name *.hpp) ./include
	mv ./include/$(LIB_SRC_DIR) ./include/${LIB_NAME}

rlib: ${REL_LIB_OBJ}
	ar crv lib${LIB_NAME}_release.a $(shell find ${LIB_OBJ_DIR} -name *_lib.o)
	mv lib${LIB_NAME}_release.a ./lib/
	rm -r -f ./include/${LIB_NAME}
	cp --parents $(shell find $(LIB_SRC_DIR) -name *.hpp) ./include
	mv ./include/$(LIB_SRC_DIR) ./include/${LIB_NAME}

%_lib_d.o: %.cpp %.hpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

%_lib_d.o: %.cpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

%_lib.o: %.cpp %.hpp
	${CC} ${RELEASE_FLAGS} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

%_lib.o: %.cpp
	${CC} ${RELEASE_FLAGS} ${COMP_FLAGS} $< -o ${LIB_OBJ_DIR}$@

dsrc: ${DEBUG_OBJ}
	${CC} $(addprefix ${OBJ_DIR},${DEBUG_OBJ}) -o debug ${DEBUG_LIB_FLAGS}

rsrc: ${REL_OBJ}
	${CC} $(addprefix ${OBJ_DIR},${REL_OBJ}) -o release ${RELEASE_LIB_FLAGS}

%_src_d.o: %.cpp %.hpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%_src_d.o: %.cpp
	${CC} ${DEBUG_FLAGS} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%_src.o: %.cpp %.hpp
	${CC} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

%_src.o: %.cpp
	${CC} ${COMP_FLAGS} $< -o ${OBJ_DIR}$@

clean:
	rm -r -f $(shell find ${OBJ_DIR} -name *.o) $(shell find ${LIB_OBJ_DIR} -name *.o) ./include/${LIB_NAME}/ ./lib/lib${LIB_NAME}* release debug
