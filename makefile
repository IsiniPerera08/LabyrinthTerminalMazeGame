CC = gcc
CFLAGS= -Wall -pedantic -ansi
TARGET = labyrinth
OBJ = main.o map.o color.o terminal.o random.o player.o enemy.o linkedList.o newSleep.o

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

main.o : main.c map.h random.h terminal.h player.h enemy.h color.h linkedList.h
	$(CC) $(CFLAGS) -c main.c

map.o : map.c map.h color.h
	$(CC) $(CFLAGS) -c map.c

color.o : color.c color.h
	$(CC) $(CFLAGS) -c color.c

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

random.o : random.c random.h
	$(CC) $(CFLAGS) -c random.c

player.o : player.c player.h map.h
	$(CC) $(CFLAGS) -c player.c

enemy.o : enemy.c enemy.h map.h random.h
	$(CC) $(CFLAGS) -c enemy.c

linkedList.o : linkedList.c linkedList.h
	$(CC) $(CFLAGS) -c linkedList.c

newSleep.o : newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

clean : 
	rm -f $(OBJ) $(TARGET)