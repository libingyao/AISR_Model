/*
 * 
 * Created on: Apr 14, 2019
 * Author: Bingyao Li
 * Description:capacity.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "AllFunc.h"

int getCapacity(string path)
{

	const char *dir = path.c_str();

	int totalSize = BYTES_OF_FOLDER/1024;

	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if ((dp=opendir(dir)) == NULL)
	{
		fprintf(stderr, "Cannot open dir: %s\n", dir);
		exit(0);
	}
	chdir(dir);

	while((entry=readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(".", entry->d_name)==0 || strcmp("..", entry->d_name)==0)
				continue;

			totalSize +=statbuf.st_size/1024;
			getCapacity(entry->d_name);
		}
		else
			totalSize += statbuf.st_size/1024;
	}
	chdir("..");
	closedir(dp);

	cout<<"Current Capacity: "<<totalSize<<endl;

	return totalSize;

}


int getFileSize(string path)
{
	const char *filePath = path.c_str();

	FILE* fp = NULL;
	int fileLen = 0;

	fp = fopen(filePath, "rb");
	if(fp == NULL)
		return 0;

	fseek(fp,0,SEEK_END);
	fileLen = ftell(fp);

	return fileLen;
}

