# This is a Makefile for the Battlefield project
CC = gcc
CFLAGS = -g -Wall -std=c99
CCLINK = $(CC)
LIBS =
OBJS = Soldier.o APC.o Squad.o WarZone.o List.o Battlefield.o Main.o
RM = rm -f
# Creating the executable (Battlefield)
Battlefield: $(OBJS)
	$(CCLINK) -o Battlefield $(OBJS) $(LIBS)
# Creating object files using default rules
APC.o: APC.c APC.h Soldier.h defs.h
Battlefield.o: Battlefield.c Battlefield.h WarZone.h List.h defs.h Squad.h Soldier.h APC.h
List.o: List.c List.h defs.h
Main.o: Main.c defs.h Battlefield.h WarZone.h List.h Squad.h Soldier.h APC.h
Soldier.o: Soldier.c Soldier.h defs.h
Squad.o: Squad.c Squad.h List.h defs.h Soldier.h APC.h
WarZone.o: WarZone.c WarZone.h List.h defs.h Squad.h Soldier.h APC.h

# Cleaning old files before new make
clean:
	$(RM) Battlefield *.o *.bak *~ "#"* core
	
	
	

