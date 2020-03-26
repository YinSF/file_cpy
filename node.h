#define MAXSIZE 100

typedef struct file_node
{
	char s[MAXSIZE];
	struct file_node *next;
}Node;

typedef struct dir_node
{
	char c[MAXSIZE];
	struct dir_node * next;
}Dir_node;
Node * init_node();
void input_node(Node *node,const char *file);
Dir_node *init_dir_node();
void input_dir_node(Dir_node * node, const char * file);
void remove_node(Node * node, int i);
Node * getNode(Node * node, int i);
void str_match(Node * node);
void file_cpy(Node * node);
int is_file_or_dir(const char *file_name);
char * getFile_name(const char * path_name);
char * str_sort(char * str);
