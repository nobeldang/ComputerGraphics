BIN = cg03 
CC = g++
FLAGS = -Wall -pedantic -no-pie
INC = -I ../common/include
LOC_LIB = ../common/linux_x86_64/libGLEW.a ../common/linux_x86_64/libglfw3.a
SYS_LIB = -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi
SRC = main.cpp stub.cpp gl_utils.cpp maths_funcs.cpp obj_parser.cpp stb_image.c

all:
	${CC} ${FLAGS} -o ${BIN} ${SRC} ${INC} ${LOC_LIB} ${SYS_LIB}
