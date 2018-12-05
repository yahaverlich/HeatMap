#include <vector>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>
#include "heat_map.hpp"
#include "data_cell.hpp"
#include "agg_pixfmt_rgb.h"
#include "data_input.hpp"
#define DATA1_PIX_SIZE 3
#define DATA2_PIX_SIZE 3
#define HEAT_MAP_WIDTH 2115
#define HEAT_MAP_HEIGHT 4549


using namespace agg;
using namespace std;


int main()
{
//--------------------
// 1) Create a HeatMap object
// 2) Allocate the buffer.
// 3) Clear the buffer, for now "manually"
// 4) Create the rendering buffer object
// 5) Create the Pixel Format renderer
// 6) Write the buffer to .ppm file

	HeatMap * map = new HeatMap();
	DataInput * input = new DataInput();
	int bufferWidth = 0, bufferHeight = 0;


	int start_row = 1, end_row = 4549;
	bool success = true;
	string ans;
	bool skip_row_check = false;
	while(1)
	{
		cout << "Would you like to create a map of the whole file?   (y/n):   ";

		cin >> ans;
		cout << endl;

		if( (ans == "y") || (ans == "n") )
		{
			success = true;
		}
		else
		{
			cout << "Please type a 'y' or an 'n' " << endl;
			success = false;
		}

		if(success)
			break;

	}	

	if(ans == "n")
	{
		int pos = 0;
		double input = 0;

		while(1)
		{

			cout << "At what Row # would you like to start reading from?  (1-4549):   ";
			cin >> input;
			start_row = (int) input;
			cout << endl;
		
			if(cin.fail() || ((start_row < 1) || (start_row > HEAT_MAP_HEIGHT)))
			{
				cout << "Error with input. Make sure you only input one token, and that it's an integer between 1 - 4549." << endl;
				success = false;	

				// user didn't input a number
				cin.clear(); // reset failbit
				cin.ignore(INT_MAX, '\n');//skip bad input
			}else{
				success = true;
				cout << "** Note: Any inputted decimals will be truncated into whole numbers. **" << endl << endl; 
			}


			if(success)
				break;
		}


		success = true;
		while(1)
		{
			cout << "At what Row # would you like to end reading from?  (1-4549):   ";
			cin >> end_row;
			cout << endl;

			if(cin.fail())
			{
				cerr << "Error, must input one integer." << endl;
				success = false;	
			}else{
				if(end_row < start_row)
				{
					cout << "Please enter a row greater than or equal to the start row." << endl;
					continue;
				}
				success = true;
			}

			if(success)
				break;
		}

		bufferHeight = (end_row - start_row + 1) * DATA2_PIX_SIZE;
	}else{

		bufferHeight = HEAT_MAP_HEIGHT * DATA2_PIX_SIZE;
	}

	bufferWidth = HEAT_MAP_WIDTH * DATA1_PIX_SIZE;
	map->setWidth(bufferWidth);
	map->setHeight(bufferHeight);
	// 2.
	unsigned char* buffer = new unsigned char[ bufferWidth * bufferHeight * 3];

	// 3.
	memset(buffer, 255, bufferWidth * bufferHeight * 3);

	// 4.
	rendering_buffer rbuf(buffer, 
			       bufferWidth, 
			       bufferHeight, 
			       bufferWidth * 3);

	// 5.
	pixfmt_rgb24 pixf(rbuf);


	input->input_data(map, pixf, start_row, end_row);
	map->write_ppm(buffer, map->getWidth(), map->getHeight(), "heat_map.ppm");

	delete [] buffer;
	delete(map);
	delete(input);
	
	return 0;
}


