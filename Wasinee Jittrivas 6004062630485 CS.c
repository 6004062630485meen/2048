#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>
#define P 8

typedef struct
{
    int x;
    int y;
}nole;


int sym[4][4]={{0,0,0,0},{0,0,0,0},{0,2,0,0},{0,0,0,0}};
int i,j;
int high;
int sum=0;
int k;
int win=0;

int START();
int RUN();
int MOVE_TheSame(char ch_move);
void MOVE_Zero(char ch_move);
void RANDOM(char ch_m1,int v);
void HighScore();
void CHECK();
void WIN();

int main()
{
    char move;
    int sum_sc;
    move='s';
    HighScore();
    START();

    //SHOW GAME 2048.
    againRUN:
    printf("\n\t\t\t\tPress W or w to move upwards.\n");
    printf("\t\t\t\tPress S or s to move downwards.\n");
    printf("\t\t\t\tPress A or a to move leftwards.\n");
    printf("\t\t\t\tPress D or d to move rightwards.\n\n\n");
    RANDOM(move,P);
    printf("\t\t\tHIGH SCORE: %d\n\n\t\t\tSCORE: %d",high,sum);
    RUN();

    if(win==2048){
        WIN();
    }
    CHECK();

    //INPUT AND CHECK DIRECTION.
    againDirection:
    printf("\n\n\n\t\t\tEnter Your Direction('w/a/s/d'): ");
    move=tolower(getche());
    if(move=='w'||move=='a'||move=='s'||move=='d'){
        MOVE_Zero(move);             //FUNCTION MOVE.
        sum_sc=MOVE_TheSame(move);
        sum+=sum_sc;
        MOVE_Zero(move);
        system("cls");     //Remove all displayed.
        goto againRUN;
    }
    else{
        printf("\n\t\t\t  Input is invalid\n");
        goto againDirection;
    }

}

//KEEP HIGH SCORE.
void HighScore()
{
    FILE *hi;
    int r_hi;
    if(high==0)
    {
        if((hi=fopen("HIGH SCORE.txt","r"))==NULL){
            printf("Error in open file.");
            exit(1);
        }
        else{
            fscanf(hi,"%d",&r_hi);
            high=r_hi;
        }
    }
    else if(sum>high)
    {
        if((hi=fopen("HIGH SCORE.txt","wb"))==NULL){
            printf("Error in open file.");
            exit(1);
        }
        else{
            high=sum;
            fprintf(hi,"%d",high);
        }
    }
    fclose(hi);
}

//SHOW TABLE AND OUTPUT OF ARRAY.
int RUN()
{
    printf("\n\t\t\t\t ___________________________");
    for(i=0;i<4;i++)
    {
        printf("\n\t\t\t\t|      |      |      |      |");
        printf("\n\t\t\t\t|");
        for(j=0;j<4;j++)
        {
            if(sym[i][j]==0){
                    printf("      |");
            }
            else{
                    printf(" %4d |",sym[i][j]);
            }
        }
        printf("\n\t\t\t\t|______|______|______|______|");
    }

    return 0;
}

//SHOW HOME.
int START()
{
    char n;
    FILE *hp,*top;
    char r_hp,r_top;


    //READ&PRINT File Header of GAME 2048
    if((top=fopen("TOP.txt","r"))==NULL)
    {
        printf("Error in open file.");
        exit(1);
    }
    else
    {
        while((r_top=getc(top))!=EOF)
        {
            printf("%c",r_top);
        }
    fclose(top);
    }


    //Input 1or2-->1.START GAME or 2.HOW TO PLAY
    again:
    fflush(stdin);
    printf("\n\n\t\t\t\t\t    1.) START GAME\n\t\t\t\t\t    2.) HOW TO PLAY\n\n");
    printf("\t\tEnter choice 1 or 2: ");
    scanf("%c",&n);

    //Check 1.START GAME or 2.HOW TO PLAY
    switch(n){
        case '1': system("cls");
                  return;
                  break;
        case '2': system("cls");
                  hp=fopen("HOW TO PLAY.txt","r");  //READ&PRINT FLIE HOW TO PLAY GAME
                  if(hp==NULL)
                  {
                      printf("Error in open file.");
                      exit(1);
                  }
                  else
                  {
                      while((r_hp=getc(hp))!=EOF)
                      {
                          printf("%c",r_hp);
                      }
                  }
                  fclose(hp);
                  goto again;  //ASK START GAME or HOW TO PLAY AGAIN.
                  break;
        default: printf("\t\t\tInput is invalid\n\n");
                 goto again;
    }

    return 0;
}


