build: display.h display.cpp entity.cpp entity.h input.cpp input.h main.cpp mesh.cpp mesh.h physics.cpp physics.h shader.cpp shader.h
	g++ *.cpp -lSDL2 -lGLEW -lGLU -lGL -o raytracer -std=c++11
run:
	./raytracer
