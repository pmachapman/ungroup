CC = bcc32
CFLAGS = -P -O2 -w -N -3 -d

all:
		$(CC) $(CFLAGS) ungroup.c

clean:
		del *.obj
		del ungroup.exe
		del ungroup.tds
