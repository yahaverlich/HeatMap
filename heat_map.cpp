#include <stdio.h>
#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include "heat_map.hpp"
#include "agg_pixfmt_rgb.h"



	//HeatMap Default Constructor
	//--------------------------------------------------
	HeatMap::HeatMap() { setWidth(320); setHeight(200); }


	//HeatMap Constructor -- Set Frame Width/Height
	//--------------------------------------------------
	HeatMap::HeatMap(unsigned int x, unsigned int y)
	{

		setWidth(x);
		setHeight(y);	
	}


	//HEAT MAP DESTRUCTOR
	HeatMap::~HeatMap()
	{
		/*
		getData1().clear();
		getData2().clear();
		getDataCells().clear();
		*/
	}

	// Write the heat map (drawing) to a .ppm file
	//---------------------------------------------
	bool HeatMap::write_ppm(const unsigned char* buf, 
		       unsigned width, 
		       unsigned height, 
		       const char* file_name)
	{
		FILE* fd = fopen(file_name, "wb");
		if(fd)
		{
			fprintf(fd, "P6 %d %d 255 ", width, height);
			fwrite(buf, 1, width * height * 3, fd);
			fclose(fd);
			return true;
		}
			return false;
	}

	// Input the data for the heat map, from the command line
	//-------------------------------------------------------
	bool HeatMap::input_data( vector<string> & data1, vector<string> & data2 )
	{

		// Input all Data 1 Elements from command line (cin)
		cout << "Input all Data 1 Elements, with a space seperating each element. " <<
			"Then hit <ENTER> when you're done." << endl;

		string full_input1;
		getline(cin, full_input1);
		string delimiter = " ";
		string token;
		int pos = 0;

		//split user input into substrings for each word and insert into data1 vector
		while( (pos = full_input1.find(delimiter)) != string::npos ) 
		{
			token = full_input1.substr(0, pos);
			data1.push_back(token);
			full_input1.erase(0, pos + delimiter.length());
		}
			data1.push_back(full_input1); //push back last substring

		// Input all Data 2 Elements from command line (cin)
		cout << "Input all Data 2 Elements, with a space seperating each element. " <<
			"Then hit <ENTER> when you're done." << endl;

		string full_input2;
		getline(cin, full_input2);
		string token2;
		pos = 0;

		//same as above while loop for data2 vector
		while( (pos = full_input2.find(delimiter)) != string::npos )
		{
			token2 = full_input2.substr(0, pos);
			data2.push_back(token2);
			full_input2.erase(0, pos + delimiter.length());
		}
			data2.push_back(full_input2);

		return true;
	}
		



















