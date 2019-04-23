/*
 * 
 * Created on: Apr 15, 2019
 * Author: Bingyao Li
 * Description:main.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */


#include "AllFunc.h"


int random(int x)
{
	return (rand()%x);
}

void initFiles(FileInfo *files)
{
	srand((int)time(0));
	for(int i=0; i<NUM_FILES; i++)
	{
        files[i].filename = i;
        files[i].hot = 1 + random(NUM_HOT);
        files[i].type = 1 + random(NUM_TYPE);
        files[i].hotzone = 1 + random(NUM_HOT_ZONE);
        files[i].reqcounts = 0;
        files[i].idletime =0;
    }
}




void readCSV(string filePath, list<RequestInfo> *requestsList)
{
	ifstream infile(filePath.c_str());
	string tmp;
	while(getline(infile,tmp))
	{
		vector<string> info = split(tmp, ",");
		RequestInfo request = {info[0], atoi(info[1].c_str()), atoi(info[2].c_str()), atoi(info[3].c_str()),
						atoi(info[4].c_str()), atoi(info[5].c_str()), atoi(info[6].c_str()), atof(info[7].c_str()), atoi(info[8].c_str())};
		(*requestsList).push_back(request);
	}
}


void genReqFromTrack(list<RequestInfo> *requestsList)
{
	readCSV(TRACK_PATH, requestsList);
}

void send(string ip, RequestInfo request, string pattern);
void reqEOF();

int main(){

	cout << "==========>>>>> START TO RUN <<<<<==========\n" << endl;

	cout << "==========>>>>>  INIT FILES  <<<<<==========\n" << endl;

	//files
	FileInfo files[NUM_FILES];

	//generate files
	initFiles(files);


	cout << "==========>>>>> GENERATE REQUESTS <<<<<==========\n" << endl;

	//store all the request
	list<RequestInfo> requestsList;

	//store all the request result
	list<RequestInfo> resultList;

	//requests' list's iterator
	list<RequestInfo>::iterator reqIter;

	//generate requests
//	genRequests(files, &requestsList);

	//generate requests from track
	genReqFromTrack(&requestsList);

	if(requestsList.size()>0)
		cout << "==========>>>>> REQUESTS' NUM: " << requestsList.size() << " <<<<<==========\n" << endl;

	cout << "==========>>>>> START TO SERVE <<<<<==========\n" << endl;

	string serverIp = SERVER_IP;
	//服务器IP
	int i = 0;									//计数
	for(reqIter=requestsList.begin(); reqIter!=requestsList.end(); reqIter++)
	{
		sleep((*reqIter).idle);					//等待开始
		struct timeval tv;
	    gettimeofday(&tv, NULL);
	    //long timeuse = tv.tv_sec*1000 + tv.tv_usec/1000;
	    long timeuse = tv.tv_sec * 1000;
	    //request count
	    cout<<"Req:"<<i++<<"  Time:"<<timeuse<<endl;

	    (*reqIter).genTime = timeuse;
	    cout<<(*reqIter).fileName<<","<<(*reqIter).startx<<","<<(*reqIter).starty<<","<<(*reqIter).endx<<","<<(*reqIter).endy<<endl;
		send(serverIp, *reqIter, PATTERN);		//发送到服务器
	}

	//EOF
	reqEOF();

}