//MOVE: 'a'->MOVE LEFT, 'd'->MOVE RIGHT, 'w'->MOVE UP, 's'->MOVE DOWN.
//INCLUDE THE SAME VALUES.
int MOVE_TheSame(char ch_move)
{
    int sc=0;
    int num;

    //MOVE RIGHT.
    if(ch_move=='d'){
        for(i=0;i<4;i++){
            for(j=2;j>=0;j--){
                if(sym[i][j+1]==sym[i][j]){
                    if(j==2||j==0){
                        sym[i][j+1]=2*sym[i][j];
                        sym[i][j]=0;
                        num=sym[i][j+1];
                    }
                    if(j==1){
                        sym[i][2]=2*sym[i][1];
                        sym[i][1]=0;
                        num=sym[i][2];
                    }
                    if(num==2048){        //SUND VALUE TO FUNTION WIN.
                        win=2048;
                    }
                    sc+=num;
                }
            }
        }
    }

    //MOVE LEFT.
    else if(ch_move=='a'){
        for(i=0;i<4;i++){
            for(j=1;j<4;j++){
                if(sym[i][j]==sym[i][j-1]){
                    if(j==1||j==3){
                        sym[i][j-1]=2*sym[i][j];
                        sym[i][j]=0;
                        num=sym[i][j-1];
                    }
                    if(j==2){
                        sym[i][1]=2*sym[i][2];
                        sym[i][2]=0;
                        num=sym[i][1];
                    }
                    if(num==2048){
                        win=2048;
                    }
                    sc+=num;
                }
            }
        }
    }

    //MOVE UP.
    else if(ch_move=='w'){
        for(i=1;i<4;i++){
            for(j=0;j<4;j++){
                if(sym[i][j]==sym[i-1][j]){
                    if(i==1||i==3){
                        sym[i-1][j]=2*sym[i][j];
                        sym[i][j]=0;
                        num=sym[i-1][j];
                    }
                    if(i==2){
                        sym[1][j]=2*sym[2][j];
                        sym[2][j]=0;
                        num=sym[1][j];
                    }
                    if(num==2048){
                        win=2048;
                    }
                    sc+=num;
                }
            }
        }
    }

    //MOVE DOWN.
    else if(ch_move=='s'){
        for(i=2;i>=0;i--){
            for(j=0;j<4;j++){
                if(sym[i][j]==sym[i+1][j]){
                    if(i==2||i==0){
                        sym[i+1][j]=2*sym[i][j];
                        sym[i][j]=0;
                        num=sym[i+1][j];
                    }
                    if(i==1){
                        sym[2][j]=2*sym[1][j];
                        sym[1][j]=0;
                        num=sym[2][j];
                    }
                    if(num==2048){
                        win=2048;
                    }
                    sc+=num;
                }
            }
        }
    }

    return sc;     //SCORE
}


//GET RID OF ZERO.
void MOVE_Zero(char ch_move)
{
    //MOVE RIGHT.
    if(ch_move=='d'){
        for(i=0;i<4;i++){
            for(j=3;j>0;j--){
                if(sym[i][3]==0){
                    sym[i][3]=sym[i][2];
                    sym[i][2]=sym[i][1];
                    sym[i][1]=sym[i][0];
                    sym[i][0]=0;
                }
                if(sym[i][j]==0){
                    sym[i][j]=sym[i][j-1];
                    sym[i][j-1]=0;
                }
                if(sym[i][3]!=0&&sym[i][2]==0&&sym[i][1]!=0){
                    sym[i][2]=sym[i][1];
                    sym[i][1]=0;
                }
            }
        }
    }

    //MOVE LEFT.
    else if(ch_move=='a'){
        for(i=0;i<4;i++){
            for(j=0;j<3;j++){
                if(sym[i][0]==0){
                    sym[i][0]=sym[i][1];
                    sym[i][1]=sym[i][2];
                    sym[i][2]=sym[i][3];
                    sym[i][3]=0;
                }
                if(sym[i][j]==0){
                    sym[i][j]=sym[i][j+1];
                    sym[i][j+1]=0;
                }
                if(sym[i][0]!=0&&sym[i][1]==0&&sym[i][2]!=0){
                    sym[i][1]=sym[i][2];
                    sym[i][2]=0;
                }
            }
        }
    }

    //MOVE UP.
    else if(ch_move=='w'){
        for(i=0;i<3;i++){
            for(j=0;j<4;j++){
                if(sym[0][j]==0){
                    sym[0][j]=sym[1][j];
                    sym[1][j]=sym[2][j];
                    sym[2][j]=sym[3][j];
                    sym[3][j]=0;
                }
                if(sym[i][j]==0){
                    sym[i][j]=sym[i+1][j];
                    sym[i+1][j]=0;
                }
                if(sym[0][j]!=0&&sym[1][j]==0&&sym[2][j]!=0){
                    sym[1][j]=sym[2][j];
                    sym[2][j]=0;
                }
            }
        }
    }

    //MOVE DOWN.
    else if(ch_move=='s'){
        for(i=3;i>0;i--){
            for(j=0;j<4;j++){
                if(sym[3][j]==0){
                    sym[3][j]=sym[2][j];
                    sym[2][j]=sym[1][j];
                    sym[1][j]=sym[0][j];
                    sym[0][j]=0;
                }
                if(sym[i][j]==0){
                    sym[i][j]=sym[i-1][j];
                    sym[i-1][j]=0;
                }
                if(sym[3][j]!=0&&sym[2][j]==0&&sym[1][j]!=0){
                    sym[2][j]=sym[1][j];
                    sym[1][j]=0;
                }
            }
        }
    }

}


