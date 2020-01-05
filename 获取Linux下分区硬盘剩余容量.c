
#include <sys/vfs.h>


	
void freedisk_is_ok(){
	
		struct statfs diskInfo;
		statfs("/root", &diskInfo);
		
		unsigned long long totalBlocks = diskInfo.f_bsize;
		unsigned long long totalSize = totalBlocks * diskInfo.f_blocks;
		
		size_t mbTotalsize = totalSize>>20;
		unsigned long long freeDisk = diskInfo.f_bfree*totalBlocks;
		size_t mbFreedisk = freeDisk>>20;
		
		//printf ("/  total=%dMB, free=%dMB\n", mbTotalsize, mbFreedisk);
		

		if(mbFreedisk<1024){
			printf("磁盘空间小于1G，未避免造成运行当中出现错误，\n请扩大容量或者清理磁盘空间之后，重新启动该程序，谢谢！\n");
			exit(0);
		}

}


