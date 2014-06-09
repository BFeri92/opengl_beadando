MAIN = main
SRCPATH = ./
SHAREDPATH = ./GLTools/src/
SHAREDINCPATH = ./GLTools/include/
LIBDIRS = -L/usr/X11R6/lib -L/usr/X11R6/lib64 -L/usr/local/lib
INCDIRS = -I. -I/usr/include -I/usr/local/include -I/usr/include/GL -I$(SHAREDINCPATH)  -I$(SHAREDINCPATH)GL

CC = g++
CFLAGS = $(COMPILERFLAGS) -g -ggdb $(INCDIRS)
LIBS = -lX11 -lglut -lGL -lGLU -lm

compile:
	$(CC) $(CFLAGS) -o $(MAIN) $(LIBDIRS) $(SRCPATH)*.cpp $(SHAREDPATH)glew.c $(SHAREDPATH)GLTools.cpp $(SHAREDPATH)GLBatch.cpp $(SHAREDPATH)GLTriangleBatch.cpp $(SHAREDPATH)GLShaderManager.cpp $(SHAREDPATH)math3d.cpp $(LIBS)
	
clean:
	rm -f *.o
