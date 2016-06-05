CC      = gcc
CFLAGS  =-std=c99 -Wall -pedantic -g 
#header file location 
HEADDIR = #-I./git/utf8proc/ 
#libery name 
LDFLAGS =# -static -lutf8proc  -lutf8proc 
#libery location
LIBDIR = -L./git/utf8proc/
#libery source code 
LIBSRC = #./lib/PR_libsqlite.c
LIBOBJ = $(LIBSRC:.c=.o)
LIB = $(LIBSRC:.c=.a)
#src file name 
SRC = main.c 
OBJ = $(SRC:.c=.o) 
EXECUTABLE = $(SRC:.c=) 

all:clean cleanest $(SRC) $(LIBSRC) $(LIB) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ) 
	$(CC) $(OBJ) $(LIBDIR) -o $@ $(LDFLAGS) 
# all .o files 	
%.o : %.c 
	$(CC) $(CFLAGS) $(LIBDIR) $(LDFLAGS) -c $(HEADDIR) $< -o $@
#compile lib obj 
$(LIB):$(LIBOBJ)
	ar rcs $@ $<

.PHONY: clean cleanest all

clean:
	rm -f $(OBJ)

cleanest: clean
	rm -f *~

