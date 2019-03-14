/*****************************************************************
* Basic driver file
* Author: Kgomotso Welcome
* Date started: 19/02/2019
* Date completed: 24/02/2019
******************************************************************/
#include <iostream>
#include <string>
#include "VolImage.h"

using namespace WLCKGO001;
using namespace std;
VolImage volimage;

int main(){
 	cout << "THIS IS THE DRIVER FILE." << endl;
 	volimage.readImages("MRI");
	return 0;
}


