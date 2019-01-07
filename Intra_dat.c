#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 30 //Domainの数…じゃない。適切な数値を入れる。
#define LineMax 256

typedef struct P_Request_t{
    int Domain;
    int source;
    int destination;
    int top_slots;
}Path_Request_t;

typedef struct S_Request_t{
    int request_number;
    int source_Domain;
    int destination_Domain;
    int need_slots;
    Path_Request_t Use_Path[N];
    Path_Request_t Backup_Path[N];
}Sum_Request_t;
char substring(char *instr,int u,int v,char *outstr){
    char t[256];
    //printf("instr = %s\n",instr);
    //printf("outstr= %s\n",outstr);
    strncpy(t,instr + u,v);
    strncpy(outstr,instr + u ,v);
    t[v] ='\0';
    //printf("instr = %s\n",instr);
    //printf("outstr= %s\n",outstr);
    //printf("%s\n",t);
    return *t;
}
int domain_search(int i){
    if(i <= 3){
        return 1;
    }else if(i > 3 && i <= 7){
        return 2;
    }else if(i > 7 && i <= 10){
        return 3;
    }else if(i > 10 && i <= 15){
        return 4;
    }else if(i > 15 && i <= 19){
        return 5;
    }else if(i > 19 && i <= 23){
        return 6;
    }else{
        printf("ERROR! domain_search function.\n");
        exit(1);
    }
}


