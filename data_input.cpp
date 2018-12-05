#include "data_input.hpp"
#include <iomanip>
#include "agg_pixfmt_rgb.h"
#include "heat_map.hpp"
#include "data_cell.hpp"
#include <fstream>
#include <iostream>
#include <string>
#define DATA1_PIX_SIZE 3
#define DATA2_PIX_SIZE 3

using namespace std;

// input all cell values and color map -- for each cell in the given row - TEST
void DataInput::input_cells_in_row( HeatMap * map, string & next_line, string & delimiter,
				    DataCell & cell, int & x, int & y, int & pos,
				    pixfmt_rgb24 & pixf, bool in_loop, int & b )
{
	double val = 0;
	int r = 0, g = 0;
	double token;
	string token_string;

	// take in next data value as a string,
	// convert it into a floating point vlaue (double),
	// create a new DataCell object and set its data value accordingly,
	// adds the DataCell into our vector
	if(in_loop){
		token_string = next_line.substr(0, pos);
		if(token_string != "")
			token = stod(token_string, NULL);
	}else{
		if(next_line != "")
			token = stod(next_line, NULL);
	}
	
	cell.setDataVal(token);
	val = token;
	r = (255 * val) / 16;		//R,G,B values based on data value
	g = (255 * (16 - val)) / 16;	// closer to 2 (technically 0) = more green
					// closert to 16 = more red
					// green -> yellow -> orange -> red,  meter
	cell.setXCoord(x);
	cell.setYCoord(y);
	cell.setR(r);
	cell.setG(g);
	if( (x + DATA1_PIX_SIZE) > map->getWidth() )
		x = 0;
	else
		x += DATA1_PIX_SIZE;
	cell.color_data_cell(pixf);

	cout << b << ". " << "Cell created with Value:  " << setprecision(10) << token << '\n';
	b++;

	// erases token from string
	if(in_loop)
		next_line.erase(0, pos + delimiter.length());

	//this line gets ride of that 1 extra tab in the middle
//	if( next_line.find(delimiter) == 0 )
//		next_line.erase(0, delimiter.length());
}

// Input the data for the heat map, from a file
//---------------------------------------------
void DataInput::input_data( HeatMap * map, pixfmt_rgb24 & pixf, int start, int end_row ) //   takes in specifically a pixfmt_rgb24 renderer.
{											    //   can make this take any type of renderer by making
											   //   this a template function and putting it in the .hpp file.
											   //   look at the example on data_cell.hpp -> color_data_cell()
	ifstream colon_file;
	colon_file.open("bio_data/colon-purged-carcinoma-dyn-expr.cdt");
	string next_line;
	int pos = 0;
	string delimiter = "\t";
	int start_row = start;


	DataCell cell;

		
	// Skip the first 3 lines of the file
	for ( int i = 1; i < start_row + 3; i++ )
	{
		getline(colon_file, next_line);
	}


	// Read in the .cdt file line-by-line (row by row) and take in each value (2-16) that
	// is located in each column (the tab delimited numbers), and puts them in DataCells and then
	// into the vector<DataCell> of the HeatMap
	int a = start_row, b = 1, x = 0, y = 0;
	bool column_delete = true;
		
	while( (start_row != end_row+1) && getline(colon_file, next_line) )
	{
		cout << "NEW ROW  " << a << "!" <<'\n' <<'\n'<<'\n'<<'\n';

		while( (pos = next_line.find(delimiter)) != string::npos )
		{

			if(column_delete)
			{
				// Get rid of first 4 columns in each row
				for( int j = 1; j<= 4; j++)
				{
					next_line.erase(0, pos + delimiter.length());
					pos = next_line.find(delimiter);

				}
			}

			// Call to the above method
			input_cells_in_row( map, next_line, delimiter, cell, x, y, pos, pixf, true, b );

			column_delete = false;

		}

		// Call to the above method
//		if( b != 2 )
//		input_cells_in_row( map, next_line, delimiter, cell, x, y, pos, pixf, false, b );

		column_delete = true;

		if( (y + DATA2_PIX_SIZE) > map->getHeight() )
			y = 0;
		else
			y += DATA2_PIX_SIZE;
		a++;
		cout << "MADE IT" << '\n';
		start_row++;

	}


	colon_file.close();



}
