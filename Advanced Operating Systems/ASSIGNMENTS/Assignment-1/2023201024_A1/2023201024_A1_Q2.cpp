#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include<sys/stat.h>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	char buff[100001];
	long long read_at_time = 100000;
	int errno;

//=====================================================
//      creating a directory and output path
//=====================================================
	int d1 = mkdir("Assignment1_2", 0700); 
	if(d1 < 0) 
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1: ");
	}
	
	string output_path = "./Assignment1_2/2_";
	string input_path = argv[1];
	long long start_index = strtol(argv[2], NULL, 10);
	long long end_index   = strtol(argv[3], NULL, 10);
	output_path = output_path + input_path;

//=====================================================
//             Opening of the files
//=====================================================
	//cout<<"opening a file for reading purpose\n";
	int f1 = open(input_path.c_str(), O_RDONLY);
	if(f1 < 0) 
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1: ");
	}
	
	//cout<<"opening a file for writing purpose\n";
	int f2 = open((output_path).c_str(), O_CREAT | O_RDWR | O_TRUNC, 0600);
	if(f2 < 0) 
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f2: ");
	}

//=====================================================
//         finding the size of the input file
//=====================================================

	struct stat file_attributes;
	long long file_size = 0;

	int x = stat(input_path.c_str(), &file_attributes);
	if(x == -1)
	{
		cout<<"Unable to fetch stats of the file\n";
		perror("error message x: "); 
	}
  	file_size = file_attributes.st_size;
  	
  	if(end_index > file_size or start_index < 0)
  	{
  		cout<<"entered indexes are out of file range\n";
  		return 1;
  	}
	
	
//=========================================================================
//			 PHASE 1: reserse the first half		        
//=========================================================================

	// setting up the offsets.

	int f1lsr1 = lseek(f1, start_index, SEEK_SET); // putting file offset
	if(f1lsr1 < 0)  
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1lsr1: ");
	}
	
	int f1lsr3 = lseek(f2,  0, SEEK_SET); // putting file offset of output file at the start of the file
	if(f1lsr3 < 0)  
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1lsr3: ");
	}
	
	//dividing first parts into iterations of buffer size
	long long total = (start_index) / read_at_time;
	long long iterations = (total==0) ? 1 : 0;	
	total = (total==0) ? 1 : total;
	long long rem_bytes = ((start_index) % read_at_time) ; 
	while(iterations < total)
	{
		int f1s1 = lseek(f1, -read_at_time, SEEK_CUR);
		if(f1s1 < 0)
		{
			break;
		}
		
		int f1r1 = read(f1, buff, read_at_time);
		if(f1r1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f1r1: ");
			break;
		}
		
		int f1s2 = lseek(f1, -read_at_time, SEEK_CUR);
		if(f1s2 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f1s2: ");
			break;
		}
		reverse(buff, buff+read_at_time);
		int f1w1 = write(f2, buff, read_at_time);
		if(f1w1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f1w1: ");
			break;
		}
		float percent = ((float)iterations)/(float)total;
		percent *= 100;
		cout<<"Phase1: "<<percent<<"%\033[0K\r";
		iterations ++;
		
	}
	int f1so1 = lseek(f1, 0, SEEK_SET);
	if(f1so1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1so1: ");
	}
	int f1r = read(f1, buff, rem_bytes);
	if(f1r < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1r: ");
	}
	reverse(buff, buff+rem_bytes);
	int f1wo1 = write(f2, buff, rem_bytes);
	if(f1wo1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message wo1: ");
	}
	
	iterations = (iterations==0) ? 1 : iterations;
	float percent = ((float)iterations)/(float)total;
	percent *= 100;
	cout<<"Phase1 "<<percent<<"%\033[0K\r\n";
	
//=========================================================================
//        Phase 2: copy the second half
//=========================================================================

	// setting up the offsets.
	int f2lsr1 = lseek(f1, (start_index), SEEK_SET); // putting file offset at the start index
	if(f2lsr1 < 0)  
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f2lsr1: ");
	}
	
	//dividing first parts into iterations of buffer size
	long long second_size = ((end_index - start_index) + 1);
	total = second_size / read_at_time;
	iterations = (total==0) ? 1 : 0;
	total = (total==0) ? 1 : total;
	rem_bytes = (second_size % read_at_time);
	
	while(iterations < total)
	{		
		int f2r1 = read(f1, buff, read_at_time);
		if(f2r1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f2r1: ");
			break;
		}
		
		int f2w1 = write(f2, buff, read_at_time);
		if(f2w1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f2w1: ");
			break;
		}
		
		float percent = ((float)iterations)/(float)total;
		percent *= 100;
		cout<<"Phase2 "<<percent<<"%\033[0K\r";
		iterations++;
	}
		
	read(f1, buff, rem_bytes);
	int wo1 = write(f2, buff, rem_bytes);
	if(wo1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message wo1: ");
	}
	
	percent = ((float)iterations)/(float)total;
	percent *= 100;
	cout<<"Phase2 "<<percent<<"%\033[0K\r\n";
	
//=========================================================================
//        Phase 3: reverse the third half
//=========================================================================

	// setting up the offsets.
	int f3lsr1 = lseek(f1, -1, SEEK_END); // putting file offset at end byte of file
	if(f3lsr1 < 0) 
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f3lsr1: ");
	}
	
	//dividing first parts into iterations of buffer size
	long long third_size = (f3lsr1 - end_index - 1);
	total = third_size / read_at_time;
	iterations = (total==0) ? 1 : 0;
	total = (total==0) ? 1 : total;
	rem_bytes = (third_size % read_at_time) ; 
	while(iterations < total)
	{
		int f3s1 = lseek(f1, -read_at_time, SEEK_CUR);
		if(f3s1 < 0)
		{
			break;
		}
		
		int f3r1 = read(f1, buff, read_at_time);
		if(f3r1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f3r1: ");
			break;
		}
		
		int f3s2 = lseek(f1, -read_at_time, SEEK_CUR);
		if(f3s2 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f3s2: ");
			break;
		}
		reverse(buff, buff+read_at_time);
		int f3w1 = write(f2, buff, read_at_time);
		if(f3w1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message f3w1: ");
			break;
		}
		float percent = ((float)iterations)/(float)total;
		percent *= 100;
		cout<<"Phase3: "<<percent<<"%\033[0K\r";
		iterations++;
		
	}
	
	int f3so1 = lseek(f1, end_index+1, SEEK_SET);
	if(f3so1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f3so1: ");
	}
	int f3r = read(f1, buff, rem_bytes);
	if(f3r < 0)
	{
		//cout<<"error number: "<<errno<<"\n";
		//perror("error message f3r: ");
	}
	reverse(buff, buff+rem_bytes);
	int f3wo1 = write(f2, buff, rem_bytes);
	if(f3wo1 < 0)
	{
		//cout<<"error number: "<<errno<<"\n";
		//perror("error message f3wo1: ");
	}
	//cout<<total<<" - "<<iterations<<"\n";
	percent = ((float)iterations)/(float)total;
	percent *= 100;
	cout<<"Phase3 "<<percent<<"%\033[0K\r\n";
		


//=========================================================================
//             closing all the files
//=========================================================================
	//cout<<"closing a input file\n";
	int c1 = close(f1);
	if(c1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message: ");
	}
	
	//cout<<"closing a output file\n";
	int c2 = close(f2);
	if(c2 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message: ");
	}
	cout<<"\n";
}
