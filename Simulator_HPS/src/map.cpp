/*
 * 
 * Created on: Apr 14, 2019
 * Author: BingYao Li
 * Description:map.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "variables.h"


//FUNCTION: Map coordinates by accuracy
int * mapXY(int startx, int starty, int endx, int endy)
{
	int *xy;
	xy = new int[NUM_XY];

	//size of scale
	int scale = SIZE_ZONE/ACCURACY;

	//Lower
	xy[0] = (startx/scale)*scale;
	xy[1] = (starty/scale)*scale;

	if(xy[0] == 0)
		xy[0] = 1;

	if(xy[1] == 0)
		xy[1] = 1;

	//Upper
	if(endx%scale)
		xy[2] = (endx/scale + 1)*scale;
	else
		xy[2] = (endx/scale)*scale;

	if(endy%scale)
		xy[3] = (endy/scale + 1)*scale;
	else
		xy[3] = (endy/scale)*scale;

	return xy;
}




