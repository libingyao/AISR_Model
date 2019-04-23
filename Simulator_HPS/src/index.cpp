/*
 * 
 * Created on: Apr 14, 2019
 * Author: Bingyao Li
 * Description:index.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "AllFunc.h"

//FUNCTION: Compute Area
int comArea(int startx,int starty, int endx,int endy)
{
	return (endx-startx)*(endy-starty);
}


//FUNCTION: Compute Cross Area
int comCrossArea(int oldStartx, int oldStarty, int oldEndx, int oldEndy, int newStartx, int newStarty, int newEndx, int newEndy)
{
	//not cross
	if(newEndx<oldStartx || newEndy<oldStarty || oldEndx<newStartx || oldEndy<newStarty)
	{
		return 0;
	}

	//cross
	int startx = newStartx>oldStartx ? newStartx : oldStartx;
	int starty = newStarty>oldStarty ? newStarty : oldStarty;
	int endx = newEndx<oldEndx ? newEndx : oldEndx;
	int endy = newEndy<oldEndy ? newEndy : oldEndy;

	return comArea(startx,starty,endx,endy);

}


//FUNCTION: Is File Name Hit or Not
bool fileNameHit(RequestInfo request)
{
	int count = 0;
	stringstream instrStream;
	instrStream<<"select count(*) from `index` where filename='"<<request.fileName<<"'";
	string sql = instrStream.str();
	count = getCount(sql.c_str());
	if(count>0)
	{
		return true;
	}
	return false;

}


//FUNCTION: Is Area Hit or Not
bool areaHit(RequestInfo request)
{
	int count = 0;

	stringstream instrStream;
	instrStream<<"select count(*) from `index` where filename='"<<request.fileName<<
			"' and start_x<="<<request.startx<<" and start_y<="<<request.starty<<
			" and end_x>="<<request.endx<<" and end_y>="<<request.endy;
	string sql = instrStream.str();
	count = getCount(sql.c_str());

	if(count>0)
	{
		return true;
	}
	return false;
}


//FUNCTION: Merge Two IndexInfo
IndexInfo merge(IndexInfo oldIndex, RequestInfo request)
{
	int * mapxy = mapXY(request.startx, request.starty, request.endx, request.endy);

	int newStartx = oldIndex.startx<mapxy[0] ? oldIndex.startx : mapxy[0];
	int newStarty = oldIndex.starty<mapxy[1] ? oldIndex.starty : mapxy[1];

	int newEndx = oldIndex.endx>mapxy[2] ? oldIndex.endx : mapxy[2];
	int newEndy = oldIndex.endy>mapxy[3] ? oldIndex.endy : mapxy[3];


	double newSize = 0;
	IndexInfo newIndex = {request.fileName, newStartx, newStarty, newEndx, newEndy,
			oldIndex.count, request.genTime, newSize, oldIndex.priority, ""};

	//Delete Index
	string sql = "delete from `index` where `sub_name` = '" + oldIndex.subName + "'";
	updateInfo(sql.c_str());

	//Delete File
	removeFile(oldIndex.subName);

	return newIndex;
}



//FUNCTION: Search In Index
bool searchInIndex(RequestInfo request)
{
	//file name hit
	if(!fileNameHit(request))
		return false;

	//area hit
	if(areaHit(request))
		return true;

	return false;
}

//FUNCTION: Update Index
string updateIndex(RequestInfo request)
{
	string subFitsName = "";

	stringstream instrStream;
	instrStream<<"select count(*) from `index` where filename='"<<request.fileName<<
			"' and start_x<="<<request.startx<<" and start_y<="<<request.starty <<
			" and end_x>="<<request.endx<<" and end_y>="<<request.endy;

	string sql = instrStream.str();

	subFitsName = getValue(sql.c_str());

	if(subFitsName != "")
	{
		stringstream instrStream;
		instrStream<<"update `index` set `count`=`count`+1, idle_time="<<
				request.genTime<<" where `sub_name`='"<<subFitsName<<"'";

		string sql = instrStream.str();
		cout<<sql<<endl<<endl;

		updateInfo(sql.c_str());
	}

	return subFitsName;
}



//FUNCTION: Insert Into Index
void insertIntoIndex(RequestInfo request, int* mapxy)
{
	stringstream outstrStream;
	outstrStream<<"_"<<mapxy[0]<<"_"<<mapxy[1]<<"_"<<mapxy[2]<<"_"<<mapxy[3]<<".fits";
	string tmpstr = outstrStream.str();
	string indexFileName = request.fileName + tmpstr;

	double size = getFileSize(HPS_SOURCE_PATH + indexFileName);

	IndexInfo newIndex = {request.fileName, mapxy[0], mapxy[1], mapxy[2], mapxy[3],
							1, request.genTime, size, 0.0, indexFileName};

	stringstream instrStream;
	instrStream<<"insert into `index`(`filename`,`start_x`, `start_y`, `end_x`, `end_y`, `count`, `idle_time`, `size`, `priority`, `sub_name`) values('"
				<<newIndex.fileName<<"',"<<newIndex.startx<<","<<newIndex.starty<<
				","<<newIndex.endx<<","<<newIndex.endy<<","<<newIndex.count<<","<<newIndex.idleTime<<
				","<<newIndex.size<<","<<newIndex.priority<<",'"<<newIndex.subName<<"')";

	string sql = instrStream.str();

	updateInfo(sql.c_str());
}


//FUNCTION: LRU replacement algorithm
void LRU(long currentTime)
{
	stringstream instrStream;
	instrStream<<"update `index` set `priority`= 100000/("<<currentTime<<"- `idle_time` + 1)";
	string sql = instrStream.str();
	//update all priority
	updateInfo(sql.c_str());
}


//FUNCTION: LRFU replacement algorithm
void LRFU(long currentTime)
{
	stringstream instrStream;
	instrStream<<"update `index` set `priority`= 100 * `count`/("<<currentTime<<"- `idle_time`+1)";
	string sql = instrStream.str();
	//update all priority
	updateInfo(sql.c_str());

}


//FUNCTION: LFU replacement algorithm
void LFU(long currentTime)
{
	stringstream instrStream;
	instrStream<<"update `index` set `priority`= `count`";
	string sql = instrStream.str();
	//update all priority
	updateInfo(sql.c_str());
}




