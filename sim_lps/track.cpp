/*
 * 
 * Created on: Apr 15, 2019
 * Author: Bingyao Li
 * Description:track.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "AllFunc.h"


void writeCSV(string filePath, list<RequestInfo> requestsList)
{
	ofstream outfile(filePath.c_str());
	//requests' list's iterator
	list<RequestInfo>::iterator reqIter;

	for(reqIter=requestsList.begin(); reqIter!=requestsList.end(); reqIter++)
	{
		outfile<<(*reqIter).fileName<<","<<(*reqIter).startx<<","<<(*reqIter).starty
				<<","<<(*reqIter).endx<<","<<(*reqIter).endy<<","<<(*reqIter).genTime
				<<","<<(*reqIter).endTime<<","<<(*reqIter).qos<<","<<(*reqIter).hit<<'\n';
	}
	 outfile.flush();
	 outfile.close();
}


void writeCSV(string filePath, string record)
{
	ofstream outfile(filePath.c_str());
	outfile<<record<<'\n';
	outfile.flush();
	outfile.close();
}


void readCSV(string filePath, list<RequestInfo> *requestsList)
{
	ifstream infile(filePath.c_str());
	string tmp;
	while(getline(infile,tmp))
	{
		vector<string> info = split(tmp, ",");
		RequestInfo request = {info[0], atoi(info[1].c_str()), atoi(info[2].c_str()), atoi(info[3].c_str()),
				atoi(info[4].c_str()), atoi(info[5].c_str()), 0, 0};
		(*requestsList).push_back(request);
	}
}



//FUNCTION: record
void record(list<RequestInfo> requestsList)
{
	writeCSV(REQUEST_RECORD_PATH, requestsList);

}


//FUNCTION: recordRate
void recordRate(string hitRate)
{
	writeCSV(RATE_RECORD_PATH, hitRate);
}
