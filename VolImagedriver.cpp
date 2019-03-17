/*****************************************************************
* Basic driver file
* Author: Kgomotso Welcome
* Date started: 19/02/2019
* Date completed: 24/02/2019
******************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include "VolImage.h"

using namespace WLCKGO001;
using namespace std;
VolImage volimage;

int main(int argc, char* argv[]){
 	cout << "THIS IS THE DRIVER FILE." << endl;

 	string executable = argv[0];
 	string imageBase = argv[1];
 	volimage.readImages(imageBase);
 	cout << "Number of images: " << volimage.numOfImages() << endl;
	cout << "Number of bytes required: " << volimage.volImageSize() << endl;

 	if (argc == 3){
 		cout << "Number of images: " << volimage.numOfImages() << endl;
		cout << "Number of bytes required: " << volimage.volImageSize() << endl;
 	}

 	else if(argc == 5){
 		if (string(argv[2]) == "-x"){
 			int slice;
 			istringstream (argv[3]) >> slice;
 			string output_file_name = argv[4];
 			volimage.extract(slice, output_file_name);
 		}

 		else if (string(argv[2]) == "-g"){
 			int sliceG;
 			istringstream (argv[3]) >> sliceG;
 			string output_file_name = argv[4];
 			volimage.extractRow(sliceG, output_file_name);
 		}
 	}

 	else if(argc == 6){
 		if (string(argv[2]) == "-d"){
 			int sliceI;
 			int sliceJ;
 			istringstream (argv[3]) >> sliceI;
 			istringstream (argv[4]) >> sliceJ;
 			string output_file_name = argv[5];
 			volimage.diffmap(sliceI, sliceJ, output_file_name);
 		}
 	}

	return 0;
}
