//遍历文件夹中所有子文件夹名，保存到数组

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


int main(int argc,char *argv[]){
	
    DIR *dp;
    struct dirent *filename;
	
	char old_data_dir[]="/root/Documents/RASY_data";  
	
    if((dp = opendir(old_data_dir))==NULL){
		
		perror("open old_data_dir error:");
    }
	
	
	char dir_data[20][20];	//first 20：dir_count
	int i=0;
	
	while((filename = readdir(dp))!=NULL){
		
		
		if(!( strcmp(filename->d_name,".")==0 || strcmp(filename->d_name,"..")==0 || filename->d_type==8 )){
					
			char* tmp=filename->d_name;
			
			strcpy(dir_data[i],tmp);
			
			//printf("filename:%s\n",dir_data[i]);
			i++;
			

		}

	}
    
	for(int j=0;j<i;j++){
		
		printf("filename:%s\n",dir_data[j]);
	}
	
    closedir(dp);
    return 0;
}


//windows
/*
#include <string>
#include <iostream> 
using namespace std;

#include <WINDOWS.H>  

void main()  
{  
    string szPath="d:/*.*";
	WIN32_FIND_DATA wfd;  
    HANDLE hFind;  
	char file_list[100][40];
    int i=0;
	
	hFind = FindFirstFile(szPath.c_str(), &wfd) ;
    do  
    {  
		cout << wfd.cFileName << endl ; 
		strcpy(file_list[i],wfd.cFileName ); //存储到数组
		if ( ++i>=100 ) break;
    }while (FindNextFile(hFind, &wfd));  
	
    FindClose(hFind);  
}
*/

