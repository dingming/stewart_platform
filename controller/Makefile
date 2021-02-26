CC	= gcc
CFLAG	= -ggdb -Wall -O3

PROG	= controller

LIBDIR	= `pkg-config --libs gtk+-2.0  gmodule-2.0 libglade-2.0` 
INCS	= `pkg-config --cflags gtk+-2.0 gmodule-2.0 libglade-2.0` 
LIBS	= $(LIBDIR) -lm

SRC	= main.c callback.c shm.c
#HEAD	=

OBJ	= $(SRC:.c=.o)

all: $(PROG) #$(HEAD)

$(PROG): $(OBJ)
	$(CC) $(CFLAG) $(INCS) $(LIBS) $(OBJ) -o $@

#$(OBJ):$(HEAD)

.c.o:
	$(CC) $(CFLAG) $(INCS) -c $<

clean: 
	$(RM) -f ~* *.o *core core

depent:
	makedepend -- $(CFLAG) $(INCS) -- $(SRC);

remake:
	make clean;
	make;
# DO NOT DELETE
