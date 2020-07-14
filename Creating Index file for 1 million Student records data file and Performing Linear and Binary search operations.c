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
struct ind
{
    long int rollno, ofs;
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

void swap ( long int* a,long int* b )
{   long int t = *a;      *a = *b;       *b = t;
}

void swapi ( int* a, int* b )
{   int t = *a;      *a = *b;       *b = t;
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
            strcpy(n,i->branch);
            strcpy(i->branch,j->branch);
            strcpy(j->branch,n);
        }
    }
    i = (i == NULL)? l : i->next;
    swap(&(i->rollno), &(h->rollno));
    swapi(&(i->age), &(h->age));
    strcpy(n,i->nam);
    strcpy(i->nam,h->nam);
    strcpy(h->nam,n);
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
    quickSort(a);
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


void merge(char *file1,char *file2)
{
    int flg1=1,flg2=1;
    struct Node n1, n2;
    struct ind inde;
    FILE *fp,*fp1,*fp2,*index;
    fp1=fopen(file1,"rb");
    fp2=fopen(file2,"rb");
    fp=fopen("file.dat","wb");
    index=fopen("index.dat","wb");
    while (1){
        if (flg1) {
            if(!fread(&n1, sizeof(struct Node), 1, fp1)){
                inde.rollno=n2.rollno;
                inde.ofs=ftell(fp);
                fwrite(&inde, sizeof(struct ind), 1, index);
                fwrite(&n2, sizeof(struct Node), 1, fp);
                while(fread(&n2, sizeof(struct Node), 1, fp2)){
                    inde.rollno=n2.rollno;
                    inde.ofs=ftell(fp);
                    fwrite(&inde, sizeof(struct ind), 1, index);
                    fwrite(&n2, sizeof(struct Node), 1, fp);
                }
                break;
            }
        }

        if (flg2) {
            if(!fread(&n2, sizeof(struct Node), 1, fp2)){
                inde.rollno=n1.rollno;
                inde.ofs=ftell(fp);
                fwrite(&inde, sizeof(struct ind), 1, index);
                fwrite(&n1, sizeof(struct Node), 1, fp2);
                while(fread(&n1, sizeof(struct Node), 1, fp1)){
                    inde.rollno=n1.rollno;
                    inde.ofs=ftell(fp);
                    fwrite(&inde, sizeof(struct ind), 1, index);
                    fwrite(&n1, sizeof(struct Node), 1, fp);
                }
                break;
            }
        }


        if (n1.rollno > n2.rollno)  {
            flg1 = 0;
            flg2 = 1;
            inde.rollno=n2.rollno;
            inde.ofs=ftell(fp);
            fwrite(&inde, sizeof(struct ind), 1, index);
            fwrite(&n2, sizeof(struct Node), 1, fp);
        }else {
            flg1 = 1;
            flg2 = 0;
            inde.rollno=n1.rollno;
            inde.ofs=ftell(fp);
            fwrite(&inde, sizeof(struct ind), 1, index);
            fwrite(&n1, sizeof(struct Node), 1, fp);
        }
    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(index);
    remove(file1);
    remove(file2);

}


void search(char *f, long int rollno){
    FILE *fp, *fp1;
    fp=fopen(f, "rb");
    fp1=fopen("file.dat", "rb");
    struct Node input;
    struct ind inde;
    while(fread(&inde, sizeof(struct ind), 1, fp)){
        if(inde.rollno == rollno){
            fseek(fp1,inde.ofs,1);
            fread(&input, sizeof(struct Node),1,fp1);
            printf("\n\n\n\t%ld\t%s\t%s\t%d\n\n",input.rollno,input.nam,input.branch,input.age);
            return;
        }
}
printf("\n\n\n\tNot Found\n");
return ;
}



void binarysearch(char *f, long int x)
{
    FILE *fp, *fp1;
    fp=fopen(f, "rb");
    fp1=fopen("file.dat", "rb");
    struct Node input;
    struct ind inde;
    int s = sizeof(struct ind);
    fseek(fp, 0, SEEK_END);
    long int l = 0, r = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    while(l<=r) {
        //ll=l/s;rr=r/
        long int mid = (l/8+r/8)/2;
        mid*=s;
        //printf("%ld %ld %ld\n",l*s,r*8,mid);
        fseek(fp, mid, SEEK_SET);
        fread(&inde, sizeof(struct ind), 1, fp);
        if( inde.rollno==x) {
            fseek(fp1,inde.ofs,1);
            fread(&input, sizeof(struct Node),1,fp1);
            printf("\n\n\n\t%ld\t%s\t%s\t%d\n\n",input.rollno,input.nam,input.branch,input.age);
            return ;
        }else if( x < inde.rollno ) {
            r = mid-s;
        }else {
            l = mid+s;
        }
    }
    printf("\n\n\n\tNot Found\n");
return ;
}

int main(){
    long int len = N2-N1+1, i , r , temp;
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
FILE *outfile, *index;
outfile = fopen ("file.dat", "wb");
index = fopen ("index.dat", "wb");
struct Node input;
struct ind inde;
for(int i=0; i<N2; i++){
int r=ran[i];
int l = (rand() % (12 - 7 + 1)) + 7;
char *s=printRandomString(l);
input.rollno=num[i];
        strcpy(input.branch, branch[r]);
        strcpy(input.nam, s);
        input.age= (rand() % (21 - 18 + 1)) + 18;
        inde.rollno=num[i];
        inde.ofs=ftell(outfile);
fwrite (&input, sizeof(struct Node), 1, outfile);
fwrite (&inde, sizeof(struct ind), 1, index);
}
fclose (outfile);
fclose(index);
    outfile = fopen ("file.dat", "rb");
fseek(outfile, 0, SEEK_SET);
FILE *fp1, *fp2;
fp1 = fopen ("file1.dat", "wb");
fp2 = fopen ("file2.dat", "wb");
for(int i=0; i<N2/2; i++){
        fread(&input, sizeof(struct Node), 1, outfile);
        fwrite (&input, sizeof(struct Node), 1, fp1);
}
    while(fread(&input, sizeof(struct Node), 1, outfile)){
        fwrite (&input, sizeof(struct Node), 1, fp2);
}
    fclose(outfile);
    fclose(fp1);
    fclose(fp2);
sortfile("file1.dat");
    sortfile("file2.dat");
    merge("file1.dat","file2.dat");
while(1){
   long int x;
   int c;
   printf("Enter 1->Linear Search\n\t2->Binary Search\n\t0->Exit\n");
   scanf("%d",&c);
   if(c==0){
            break;
        }
   printf("Enter Number:");
        scanf("%ld",&x);
        clock_t t;
        if(c==1){
            t = clock();
            search("index.dat",x);
            t = clock() - t;
            double time_taken = ((double)t)/CLOCKS_PER_SEC;
            printf("\tLinear search operation took %f seconds\n", time_taken);
        }else{
            t = clock();
            binarysearch("index.dat",x);
            t = clock() - t;
            double time_taken = ((double)t)/CLOCKS_PER_SEC;
            printf("\tBinary search operation took %f seconds\n", time_taken);
        }
}
    return 0;
}
