#ifndef DATA_INPUT_HPP
#define DATA_INPUT_HPP

#include "heat_map.hpp"
#include "agg_pixfmt_rgb.h"
#include <string>
using namespace std;

using namespace std;
class DataInput {

  public:

	DataInput(){}
	~DataInput(){}

  	void input_data(HeatMap * map, pixfmt_rgb24 & pixf, int start, int end_row);

	void input_cells_in_row( HeatMap * map, string & next_line, string & delimiter,
				 DataCell & cell, int & x, int & y, int & pos,
				 pixfmt_rgb24 & pixf, bool in_loop, int & b );



};

#endif
