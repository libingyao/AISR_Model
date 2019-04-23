/*
 * 
 * Created on: Apr 15, 2019
 * Author: Bingyao Li
 * Description:main.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */


#include <iostream>
#include <map>
#include <list>
#include "variables.h"
#include "AllFunc.h"
using namespace std;


int CACHE_HIT = 0;
double TOTAL_QOS = 0;



//FUNCTION: send message to server
void send(string ip, RequestInfo request, string pattern)
{
	struct sockaddr_in s_in;
	int s_fd;

	memset((void *)&s_in,0,sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(CACHE_PORT);
	inet_pton(AF_INET, ip.c_str(), (void *)&s_in.sin_addr);
	s_fd = socket(AF_INET,SOCK_STREAM,0);
	connect(s_fd,(struct sockaddr *)&s_in,sizeof(s_in));
	string reqStr = request2String(request, pattern);
	write(s_fd, reqStr.c_str(), reqStr.size());
	close(s_fd);
}



int main()
{
	cout << "==========>>>>> START TO SERVE <<<<<==========\n" << endl;

	//store all the request result
	list<RequestInfo> resultList;

	//初始化数据库
	init_db();
	//连接到数据库
	if (conn_db(DB_HOST_NAME, DB_USER_NAME, DB_PASSWORD, DB_DB_NAME) != 0)
		return -1;								//连接数据库失败，函数退出


	struct sockaddr_in s_in;					//server address structure
	struct sockaddr_in c_in;					//client address structure
	int l_fd,c_fd;
	socklen_t len;
	char buf[NUM_MAX];							//content buff area

	memset((void *)&s_in, 0, sizeof(s_in));

	s_in.sin_family = AF_INET;					//IPV4 communication domain
	s_in.sin_addr.s_addr = INADDR_ANY;			//accept any address
	s_in.sin_port = htons(SERVER_PORT);			//change port to netchar

	l_fd = socket(AF_INET, SOCK_STREAM, 0);		//socket(int domain, int type, int protocol)

	bind(l_fd, (struct sockaddr *)&s_in, sizeof(s_in));

	listen(l_fd, NUM_MAX);						//lisiening start

	//serve
	double qos = 0.0;
	int delay = 0;

	string serverIp = SERVER_IP;				//服务器IP

	string path = "";
	struct timeval start, cur, end;

	while(1)
	{
		c_fd = accept(l_fd,(struct sockaddr *)&c_in,&len);
		memset(&buf,0,sizeof(buf));
		read(c_fd, buf, NUM_MAX);				//read the message send by client
		string reqStr(buf);

		if(reqStr == "EOF")
			break;


		RequestInfo request = string2Request(reqStr, PATTERN);

		//cout << "Request gentime: "<< request.genTime <<endl;
		gettimeofday(&start, NULL);				//start to serve
		qos = 0.0;
		//file name: Full | Sub
		string subFitsName = "";

		if(searchInIndex(request))
		{
			//hit in cache perfectly
			cout<<"---------------Hit---------------"<<endl;
			subFitsName = updateIndex(request);

			//Update priority
			gettimeofday(&cur, NULL);
			long currentTime = cur.tv_sec * 1000;
			//LRU(currentTime);
			//LFU(currentTime);
			LRFU(currentTime);

			path = HPS_SOURCE_PATH;
			request.hit = 1;
			CACHE_HIT++;
			delay = HPS_DELAY;
		}
		else
		{
			//not hit
			cout<<"---------------Not Hit---------------"<<endl;
			send(serverIp, request, PATTERN);	//发送到缓存服务器
			path = LPS_SOURCE_PATH;
			subFitsName = request.fileName + ".fits";
			delay = LPS_DELAY;
		}

		int x0=0, y0=0; 						//sub fits (0, 0)
		vector<string> result = split(subFitsName, "_");

		if(result.size() > 2) {
			x0 = atoi(result[1].c_str());
			y0 = atoi(result[2].c_str());
		}


		//response to user
		response(subFitsName, request.startx, request.starty,
					request.endx, request.endy, x0, y0, path);

	    gettimeofday(&end, NULL);				//end of request
	    //long timeuse = end.tv_sec*1000 + end.tv_usec/1000;
	    long timeuse = end.tv_sec * 1000 + delay;
	    request.endTime = timeuse;

	    //服务时间
	    //qos = (end.tv_sec-start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
	    qos = timeuse - request.genTime;

	    request.qos = qos;
		//store result to new list
		resultList.push_back(request);
        cout<<"Response time: "<<qos<<endl;
		TOTAL_QOS += qos;

		close(c_fd);
	}


	cout<<"HitTimes:"<<CACHE_HIT<<"    HITRATE:"<<((double)CACHE_HIT/(double)resultList.size())<<endl;
	cout<<"TOTAL_QOS:"<<TOTAL_QOS<<"ms"<<"    AVGRAGE_QOS:"<<(TOTAL_QOS/(double)resultList.size())<<"ms"<<endl;

	stringstream hitRate;
	hitRate<<"RequestSize,HitTimes,HitRate,TotalQos,AvgrageQos\n"<<resultList.size()<<","
				<<CACHE_HIT<<","<<((double)CACHE_HIT/(double)resultList.size())<<","
				<<TOTAL_QOS<<","<<(TOTAL_QOS/(double)resultList.size())<<"\n";

	//record hitRate
	recordRate(hitRate.str());

	//Record resultList
	record(resultList);

}
