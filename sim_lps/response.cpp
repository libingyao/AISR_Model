/*
 * 
 * Created on: Apr 15, 2019
 * Author: Bingyao Li
 * Description:response.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "AllFunc.h"

//FUNCTION: response to user
double response(string filename, int sx, int sy, int ex, int ey, int x0, int y0, string path)
{
	cout<<"-----------Response to user----------"<<endl;
    fitsfile *infptr, *outfptr;
    int status = 0;

    struct timeval start, end;
    double duration;

    int newsx = (sx-x0) ? (sx-x0) : 1;
    int newex = (ex-x0) ? (ex-x0) : 1;
    int newsy = (sy-y0) ? (sy-y0) : 1;
    int newey = (ey-y0) ? (ey-y0) : 1;


    gettimeofday(&start, NULL);

    stringstream instrStream;
    instrStream<<"["<<newsx<<":"<<newex<<","<<newsy<<":"<<newey<<"]";
    string s1 = instrStream.str();
    string infilename = path + filename + s1;

    //cout<<infilename<<endl;

    if(!fits_open_file(&infptr, infilename.c_str(), READONLY, &status)){
        stringstream outstrStream;
        outstrStream<<"_"<<sx<<"_"<<sy<<"_"<<ex<<"_"<<ey<<".fits";
        string s2 = outstrStream.str();
        string outfilename = HPS_TARGET_PATH + filename + s2;

        //cout<<outfilename<<endl;

        if(!fits_create_file(&outfptr, outfilename.c_str(), &status)){
            fits_copy_file(infptr, outfptr, 1, 1, 1, &status);
            fits_close_file(outfptr, &status);
        }
        fits_close_file(infptr, &status);
    }

    gettimeofday(&end, NULL);
    duration = (end.tv_sec - start.tv_sec)*1000 ;
    cout<<"--------------Complete--------------"<<endl;
    return duration;

}
