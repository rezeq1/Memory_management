#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

/*
Rezeq Abu Madeghem 211606801
Omar Hmdea 206635922
*/

typedef struct Page
{

  int id;
  int len;
  char data[MAX_LEN];
  int used;

} Page;



void Read_Input_File(char * input_file,char * output_file,Page ** main , int n ,Page ** sec, int m , int useLru);
void Init_Main_Memory(Page** pages , int size);
void Init_Secondary_Memory(Page** pages , int size);
void print(char * input_file,Page ** sec, int m ) ;
void print_main(Page ** main, int n ) ;
void write(Page ** main , int n ,Page ** sec, int m , int index , char letter, int useLru) ;
void read(Page ** main , int n ,Page ** sec, int m , int index , int useLru) ;
int Contain_Page ( Page ** pages , int size , int id);
int Last_Used_Page ( Page ** pages, int size);
int MemorySize(char * input_file);




