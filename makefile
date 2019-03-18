#*****************************************************************
# makefile used to compile the driver file
# Author: Kgomotso Welcome
# Date: 25/02/2019
# Date completed: 17/03/2019
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
	./VolImage MRI

extract:
	./VolImage MRI -x 10 output

difference:
	./VolImage MRI -d 10 50 output2

extractCross:
	./VolImage MRI -g 10 output3

clean:
	@rm -f *.o
	@rm VolImage


