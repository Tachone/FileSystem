
#ifndef _FILEOPERA_H_
#define _FILEOPERA_H_


#include "common.h"
#include "MFD.h"
using namespace std;

extern vector<MFD> UsrInfo;
extern int num;
extern MFD UsrInput;
extern int Headnum;
extern vector< vector<UOF> > FileState;
extern UFD FileInput;
extern UOF StateInput;
extern Cluster ClusterInput;
extern vector < vector<UFD> > FileInfo;
extern vector< Cluster> FileCluster;

void initFiletoRom()
{
	FILE *streamInit;
	if ((streamInit = fopen("disk.txt", "r")) == NULL)
	{
		cout << "从磁盘中读入时失败！" << endl;
		return ;
	}

	//读入用户信息
	fscanf(streamInit, "%d", &Headnum);
	int alreadynum;
	int ret;
	alreadynum = 0;
	//需要再处理，最好以\n分割
	while (alreadynum<Headnum&&(ret = fscanf(streamInit, "%s %s %d", &UsrInput.usrname, &UsrInput.usrpass, &UsrInput.link)) != -1)
	{
		UsrInfo.push_back(UsrInput);
		alreadynum++;
	}
	//初始化文件信息
	vector<UFD> t;
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		FileInfo.push_back(t);
	}
	vector<UOF> temp;
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		FileState.push_back(temp);
	}

	//读入
	/*
	char filename[14];
	int mode;
	int length;
	int addr;
	*/
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		fscanf(streamInit, "%d", &Headnum);
	    alreadynum = 0;
		
		//需要再处理，最好以\n分割
		while (alreadynum<Headnum && (ret = fscanf(streamInit, "%s %d %d %d", &FileInput.filename, &FileInput.mode, &FileInput.length, &FileInput.addr)) != -1)
		{
			FileInfo[i].push_back(FileInput);
			alreadynum++;
		}
	}
	/*char filename[14];
	int mode;
	int state; //0建立,1打开
	int read_poit; //读写指针
	int write_poit;*/
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		fscanf(streamInit, "%d", &Headnum);
	    alreadynum = 0;
		//需要再处理，最好以\n分割
		while (alreadynum<Headnum && (ret = fscanf(streamInit, "%s %d %d %d %d", &StateInput.filename, &StateInput.mode, &StateInput.state, &StateInput.read_poit,&StateInput.write_poit)) != -1)
		{
			FileState[i].push_back(StateInput);
			alreadynum++;
		}
	}

	/*
	int next_num;
	int is_data;
	char data[256];*/
	//fscanf(streamInit, "%d", &Headnum);
    alreadynum = 0;
	char Tempbuf[256];
	//需要再处理，最好以\n分割
	int total = 0;
	char c;
	while (total < 68)
	{
		total++;
		memset(Tempbuf, 0, sizeof(Tempbuf));
		if ((ret = fscanf(streamInit, "%d %d", &ClusterInput.next_num, &ClusterInput.is_data)) != -1)
		{
			if (ClusterInput.is_data == 1)
			{
				 fscanf(streamInit, "%c", &c);
				 fgets(Tempbuf, 256, streamInit);
			}
			strcpy(ClusterInput.data, Tempbuf);
			FileCluster.push_back(ClusterInput);
		}
		else
		{
			//初始化
			//FileCluster[alreadynum].next_num = alreadynum;
			//FileCluster[alreadynum].is_data = 0;
			ClusterInput.next_num = alreadynum;
			ClusterInput.is_data = 0;
			strcpy(ClusterInput.data, Tempbuf);

			FileCluster.push_back(ClusterInput);
		}
		alreadynum++;
	}
	
	fclose(streamInit);
}

void out_to_file()
{
	FILE* fd;
	fd = fopen("disk.txt", "w");
	fprintf(fd, "%d%c", UsrInfo.size(), ' ');
	for (int i = 0; i < UsrInfo.size(); i++)
		fprintf(fd, "%s %s %d%c", UsrInfo[i].usrname, UsrInfo[i].usrpass, UsrInfo[i].link, ' ');
	fprintf(fd, "\n");

	/*
	char filename[14];
	int mode;
	int length;
	int addr;
	*/
	for (int i = 0; i < FileInfo.size(); i++)
	{
		fprintf(fd, "%d%c", FileInfo[i].size(), ' ');
		for (int j = 0; j < FileInfo[i].size(); j++)
		{
			fprintf(fd, "%s %d %d %d%c", FileInfo[i][j].filename, FileInfo[i][j].mode, FileInfo[i][j].length,FileInfo[i][j].addr, ' ');
		}
		fprintf(fd, "\n");
	}
	
	/*char filename[14];
	int mode;
	int state; //0建立,1打开
	int read_poit; //读写指针
	int write_poit;*/
	for (int i = 0; i < FileState.size(); i++)
	{
		fprintf(fd, "%d%c", FileState[i].size(), ' ');
		for (int j = 0; j < FileState[i].size(); j++)
		{
			fprintf(fd, "%s %d %d %d %d%c", FileState[i][j].filename, FileState[i][j].mode, FileState[i][j].state, FileState[i][j].read_poit,FileState[i][j].write_poit, ' ');
		}
		fprintf(fd, "\n");
	}

	/*int num;
	int next_num;
	int is_data;
	char data[256];*/

	//fprintf(fd, "%d%c", FileCluster.size(), ' ');
	for (int i = 0; i < FileCluster.size(); i++)
	{
		//fprintf(fd, "%d %d %s%c",FileCluster[i].next_num, FileCluster[i].is_data, FileCluster[i].data, ' ');
		fprintf(fd, "%d %d%c", FileCluster[i].next_num, FileCluster[i].is_data,' ');
		fputs(FileCluster[i].data, fd);
		fprintf(fd, "\n");
	}

	fclose(fd);
}

#endif
