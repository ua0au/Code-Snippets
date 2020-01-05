
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;//文件指针
    int i, d;

    /*文件的打开*/
    fp=fopen("data.txt","w");//fopen打开文件，这个文件可以是当前不存在的。“w”以写入的形式打开，“r”以读的形式打开
    if(fp==NULL) //判断如果文件指针为空
    {
        printf("File cannot open! " );
        exit(0);//在以0的形式退出，必须在文件开头有#include <stdlib.h>,stdlib 头文件即standard library标准库头文件
    }

    //写入东西
    for(i=0; i<10; i++)
    {
        scanf("%d", &d);//用户输入
        fprintf(fp,"%d\t", d);//写入指针fp，写入的东西就是刚才的用户输入的d,注意这里的fp和d没有引号
    }

     //关闭文件
    fclose(fp);
    return 0;
}

//*************************************************************************************************************

#include <time.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#define FILE_NAME_ROOM	50
#define DATA_TIME_ROOM	24


void savevalue(double a,double b){
	
	time_t t_name = time(0); 
	
	static char F_name[50]; 
	static char F_time[24]; 
	
	char data_dir[]="/root/Documents/RASY_data";

	if(access(data_dir,0) != 0){

		mkdir(data_dir,0744);	//owner:r,w,x; group && others :only r

	}
	
	strftime(F_name, FILE_NAME_ROOM, "/root/Documents/RASY_data/%Y%m%d%H%M.txt",localtime(&t_name) ); //%Y%m%d%H:%M:%S
	strftime(F_time, DATA_TIME_ROOM, "%Y-%m-%d\t%H:%M:%S",localtime(&t_name) ); 
	
	FILE *fp;//文件指针

    fp=fopen(F_name,"a");	//参数a：追加内容
	
    if(fp==NULL) //判断如果文件指针为空
    {
        printf("File cannot open! " );
        exit(0);
    }

  
    fprintf(fp,"\t%s:\n\tV4:%9.8lf\tV8:%9.8lf\t\n\n",F_time,a,b);
    

     //关闭文件
    fclose(fp);

}

int main(int argc, char *argv[]){
	
	savevalue(1,2);
	return 0;
}

