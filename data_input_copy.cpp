#include "data_input.hpp"
#include "heat_map.hpp"
#include "data_cell.hpp"
#include <fstream>
#include <iostream>
#include <string>
#define DATA1_PIX_SIZE 3
#define DATA2_PIX_SIZE 3

using namespace std;

// Input the data for the heat map, from a file
//---------------------------------------------
void DataInput::input_data( HeatMap * map )
{

	ifstream colon_file;
	colon_file.open("bio_data/colon-purged-carcinoma-dyn-expr.cdt");
	string next_line;
	string token_string;
	string delimiter = "\t";
	int pos = 0;
	double token;

	unsigned int width = 0;
	unsigned int height = 0;

	vector <DataCell *> all_cells;
	DataCell * cell;

	// Skip the first 3 lines of the file
	for ( int i = 1; i <= 3; i++ )
	{
		getline(colon_file, next_line);
	}


	// Read in the .cdt file line-by-line (row by row) and take in each value (2-16) that
	// is located in each column (the tab delimited numbers), and puts them in DataCells and then
	// into the vector<DataCell> of the HeatMap
	int a = 1, b = 1;
	bool width_check = true;
	while( !colon_file.eof() )
	{
		cout << "NEW ROW  " << a << "!" <<'\n' <<'\n'<<'\n'<<'\n';
		getline(colon_file, next_line);
		height++;

		while( (pos = next_line.find(delimiter)) != string::npos )
		{
			// Get rid of first 4 columns in each row
			for( int i = 1; i<= 4; i++)
			{
				next_line.erase(0, pos + delimiter.length());
				pos = next_line.find(delimiter);

			}

			// take in next data value as a string,
			// convert it into a floating point vlaue (double),
			// create a new DataCell object and set its data value accordingly,
			// adds the DataCell into our vector
			token_string = next_line.substr(0, pos);
			if(token_string != "")
				token = stod(token_string, NULL);
			cell = new DataCell();
			cell->setDataVal(token);
			all_cells.push_back(cell);
			if(width_check)
				width++;
			cout << b << ". " << "Cell created withh Value:  " << token << '\n';
			b++;

			// erases token from string
			next_line.erase(0, pos + delimiter.length());
			
		}

		width_check = false;

/*
		if(next_line != "")
			token = stod(next_line, NULL);
		cell = new DataCell();
		cell->setDataVal(token);
		all_cells.push_back(cell); //push back last substring
		width++;
*/
		a++;
		cout << "MADE IT" << '\n';

	}

	// Give the HeatMap a vector of all the DataCells,
	// and set the width and height of the frame of the map
	map->setDataCells(all_cells);
	map->setWidth(width * DATA1_PIX_SIZE);
	map->setHeight(height * DATA2_PIX_SIZE);

	colon_file.close();

	// Loop through every DataCell just created,
	// and set it's R,G,B values,
	// as well as its X,Y coordinates
	int r = 0, g = 0, i = 1;
	double val = 0;
	vector<DataCell *>::iterator it = all_cells.begin();

	for( int x = 0; x < map->getWidth(); x += DATA1_PIX_SIZE )
	{
		for( int y = 0; y < map->getHeight(); y += DATA2_PIX_SIZE )
		{
			
			if( it != all_cells.end() )
			{
				cell = *it;
				val = cell->getDataVal();
				r = (255 * val) / 16;		//R,G,B values based on data value
				g = (255 * (16 - val)) / 16;	// closer to 2 (technically 0) = more green
								// closert to 16 = more red
								// green -> yellow -> orange -> red,  meter
				cell->setXCoord(x);
				cell->setYCoord(y);
				cell->setR(r);
				cell->setG(g);
				it++;
				cout << "Coloring Cell:  " << i << '\n';
				i++;
			}

		}

	}

}
	


