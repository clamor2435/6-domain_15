//random_node.c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CHARA 256 //1行の最大文字バイト数

//↓ここを変更
#define Node 22 //全ノード数
#define Slots 5 //最大要求スロット
//↑ここを変更

typedef struct {
    int array[Node];
} request_t;

void setnumber(request_t *,int);
void randomize(request_t *,int);
void printf_array(int,request_t *);

int main(int argc, char *argv[]){
    srand((unsigned)time(NULL));//時間による疑似乱数生成
    int number;
    int p;
    FILE *fp;
    if (argc != 2){//エラーメッセージ
        printf("Error! command -> ./random_node request\n");
        exit(0);
    }
    char *filename = "6-node_data.txt";//ファイル名
    char str[CHARA];
    number = atoi(argv[1]);//要求の数
    request_t *req_t;//要求の数だけ構造体
    req_t = (request_t*)malloc(number * sizeof(request_t));//ノード数分だけメモリ確保
    printf("param R := %d;\n",number);//リクエスト数出力
    fp = fopen(filename,"r");
    
    while(fgets(str,CHARA,fp) != NULL){
        printf("%s",str);
    }
    
    fclose(fp);
    
    for(int i = 0;i<number;i++){
    //setnumber(req_t[i]);
    randomize(req_t,i);
    }
    printf_array(number,req_t);
    printf(";\n");
    printf("param :r :=\n");
    for(p=0;p<number;p++){
        printf("%d %d \n",p+1,rand()%5+1);
    }
    printf(";\n");
    printf("end;");
    return 0;
}
void setnumber(request_t *a,int t){
    for(int i = 0;i < Node;i++){
        a[t].array[i] = i;
        //printf("%d\n",a.array[i]);
    }
}
void randomize(request_t *a,int num){
    int i = Node;
    for(int x = 1;x < Node+1;x++){
        a[num].array[x-1] = x;
        //printf("%d\n",a.array[i]);
    }
    //for(int j = 0;j<Node;j++){
    //    printf("%d\n",a[num].array[j]);
    //}
    while(i > 1){
        int j = rand() % Node ;
        i--;
        int t = a[num].array[i];
        a[num].array[i] = a[num].array[j];
        a[num].array[j] = t;
    }
    //for(int j = 0;j<Node;j++){
    //    printf("%d\n",a[num].array[j]);
    //}
}
void printf_array(int t,request_t *a){
    printf("param :s :=\n");//ソースノード
    for(int i = 0;i < t;i++){
        printf("%d %d \n",i+1,a[i].array[1]);
    }
    printf(";\n");
    printf("param :d :=\n");//デスティネーションノード
    for(int i=0;i<t;i++){
        printf("%d %d \n",i+1,a[i].array[2]);
    }
    return;
}
