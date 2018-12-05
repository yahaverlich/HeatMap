#ifndef HEAT_MAP_HPP
#define HEAT_MAP_HPP
#include "agg_pixfmt_rgb.h"
#include "data_cell.hpp"
#include <vector>
#include <string>

using namespace agg;
using namespace std;

class HeatMap {
	
  private: 

	unsigned int frame_width;
	unsigned int frame_height;

	vector <string> data1;
	vector <string> data2;

	vector <DataCell *> data_cells;

  public:
	//HeatMap Default Constructor
	//--------------------------------------------------
	HeatMap();


	//HeatMap Constructor -- Set Frame Width/Height
	//--------------------------------------------------
	HeatMap(unsigned int x, unsigned int y);

	~HeatMap();



	// GETTERS
	//---------------------------------------------
	unsigned int getWidth() { return frame_width; }
	unsigned int getHeight() { return frame_height; }
	vector <string> & getData1() { return data1; }
	vector <string> & getData2() { return data2; }
	vector <DataCell *>  getDataCells() { return data_cells; }
// MAKE THIS RETURN A VECTOR OF DATA CELL *, AND ALSO CHANGE THE GLOBAL VECTOR VARIABLE

	// SETTERS
	//---------------------------------------------
	void setWidth( unsigned int x ) { frame_width = x; }
	void setHeight( unsigned int y ) { frame_height = y; }
	void setData1( vector<string> data ) { data1 = data; }
	void setData2( vector<string> data ) { data2 = data; }
	void setDataCells( vector<DataCell *> cells ) { data_cells = cells; }


	// Write the heat map (drawing) to a .ppm file
	//---------------------------------------------
	bool write_ppm(const unsigned char* buf, 
		       unsigned width, 
		       unsigned height, 
		       const char* file_name);


	// Input the data for the heat map, from a file
	//---------------------------------------------
	static bool input_data(vector<string> & data1, vector<string> & data2);


// Template Functions -- need to be implemented in this header file
//----------------------------------------------------------------

	// Draw the vertical lines for the heat map (table)
	//--------------------------------------------------
	template<class Ren>
	void draw_vertical_lines(Ren & ren)
	{
		unsigned x = 0; 
		rgba8 c(0,0,0);

		for(x; x <= ren.width() - 1; x += 3)
		{
			ren.copy_vline(x, 0, ren.height(), c);
		}

		ren.copy_vline(ren.width() - 1, 0, ren.height(), c);
	}

	// Draw the horizontal lines for the heat map (table)
	//--------------------------------------------------
	template<class Ren>
	void draw_horizontal_lines(Ren & ren)
	{
		unsigned y = 0;
		rgba8 c(0,0,0);

		for(y; y <= ren.height() - 1; y += 3)
		{
			ren.copy_hline(0, y, ren.width(), c);
		}

		ren.copy_hline(0, ren.height() - 1, ren.width(), c);
	}

};

#endif
