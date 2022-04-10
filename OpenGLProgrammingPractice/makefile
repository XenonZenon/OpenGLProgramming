# OpenGL Version 4.6.0
appname := OpenGLPractice
assets := ../OpenGLProgrammingPractice/assets
source := ../OpenGLProgrammingPractice/source
header := ../OpenGLProgrammingPractice/header
build_objects := ../OpenGLProgrammingPractice/build/objects
build_debug := ../OpenGLProgrammingPractice/build/debug
objects := 	resource.res \
						main.o \
						headercollection.o \
						shaderutility.o \
						dataobjects.o \
						texture.o \
						camera.o \
						light.o \
						model.o
c_flags := -O3 -Wall -std=c++1z -static-libstdc++ -static-libgcc
windows_flag  := -mwindows
link := -lglew32 -lglfw3dll -lopengl32 -lglu32 -lglut32 -lgdi32 -luser32 -lkernel32

debug: $(objects)
	g++ -s $(c_flags) \
	 			 -I $(header)/stb\
         -I $(header)/glfw \
				 -I $(header)/glm \
	       -I $(header)/noysoft \
			$(build_objects)/light.o \
			$(build_objects)/model.o \
			$(build_objects)/camera.o \
			$(build_objects)/texture.o \
			$(build_objects)/dataobjects.o \
			$(build_objects)/shaderutility.o \
			$(build_objects)/headercollection.o \
			$(build_objects)/main.o \
	    -o $(build_debug)/$(appname) \
			$(build_objects)/resource.res \
			$(link)

resource.res:
	windres $(assets)/resource/resource.rc -O coff -o $(build_objects)/resource.res

main.o:
	g++ -c $(source)/main.cpp -o $(build_objects)/main.o

headercollection.o:
	g++ -c $(source)/headercollection.cpp -o $(build_objects)/headercollection.o

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

light.o:
	g++ -c $(source)/light.cpp -o $(build_objects)/light.o

test:
	$(build_debug)/$(appname)
