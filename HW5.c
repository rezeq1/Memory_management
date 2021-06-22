#include "header.h"

/*
Rezeq Abu Madeghem 211606801
Omar Hmdea 206635922
*/

int Last_used=0;

int main(int argc,char* argv[])
{

char input_file[MAX_LEN],output_file[MAX_LEN];
Page **main , **sec;
int m,n,useLru;

useLru=atoi(argv[1]);
m=atoi(argv[4]);
n=atoi(argv[5]);
strcpy(input_file,argv[2]);
strcpy(output_file,argv[3]);


m=MemorySize(input_file)+1;

main= (Page **) malloc(sizeof(Page *)*n);
sec = (Page **) malloc(sizeof(Page *)*m);     

Init_Secondary_Memory(sec,m);     
Init_Main_Memory(main,n);


Read_Input_File(input_file,output_file,main,n,sec,m,useLru);

for(int i=0 ; i<n ; i++)
    free(main[i]);
    
for(int i=0 ; i<m ; i++)
    free(sec[i]);
    
free(main);
free(sec);

}


void Init_Secondary_Memory(Page** sec , int size)
{
     for(int i=0 ; i<size; i++)
     {
        sec[i]= (Page *) malloc(sizeof(Page));
        sec[i]->id = i ;
        sec[i]->len = 0 ;
        sec[i]->used = -1 ;
     }

}
void Init_Main_Memory(Page** main , int size)
{

     for(int i=0 ; i<size; i++)
     {
        main[i]= (Page *) malloc(sizeof(Page));
        main[i]->id = i ;
        main[i]->len = 0 ;
        main[i]->used = -1 ;
     }
}

void Read_Input_File(char * input_file,char * output_file,Page ** main , int n ,Page ** sec, int m , int useLru )
{

	 FILE *fileInput;
	 char letter,action[6];
	 int page_id;


	 fileInput=fopen(input_file,"r");

	 if(fileInput==NULL)
	 {
	      printf(" unable to open input file \n");
	      exit(1);
	 }
	 
	 while (!feof(fileInput))
	 {
	      fscanf(fileInput, "%s",action);
	      if(strcmp(action,"write") == 0)
	      {
	         fscanf(fileInput, "%d %c ",&page_id,&letter);
	         write(main , n ,sec, m ,page_id , letter,useLru); 
              }
	      else if (strcmp(action,"read") == 0)
	      {
	         fscanf(fileInput, "%d",&page_id);
	         read(main , n ,sec, m ,page_id,useLru); 
	      } 
	      else if (strcmp(action,"print") == 0)
	      {
	         print(output_file,sec,m);
	      }
	      else
	      {
	         break;
	      }
	         

	 }
	fclose(fileInput);
}
 
