#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define N1 1
#define N2 1000000
#define MAX 26
long int N=N2;
struct Node
{
    long int rollno;
    char nam[15], branch[15];
int age;
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


void displayifile(char *f){
    FILE *fp = fopen(f, "rb");
fseek(fp, 0, SEEK_SET);
struct ind input;
while(fread(&input, sizeof(struct ind), 1, fp)){
        printf("\n\t%ld\t%ld",input.rollno,input.ofs);
}
fclose(fp);
}


void linearsearch(char *f, long int rollno)
{
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


int hashfunc(long int rollno){
    return rollno%20;
}

char *indfiles[20]={"file0.dat","file1.dat","file2.dat","file3.dat","file4.dat",
                "file5.dat","file6.dat","file7.dat","file8.dat","file9.dat",
                "file10.dat","file11.dat","file12.dat","file13.dat","file14.dat",
                "file15.dat","file16.dat","file17.dat","file18.dat","file19.dat"};


void search(long int rollno){
    linearsearch(indfiles[hashfunc(rollno)],rollno);
}

void add(){
    N++;
    struct Node input;
    struct ind inde;
    int a;
    long int r;
    char nam[15], bran[15];
    printf("Enter rollno name branch age: ");
    scanf("%ld %s %s %d",&r, nam, bran, &a);
    input.rollno=r;
    input.age=a;
    strcpy(input.branch,bran);
    strcpy(input.nam,nam);
    FILE *fp=fopen("file.dat", "ab");
    FILE *fp1=fopen(indfiles[hashfunc(r)],"ab");
    fseek(fp, 0, SEEK_END);
    inde.ofs=ftell(fp);
    fwrite (&input, sizeof(struct Node), 1, fp);
    inde.rollno=r;
    fwrite (&inde, sizeof(struct ind), 1, fp1);
    fclose(fp);
    fclose(fp1);
}

void rem(long int rollno){
    N--;
    FILE *fp=fopen("file.dat", "rb");
    FILE *fp1=fopen("filed.dat", "wb");
    struct Node input;
    while(fread(&input, sizeof(struct Node), 1, fp)){
        if(input.rollno==rollno){
            printf("\n\tRecord %ld deleted\n",rollno);
        }else{
            fwrite(&input, sizeof(struct Node), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    FILE *outfile, *index[20];
    outfile = fopen ("file1.dat", "rb");
struct ind inde;
    for(int i=0; i<20; i++){
        index[i] = fopen (indfiles[i], "wb");
fclose(index[i]);
}
    for(int i=0; i<20; i++){
        index[i] = fopen (indfiles[i], "ab");
}
fseek(outfile, 0, SEEK_SET);
for(int i=0; i<N; i++){
        inde.ofs=ftell(outfile);
fread(&input, sizeof(struct Node), 1, outfile);
        inde.rollno=input.rollno;
fwrite (&inde, sizeof(struct ind), 1, index[hashfunc(input.rollno)]);
}
fclose (outfile);
for(int i=0; i<20; i++){
fclose(index[i]);
}
remove("file.dat");
rename("file1.dat", "file.dat");

}
int main(){
    long int len = N2-N1+1, i , r , temp;
    long int *num, *ran;
    num = (long int*)malloc(len * sizeof(long int));
    ran = (long int*)malloc(len * sizeof(long int));
    FILE *outfile, *index[20];
    for(int i=0; i<20; i++){
        index[i] = fopen (indfiles[i], "wb");
fclose(index[i]);
}
    for(int i=0; i<20; i++){
        index[i] = fopen (indfiles[i], "ab");
}
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
outfile = fopen ("file.dat", "wb");
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
fwrite (&inde, sizeof(struct ind), 1, index[hashfunc(num[i])]);

}
fclose (outfile);
for(int i=0; i<20; i++){
fclose(index[i]);
}

while(1){
   long int x;
   int c;
   printf("Enter 1->Search\n\t2->Add\n\t3->Remove\n\t0->Exit\n");
   scanf("%d",&c);
   if(c==0){
            break;
        }
        if(c==1){
            printf("Enter Roll Number:");
            scanf("%ld",&x);
            struct timeval start, end;
            gettimeofday(&start, NULL);
            search(x);
            gettimeofday(&end, NULL);
            long seconds = (end.tv_sec - start.tv_sec);
            double nano = ((seconds * 1000) + end.tv_usec/1000) - (start.tv_usec/1000);
            printf("\tSearch operation took %lf nanoseconds\n", nano);
        }else if (c==2){
            struct timeval start, end;
            gettimeofday(&start, NULL);
            add();
            gettimeofday(&end, NULL);
            long seconds = (end.tv_sec - start.tv_sec);
            double nano = ((seconds * 1000) + end.tv_usec/1000)-(start.tv_usec/1000);
            printf("\tAdd operation took %lf milliseconds\n",nano);
        }else{
            printf("Enter Roll Number:");
            scanf("%ld",&x);
            struct timeval start, end;
            gettimeofday(&start, NULL);
            rem(x);
            gettimeofday(&end, NULL);
            long seconds = (end.tv_sec - start.tv_sec);
            double nano = ((seconds * 1000) + end.tv_usec/1000) - (start.tv_usec/1000);
            printf("\tRemove operation took %lf milliseconds\n", nano);
        }
}

    return 0;
}