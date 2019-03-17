/*****************************************************************
* .cpp file for function definitions and implementations
* Author: Kgomotso Welcome
* Date: 19/02/2019
* Date completed: 24/02/2019
******************************************************************/
#include <cstdlib>
#include "VolImage.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <exception>
#include <sstream>

using namespace std; 

/**
* Default constructor - set the width and height to 0. 
* 					  - intialize vector size to 0. 
**/
WLCKGO001 :: VolImage :: VolImage(){
	width = 0;
	height = 0;
	vector<unsigned char**> slices(0);
	
}
 
/**
* Destructor - Delete all the dynamically created
* memory by deleting the 2D array
**/
WLCKGO001 :: VolImage :: ~VolImage(){
	for (int i = 0; i<slices.size(); i++){
		for(int j = 0; j< height; j++){
			delete [] slices[i][j]; 
		}
		delete [] slices[i] ;
	}
} 

/**
* populate the object with images in stack and
* set member variables define in .cpp
*/ 
bool WLCKGO001 :: VolImage :: readImages(string baseName){
	vector<string> tokens;
	string fileName;
	string directory;
	cout << "Enter the file directory holding the MRI .raw files" << endl;
	cin >> directory;

	fileName = directory + "/" + baseName + ".data";
	ifstream file(fileName);
	std::string line;
	if(!file){
		cout << "Could not open " << baseName + ".data" << endl;
	}

	else{
		file >> std :: ws;
		while (getline(file, line)) {
			stringstream check1(line);
			string intermediate;
			while(std::getline(check1, intermediate, ' ')){
				tokens.push_back(intermediate);
			}
		}
		file.close();
	}

	istringstream(tokens[0]) >> width;
	istringstream(tokens[1]) >> height;
	istringstream(tokens[2]) >> number_images;
	
	cout << width << " " << height << " " << number_images << endl;

	unsigned char ** slice;
	for (int i = 0; i < number_images; i++){
		string string_num = to_string(i);
		string buffername = directory + "/" + baseName + string_num +".raw";

		ifstream binaryImage(buffername.c_str(), ios::binary);
		
		if (binaryImage.is_open()){
			slice = new unsigned char*[height];

			unsigned char * sliceRow;
			for (int i = 0; i < height; i++ ){
				sliceRow = new unsigned char[width];
				binaryImage.read((char *)sliceRow, width);
				slice[i] = sliceRow;
			}
			slices.push_back(slice);
			binaryImage.close();
		}
	}
	return true;
}

// compute difference map and write out; define in .cpp
void WLCKGO001 :: VolImage :: diffmap(int sliceI, int sliceJ, string output_prefix){

	//create header file
	string header_filename = output_prefix + ".data";
	ofstream output_header(header_filename.c_str(), ios::out);
	if(!output_header){
		cout << "Could not open " << header_filename << endl;
	}
	else if(output_header.is_open()){
        output_header << width << " " << height << " " << 1 << endl;
        //always close files!
        output_header.close();
    }

    //create binary output file
    string binary_file = output_prefix + ".raw";
    ofstream output_binary(binary_file.c_str(), ios::binary);
    if(!output_binary){
		cout << "Could not open " << header_filename << endl;
	}
	else if(output_binary.is_open()){
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				char byte = abs(((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j])/2);
				output_binary.write(&byte,1);
			}
		}
        output_binary.close();
    }
}

// extract slice sliceId and write to output - define in .cpp
void WLCKGO001 :: VolImage :: extract(int sliceId, string output_prefix){
	string header_filename = output_prefix + ".dat";
	ofstream output_header(header_filename.c_str(), ios::out);
	if(!output_header){
		cout << "Could not open " << header_filename << endl;
	}
	else if(output_header.is_open()){
        output_header << width << " " << height << " " << 1 << endl;
        //always close files!
        output_header.close();
    }

    string binary_file = output_prefix + ".raw";
    ofstream output_binary(binary_file.c_str(), ios::binary);
    if(!output_binary){
		cout << "Could not open " << header_filename << endl;
	}
	else if(output_binary.is_open()){
		for(int i = 0; i < height; i++){
			char* byte = (char*)slices[sliceId][i];
			output_binary.write(byte,width);
		}
        output_binary.close();
    }
}

void WLCKGO001 :: VolImage :: extractRow(int rowId, string output_prefix){
	string header_filename = output_prefix + ".dat";
	ofstream output_header(header_filename.c_str(), ios::out);
	if(!output_header){
		cout << "Could not open " << header_filename << endl;
	}
	else if(output_header.is_open()){
        output_header << width << " " << height << " " << 1 << endl;
        //always close files!
        output_header.close();
    }

    string binary_file = output_prefix + ".raw";
    ofstream output_binary(binary_file.c_str(), ios::binary);
    if(!output_binary){
		cout << "Could not open " << header_filename << endl;
	}
	else if(output_binary.is_open()){
		for(int i = 0; i < slices.size(); i++){
			char* byte = (char*)slices[i][rowId];
			output_binary.write(byte,width);
		}
        output_binary.close();
    }
}

// number of bytes uses to store image data bytes
//and pointers (ignore vector<> container, dims etc)
int WLCKGO001 :: VolImage :: volImageSize(void){
	return height*width*slices.size();
} 

int WLCKGO001 :: VolImage :: numOfImages(void){
	return slices.size();
} // define in .cpp

