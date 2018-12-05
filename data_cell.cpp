#include "data_cell.hpp"


	//HeatMap Default Constructor
	//--------------------------------------------------
	DataCell::DataCell() 
	{
		setData1Elem("");
		setData2Elem("");
		setXCoord(0);
		setYCoord(0);
		setDataVal(0);
		setR(0); setG(0); setB(0);
	}

	//HeatMap Constructor -- Set Member Variables
	//--------------------------------------------------
	DataCell::DataCell( string data1, string data2, int x, int y,
	 	  double val, int r, int g, int b ) 
	{
		setData1Elem( data1 );
		setData2Elem( data2 );
		setXCoord( x );
		setYCoord( y );
		setDataVal( val );
		setR( r );
		setG( g );
		setB( b );
	}

	//DATA CELL DESTRUCTOR
	DataCell::~DataCell(){}
