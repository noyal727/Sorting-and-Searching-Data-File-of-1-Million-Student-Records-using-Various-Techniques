#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N1 1
#define N2 1000000
#define MAX 26
struct Node
{
    long int rollno;
    char nam[15], branch[15];
int age;
struct Node *next;
struct Node *prev;
};
struct Node records[N2];
char *branch[4]={"CSE","ECE","MECH","EEE"};

char *printRandomString(int n)
{
char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
'h', 'i', 'j', 'k', 'l', 'm', 'n',
'o', 'p', 'q', 'r', 's', 't', 'u',
'v', 'w', 'x', 'y', 'z' };

    char *res;
    res=malloc((n+1)*sizeof(char));
for (int i = 0; i < n; i++)
res[i] =  alphabet[rand() % MAX];
    res[n]='\0';
return res;
}

int cmp(const void * a, const void * b) {
   return (((struct Node *)a)->rollno - ((struct Node *)b)->rollno);
}

void swap ( long int* a,long int* b )
{   long int t = *a;      *a = *b;       *b = t;
}

void swapi ( int* a, int* b )
{   int t = *a;      *a = *b;       *b = t;
}

void swaps(char *str1, char *str2)
{
  char *temp = str1;
  str1 = str2;
  str2 = temp;
}

struct Node *lastNode(struct Node *root)
{
    while (root && root->next){
        root = root->next;}
    return root;
}


struct Node* partition(struct Node *l, struct Node *h)
{
    long int x  = h->rollno;
    //int a;
    char *n;// *b;
    n=(char *)malloc(sizeof(char)*15);
    //b=(char *)malloc(sizeof(char)*15);
    struct Node *j,*i = l->prev;
    for (j = l; j != h; j = j->next)
    {
        if (j->rollno <= x)
        {
            i = (i == NULL)? l : i->next;
            swap(&(i->rollno), &(j->rollno));
            swapi(&(i->age), &(j->age));
            strcpy(n,i->nam);
            strcpy(i->nam,j->nam);
            strcpy(j->nam,n);
            //swaps((i->nam), (j->nam));
            strcpy(n,i->branch);
            strcpy(i->branch,j->branch);
            strcpy(j->branch,n);
            //swaps((i->branch), (j->branch));
        }
    }
    i = (i == NULL)? l : i->next;
    swap(&(i->rollno), &(h->rollno));
    swapi(&(i->age), &(h->age));
    strcpy(n,i->nam);
    strcpy(i->nam,h->nam);
    strcpy(h->nam,n);
    //swaps((i->nam), (h->nam));
    //swaps((i->branch), (h->branch));
    strcpy(n,i->branch);
    strcpy(i->branch,h->branch);
    strcpy(h->branch,n);
    return i;
}


void _quickSort(struct Node* l, struct Node *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        struct Node *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}


void quickSort(struct Node *head)
{
    struct Node *h = lastNode(head);
    _quickSort(head, h);
}



void push(struct Node** head_ref,long int new_data, char* new_nam, char *bran, int ag)
{
    struct Node* new_node;
    new_node=(struct Node *)malloc(sizeof(struct Node));
    new_node->rollno  = new_data;
    strcpy(new_node->nam,new_nam);
    strcpy(new_node->branch,bran);
    new_node->age=ag;
    new_node->prev = NULL;
    new_node->next = (*head_ref);
    if ((*head_ref) !=  NULL) {
        (*head_ref)->prev = new_node ;
     }   (*head_ref)    = new_node;

}



void sortfile(char *f){
    struct Node input, *a=NULL;
    FILE *fp;
    fp=fopen(f,"rb");
    while(fread(&input, sizeof(struct Node), 1, fp)){
        push(&a,input.rollno,input.nam,input.branch,input.age);
}
fclose(fp);

    fp=fopen(f,"wb");
while (a)
    {
        input.rollno = a->rollno;
        input.age = a->age;
        strcpy(input.nam,a->nam);
        strcpy(input.branch,a->branch);
        fwrite(&input,sizeof(struct Node),1,fp);
        a = a->next;
    }fclose(fp);
    printf("\n\tsorted file-%s",f);
}

void displayfile(char *f){
    FILE *fp = fopen(f, "rb");
fseek(fp, 0, SEEK_SET);
struct Node input;
while(fread(&input, sizeof(struct Node), 1, fp)){
        printf("\n\t%ld\t%s\t%s\t%d",input.rollno,input.nam,input.branch,input.age);
}
fclose(fp);
printf("\n\n\n");
}

