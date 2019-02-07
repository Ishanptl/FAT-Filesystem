#ifndef MYDISK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

//defined constants
//#define BLOCKS 4096 //number of blocks
//#define BLOCK_SIZE 512 //size of each block
//#define MAX_ENTRIES 8 //number of entries per block
//#define BLOCKS 4096 //number of blocks
#define BLOCKS 1024
//Files can be up to 32768 characters
#define BLOCK_SIZE 512 //size of each block
#define MAX_ENTRIES 8 //number of entries per block
//this is each individual entry in the file allocation table
/*typedef struct fileAllocationEntry{
    short busy;
    short next; 
} fileEntry;*/
struct fileEntry{
    short busy;
    short next; 
};

//FAT struct
/*typedef struct fileAllocationTable{
    fileEntry file[BLOCKS]; //there are BLOCKS number of fileEntry in the FAT
} FAT;*/
typedef struct fileAllocationTable{
    struct fileEntry file[BLOCKS]; //there are BLOCKS number of fileEntry in the FAT
} FAT;
//Each entry in directory entry table structure
//each entry is 64 bytes long
typedef struct entry{
    unsigned short fileSize; //2 bytes
    unsigned short startingIndex; //2 bytes
    char folder; //1 byte
    char last_modified_time[9]; //9 bytes (8 time + terminator)
    char last_modified_date[9]; //9 bytes; (8 time + terminator)
    char time[9]; //9 bytes (8 time + terminator)
    char date[9]; //9 bytes; (8 time + terminator)
    char filename[19]; //37 bytes (36 filename + terminator)
    char extension[4]; //4 bytes (3 extension + terminator)
} Entry;

//Directory Entry Table that occupies a 512 byte data block
//since each entry is 64 bytes long,
//each data block or directory table can hold 8 entries
//64 * 8 = 512;
typedef struct directoryTable{
    Entry entry[MAX_ENTRIES];
} directory;

//this is individual block
/*typedef struct sector{
    char sect[BLOCK_SIZE];
} Sector;*/

struct Sector{
    char sect[BLOCK_SIZE];
};
//this is collection of all data blocks
typedef struct dataBlock{
    struct Sector blocks[BLOCKS];
} DATA;

//function prototypes
void update_modified_date(char *dateString);
void update_modified_time(char *timeString);
void initialize_root(FAT *fat, Entry *root);
void editFileSize(unsigned short * oldSize, unsigned short newSize);
void editIndex(unsigned short *oldIndex, unsigned short newIndex);
void editFolder(char *oldFolder, char newFolder);
void update_extension(char * oldExtension, char * newExtension);
void editFilename(char * oldFilename, char * newFilename);
short nextFreeBlock(FAT * fat);
short nextFreeEntry(directory *dir);
void create_file(FAT * fat, DATA * data, char * filename, char * ext);
void create_directory(FAT * fat, DATA * data, char * filename);
void write_file(FAT * fat, DATA * data, char * filename, char * ext, char * buf);
int findFileOffset(FAT * fat, DATA * data, directory * dir, int file);
int findFileEntry(directory * dir, char * filename, char * ext);
void delete_file(FAT * fat, DATA * data, char * filename, char * ext);
void read_file(FAT * fat, DATA * data, char * filename, char * ext);
int isEmpty();
int isFull();
int peek();
int pop();
void push(int dirBlock);
int change_directory(DATA * data, char * dirName);

//current directory stack
int directory_stack[BLOCKS];
int top = 0; 

#endif

