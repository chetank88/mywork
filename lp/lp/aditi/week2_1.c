#include<stdio.h>
#include<string.h>

typedef struct NODE

{

    int id;

    char name[25];

    char type[10];

    char value[25];

	struct NODE *next;

}NODE;

FILE *fp1,*fp2,*fp3;

void InsertID(char ID[],int *id_num,char stored_type[],NODE **Header)

{

	NODE *temp,*last;

	last=(*Header);

	temp=(NODE*)malloc(sizeof(NODE));

    strcpy(temp->name,ID);

    strcpy(temp->type,stored_type);

    temp->id=*id_num;

    temp->next=NULL;

	if((*Header)==NULL)

        (*Header)=temp;

	else

	{

	    while(last->next!=NULL)

            last=last->next;

        last->next=temp;

	}

}

int checkID(char buff[],NODE *Header)

{

    int flag=0;

    NODE *temp;

    temp=Header;

    while(temp!=NULL)

    {

        if(strcmp(temp->name,buff)==0)

            return temp->id;

        temp=temp->next;

    }

    return 0;

}

void display(NODE *Header)

{

    NODE *temp;

    temp=Header;

    while(temp!=NULL)

    {

        fprintf(fp3,"%d\t%s\t%s\n",temp->id,temp->type,temp->name);
        temp=temp->next;

    }

}

void substr(char buff[],char copy_[],int i)

{

    int z,k=0;

    for(z=i;copy_[z]!='\0';z++)

        buff[k++]=copy_[z];

}
int main()
{

    NODE *sym_table=NULL;
	char filename1[25],filename2[25],filename3[25],ch1,store_type[25];
	char key[32][10]={{"int"},{"float"},{"char"},{"double"},{"void"},{"long"},{"short"},
	{"for"},{"while"},{"do"},{"if"},{"else"},{"goto"},{"case"},{"switch"},{"default"},
	{"break"},{"continue"},{"return"},{"auto"},{"const"},{"enum"},{"extern"},{"register"},
	{"signed"},{"sizeof"},{"static"},{"struct"},{"typedef"},{"union"},{"unsigned"},{"volatile"}};
	char spec[8][2]={{"("},{")"},{"{"},{"}"},{"["},{"]"},{";"},{","}};
	char op[36][4]={{"+"},{"-"},{"*"},{"/"},{"%"},{"<"},{">"},{"="},{"=="},{"<="},{">="},{"!="},{"!"},
	{"++"},{"--"},{"&"},{"|"},{"&&"},{"||"},{"<<"},{">>"},{"+="},{"-="},{"*="},{"/="},{"%="},{"<<="},{">>="},
	{"&="},{"|="},{"^="},{"~"},{"^"},{"."},{"?"},{":"}};
	char buff[20],copy_[20];
	int i=0,k,flag=0,l=0,*id_num,val,temp=1;
	int lineno=1;
	id_num=&temp;
	printf("Enter source file name: ");
	gets(filename1);
	printf("Enter destination file name for program: ");
	gets(filename2);
	printf("Enter destination file name for symbol table: ");
	gets(filename3);
	fp1=fopen(filename1,"r");
	fp2=fopen(filename2,"w");
	fp3=fopen(filename3,"w");
	ch1=getc(fp1);
	fprintf(fp2,"#1\n");
	while(ch1!=EOF)
	{
		if(ch1=='\n')
		{
			fprintf(fp2,"\n#%d\n",++lineno);
			ch1=getc(fp1);
		}
	    if(ch1==' ' || ch1=='\t')
            ch1=getc(fp1);
        else if(ch1=='"')
        {
            ch1=getc(fp1);
            while(ch1!='"')
            {
                buff[i++]=ch1;
                ch1=getc(fp1);
            }
            buff[i]='\0';
            i=0;
            fprintf(fp2,"%s ",buff);
            ch1=getc(fp1);
        }
		else if(isalpha(ch1) || ch1=='_')
		{
			while(isalnum(ch1) || ch1=='_')
			{
				buff[i++]=ch1;
				ch1=getc(fp1);
			}
			buff[i]='\0';
			i=0;
			for(k=0;k<32;k++)
				if(strcmp(key[k],buff)==0)
				{

				    if(k<4)

                        strcpy(store_type,buff);
				    fprintf(fp2,"%s ",buff);
                    flag=1;
                    break;
				}
            if(flag==0)

            {

                val=checkID(buff,sym_table);

                if(val==0)

                {

                    InsertID(buff,id_num,store_type,&sym_table);

                    fprintf(fp2,"id,%d ",*id_num);

                    (*id_num)++;

                }

                else

                    fprintf(fp2,"id,%d ",val);

            }
            flag=0;
		}
        else if(isdigit(ch1))
        {
            while(isdigit(ch1) || ch1=='.')
            {
                buff[i++]=ch1;
                ch1=getc(fp1);
            }
            buff[i]='\0';
            i=0;
            fprintf(fp2,"%s ",buff);
        }
        else
        {

            while(!(isalpha(ch1) || isdigit(ch1) || ch1=='_' || ch1==' ' || ch1=='\t' || ch1=='\n' || ch1=='"' || ch1==EOF))
            {
                buff[i++]=ch1;
                ch1=getc(fp1);
            }
            buff[i]='\0';

            strcpy(copy_,buff);

            while(i!=0)

            {

                if(strcmp(buff,";")==0)

                    strcpy(store_type,"");
                for(k=0;k<8;k++)
                    if(strcmp(spec[k],buff)==0)
                    {
                        fprintf(fp2,"%s ",buff);
                        flag=1;
                        break;
                    }
                if(flag!=1)
                    for(k=0;k<36;k++)
                        if(strcmp(op[k],buff)==0)
                        {
                            fprintf(fp2,"%s ",buff);
                            flag=2;
                            break;
                        }

                if(flag==0)

                {

                    i--;

                    buff[i]='\0';

                }

                else

                {

                    substr(buff,copy_,i);

                    i=strlen(copy_)-i;

                    strcpy(copy_,buff);

                }
            }

            i=0;

            flag=0;

        }
	}
	display(sym_table);
	printf("Done :)");
	close(fp1);

	close(fp2);
	return 0;
}
