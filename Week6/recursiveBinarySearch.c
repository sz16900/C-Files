#include <stdio.h>

int recBin(int k, int *a, int l, int r);
int main(void){

  int a[] = {4,7,19,25,36,37,50,100,101,205,220,271,301,321};

  if(recBin(101, a, 14) > 0){
    printf("Found it !\n");
  }
  else{
    printf("Not in list\n");
  }
  return 0;
}

int recBin(int k, int *a, int l, int r){

  int m;

  if( l > r){
    return -1;
  }
  m = (l + r) / 2;
  if(k == a[m]){
    return m;
  }
  else{
    if(k > a[m]){
      return recBin(k, a, m + l, r);
    }
    else{
      return recBin(k, a, l, m-1);

    }
  }

}
