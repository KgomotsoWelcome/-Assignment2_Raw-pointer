/*****************************************************************
* .cpp file for function definitions and implementations
* Author: Kgomotso Welcome
* Date: 25/02/2019
* Date completed: 17/03/2019
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
	vector<unsigned char**> slices;
	
}
 
/**
* Destructor - Delete all the dynamically created
* 			 - memory by deleting the 2D array
**/
WLCKGO001 :: VolImage :: ~VolImage(){
	for (int i = 0; i<slices.size(); i++){
		for(int j = 0; j< height; j++){
			delete [] slices[i][j];  // deallocates inner loop
		}
		delete [] slices[i] ; //deallocates outer loop
	}
} 

/**
* Populate the object with images in stack and
* set member variables define in .cpp
*/ 
bool WLCKGO001 :: VolImage :: readImages(string baseName){
	vector<string> tokens;
	string fileName;
	string directory;
	cout << "Enter the file directory holding the MRI .raw files" << endl;
	cin >> directory;

	fileName = directory + "/" + baseName + ".data";
	ifstream file(fileName); //open header file
	std::string line;
	if(!file){
		cout << "Could not open " << baseName + ".data" << endl;
		cout << "Make sure that " << baseName << " exists."<< endl;
		return false;
	}

	else{
		file >> std :: ws;								//read through header file
		while (getline(file, line)) {
			stringstream check1(line);
			string intermediate;
			while(std::getline(check1, intermediate, ' ')){
				tokens.push_back(intermediate);
			}
		}
		file.close();  //close files
	}

	istringstream(tokens[0]) >> width;
	istringstream(tokens[1]) >> height;
	istringstream(tokens[2]) >> number_images;
	

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
			slices.push_back(slice); //store slice in 3D vector
			binaryImage.close();  //close files
		}else{
			cout << "Could not open " << buffername << endl;
		}
	}
	return true;
}

/**
* Method for creating a header file.
* Will be used id diffmap, extract and extractCross
*/ 
void WLCKGO001 :: VolImage :: header(int width, int height, string output_prefix){

	string header_filename = output_prefix + ".data";
	ofstream output_header(header_filename.c_str(), ios::out); //create and open file
	if(!output_header){
		cout << "Could not open " << header_filename << endl;
	}
	else if(output_header.is_open()){
        output_header << width << " " << height << " " << 1 << endl;
        output_header.close(); //close files
    }
}

/**
* compute difference map and write out; define in .cpp
*/ 
void WLCKGO001 :: VolImage :: diffmap(int sliceI, int sliceJ, string output_prefix){
	cout << "diffmap() has been called." << endl;
	header(width, height, output_prefix);

    string binary_file = output_prefix + ".raw";
    ofstream output_binary(binary_file.c_str(), ios::binary);
    if(!output_binary){
		cout << "Could not open " << binary_file << endl;
	}
	else if(output_binary.is_open()){
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				char byte = abs(((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j])/2);
				output_binary.write(&byte,1);
			}
		}
        output_binary.close();  //close files
    }
    cout << "The difference between " << sliceI << " and " << sliceJ <<" has been comptuted." << endl;
}

/**
* extract slice sliceId and write to output - define in .cpp
*/
void WLCKGO001 :: VolImage :: extract(int sliceId, string output_prefix){
	cout << "extract() has been called." << endl;
	header(width, height, output_prefix);

    string binary_file = output_prefix + ".raw";
    ofstream output_binary(binary_file.c_str(), ios::binary);
    if(!output_binary){
		cout << "Could not open " << binary_file << endl;
	}
	else if(output_binary.is_open()){
		for(int i = 0; i < height; i++){
			char* byte = (char*)slices[sliceId][i];
			output_binary.write(byte,width);
		}
        output_binary.close();  //close files
    }
    cout << sliceId << " has been extracted." << endl;
}

/**
* Builds image using one row from each slice 
* Slice depends on height specified.
*/
void WLCKGO001 :: VolImage :: extractCross(int rowId, string output_prefix){
	cout << "extractCross() has been called." << endl;
	header(width,slices.size(), output_prefix);

    string binary_file = output_prefix + ".raw";
    ofstream output_binary(binary_file.c_str(), ios::binary);

    if(!output_binary){
		cout << "Could not open " << binary_file << endl;
	}
	else if(output_binary.is_open()){


		for(int i = 0; i < slices.size(); i++){
			char* byte = (char*)slices[i][rowId];
			output_binary.write(byte,width);
		}

        output_binary.close(); //close files
    }
    cout << "The side view of " << rowId << " has been extracted." << endl;
}

/**
* Returns the memory calculation
*/
int WLCKGO001 :: VolImage :: volImageSize(void){
	int slicesSize = slices.size(); //size of slices vector
	int charSize = sizeof(unsigned char); // size of u_char's
	int ptrSize = sizeof(unsigned char*); // size of u_char* pointer
	int PtrtoPtrSize = sizeof(unsigned char**); //size of u_char** pointers 
	int numOfBytes = ((charSize * slicesSize * width * height) + (ptrSize * height * slicesSize) + (PtrtoPtrSize * slicesSize)); // memory calculation

	return numOfBytes;
} 

/**
* Returns the the number of images.
*/
int WLCKGO001 :: VolImage :: numOfImages(void){
	return slices.size();
} 

