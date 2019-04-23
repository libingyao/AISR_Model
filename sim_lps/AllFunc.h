/*
 * 
 * Created on: Apr 14, 2019
 * Author: Bingyao Li
 * Description:AllFunc.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#ifndef SRC_ALLFUNC_H_
#define SRC_ALLFUNC_H_

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <list>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <vector>
#include "mysql.h"
#include "fitsio.h"
#include <sstream>
#include <fstream>




#include "struct.h"
#include "variables.h"

using namespace std;

bool searchInIndex(RequestInfo request);
string updateIndex(RequestInfo request);
void insertIntoIndex(RequestInfo request, int* mapxy);
void LRU(long currentTime);
void LFU(long currentTime);
void LRFU(long currentTime);

void init_db();
int conn_db(const char *hostname, const char *username, const char *password, const char *dbname);
void disconn_db();
int open_db(const char *SQL);
string getValue(const char *SQL);
int getCount(const char *SQL);
int updateInfo(const char *SQL);


int getCapacity(string path);
int getFileSize(string path);


vector<string> split(string str, string pattern);
string request2String(RequestInfo request, string pattern);
RequestInfo string2Request(string reqStr, string pattern);


double response(string filename, int sx, int sy, int ex, int ey, int x0, int y0, string path);


void record(list<RequestInfo> requestsList);
void recordRate(string hitRate);

#endif /* SRC_ALLFUNC_H_ */
