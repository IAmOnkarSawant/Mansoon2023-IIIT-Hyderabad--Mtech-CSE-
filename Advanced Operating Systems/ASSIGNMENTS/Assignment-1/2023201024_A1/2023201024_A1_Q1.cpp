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
	char buff[1000001];
	int errno;

//=====================================================
//      creating a directory and output path.
//=====================================================
	int d1 = mkdir("Assignment1_1", 0700); 
	if(d1 < 0) 
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1: ");
	}
	
	string output_path = "./Assignment1_1/1_";
	string input_path = argv[1];
	
	output_path = output_path+input_path;
	
//=====================================================
//             Opening of the files
//=====================================================
	//cout<<"opening a file for ing purpose\n";
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
	
	lseek(f1, -1, SEEK_END); // putting file offset at the end of input file
	lseek(f2, 0, SEEK_SET); // putting file offset of output file at the start of the file

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
  	file_size = file_attributes.st_size-1;
	
//=====================================================
//        reversing the input file
//=====================================================
	
	long long read_at_time = 1000000;
	long long total = file_size / read_at_time;
	long long iterations = (total==0) ? 1 : 0;
	total = (total==0) ? 1 : total;
	long long rem_bytes = (file_size % read_at_time) ;
	
	cout<<file_size<<" "<<total<<" "<<iterations<<" "<<rem_bytes<<"\n";
	while(iterations < total)
	{
		iterations++;
		int s1 = lseek(f1, -read_at_time, SEEK_CUR);
		
		int r1 = read(f1, buff, read_at_time);
		if(r1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message r1: ");
			break;
		}
		
		reverse(buff, buff+read_at_time);
		//cout<<buff<<"\n";
		int w1 = write(f2, buff, read_at_time);
		if(w1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message w1: ");
			break;
		}
		
		int s2 = lseek(f1, -(read_at_time), SEEK_CUR);
		if(s2 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message s2: ");
			break;
		}
		float percent = ((float)iterations)/(float)total;
		percent *= 100;
		cout<<percent<<"%\033[0K\r";
		
	}
	
	int so1 = lseek(f1, 0, SEEK_SET);
	if(so1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message so1: ");
	}
	int r1 = read(f1, buff, rem_bytes);
	reverse(buff, buff+rem_bytes);
	int wo1 = write(f2, buff, rem_bytes);
	if(wo1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message wo1: ");
	}
	

	float percent = ((float)iterations)/(float)total;
	percent *= 100;
	cout<<percent<<"%\033[0K\r\n";
	cout<<total<<" "<<iterations<<" "<<rem_bytes<<"\n";

//=====================================================
//             closing all the files
//=====================================================
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
