UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	GL_LIB=-framework OpenGL
else
	GL_LIB=-lglut -lGLU -lGL
endif

all:
	g++ -g -I/usr/local/include/ -L/usr/local/lib/ -Iinclude -o ../bin/Relic main.cpp -std=c++11 -stdlib=libc++ -lm ${GL_LIB} -lsfml-window -lsfml-system -lsfml-graphics 
html:
	emcc -lm ${GL_LIB} -I./osx/SFML/include/  -o ../bin/Relic main.cpp -std=c++11 -stdlib=libc++
