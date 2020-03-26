//文件整理程序
//1，获取目录名称。
//2，通过遍历目录，获取目录中所有文件的名并存储在数组中
//3，判断是目录还是文件，如果是目录那么就继续遍历并将获取的目录存储在数组中
//4，根据文件的后缀名进行匹配得到需要的文件并将该文件复制到相应的另一个目录中
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include "node.h"
void files_names(const char *dir_path, Node * node, Dir_node * dir_node);
void path_name(const char *dir_path, Node * node, Dir_node * dir_Node);
void get_file_name(Dir_node * dir_node, Node * node);

int main(void) 
{

	char *file;
	file = "test";
	Node * node;	
	Node * current;
	Dir_node * dir_node;
	node = init_node();
	dir_node = init_dir_node();
	path_name(file, node, dir_node);
	get_file_name(dir_node, node);
	str_match(node);
	for(current = node->next;  current != NULL; current = current->next)
	{
		puts(current->s);
	}
	file_cpy(node);

	free(node);
	free(dir_node);
	return 0;
}
//将文件与文件夹分别存放
void files_names(const char * dir_path, Node * node, Dir_node * dir_node)
{

	char *names; 
	char dir_name[MAXSIZE];
	struct dirent * dir_info; 
	DIR * dir;
	dir = opendir(dir_path);

	strcpy(dir_name, dir_path);
	strcat(dir_name, "/");
	while((dir_info = readdir(dir)) != NULL)
	{

		names = dir_info->d_name;
		if(strcmp(names, ".") != 0 && strcmp(names, "..") != 0 && strcmp(names, ".DS_Store") != 0)
		{
			strcat(dir_name, names);
			if(is_file_or_dir(dir_name) == 0)
			{
				input_node(node, dir_name);
				strcpy(dir_name, dir_path); 
				strcat(dir_name, "/");
			}
			else if(is_file_or_dir(dir_name) == 1)
			{	
				input_dir_node(dir_node, dir_name);
				strcpy(dir_name, dir_path);
				strcat(dir_name, "/");
			}
		}
	}
	closedir(dir);
}

//给定一个路径，如果是目录则进行下一步，如果是文件直接存储
void path_name(const char * dir_path, Node * node, Dir_node * dir_node)
{
	if(is_file_or_dir(dir_path) == 1)
	{
		files_names(dir_path, node, dir_node);
	}
	else if(is_file_or_dir(dir_path) == 0) 
	{
		input_node(node, dir_path);
	}
}

void get_file_name(Dir_node * dir_node, Node * node)
{
	Dir_node * current_dir;
	current_dir = dir_node->next;
	while(current_dir != NULL)
	{
		files_names(current_dir->c, node, dir_node);
		current_dir = current_dir->next;
	}
}
