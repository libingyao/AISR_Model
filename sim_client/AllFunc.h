/*
 * 
 * Created on: Apr 15, 2019
 * Author: Bingyao Li
 * Description:AllFunc.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */



#include <iostream>
#include <sys/time.h>
#include <list>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include "mysql.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include "variables.h"
#include "struct.h"
using namespace std;


vector<string> split(string str, string pattern);
string request2String(RequestInfo request, string pattern);


void send(string ip, RequestInfo request, string pattern);
void reqEOF();
