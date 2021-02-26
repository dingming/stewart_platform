CC = g++ -g
CFLAG	= -ggdb -Wall -O3 -DMACOS

PROG = stewart_platform

INCS = -I/Developer/SDKs/MacOSX10.6.sdk/usr/X11/include -I/Developer/SDKs/MacOSX10.6.sdk/usr/include -I/Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/GLUT.framework/Versions/A/Headers
LIBDIR = -framework OpenGL -framework GLUT -framework Foundation
LIBS	= $(GL_LIBS) $(LIBDIR)
FLG = $(INCS) $(LIBDIR)
SRC = main.cpp mygl.cpp draw.cpp mathutils.cpp platform.cpp shm.cpp
HEAD = myconfig.h mygl.h draw.h color.h mathutils.h platform.h shm.h

OBJ = $(SRC:.cpp=.o)

all: $(PROG)

$(PROG): $(OBJ) $(HEAD)
	$(CC) $(CFLAG) $(INCS) $(LIBS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAG) $(INCS) -c $<

clean: 
	$(RM) -f ~* *.o *core core

depent:
	makedepend -- $(CFLAG) $(INCS) -- $(SRC);

remake:
	make clean;
	make;