int main(int argc, char *argv[]){
    if(argc!=3){
        printf("引数エラー、プログラム名、datファイル、outファイル\n");
        exit(1);
    }
    //printf("1: %s\n2: %s\n3: %s\n",argv[0],argv[1],argv[2]);
    int i,j,k,m,n,request_num;
    char dat_Lines[256][30];
    char out_Lines[256][30];
    FILE *dat;
    FILE *out;
    FILE *domain_dat;
    char *datfile = argv[1];
    char *outfile = argv[2];
    char str[256];
    Sum_Request_t request[16];
    //怒濤の初期化
    for(i=0;i<16;i++){
        request[i].request_number = 0;
        request[i].source_Domain = 0;
        request[i].destination_Domain = 0;
        request[i].need_slots = 0;
        for(j=0;j<N;j++){
            request[i].Use_Path[j].Domain = 0;
            request[i].Use_Path[j].source = 0;
            request[i].Use_Path[j].destination = 0;
            request[i].Use_Path[j].top_slots = 0;
            request[i].Backup_Path[j].Domain = 0;
            request[i].Backup_Path[j].source = 0;
            request[i].Backup_Path[j].destination = 0;
            request[i].Backup_Path[j].top_slots = 0;
        }
    }
    //request = (Sum_Request_t*)malloc(15*sizeof(Sum_Request_t));
    //printf("1: %s\n2: %s\n3: %s\n",argv[0],datfile,outfile);
    /*
    for(i=0;i<256;i++){
    dat_Lines[i] = (char*)malloc(sizeof(char)*256);
    out_Lines[i] = (char*)malloc(sizeof(char)*256);
    }
    */

    for(int i=0;i<15;i++){
    request[i].request_number = i;
    }
 
    int inum;
    char cnum_1[32];
    char cnum_2[32];
    char cnum_3[32];
    char cnum_semi[32]=";";
    char cnum_dot[32]=".dat";
    //printf("%s\n%s\n",datfile,outfile);
    //ファイル読み込み↓
    
    dat = fopen(datfile,"r");
    
    if(dat == NULL){
        printf("ファイルを開けませんでした。\n");
        exit(1);
    }
    
    for(i=0;i<LineMax && fgets(dat_Lines[i],sizeof(dat_Lines[i]),dat)!=NULL;i++){
        //printf("Lines[%d]=%s",i,dat_Lines[i]);
    }
    
    out = fopen(outfile,"r");
    if(out == NULL){
        printf("ファイルを開けませんでした。\n");
        exit(1);
    }
    for(i=0;i<LineMax && fgets(out_Lines[i],sizeof(out_Lines[i]),out)!=NULL;i++){
        //printf("Lines[%d]=%s",i,out_Lines[i]);
    }
    fclose(out);
    
    fclose(dat);
    //ファイル読み込み↑
/*
    //printf("\n%c\n",out_Lines[4][0]);
    substring(out_Lines[4],0,1,cnum_1);
    //printf("%s\n",cnum_1);
    i = atoi(cnum_1);
    //printf("%d\n",i);
    request[0].request_number = i;
    substring(out_Lines[4],3,2,cnum_1);
    substring(out_Lines[4],5,2,cnum_2);
    
    i = atoi(cnum_1);
    j = atoi(cnum_2);
    request[0].Use_Path[0].source = i;
    printf("request[0].Use_Path[0].source = %d\n",request[0].Use_Path[0].source);
*/

i=0,j=0,k=0,m=0,request_num=0;
while(1){
    n=0;
    substring(out_Lines[m+4],0,2,cnum_1);
    //printf("cnum_1 = %s\n",cnum_1);
    if(strcmp(cnum_1,"\n")==0){
        break;
    }
    k = atoi(cnum_1);
    request_num = k;
    if(k != request[k].request_number) {
        request[k].request_number = k;
        }
    substring(out_Lines[m+4],16,2,cnum_1);
    k = atoi(cnum_1);
    //printf("m = %d, k_1 = %d, ",m+5,k);
    substring(out_Lines[m+4],3,2,cnum_1);
    substring(out_Lines[m+4],5,2,cnum_2);
    i = atoi(cnum_1);
    j = atoi(cnum_2);
    //printf("i = %d, j = %d, ",i,j);
    if(k == 1){
        while(1){
            if(request[request_num].Use_Path[n].Domain != 0){
                n = n + 1;
            }else{
                break;
            }
        }
            if(i == j && i != 0){
                request[request_num].Use_Path[n].Domain=i;
                substring(out_Lines[m+4],7,2,cnum_3);
                request[request_num].Use_Path[n].source = atoi(cnum_3);
                substring(out_Lines[m+4],9,2,cnum_3);
                request[request_num].Use_Path[n].destination = atoi(cnum_3);
                substring(out_Lines[m+4],11,2,cnum_3);
                request[request_num].Use_Path[n].top_slots = atoi(cnum_3);
                //printf("%d  ,%d,%d,%d,%d,%d,    Use_Path\n",request[request_num].request_number,request[request_num].Use_Path[n].Domain,request[request_num].Use_Path[n].Domain,request[request_num].Use_Path[n].source,request[request_num].Use_Path[n].destination,request[request_num].Use_Path[n].top_slots);
            }else{
                //printf("\n");
            }
        }else{
            while(1){
                if(request[request_num].Use_Path[n].Domain != 0){
                    n = n + 1;
                }else{
                    break;
                }
            }
        if(i == j && i != 0){
        request[request_num].Backup_Path[n].Domain=i;
        //printf("%s\n",out_Lines[m+4]);
        substring(out_Lines[m+4],7,2,cnum_3);
        request[request_num].Backup_Path[n].source = atoi(cnum_3);
        substring(out_Lines[m+4],9,2,cnum_3);
        request[request_num].Backup_Path[n].destination = atoi(cnum_3);
        substring(out_Lines[m+4],11,2,cnum_3);
        request[request_num].Backup_Path[n].top_slots = atoi(cnum_3);
        //printf("%d  ,%d,%d,%d,%d,%d,    Backup_Path\n",request[request_num].request_number,request[request_num].Backup_Path[n].Domain,request[request_num].Backup_Path[n].Domain,request[request_num].Backup_Path[n].source,request[request_num].Backup_Path[n].destination,request[request_num].Backup_Path[n].top_slots);
        }
        else{
            //printf("\n");
            }
    }
    m = m + 1;
}
    //ここまででoutファイルからのデータ入力が完了
    //ここから下でdatファイルからのデータ入力
    
    i=0,j=0,k=0,m=0,request_num=0;
   for(m=0;m<15;m++){
        substring(dat_Lines[m+121],0,2,cnum_1);
        //printf("%d ",atoi(cnum_1));        //ここできちんと要求1から15までを確認済
        substring(dat_Lines[m+121],2,3,cnum_2);
        //printf("%d\n",atoi(cnum_2));        //ここできちんと要求1から15までを確認済
        request[atoi(cnum_1)].source_Domain = domain_search(atoi(cnum_2));
        //printf("request[%d].source_domain = %d\n",atoi(cnum_1),request[atoi(cnum_1)].source_Domain);                      //ここで要求1～15までの発ドメインの入力を確認
    }
    for(m=0;m<15;m++){
        substring(dat_Lines[m+138],0,2,cnum_1);
        //printf("%d ",atoi(cnum_1));        //ここできちんと要求1から15までを確認済
        substring(dat_Lines[m+138],2,3,cnum_2);
        //printf("%d\n",atoi(cnum_2));        //ここできちんと要求1から15までを確認済
        request[atoi(cnum_1)].destination_Domain = domain_search(atoi(cnum_2));
        //printf("request[%d].destination_domain = %d\n",atoi(cnum_1),request[atoi(cnum_1)].destination_Domain);                      //ここで要求1～15までの発ドメインの入力を確認
    }
    for(m=0;m<15;m++){
        substring(dat_Lines[m+155],0,2,cnum_1);
        substring(dat_Lines[m+155],2,3,cnum_2);
        request[atoi(cnum_1)].need_slots = atoi(cnum_2);
    }

    //ここまででdatファイルからのデータ入力が完了
    //ここからdatファイルへの書き込み
    /*
    substring(outfile,0,2,cnum_1);
    printf("%s\n",cnum_1);
    sprintf(cnum_2,"%d",request[1].Use_Path[0].Domain);
    printf("%s\n",cnum_2);
    substring(datfile,1,4,cnum_3);
    strcat(cnum_1,datfile);
    strcat(cnum_1,cnum_2);
    strcat(cnum_1,cnum_3);
    printf("%s\n",cnum_1);
    */
   //ファイル名作成プロトタイプ

   //ドメイン1から作成していく。
   i=0,j=0,k=0,m=0,request_num=0;//回転用変数の初期化
   while(1){
       i = i + 1;
       m=0;
       memset(cnum_1,'\0',32);
       request_num = 0;
       if(i >= 7){                  //始めにドメインの数(=i)でブレイク条件
           break;
       }
       for(j = 0;j<16;j++){
           for(k=0;k<30;k++){
               if(request[j].Use_Path[k].Domain == i || request[j].Backup_Path[k].Domain == i){
                   if(request[j].Backup_Path[k].source >= 1 && request[j].Backup_Path[k].source <= 8 && request[j].need_slots > 0 && request[j].need_slots < 6){
                       m = m + 1;
                   }else if(request[j].Use_Path[k].source >= 1 && request[j].Use_Path[k].source <= 8 && request[j].need_slots > 0 && request[j].need_slots < 6){
                       m = m + 1;
                   }
               }
           }
       }
       //printf("m = %d\n",m);
       if(m >= 1){              //mはドメインiを要素に持っている要求の数
            substring(outfile,0,2,cnum_1);
            //printf("cnum_1 = %s\n",cnum_1);
            sprintf(cnum_2,"%d",i);
            //printf("%d\n",i);
            //printf("cnum_2 = %s\n",cnum_2);
            //substring(datfile,1,4,cnum_3);
            //*cnum_3 = '.dat';
            //printf("%s\n%s\n",datfile,cnum_3);
            strcat(cnum_1,datfile);
            strcat(cnum_1,cnum_2);
            strcat(cnum_1,cnum_dot);
            //printf("filename = %s\n",cnum_1);
       }
       dat = fopen(cnum_1,"a");
       if(i == 1 || i == 6){
           domain_dat = fopen("domain16.txt","r");
       }else if(i>1 && i<6){
           domain_dat = fopen("domain2345.txt","r");
       }
       fprintf(dat,"param R :=%d;\n",m);
       while(fgets(str,256,domain_dat) != NULL){
           fprintf(dat,"%s",str);
       }
       fprintf(dat,"param :s :=\n");
       for(j=0;j<16;j++){
           for(k=0;k<30;k++){
               if(request[j].Use_Path[k].Domain == i && request_num < m && request[j].Use_Path[k].source > 0 && request[j].Use_Path[k].source < 9 && request[j].need_slots > 0 && request[j].need_slots < 6){
                   //printf("%d = %d\n",i,request[j].Use_Path[k].Domain);
                   request_num = request_num + 1;
                   fprintf(dat,"%d %d\n",request_num,request[j].Use_Path[k].source);
                   //printf("request_num = %d\n",i,request[j].Use_Path[k].Domain);
               }else if(request[j].Backup_Path[k].Domain == i && request_num < m && request[j].Backup_Path[k].source > 0 && request[j].Backup_Path[k].source < 9 && request[j].need_slots > 0 && request[j].need_slots < 6){
                   //printf("%d = %d\n",i,request[j].Backup_Path[k].Domain);
                   request_num = request_num + 1;
                   fprintf(dat,"%d %d\n",request_num,request[j].Backup_Path[k].source);
               }
           }
       }
       fprintf(dat,";\n");
       request_num = 0;
       fprintf(dat,"param :d :=\n");
       for(j=0;j<16;j++){
           for(k=0;k<30;k++){
               if(request[j].Use_Path[k].Domain == i && request_num < m && request[j].Use_Path[k].source > 0 && request[j].Use_Path[k].source < 9 && request[j].need_slots > 0 && request[j].need_slots < 6){
                   request_num = request_num + 1;
                   fprintf(dat,"%d %d\n",request_num,request[j].Use_Path[k].destination);
               }else if(request[j].Backup_Path[k].Domain == i && request_num < m && request[j].Backup_Path[k].source > 0 && request[j].Backup_Path[k].source < 9 && request[j].need_slots > 0 && request[j].need_slots < 6){
                   request_num = request_num + 1;
                   fprintf(dat,"%d %d\n",request_num,request[j].Backup_Path[k].destination);
               }
           }
       }
       fprintf(dat,";\n");
       request_num = 0;
       fprintf(dat,"param :r :=\n");
       for(j=0;j<16;j++){
           for(k=0;k<30;k++){
               if(request[j].Use_Path[k].Domain == i && request_num < m && request[j].Use_Path[k].source > 0 && request[j].Use_Path[k].source < 9 && request[j].need_slots > 0 && request[j].need_slots < 6){
                   request_num = request_num + 1;
                   fprintf(dat,"%d %d\n",request_num,request[j].need_slots);
               }else if(request[j].Backup_Path[k].Domain == i && request_num < m && request[j].Backup_Path[k].source > 0 && request[j].Backup_Path[k].source < 9 && request[j].need_slots > 0 && request[j].need_slots < 6){
                   request_num = request_num + 1;
                   fprintf(dat,"%d %d\n",request_num,request[j].need_slots);
               }
           }
       }
       fprintf(dat,";\nend;");
   }
    return 0;
}
