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

	char buff1[1000001];
	char buff2[1000001];
	long long read_at_time = 1000000;
	int errno;
	
//=====================================================
//         Forming paths of two input files
//=====================================================

	string input_path = argv[1];
	string output_path = argv[2];
	string directory_path = argv[3];
	
//=====================================================
//             Opening of the files
//=====================================================	
	int f1 = open(input_path.c_str(), O_RDONLY);
	if(f1 < 0) 
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f1: ");
	}
	
	//cout<<"opening a file for writing purpose\n";
	int f2 = open((output_path).c_str(), O_RDONLY);
	if(f2 < 0) 
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message f2: ");
	}
	
//=====================================================
//         finding the file structure of the files
//=====================================================

	struct stat file1_attributes, file2_attributes;
	long long file1_size = 0;
	long long file2_size = 0;

	int x = stat(input_path.c_str(), &file1_attributes);
	if(x == -1)
	{
		cout<<"Unable to fetch stats of the file\n";
		perror("error message x: "); 
	}
  	file1_size = file1_attributes.st_size-1;
  	
  	x = stat(output_path.c_str(), &file2_attributes);
	if(x == -1)
	{
		cout<<"Unable to fetch stats of the file\n";
		perror("error message x: "); 
	}
  	file2_size = file2_attributes.st_size;
  	
//=====================================================
//             Check if Directory is created
//=====================================================
	cout<<"Directory is created: ";
	struct stat dir_attributes;
	int dir = stat(directory_path.c_str(), &dir_attributes);
	if(x == -1)
	{
		cout<<"Unable to fetch stats of the file\n";
		perror("error message dir: "); 
	}
  	if(S_ISDIR(dir_attributes.st_mode))
  		cout<<"YES\n";
	else 
		cout<<"NO\n";
	cout<<"\n";


//=====================================================
//        putting File desciptor at right place
//=====================================================	
	
	int f1lsr1 = lseek(f1, -1, SEEK_END); // putting file offset
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

//=====================================================
//        Calculating number of iterations
//=====================================================	
	long long total = file1_size / read_at_time;
	long long iterations = (total==0) ? 1 : 0;
	total = (total==0) ? 1 : total;
	long long rem_bytes = (file1_size % read_at_time);
	bool error_in_file = 0;
	
//=====================================================
//        Checking if file is reversed
//=====================================================	
	while(iterations < total)
	{
		int s1 = lseek(f1, -read_at_time, SEEK_CUR);
		
		int r1 = read(f1, buff1, read_at_time);
		if(r1 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message r1: ");
			break;
		}
		
		int r2 = read(f2, buff2, read_at_time);
		if(r2 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message r2: ");
			break;
		}
		
		int s2 = lseek(f1, -read_at_time, SEEK_CUR);
		if(s2 < 0)
		{
			cout<<"error number: "<<errno<<"\n";
			perror("error message s2: ");
			break;
		}
		reverse(buff1, buff1+read_at_time);
		for(int i = 0; i < read_at_time; i++) 
		{
			if(buff1[i] != buff2[i])
			{
				error_in_file = 1;
				break;
			}	
		}
		
		if(error_in_file)
				break;

		
		iterations++;
	}
	
	int so1 = lseek(f1, 0, SEEK_SET);
	if(so1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message so1: ");
	}
	int r1 = read(f1, buff1, rem_bytes);
	if(r1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message r1: ");
	}
	reverse(buff1, buff1+(rem_bytes));
	
	
	int r2 = read(f2, buff2, rem_bytes);
	if(r2 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message r2: ");
	}
	for(int i = 0; i < rem_bytes; i++) 
	{
		if(buff1[i] != buff2[i])
		{
			break;
		}	
	}
	
	cout<<"Whether file contents are reversed in newfile: ";
	if(!error_in_file)
		cout<<"YES\n";
	else 
		cout<<"NO\n";

//=====================================================
//             check permissions of output files
//=====================================================
	cout<<"\n";
	cout<<"User has read permissions on newfile: ";
	if(file2_attributes.st_mode & S_IRUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"User has write permissions on newfile: ";
	if(file2_attributes.st_mode & S_IWUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"User has execute permissions on newfile: ";
	if(file2_attributes.st_mode & S_IXUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
		
	cout<<"Group has read permissions on newfile: ";
	if(file2_attributes.st_mode & S_IRGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Group has write permissions on newfile: ";
	if(file2_attributes.st_mode & S_IWGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Group has execute permissions on newfile: ";
	if(file2_attributes.st_mode & S_IXGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has read permissions on newfile: ";
	if(file2_attributes.st_mode & S_IROTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has write permissions on newfile: ";
	if(file2_attributes.st_mode & S_IWOTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has execute permissions on newfile: ";
	if(file2_attributes.st_mode & S_IXOTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";


//=====================================================
//             check permissions of input files
//=====================================================
	cout<<"\n";
	cout<<"User has read permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IRUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"User has write permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IWUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"User has execute permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IXUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
		
	cout<<"Group has read permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IRGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Group has write permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IWGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Group has execute permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IXGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has read permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IROTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has write permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IWOTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has execute permissions on oldfile: ";
	if(file1_attributes.st_mode & S_IXOTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";


//=====================================================
//             check permissions of direcory
//=====================================================
	cout<<"\n";
	cout<<"User has read permissions on directory: ";
	if(dir_attributes.st_mode & S_IRUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"User has write permissions on directory: ";
	if(dir_attributes.st_mode & S_IWUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"User has execute permissions on directory: ";
	if(dir_attributes.st_mode & S_IXUSR)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
		
	cout<<"Group has read permissions on directory: ";
	if(dir_attributes.st_mode & S_IRGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Group has write permissions on directory: ";
	if(dir_attributes.st_mode & S_IWGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Group has execute permissions on directory: ";
	if(dir_attributes.st_mode & S_IXGRP)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has read permissions on directory: ";
	if(dir_attributes.st_mode & S_IROTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has write permissions on directory: ";
	if(dir_attributes.st_mode & S_IWOTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";
	
	cout<<"Others has execute permissions on directory: ";
	if(dir_attributes.st_mode & S_IXOTH)
		cout<<"YES\n";
	else 
		cout<<"NO\n";


//=====================================================
//             closing all the files
//=====================================================
	
	int c1 = close(f1);
	if(c1 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message: ");
	}
	
	int c2 = close(f2);
	if(c2 < 0)
	{
		cout<<"error number: "<<errno<<"\n";
		perror("error message: ");
	}

	
	return 0;
}
