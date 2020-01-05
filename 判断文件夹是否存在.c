
//判断文件夹是否存在，如果不存在则创建

	#include <stdio.h>
	
	#include <unistd.h>

	#include <sys/types.h>  
	#include <sys/stat.h>

	//perror();EXIT_SUCCESS表示正常，EXIT_FAILURE

int main(int argc, char *argv[]){ 

	char data_dir[]="/root/Documents/RASY_data";

	if(access(data_dir,0) == 0){
		
		printf("文件夹存在");
		
	}else{
			mkdir(data_dir,0744);	//owner:r,w,x; group && others :only r

	}

	return 0;

}


	char data_dir[]="/root/Documents/RASY_data";

	if(access(data_dir,0) != 0){

		mkdir(data_dir,0744);	//owner:r,w,x; group && others :only r

	}

