DB_FLAGS  = -Wall -g -ggdb
#DB_FLAGS = -O3

GTK_CMP   = `pkg-config --cflags --libs gtk+-3.0`
GTK_LIB   = `pkg-config --libs gtk+-3.0`

INCLUDE   = 

LIBS      =  $(GTK_LIB) -lm #-lgtkhtml-4.0

LOPTS     = 

CFLAGS    = $(DB_FLAGS) $(GTK_CMP) #-I/usr/include/libgtkhtml-4.0
LFLAGS    = $(DB_FLAGS)

CC        = gcc
RM        = rm

OBJS      = 

EXEC      = 

PROGS     = Gtk3_01_01 Gtk3_01_02\
			Gtk3_02_01 Gtk3_02_02 Gtk3_02_03 Gtk3_02_04\
			Gtk3_03_01 Gtk3_03_02 Gtk3_03_03 Gtk3_03_04 Gtk3_03_05\
			Gtk3_04_01 Gtk3_04_02 Gtk3_05_01 Gtk3_05_02\
			Gtk3_06_01 Gtk3_06_02 Gtk3_06_03 Gtk3_07_01 Gtk3_07_02\
			Gtk3_08_01 Gtk3_08_02 Gtk3_08_03\
			Gtk3_09_01 Gtk3_09_02 Gtk3_09_03 Gtk3_09_04\
			Gtk3_10_01 Gtk3_10_02 Gtk3_10_03\
			Gtk3_11_01 Gtk3_11_02 Gtk3_11_03 Gtk3_11_04\
			Gtk3_12_01 Gtk3_12_02 Gtk3_13_01 Gtk3_14_01 Gtk3_15_01\
			Gtk3_40_01 Gtk3_41_01 Gtk3_41_02 Gtk3_41_03 Gtk3_41_04\
			Gtk3_43_01 Gtk3_43_02 Gtk3_43_03 Gtk3_43_04 Gtk3_43_05\
			Gtk3_45_01 Gtk3_45_02 Gtk3_45_03 Gtk3_45_04 Gtk3_45_05\
			Gtk3_45_06 Gtk3_45_07 Gtk3_47_01 Gtk3_47_02\
			Gtk3_60_01 Gtk3_60_02 Gtk3_60_03 Gtk3_61_01 Gtk3_61_02\
			Gtk3_62_01 Gtk3_62_02 Gtk3_62_03 Gtk3_62_04 Gtk3_62_05\
			Gtk3_62_06 Gtk3_62_07 Gtk3_63_01\
			Gtk3_65_01 Gtk3_65_02 Gtk3_65_03 Gtk3_65_04\
			Gtk3_80_01

all: comp link

comp: 
	for fname in $(PROGS); do $(CC) $(CFLAGS) -c $$fname.c ; done

link: 
	for fname in $(PROGS); do $(CC) $(LFLAGS) -o $$fname $$fname.o $(LIBS) ; done

clean:
	$(RM) -f *~ *.o $(PROGS)