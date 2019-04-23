/*
 * 
 * Created on: Apr 14, 2019
 * Author: Bingyao Li
 * Description:struct.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#ifndef SRC_STRUCT_H_
#define SRC_STRUCT_H_


#include <string>
#include <stdlib.h>
using namespace std;


/* Basic Struct of File Information */
struct FileInfo {
    int filename;
    int hot;		//Random Number of 1 to 10, 1&2 represent popular file
    int type;		//Random Number of 1 to 4, 1 represents hot | 2&3 represent average | 4 represents cold
    int hotzone;	//Random Number of 1 to 4, Each number represents a different center position of the hot zone
    int reqcounts;	//The times of file requested
    int idletime;	//From the time of the last requested
};


/* Basic Struct of Request Information */
struct RequestInfo{
	string fileName;	//The file name is requested
	int startx;			//Start coordinates
	int starty;
	int endx;			//End coordinates
	int endy;

	long genTime;		//Request's generation time
	long endTime;		//Request's response time
	double qos;			//quality of service, equals endTime - genTime

	// FUNCTION: Operator < Overloading
	bool operator < (RequestInfo & b) {
		return genTime < b.genTime;
	}
};


/* Basic Struct of Index Information */
struct IndexInfo{
	string fileName;	//File name in index
	int startx;			//Start coordinates
	int starty;
	int endx;			//End coordinates
	int endy;

	int count;			//Access times
	long idleTime;		//From the time of the last requested
	double size;

	double priority;	//Priority of file

	string subName;


	//FUNCTION: Operator < Overloading
	bool operator < (IndexInfo & b) {
		return priority < b.priority;
	}

	//FUNCTION: Operator == Overloading
	bool operator == (IndexInfo & b) {
		if(fileName==b.fileName && startx==b.startx && starty==b.starty && endx==b.endx && endy==b.endy &&
				count==b.count && idleTime==b.idleTime && size==b.size && priority==b.priority)
			return true;

		return false;
	}
};



#endif /* SRC_STRUCT_H_ */
