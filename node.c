#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
struct stat buf;
//初始化文件节点
Node * init_node()
{
	Node * node = (Node *)malloc(sizeof(Node));
	if(!node)
	{
		exit(EXIT_FAILURE);
	}
	node->next = NULL;

	return node;
}
//文件名节点连接起来
void input_node(Node * node, const char *file )
{
	Node * p;
	p = (Node *)malloc(sizeof(Node));
	if(!p)
	{
		exit(EXIT_FAILURE);
	}
		strcpy(p->s, file);
		p->next = node->next;
		node->next = p;

}
//删除不需要的节点
void remove_node(Node * node, int i)
{
	Node * p, *q;
	p = getNode(node, i);
	q = p->next;
	p->next = q->next;
	free(q);
}
//获取前驱文件节点
Node * getNode(Node * node, int i)
{
	Node * current;
	current = node;
	int j;
	for(j = 0; j < i - 1; j++)
	{
		current = current->next;
	}

	return current;
}
//初始化文件夹的存储节点
Dir_node * init_dir_node()
{
	Dir_node * node;
	node = (Dir_node*)malloc(sizeof(Dir_node));
	if(!node)
	{
		exit(EXIT_FAILURE);
	}
	node->next = NULL;

	return node;
}
//添加存储文件夹的节点
void input_dir_node(Dir_node * node, const char * file)
{
	Dir_node * p;
	p = (Dir_node *)malloc(sizeof(Dir_node));
	if(!p)
	{
		exit(EXIT_FAILURE);
	}
	strcpy(p->c, file);
	p->next = node->next;
	node->next = p;
}
// 判断是文件还是目录
int is_file_or_dir(const char * file_name)
{
	int i = -1;
	stat(file_name, &buf);
	if(S_IFDIR & buf.st_mode)
	{
		i = 1;
	}
	else if(S_IFREG & buf.st_mode)
	{
		i = 0;
	}
	return i;
}
