#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX 5000

typedef struct chr{
	char ID[MAX];
	char seq[MAX];
	struct chr *next;
}Chr;


void insert(Chr *root, Chr *node){
	
	Chr *newChr;
	newChr = (Chr*)malloc(sizeof(Chr));
	*newChr = *node;

	newChr->next=root->next;
	root->next=newChr;

}

int main(int argc, char* argv[]){

	FILE *fp = NULL;
	char Buffer[MAX];
	char *pt, *str;
	int  oldlen, newlen, count=0, count2 =0;

	Chr chrom;
	Chr *root;
	root = (Chr*)malloc(sizeof(Chr));
	root->next =NULL;


	fp = fopen(argv[1], "r");
	
	if(fp==NULL) return;

	memset(Buffer, 0, MAX);
	while(fgets(Buffer, sizeof(Buffer), fp)){
		
		if(Buffer[0] == '>' && count == 0)
		{
			strcpy(chrom.ID, Buffer);
			count =1;
		}
		else if(Buffer[0] == '>' && count == 1)
		{
			insert(root, &chrom);
			memset(chrom.ID, 0, MAX);
			strcpy(chrom.ID, Buffer);
			count2 = 0;
		}
		else if(Buffer[0] != '>' && count2 ==0)
		{
			memset(chrom.seq,0, MAX);
			strcpy(chrom.seq, Buffer);
			count2 = 1;
		}
		else
		{
			oldlen = strlen(chrom.seq);
                        newlen = strlen(Buffer);
                        memcpy(&chrom.seq[oldlen-1],&Buffer,newlen);
                        chrom.seq[oldlen+newlen]='\n';
		}
		memset(Buffer, 0, MAX);
		
	}
   	insert(root, &chrom);
	fclose(fp);

	Chr *p;
	p = root;
	while(p != NULL)
        {
		printf("\nID >%s", p->ID);
		printf("\nSEQ >>%s", p->seq);
		p = p->next;
	}
	

	return 0;
}
