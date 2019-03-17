#*****************************************************************
# makefile used to compile the driver file
# Author: Kgomotso Welcome
# Date: 19/02/2019
# Date completed: 24/02/2019
#*****************************************************************

CC=g++
CK=-std=c++11

all:VolImagedriver

VolImagedriver: VolImage.o VolImagedriver.o
	$(CC) VolImagedriver.o VolImage.o -o VolImage

VolImage.o: VolImage.cpp VolImage.h
	$(CC) VolImage.cpp -c 

VolImagedriver.o: VolImagedriver.cpp VolImage.h
	$(CC) VolImagedriver.cpp -c 

run: 
	./VolImage

clean:
	@rm -f *.o
	@rm VolImage


