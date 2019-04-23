#ifndef SRC_VARIABLES_VARIABLES_H_
#define SRC_VARIABLES_VARIABLES_H_

/* Global Variables */
#define NUM_MAX 1024		//NUM of max
#define NUM_XY 4			//NUM of coordinates


/* File path variables */
#define HPS_SOURCE_PATH "/home/summer/disks/hdd2/FITS/HPS_DATA/" 	//cache file path
#define LPS_SOURCE_PATH "/home/summer/disks/hdd2/FITS/DATA/" 	    //source file path
#define HPS_TARGET_PATH "/home/summer/disks/hdd2/FITS/TargetFITS/" 	//target file path


/* Capacity variables */
#define BYTES_OF_FOLDER 4096		//folder size
#define CACHESIZE 1024*1024*20		//Cache Size(5GB)


/* Record variables */
#define REQUEST_RECORD_PATH "/home/summer/disks/hdd2/FITS/Sim_Result/Requests.csv"
#define RATE_RECORD_PATH "/home/summer/disks/hdd2/FITS/Sim_Result/Rate.csv"


/* Socket */
#define SERVER_PORT 9090
#define CACHE_PORT 9099


/* Access delay */
#define HPS_DELAY 25
#define LPS_DELAY 150


/* Servers */
#define SERVER_IP "127.0.0.1"


/* Pattern */
#define PATTERN ","


/* DB */
#define DB_HOST_NAME "localhost"		//NUM of Pthread
#define DB_USER_NAME "root"				//NUM of Pthread
#define DB_PASSWORD "1"					//NUM of Pthread
#define DB_DB_NAME "simulator"					//NUM of Pthread


#endif /* SRC_VARIABLES_VARIABLES_H_ */
