#ifndef SRC_VARIABLES_VARIABLES_H_
#define SRC_VARIABLES_VARIABLES_H_

/* Global Variables */
#define NUM_MAX 1024		//NUM of max
#define NUM_XY 4			//NUM of coordinates


/* Index variables */
#define AREA_THRESHOLD 0.50		//Threshold of cross area


/* File path variables */
#define HPS_SOURCE_PATH "/home/summer/disks/hdd2/FITS/HPS_DATA/" 	//cache file path
#define LPS_SOURCE_PATH "/home/summer/disks/hdd2/FITS/DATA/" 	    //source file path
#define HPS_TARGET_PATH "/home/summer/disks/hdd2/FITS/TargetFITS/" 	//target file path


/* Capacity variables */
#define BYTES_OF_FOLDER 4096		//folder size
//#define CACHESIZE 1024*1024*20		//Cache Size(5GB)
#define CACHESIZE 575800

/* File variables */
#define NUM_FILES 300		//NUM of files
#define NUM_HOT 10			//NUM of hot file
#define NUM_TYPE 4			//NUM of file type
#define NUM_HOT_ZONE 4		//NUM of hot zones of file
#define SIZE_ZONE 1000		//Size of zone X*X


/* fits map variables */
#define ACCURACY 5				//map division accuracy


/* Shell Path */
#define SHELL_PATH "bash /home/summer/lbyproject/shell/RemoveFile.sh /home/summer/disks/hdd2/FITS/HPS_DATA/"


/* Socket */
#define PORT 9099


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