//RANDOM VERTEX FOR THE NUMBER 2 OR 4.
void RANDOM(char ch_m1,int v)
{
    nole n1[8],*n2;
    char fname[30];
    int u;
    FILE *fp1;
    if(ch_m1=='a'){
        strcpy(fname,"nole a.txt");
    }
    else if(ch_m1=='d'){
        strcpy(fname,"nole d.txt");
    }
    else if(ch_m1=='w'){
        strcpy(fname,"nole w.txt");
    }
    else if(ch_m1=='s'){
        strcpy(fname,"nole s.txt");
    }

    if((fp1=fopen(fname,"r"))!=NULL){
        for(i=0;i<v;i++){
            fscanf(fp1,"%d %d\n",&n1[i].x,&n1[i].y);
            //printf("%d %d\n",n1[i].x,n1[i].y);
        }
        fclose(fp1);

        k=v;
        AgainRandom:
        //printf("k=%d\n",k);
        srand(time(NULL));
        u=rand()%k;
        //printf("u=%d\n",u);

        i=0;
        while(i<=u){
            if(i==u){
                if(sym[n1[i].x][n1[i].y]==0){
                      do{
                          srand(time(NULL));
                          sym[n1[i].x][n1[i].y]=rand()%5;
                      }while(sym[n1[i].x][n1[i].y]==0||sym[n1[i].x][n1[i].y]==1||sym[n1[i].x][n1[i].y]==3);
                      //printf("sym[%d][%d]=%d",n1[i].x,n1[i].y,sym[n1[i].x][n1[i].y]);
                }
                else if(sym[n1[i].x][n1[i].y]!=0){

                      n1[i].x='\0';
                      n1[i].y='\0';
                      n2=&n1[i];
                      n1[i]=n1[k-1];
                      n1[k-1]=*n2;
                      k-=1;

                      //SHOW GAME OVER! WHEN THERE IS NO SPACE IN THE TABLE.
                      if(k==0){
                         printf("\t\t\tHIGH SCORE: %d\n\n\t\t\tSCORE: %d",high,sum);
                         RUN();
                         printf("\n\n\t\t\t\t   ======GAME OVER!======\n\n");
                         HighScore();
                         exit(1);
                      }
                      else{
                            goto AgainRandom;
                      }
                }
            }
            i++;
        }
    }
    else{
        printf("Error in open file.");
        exit(1);
    }
}


//CHECK AND SHOW GAME OVER!
void CHECK()
{
    int l=0,z=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(sym[i][j]!=0){
               l+=1;
            }
        }
    }
    if(l==16){
        for(i=0;i<4;i++){
            for(j=1;j<4;j++){
                if(sym[i][j]!=sym[i][j-1]){
                   z+=1;
                }
            }
        }
        for(j=0;j<4;j++){
            for(i=1;i<4;i++){
                if(sym[i][j]!=sym[i-1][j]){
                   z+=1;
                }
            }
        }
        if(z==24){
            printf("\n\n\t\t\t\t   ======GAME OVER!======\n\n");
            HighScore();
            exit(1);
        }
    }
}


//SHOW "YOU WIN" WHEN VARIABLE(WIN) IS 2048.
void WIN()
{
    printf("\n\n\t\t\t\t     ======YOU WIN======\n\n");
    HighScore();
    exit(1);
}
