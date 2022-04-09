# OpenGL Version 4.6.0
appname := OpenGLPractice
source := ../OpenGLProgrammingPractice/source
header := ../OpenGLProgrammingPractice/header
lib := ../OpenGLProgrammingPractice/lib
build_objects := ../OpenGLProgrammingPractice/build/objects
build_debug := ../OpenGLProgrammingPractice/build/debug
objects := 	main.o \
						shaderutility.o \
						dataobjects.o \
						texture.o \
						camera.o \
						model.o 
c_flags := -O3 -Wall -std=c++1z
windows_flag  := -mwindows
link := -lglew32 -lglfw3dll -lopengl32 -lglu32 -lglut32 -lgdi32 -luser32 -lkernel32

debug: $(objects)
	g++ -s -I $(header)/stb\
         -I $(header)/glfw \
				 -I $(header)/glm \
	       -I $(header)/noysoft \
			$(build_objects)/model.o \
			$(build_objects)/camera.o \
			$(build_objects)/texture.o \
			$(build_objects)/dataobjects.o \
			$(build_objects)/shaderutility.o \
			$(build_objects)/main.o \
	    -o $(build_debug)/$(appname) \
			$(link) \
			$(c_flags)

main.o:
	g++ -c $(source)/main.cpp -o $(build_objects)/main.o

shaderutility.o:
	g++ -c $(source)/shaderutility.cpp -o $(build_objects)/shaderutility.o

dataobjects.o:
	g++ -c $(source)/dataobjects.cpp -o $(build_objects)/dataobjects.o

texture.o:
	g++ -c $(source)/texture.cpp -o $(build_objects)/texture.o

camera.o:
	g++ -c $(source)/camera.cpp -o $(build_objects)/camera.o

model.o:
	g++ -c $(source)/model.cpp -o $(build_objects)/model.o

test:
	$(build_debug)/$(appname)
