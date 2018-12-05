#ifndef DATA_CELL_HPP
#define DATA_CELL_HPP

#include <string>
#include "agg_pixfmt_rgb.h"
#define DATA1_PIX_SIZE 3
#define DATA2_PIX_SIZE 3

using namespace std;
using namespace agg;

class DataCell {

   private:
	
	string data_1_element;
	string data_2_element;

	unsigned int x_coord;
	unsigned int y_coord;

	double data_value;

	int R, G, B;

   public:
	
	//HeatMap Default Constructor
	//--------------------------------------------------
	DataCell();

	//HeatMap Constructor -- Set Member Variables
	//--------------------------------------------------
	DataCell( string data1, string data2, int x, int y,
		  double val, int r, int g, int b );

	~DataCell();


	// GETTERS
	//---------------------------------------------
	unsigned int getXCoord() { return x_coord; }
	unsigned int getYCoord() { return y_coord; }
	string getData1Elem() { return data_1_element; }
	string getData2Elem() { return data_2_element; }
	double getDataVal() { return data_value; }
	int getR() { return R; }
	int getG() { return G; }
	int getB() { return B; }


	// SETTERS
	//---------------------------------------------
	void setXCoord( int x ) { x_coord = x; }
	void setYCoord( int y ) { y_coord = y; }
	void setData1Elem( string data ) { data_1_element = data; }
	void setData2Elem( string data ) { data_2_element = data; }
	void setDataVal( double val ) { data_value = val; }
	void setR( int r ) { R = r;  }
	void setG( int g ) { G = g; }
	void setB( int b ) { B = b; }


// TEMPLATE FUNCTIONS
//-------------------

	// Fill in the cell at corresponding coordinates with color
	//--------------------------------------------------------
	template<class Ren>
	void color_data_cell( Ren & ren )
	{

		//color cell from green->yellow->orange->red based
		//on its data value
		rgba8 c(R, G, B);
		int i = 0, j = 0;
		for( int y = y_coord; j < DATA2_PIX_SIZE; y++ )   //for use of black lines use: y = y_coord+1; j < DATA2_PIX_SIZE-1
		{
			for( int x = x_coord; i < DATA1_PIX_SIZE; x++ )   //for use of black lines use: x = x_coord+1; i < DATA1_PIX_SIZE-1
			{
				ren.copy_pixel(x, y, c);	
				i++;
			}
			j++;
			i = 0;
		}

	}
/*
	// Fill in the cell at corresponding coordinates with color
	//--------------------------------------------------------
	template<class Ren>
	void color_data_cell( Ren & ren, int cell_x, int cell_y,
			      int r, int g, int b)
	{

		//color cell from green->yellow->orange->red based
		//on its data value
		rgba8 c(r, g, b);
		int i = 0, j = 0;
		for( int y = cell_y+1; j < DATA2_PIX_SIZE-1; y++ )
		{
			for( int x = cell_x+1; i < DATA1_PIX_SIZE-1; x++ )
			{
				ren.copy_pixel(x, y, c);	
				i++;
			}
			j++;
			i = 0;
		}

	}
*/

};
#endif
