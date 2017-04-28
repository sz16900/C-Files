#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr[20][20]={
    {2,5,8},
    {4,3,1,},
    {0,6,7}
};

int moveX[20]={1,1,1,0,0,-1,-1,-1};
int moveY[20]={0,1,-1,1,-1,0,1,-1};
int depth=0;

int findRow(){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(arr[i][j]==0){
                return i;
            }
        }
    }
}

int findCol(){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(arr[i][j]==0){
                return j;
            }
        }
    }
}

void print(){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%i ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isReady(){
    if(arr[0][0]==1 && arr[0][1]==2 && arr[0][2]==3 &&
            arr[1][0]==4 && arr[1][1]==5 && arr[1][2]==6 &&
            arr[2][0]==7 && arr[2][1]==8){
        return 1;
    }
    else return 0;
}

void perm(int row,int col,int n){

    int i=0;int diffX,diffY,temp;
    int r=findRow();
    int c=findCol();
    temp=arr[r][c];
    arr[r][c]=arr[row][col];
    arr[row][col]=temp;
    if(n>=9){
        print();
        if(isReady())
            printf("Finished");
        depth++;

        return;
    }

    for(i=0;i<8;i++){
        diffX=row+moveX[i];
        diffY=col+moveY[i];
        if(diffX>=0 && diffX<3 && diffY>=0 && diffY<3){
            perm(diffX,diffY,n+1);
        }
    }
    temp=arr[r][c];
    arr[r][c]=arr[row][col];
    arr[row][col]=temp;
}

int main()
{
    perm(1,1,0);
    return 0;
}