long int merge(char *file1,char *file2)
{
    int flg1=1,flg2=1;
    long int c=0;
    struct Node n1, n2;
    FILE *fp,*fp1,*fp2;
    fp1=fopen(file1,"rb");
    fp2=fopen(file2,"rb");
    fp=fopen("file.dat","wb");

    while (1){
        if (flg1) {
            if(!fread(&n1, sizeof(struct Node), 1, fp1)){
                fwrite(&n2, sizeof(struct Node), 1, fp);
                c++;
                while(fread(&n2, sizeof(struct Node), 1, fp2)){
                    fwrite(&n2, sizeof(struct Node), 1, fp);
                    c++;
                }
                break;
            }
        }

        if (flg2) {
            if(!fread(&n2, sizeof(struct Node), 1, fp2)){
                fwrite(&n1, sizeof(struct Node), 1, fp2);
                c++;
                while(fread(&n1, sizeof(struct Node), 1, fp1)){
                    fwrite(&n1, sizeof(struct Node), 1, fp);
                    c++;
                }
                break;
            }
        }


        if (n1.rollno > n2.rollno)  {
            flg1 = 0;
            flg2 = 1;
            fwrite(&n2, sizeof(struct Node), 1, fp);
            c++;
        }else {
            flg1 = 1;
            flg2 = 0;
            fwrite(&n1, sizeof(struct Node), 1, fp);
            c++;
        }
    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    remove(file1);
    remove(file2);
    return c;
}


void search(char *f, long int rollno){
    FILE *fp;
    fp=fopen(f, "rb");
    struct Node input;
    while(fread(&input, sizeof(struct Node), 1, fp)){
        if(input.rollno == rollno){
            printf("\n\n\n\t%ld\t%s\t%s\t%d\n\n",input.rollno,input.nam,input.branch,input.age);
            return;
        }
}
printf("\n\n\n\tNot Found\n");
return ;
}

int main(){
    long int len = N2-N1+1, i , r , temp, c1=0, c2=0, c=0;
    long int *num, *ran;
    num = (long int*)malloc(len * sizeof(long int));
    ran = (long int*)malloc(len * sizeof(long int));
    for( temp=0,i=N1; temp<len; i++,temp++ ){
        num[temp] = i;
        ran[temp] = rand()%4;
    }
    srand( time(NULL) );
    for( i=len-1; i>0; i-- ){
        r = rand()%i;
        temp = num[i];
        num[i] = num[r];
        num[r] = temp;
    }
FILE *outfile;
outfile = fopen ("file.dat", "wb");
struct Node input;
for(int i=0; i<N2; i++){
int r=ran[i];
int l = (rand() % (12 - 7 + 1)) + 7;
char *s=printRandomString(l);
input.rollno=num[i];
        strcpy(input.branch, branch[r]);
        strcpy(input.nam, s);
        input.age= (rand() % (21 - 18 + 1)) + 18;
fwrite (&input, sizeof(struct Node), 1, outfile);
}
fclose (outfile);
    outfile = fopen ("file.dat", "rb");
fseek(outfile, 0, SEEK_SET);
FILE *fp1, *fp2;
fp1 = fopen ("file1.dat", "wb");
fp2 = fopen ("file2.dat", "wb");
for(int i=0; i<N2/2; i++){
        fread(&input, sizeof(struct Node), 1, outfile);
        fwrite (&input, sizeof(struct Node), 1, fp1);
        c1++;
}
    while(fread(&input, sizeof(struct Node), 1, outfile)){
        fwrite (&input, sizeof(struct Node), 1, fp2);
        c2++;
}
    fclose(outfile);
    fclose(fp1);
    fclose(fp2);
    printf("\tfile1 contains %ld records\n\tfile2 contains %ld records\n",c1,c2);
//displayfile("file1.dat");
//displayfile("file2.dat");
clock_t t, t2;
t = clock();
sortfile("file1.dat");
    sortfile("file2.dat");
    //displayfile("file1.dat");
    //displayfile("file2.dat");
    c=merge("file1.dat","file2.dat");
    printf("\n\tAfter sorting and merging into file contains %ld records\n",c);
    t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf("\n\n\tsort operation took %f seconds\n", time_taken);
    //displayfile("file.dat");
t2 = clock();
search("file.dat",100000);
t2 = clock() - t2;
time_taken = ((double)t2)/CLOCKS_PER_SEC;
printf("\tsearch operation took %f seconds\n", time_taken);
    return 0;
}