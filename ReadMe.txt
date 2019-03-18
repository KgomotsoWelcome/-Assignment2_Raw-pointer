************************************ReadMe.txt***********************************************

Submitted content:
	Assignment2:
	-brain_mri_raws
		-MRI.data
		-MRI1.raw - MRI122.raw
	-MRI_originals_png
		-MRI1.png - MRI122.png
	-VolImage.h
	-VolImage.cpp
	-VolImagedriver.cpp
	-makefile
	-README.txt
	-.git folder
	-diffmap.py
	-viewer.py

How to run the program:
	1. Compile VolImagedriver.cpp, VolImage.h and the VolImage.cpp provided by using the makfile provided by typing "make" on the terimnal.
	2. To run the program without commands use "make run".
	3. To run the difference use "make difference".
	4. To run the extraction use "make extract".
	5. To run the extractCross method use "make extractCross".
	*** When the program asks you to "Enter the file directory holding the MRI .raw files" please type "brain_mri_raws".
 
	
Otherwise to specify your own image number(s) use :
	1. /VolImage MRI -x <own number> output
	2. /VolImage MRI -d <own number> <own number> output2
	3. /VolImage MRI -g <own number> output3

