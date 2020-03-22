#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 530 
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

int fastRead_int() {
 register int c = getchar_unlocked();
 int x;
 x = 0;
 int neg = 0;

 for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());

 if(c=='-') {
  neg = 1;
  c = getchar_unlocked();
 }

 for(; c>47 && c<58 ; c = getchar_unlocked()) {
  x = (x<<1) + (x<<3) + c - 48;
 }

 if(neg)
  x = -x;
 return x;
}

void fastRead_string(char *str, char delim)
{
 register char c = 0;
 register int i = 0;

 while (c < 33)
  c = getchar_unlocked();

 while (c != delim) {
  str[i] = c;
  c = getchar_unlocked();
  i = i + 1;
 }

 str[i] = '\0';
}

struct Node 
{ 
	int numelements;
	char arr[MAX];
    struct Node *next; 
} ;

struct Node *head = NULL; 

struct Node* getNode(char data) 
{ 
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->arr[0] = data;
    newNode->next = NULL;
    newNode->numelements = 1;
    return newNode;
} 
  
void locate(int *pos, struct Node **now){ //locates which node pos is at and its array index.
	while(*pos > (*now)->numelements){
		*pos -= (*now)->numelements;
		*now = (*now)->next;
	}
}


void merge(struct Node *A, struct Node *B){
	int count = 0;
	while(B->numelements > 0){
		A->arr[A->numelements] = B->arr[count];
		A->numelements++;
		B->numelements--;
		count++;
	}
}
void insertPos(int pos, char data) 
{	
	//locate(&pos, &head);
	if(!head)
		head = getNode(data);
	else
	{
		struct Node *now = head;
		locate(&pos, &now);
		if((now->numelements) >= pos-1){ //this implies that the idx_array where we want to insert 
										//value is already occupied, and need to be shifted
			for(int i = (now->numelements)-1; i >= pos; i--) //this takes O(k) time
				now->arr[i+1] = now->arr[i];
			now->arr[pos] = data;
			now->numelements++;		
		}
		else{
			now->arr[pos] = data;
			now->numelements++;	
		}
		if(now->numelements == MAX){
				struct Node *temp = getNode(now->arr[MAX-1]);
				temp->next = now->next;
				now->next = temp;
				now->numelements--;
				if(temp->next != NULL && temp->next->numelements <= (MAX)/2){
					merge(temp, temp->next);
					free(temp->next);
					temp->next = temp->next->next;
				}
		}
			
	} 
}

void deletion(int pos)
{
	pos += 1;
	struct Node *now = head;
	locate(&pos, &now);
	pos -= 1;
	if(now->numelements >= pos){
		for(int i = pos; i < (now->numelements)-1; i++)
			now->arr[i] = now->arr[i+1]; 
		now->numelements--;	
	}
	else{
		now->numelements--;
	}
	if(now->next != NULL && now->next->numelements <= (MAX-1)/2 && now->numelements <= (MAX-1)/2){
		merge(now, now->next);
		free(now->next);
		now->next = now->next->next;
	}
}

char print[100000001];
int count = 0;

int query(int pos, int x){
	struct Node *now = head;
	locate(&pos, &now);
	while(x>0){
		while(pos > now->numelements){
			now = now->next;
			pos = 1;	
		}
		print[count] = now->arr[pos-1];
		count++;
		pos++;
		x--;
	}
}

int main(){
	int N;
	N = fastRead_int();
	char command[2];
	int position;
	char limit[2];
	int flag = 0, number;
	char num[10];
	for(int i = 0; i<N; i++){
		fastRead_string(command, ' ');
		if(strncmp(command, "1", 1) == 0){
			position = fastRead_int();
			fastRead_string(limit, '\n');
			insertPos(position, limit[0]);
		}
		else if(strncmp(command, "2", 1) == 0){
			position = fastRead_int();
			deletion(position);
		}
		else if(strncmp(command, "3", 1) == 0){
			position = fastRead_int();
			number = fastRead_int();
			if(flag > 0){
				print[count] = '\n';
				count++;
			}
			query(position+1, number-position);
			flag++;
		}
	}
	printf("%s", print);
}




