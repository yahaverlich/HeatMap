#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include "heat_map.hpp"
#include "data_cell.hpp"
#include "agg_pixfmt_rgb.h"
#include "data_input.hpp"
#define DATA1_PIX_SIZE 3
#define DATA2_PIX_SIZE 3
#define HEAT_MAP_WIDTH 424
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

	//temp vectors
//	vector <string> data1;
//	vector <string> data2;


	// input Data from command line
//	HeatMap::input_data(data1, data2);

	// 1.
//	HeatMap * map = new HeatMap( DATA1_PIX_SIZE * data1.size(),	//frame_width
//				DATA2_PIX_SIZE * data2.size() );	//frame_height

//	map->setData1(data1);	// set member variable vector data1
//	map->setData2(data2);	// set member variable vector data2

	HeatMap * map = new HeatMap();
	DataInput * input = new DataInput();
	input->input_data(map);


	// 2.
	unsigned char* buffer = new unsigned char[map->getWidth() * map->getHeight() * 3];

	// 3.
	memset(buffer, 255, map->getWidth() * map->getHeight() * 3);

	// 4.
	rendering_buffer rbuf(buffer, 
			       map->getWidth(), 
			       map->getHeight(), 
			       map->getWidth() * 3);

	// 5.
	pixfmt_rgb24 pixf(rbuf);



	for(DataCell * cell : map->getDataCells())
	{
		cell->color_data_cell (pixf);
				       
	}


	// create all DataCell objects and put them in the vector. Color
	// the cells of the table by their corresponding data value
/*	DataCell * cell;
	vector<DataCell> cells;
	int i = 0, j = 0, val = 0, r = 0, g = 0, b = 0;
	string s1, s2;
	for( int x = 0; x < DATA1_PIX_SIZE * map->getData1().size(); x += DATA1_PIX_SIZE )
	{
		for( int y = 0; y < DATA2_PIX_SIZE * map->getData2().size(); y += DATA2_PIX_SIZE )
		{
			val = rand() % 100 + 1;		// pick a number from 1 - 100
			r = (255 * val) / 100;		//R,G,B values based on data value
			g = (255 * (100 - val)) / 100;	// closer to 1 = more green
							// closert to 100 = more red
							// green -> yellow -> orange -> red,  meter

			vector<string> & temp1 = map->getData1();
			vector<string> & temp2 = map->getData2();

			s1 = temp1[i];
			s2 = temp2[j];
			
			cell = new DataCell( s1, s2, x, y, val, r, g, b );

			cell->color_data_cell (pixf, cell->getXCoord(), cell->getYCoord(), 
					       cell->getR(), cell->getG(), cell->getB()); 
			cells.push_back(*cell);

			j++;
		}

		i++;
		j = 0;
	}
	map->setDataCells(cells);
*/			
	// draw tha map/table lines
//	map->draw_vertical_lines (pixf);
//	map->draw_horizontal_lines (pixf);

	map->write_ppm(buffer, map->getWidth(), map->getHeight(), "heat_map.ppm");

	delete [] buffer;
	delete(map);
	delete(input);
	
	return 0;
}


