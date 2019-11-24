DEBUG   = -g -ggdb -Wall
#DEBUG  = -O3

GTK_INC = `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk+-2.0`

GTK_CMP = `pkg-config --cflags --libs gtk+-3.0`
GTK_LIB = `pkg-config --libs gtk+-3.0`

#LIBS   = `pkg-config --libs glib-2.0` `pkg-config --libs gtk+-2.0` -lm
LIBS    =  $(GTK_LIB) -lm


CFLAGS  = $(DEBUG) $(GTK_CMP)
LFLAGS  = $(DEBUG)

CC      = gcc
RM      = rm

OBJS    = gb_error.o gb_styles.o gb_window.o gb_auxil.o

all: comp link

comp: $(OBJS)

link: ShowGtkBox $(OBJS)

ShowGtkBox: ShowGtkBox.o $(OBJS)
	$(CC) $(LFLAGS) -o ShowGtkBox ShowGtkBox.o $(OBJS) $(LIBS)

ShowGtkBox.o: ShowGtkBox.h ShowGtkBox.c
	$(CC) $(CFLAGS) -c ShowGtkBox.c

gb_error.o: gb_error.h gb_error.c
	$(CC) $(CFLAGS) -c gb_error.c

gb_styles.o: gb_styles.h gb_styles.c
	$(CC) $(CFLAGS) -c gb_styles.c

gb_window.o: gb_window.h gb_window.c
	$(CC) $(CFLAGS) -c gb_window.c

gb_auxil.o: gb_auxil.h gb_auxil.c
	$(CC) $(CFLAGS) -c gb_auxil.c

clean:
	$(RM) -f *~ *.o ShowGtkBox