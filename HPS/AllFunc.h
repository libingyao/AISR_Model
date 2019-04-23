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
#include <mysql/mysql.h>
#include "fitsio.h"
#include <sstream>




#include "struct.h"
#include "variables.h"

using namespace std;

int comArea(int startx,int starty, int endx,int endy);
int comCrossArea(int oldStartx, int oldStarty,int oldEndx, int oldEndy, int newStartx, int newStarty, int newEndx, int newEndy);
bool fileNameHit(RequestInfo request);
bool areaHit(RequestInfo request);
IndexInfo merge(IndexInfo oldIndex, RequestInfo request);
bool searchInIndex(RequestInfo request);
string updateIndex(RequestInfo request);
void insertIntoIndex(RequestInfo request, int* mapxy);
void LRU(long currentTime);
void LRFU(long currentTime);
void LFU(long currentTime);
void Replacement();


int *mapXY(int startx, int starty, int endx, int endy);


void init_db();
int conn_db(const char *hostname, const char *username, const char *password, const char *dbname);
void disconn_db();
int open_db(const char *SQL);
int exec_db(const char *SQL);
int getCount(const char *SQL);
string getValue(const char *SQL);
int updateInfo(const char *SQL);
list<IndexInfo> getIndexList(const char *SQL);


int getCapacity(string path);
int getFileSize(string path);


vector<string> split(string str, string pattern);
string request2String(RequestInfo request, string pattern);
RequestInfo string2Request(string reqStr, string pattern);


void send(string ip, RequestInfo request, string pattern);



void removeFile(string fileName);
double extractFile2Cache(string filename, int sx, int sy, int ex, int ey);
#endif /* SRC_ALLFUNC_H_ */
