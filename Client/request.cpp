/*
 * 
 * Created on: Apr 15, 2019
 * Author: Bingyao Li
 * Description:request.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */


#include "AllFunc.h"



//Function:Split RequestString
vector<string> split(string str, string pattern)
{
	string::size_type pos;
	vector<string> result;
	str += pattern;
	int size = str.size();
	for(int i=0; i<size; i++)
	{
		pos = str.find(pattern,i);
		if(pos < size)
		{
			string s = str.substr(i, pos-i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

//FUNCTION: Request to String
string request2String(RequestInfo request, string pattern)
{

	stringstream strStream;
	strStream<<request.fileName<<pattern
			<<request.startx<<pattern<<request.starty<<pattern
			<<request.endx<<pattern<<request.endy<<pattern
			<<request.genTime<<pattern<<request.endTime<<pattern<<request.qos<<pattern;

	string reqStr = strStream.str();
	return reqStr;
}