void print(char * file_name,Page ** sec, int m ) 
{
    FILE *fileOuput;

    fileOuput=fopen(file_name,"a+");

    if(fileOuput==NULL) 
    {
        printf(" unable to open output file \n");
        exit(1);
    }
 
    fprintf(fileOuput,"secondaryMemory=[");
    
    for (int i=0 ; i<m-1 ; i++ )
        fprintf(fileOuput,"%s,",sec[i]->data);   
    
    fprintf(fileOuput,"%s]\n",sec[m-1]->data);
    
    fclose(fileOuput);
	

} 
void write(Page ** main , int n ,Page ** sec, int m , int index , char letter , int useLru) 
{
    int indx,id=0;
    
    if ( Contain_Page(main,n,index) == -1 )
    {
	if(useLru == 1)
	   id=Last_Used_Page(main,n);


        indx=main[id]->id;
    	sec[indx]->len = main[id]->len ; 
    	sec[indx]->used = main[id]->used ; 
    	
    	for ( int i=0 ; i < main[id]->len ;i++)
    	    sec[indx]->data[i]=main[id]->data[i];
    	
    	if(useLru == 0)
    	{
	    	for ( int i=0 ; i < n-1 ;i++)
	    	{
	    	    main[i]->id=main[i+1]->id;
	    	    main[i]->len=main[i+1]->len;
	    	    main[i]->used=main[i+1]->used;
	    	    for ( int k=0 ; k < main[i+1]->len ;k++)
	    	         main[i]->data[k]=main[i+1]->data[k];
	    	}
	
		main[n-1]->len=sec[index]->len;
	    	main[n-1]->id = sec[index]->id;
	    	main[n-1]->used = sec[index]->used;
    	
	    	for ( int i=0 ; i < sec[index]->len ;i++)
	    	    main[n-1]->data[i]=sec[index]->data[i];
	}
	else
	{
		main[id]->len=sec[index]->len;
	    	main[id]->id = sec[index]->id;
	    	main[id]->used = sec[index]->used;
    	
	    	for ( int i=0 ; i < sec[index]->len ;i++)
	    	    main[id]->data[i]=sec[index]->data[i];
	
	}
    }
    
    indx = Contain_Page(main,n,index) ;
    main[indx]->data[main[indx]->len] = letter;
    main[indx]->len = main[indx]->len +1 ;
    main[indx]->used = Last_used ;
    Last_used++;


}

 
void read(Page ** main , int n ,Page ** sec, int m , int index ,int useLru) 
{
    int indx,id=0;
    
    if ( Contain_Page(main,n,index) == -1 )
    {
	if(useLru == 1)
	   id=Last_Used_Page(main,n);

        indx=main[id]->id;
    	sec[indx]->len = main[id]->len ; 
    	sec[indx]->used = main[id]->used ; 
    	
    	for ( int i=0 ; i < main[id]->len ;i++)
    	    sec[indx]->data[i]=main[id]->data[i];
    	
    	if(useLru == 0)
    	{
	    	for ( int i=0 ; i < n-1 ;i++)
	    	{
	    	    main[i]->id=main[i+1]->id;
	    	    main[i]->len=main[i+1]->len;
	    	    main[i]->used=main[i+1]->used;
	    	    for ( int k=0 ; k < main[i+1]->len ;k++)
	    	         main[i]->data[k]=main[i+1]->data[k];
	    	}
	
		main[n-1]->len=sec[index]->len;
	    	main[n-1]->id = sec[index]->id;
	    	main[n-1]->used = sec[index]->used;
    	
	    	for ( int i=0 ; i < sec[index]->len ;i++)
	    	    main[n-1]->data[i]=sec[index]->data[i];
	}
	else
	{
		main[id]->len=sec[index]->len;
	    	main[id]->id = sec[index]->id;
	    	main[id]->used = sec[index]->used;
    	
	    	for ( int i=0 ; i < sec[index]->len ;i++)
	    	    main[id]->data[i]=sec[index]->data[i];
	
	}
    }
    
    indx = Contain_Page(main,n,index) ;
    main[indx]->used = Last_used ;
    Last_used++;
    printf("%s\n",main[indx]->data);

}

int Contain_Page ( Page ** pages , int size , int id)
{

    for ( int i=0 ; i<size ; i++ )
        if ( pages[i]->id == id ) 
              return i ;
    return -1;

} 

int Last_Used_Page ( Page ** pages , int size)
{

  int location=0;
  for(int i=0 ; i<size ; i++)
      if(pages[i]->used>-1)
      {
         location=i;
         break;
      }
  if(pages[location]->used == -1 )
      return location ;
  
  for (int c = 0; c < size; c++)
  {
    if(pages[c]->used > -1 )
       if (pages[c]->used < pages[location]->used)
          location = c;
  }
  return location;
}

 int MemorySize(char * input_file)
 {
 
 	 FILE *fileInput;
 	 char letter,action[6];
         int count=0,page_id;


	 fileInput=fopen(input_file,"r");

	 if(fileInput==NULL)
	 {
	      printf(" unable to open input file \n");
	      exit(1);
	 }
	 
	 while (!feof(fileInput))
	 {
	      fscanf(fileInput, "%s",action);
	      if(strcmp(action,"write") == 0)
	      {
	         fscanf(fileInput, "%d %c ",&page_id,&letter);
	         if(page_id > count)
	             count=page_id;
              }
	      else if (strcmp(action,"read") == 0)
	      {
	         fscanf(fileInput, "%d",&page_id);
	         if(page_id > count)
	             count=page_id;
	      } 
	      else if (strcmp(action,"print") != 0)
	      {
	         break;
	      }

	 }
	fclose(fileInput);
	return count;
 
 }





 
 
