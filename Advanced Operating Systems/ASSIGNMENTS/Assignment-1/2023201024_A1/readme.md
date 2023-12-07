# Advance Operating System
## Assignment No. 1

All the codes are done using linux system calls expected to run on linux system.
> Question no. 1

following steps have been followed to complete the question
- Creating a directory and output path. here I interpreted that I'll be given a input file (Not a path to file).
- create output file and Opening of the files and placing file descriptor at correct position. 
- Logic of reversal - I have taken a buffer to fast implementation so at a time I'll be reading n bytes at a time. reverse the string and write in the output file.
- there will  (<file size> / <buffer size>) this many iterations. and remaning bytes will be handled separately
- I have calculated file size using Stat() system call and used st_size parameter
- Errror handling is done
 
 > Question no. 2

following steps have been followed to complete the question
- Creating a directory and output path. here I interpreted that I'll be given a input file (Not a path to file).
- Start index and end index can be accessed using commnad line argument.
- create output file and Opening of the files and placing file descriptor at correct position. 
- Logic of reversal - I have taken a buffer to fast implementation so at a time I'll be reading n bytes at a time.
- I have divided question 2 into 3 phases.
-- First Phase: reverse the contents of [0, start_index-1]
-- Second Phase: keep the [start_index, end_index] 
-- Third Phase: reverse the [end_index+1, SEEK_END] 
- reused the most of the logic of question 1
- reverse the string and write in the output file.
- there will  (<phase input size> / <buffer size>) this many iterations. and remaning bytes will be handled separately, this is done for all 3 phases. 
- Errror handling is also done
  
> Question no. 3

following steps have been followed to complete the question
- Here I interpreted that I'll be given a input, output and directory path. Can be accessed using the command line argument argv[1], argv[2], argv[3].
- travesred input file in reversed fashion and output file in normal way, we are taking n bytes at time that is using 2 different buffers. 
- these two buffers can be compared using strcmp function which returns 0 is two buffers are equal. it will be checked and giving the result.
- used stat system call to check permissions and to check if directory is existing or not.
- Errror handling is done
 

