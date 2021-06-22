# Memory management-

The program implements a system that simulates a system for virtual memory management.
![1](https://user-images.githubusercontent.com/57844508/122911209-b9f30f00-d35f-11eb-9cc4-d3ee0e46692e.png)


In such like this system it is assumed that the amount of data the program needs while running is very large
and it is not possible to copy them all to the main memory. But the processor knows to use the data or execute instructions
only if they are in the main memory.

How do you overcome the problem?
Divide the data into m blocks of a fixed size called pages (for example 4K size) and at any given moment make sure that 
the pages necessary for carrying out the current instruction of the program are in the main memory.

All pages are saved in secondary memory. In contrast, the main memory can only hold n pages at any given time.
Note: m >> n.

When the program wants to turn to a particular page, in order to read from it or write to it, the page should be in the main memory.
Therefore before accessing the page we check if it is in the main memory. If it is not found it is retrieved from the secondary memory.

In this program we assume that each page in the secondary memory has a unique index , an index from 0 to m-1 , and access to the page is done using its key.

From the moment a page is uploaded to the main memory, its content changes only in the main memory.
Only as soon as a page comes out of the main memory will we update it in the secondary memory as well.

## System components:
• Secondary memory:
  We represent pages in the secondary memory by an array A of size m of strings.
  Each cell in the array represents a page in memory, where A[i] saves the contents of the page whose key is i.

• Main memory:
  We will represent the pages in the main memory using a n-length queue.
  
## Queue management and page swap strategies :
Because the main memory is limited in the number of pages, when a new page is brought from the secondary memory to the main
if there is no free space, it should be replaced with another page in the main memory. In this program two strategies are implemented .

For page swaps:

• FIFO (First In First Out): Replaces the oldest page.

• LRU (Least Recently Used): Replaces the page that has the reference time (Read or Write)
the last to it is the farthest (oldest) of all the pages in memory.

## System initialization :
Secondary memory: We initialize all the cells of an array in the secondary memory in empty strings.

Main memory: Lock the first n pages from the secondary memory to the main memory in order ( A[0] ... A[n-1] ) .

## Supported actions : 

1) read(index) - The action returns the content of the page whose index is index.
2) write(index,char) - The action adds the letter to the content of the page whose index is index.
using thread to end of page.

In both operations 1) and 2)  the system first searches for whether the page is in the main memory.
If the page exists in the main memory, it works with the above page.
Otherwise, the system copies the page from the secondary memory to the main one with replacing pages as needed according to the selected strategy.

## Run the program :

The program should be executed from the command line as follows:

     ./MemoryManagement useLru InputFileName OutputFileName m n
     
When the rest :

  • MemoryManagement is the name of an executable file
  
  • useLru - The page swapping strategy. This parameter is an indicator for using a page swapping strategy. 
  If 1 = useLRU use the "LRU" strategy, and for any other integer value use the "FIFO" strategy.
  
  • InputFileName - The name of the input file that contains the commands to the system.
  
  • OutputFileName - The name of the output file to which we will write the output of the commands given to the system.
  
  • m - the size of the secondary memory
  
  • n - the size of the main memory


For example :
    gcc -o MemoryManagement HW5.c
    ./MemoryManagement 1 intput.txt output(LRU).txt 100 50


## Sample input and output files:
Attached to the program is an input file for example "input.txt"  which contains the collection of commands for your memory management system.
In addition, two output files are attached txt  which contain the output of the system according to
the two different working strategies for n=50 , m=100.

Note: Whenever a print command appears inside an input file, the current contents of a secondary memory must be written to the output file.

