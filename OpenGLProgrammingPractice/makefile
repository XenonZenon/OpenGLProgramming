# OpenGL Version 4.6.0
appname := OpenGLPractice
source := ../OpenGLProgrammingPractice/source
header := ../OpenGLProgrammingPractice/header
lib := ../OpenGLProgrammingPractice/lib
build_objects := ../OpenGLProgrammingPractice/build/objects
build_debug := ../OpenGLProgrammingPractice/build/debug
objects := 	main.o \
						shaderutility.o \
						objects.o \
						texture.o
c_flags := -O3 -Wall -std=c++1z
windows_flag  := -mwindows
link := -lglew32 -lglfw3dll -lopengl32 -lglu32 -lglut32 -lgdi32 -luser32 -lkernel32

debug: $(objects)
	g++ -s -I $(header)/stb\
         -I $(header)/glfw \
	       -I $(header)/noysoft \
			$(build_objects)/texture.o \
			$(build_objects)/objects.o \
			$(build_objects)/shaderutility.o \
			$(build_objects)/main.o \
	    -o $(build_debug)/$(appname) \
			$(link) \
			$(c_flags)

main.o:
	g++ -c $(source)/main.cpp -o $(build_objects)/main.o

shaderutility.o:
	g++ -c $(source)/shaderutility.cpp -o $(build_objects)/shaderutility.o

objects.o:
	g++ -c $(source)/objects.cpp -o $(build_objects)/objects.o

texture.o:
	g++ -c $(source)/texture.cpp -o $(build_objects)/texture.o

test:
	$(build_debug)/$(appname)
