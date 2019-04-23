/*
 * 
 * Created on: Apr 14, 2019
 * Author: Bingyao Li
 * Description:replacement.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */


#include "AllFunc.h"


//FUNCTION: delete index and file
void Replacement()
{
	//get min
	stringstream instrStream;
	instrStream<<"select `sub_name` from `index` where `priority`= (select min(priority) from `index`)";
	string sql = instrStream.str();
	string subName = getValue(sql.c_str());
	//Delete Index
	sql = "delete from `index` where `sub_name` = '" + subName + "'";
	updateInfo(sql.c_str());
	//Delete File
	removeFile(subName);
}


//FUNCTION: removeFile
void removeFile(string fileName)
{
    string rfileName = SHELL_PATH + fileName;
    char buffer[1024];
    strcpy(buffer, rfileName.c_str());
    printf("%s\n", buffer);
    system(buffer);
}


//FUNCTION: extractFile2Cache
double extractFile2Cache(string filename, int sx, int sy, int ex, int ey)
{
    fitsfile *infptr, *outfptr;
    int status = 0;

    struct timeval start, end;
    double duration;

    gettimeofday(&start, NULL);

    stringstream instrStream;
    instrStream<<".fits["<<sx<<":"<<ex<<","<<sy<<":"<<ey<<"]";
    string s1 = instrStream.str();
    string infilename = LPS_SOURCE_PATH + filename + s1;

    if(!fits_open_file(&infptr, infilename.c_str(), READONLY, &status))
    {
        stringstream outstrStream;
        outstrStream<<"_"<<sx<<"_"<<sy<<"_"<<ex<<"_"<<ey<<".fits";
        string s2 = outstrStream.str();
        string outfilename = HPS_SOURCE_PATH + filename + s2;

        if(!fits_create_file(&outfptr, outfilename.c_str(), &status))
        {
            fits_copy_file(infptr, outfptr, 1, 1, 1, &status);
            fits_close_file(outfptr, &status);
        }
        fits_close_file(infptr, &status);
    }

    gettimeofday(&end, NULL);
    duration = (end.tv_sec - start.tv_sec)*1000;
    return duration;
}


