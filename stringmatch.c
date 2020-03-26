#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"

//文件名的匹配, 需要就留下，不需要就删除
void str_match(Node * node)
{
	Node * current;
	char * str;
	char str_match[][20] = {".c", ".mp4", ".txt", ".mkv", ".cpp"};
	int str_len,i, j, k, l, m;
	char ch[20];
	i = 0;
	k = 0;
	l = 1;
	m = sizeof(str_match)/sizeof(str_match[0]);
	current = node;
	current = current->next;

	while(current != NULL)
	{
		str_len = strlen(current->s);
		j = str_len - 1;
	/*	do{
			puts(current->s);
			ch[i] = current->s[j];
			i = i + 1;
			j = j - 1;

		}while(current->s[j] != '.' && j > 0);
		*/

		while(current->s[j] != '.' && j > 0)
		{
			//puts(current->s);
			ch[i] = current->s[j];
			i = i + 1;
			j = j - 1;
		}

		ch[i] = '.';
		ch[i+1] = '\0';
		str = str_sort(ch);

		for(i = 0; i < m; i++)
		{
			if(strcmp(str, str_match[i]) != 0)
				k = k + 1;
		}
		if(k == m)
		{
			remove_node(node, l);
		}

		i = 0;
		k = 0;
		l = l + 1;
		current = current->next;
	}
	free(str);
}
//文件复制
void file_cpy(Node * node)
{
	FILE * fp, * fout;
	char dir_path[MAXSIZE];
	char f_dir[MAXSIZE*2] = {"/Users/yinshifeng/"};
	char  string[MAXSIZE*2];
	char ch;
	char * str;
	int status;
	int i = 0;
	int cha;
	Node * current;
	current = node;
	current =  current->next;
	puts("请建立一个目录，并以'#'结束!");

	while((ch = getchar()) != '#')
	{
		dir_path[i] = ch;
		i = i + 1;
	}
	dir_path[i] = '\0';
	strcat(f_dir, dir_path);
	strcat(f_dir, "/");
	strcpy(string, f_dir);
	puts(f_dir);

	//进行复制文件的操作，将文件存储到给定的目录中
	while(current != NULL)
	{
		if(is_file_or_dir(f_dir) != 1)
		{
			status = mkdir(f_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			printf("status = %d\n", status);
		}
		fp = fopen(current->s, "rb");
		str = getFile_name(current->s);
		fout = fopen(strcat(string,str), "ab");
		puts(string);
		puts("正在复制文件------");

		//读取文件中的每一个字符存储到目标文件中
		while((cha = getc(fp)) != EOF)
		{
			putc(cha, fout);
		}

		current = current->next;
		strcpy(string, f_dir);
		fclose(fp);
		fclose(fout);
		free(str);
	}
}

//返回一个含有文件名称的字符串
char * getFile_name(const char * path_name)
{
	char *ch;
	char *str;
	int i, j;
	ch = (char *)malloc((strlen(path_name) + 1) * sizeof(char));
	if(!ch)
	{
		exit(EXIT_FAILURE);
	}
	i = strlen(path_name) - 1;
	j = 0;

	//将文件名保存到申请的内存中
	while(path_name[i] != '/' && i >= 0)
	{
		ch[j] = path_name[i];
		j = j + 1;
		i = i - 1;
	}
	ch[j] = '\0';


	str = str_sort(ch);
	free(ch);
	return str;
}

//对文件名字符串进行倒序
char * str_sort(char * str)
{
	char *ch;
	ch = (char *)malloc((strlen(str) + 1) * sizeof(char));
	int i, j, k;
	i = 0;
	k = strlen(str);
	j = k - 1;
	for(; j >= 0; i++, j--)
	{
		ch[i] = str[j];
	}
	ch[i] = '\0';

	return ch;
}
