#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
void pBlue(string str){
  cout << "\033[1;34m"<<str<<"\033[0m";
}
void pGreen(string str){
  cout << "\033[1;32m"<<str<<"\033[0m";
}
void pGreen(int i){
  cout << "\033[1;32m"<<i<<"\033[0m";
}
void pRed(string str){
  cout << "\033[1;31m"<<str<<"\033[0m";
}
void clear(){
  system("CLS");
}
void pTable(int a[9][9] , bool b[9][9]){
  clear();
  pBlue("\n+");
  for (int j=0 ; j<9 ; j++){
    pBlue("---+");
  }
  for (int i=0 ; i<9 ; i++){
    pBlue("\n|");
    for (int j=0 ; j<9 ; j++){
      if (b[i][j]){
        cout<<" ";
        if (a[i][j] == 0){
          cout<<" ";
        }
        else{
            pGreen(a[i][j]);
        }
        cout<<" ";
      }
      else{
        if (a[i][j] == 0){
          cout<<"   ";
        }
        else{
          cout<<" "<<a[i][j]<<" ";
        }
      }
      if ((j+1) % 3 == 0){
        pBlue("|");
      }
      else{
        cout<<"|";
      }
    }

    pBlue("\n+");
    for (int j=0 ; j<9 ; j++){
      if ((i+1) % 3 == 0){
        pBlue("---+");
      }
      else{
        cout<<"---";
        if ((j+1) % 3 == 0){
          pBlue("+");
        }
        else{
          cout<<"+";
        }
      }
    }
  }
}
int r9(){
  return rand()%9 + 1;
}
bool rules(int a[9][9] , int x , int y , int v){
  for (int i=0 ; i<9 ; i++){
    // col
    if ( (i!=y) && (v==a[x][i]) ){
      return false;
    }
    // row
    if ( (i!=x) && (v==a[i][y]) ){
      return false;
    }
  }
  // sq 3 x 3
  int ii = x - (x % 3);
  int jj = y - (y % 3);
  for (int i=ii ; i<ii+3 ; i++){
    for (int j=jj ; j<jj+3 ; j++){
      if ( !(i==x && j==y) && (v==a[i][j]) ){
        return false;
      }
    }
  }
  return true;
}
void init(int a[9][9] , bool b[9][9]){
  for (int i=0 ; i<9 ; i++){
    for (int j=0 ; j<9 ; j++){
      a[i][j] = 0;
      b[i][j] = false;
    }
  }
}
void rSudoku(int a[9][9] , bool b[9][9]){
  init(a , b);
  int r , temp , eror;
  for (int i=0 ; i<9 ; i++){
    for (int j=0 ; j<9 ; j++){
      r = rand() % 10 + 1;
      eror = 0;
      if (r <= 4){
        do{
          temp = r9();
          eror++;
          if (eror == 20){
            rSudoku(a , b);
            return;
          }
        }while(!rules(a , i , j , temp));
        a[i][j] = temp;
        b[i][j] = true;
      }
    }
  }
}
bool end(int a[9][9] , bool b[9][9]){
  for (int i=0 ; i<9 ; i++){
    for (int j=0 ; j<9 ; j++){
      if (a[i][j] == 0){
        return false;
      }
    }
  }

  for (int i=0 ; i<9 ; i++){
    for (int j=0 ; j<9 ; j++){
      if (!b[i][j]){
        if (!rules(a , i , j , a[i][j])){
          return false;
        }
      }
    }
  }

  return true;
}

int main(){
  srand(time(0));
  int a[9][9] , x , y , v;
  bool b[9][9];
  rSudoku(a , b);
  do{
    do{
      pTable(a , b);
      pRed("\t \' x \>\> y \>\> value \' : ");
      cin>>x>>y>>v;
    }while( !( (x==10 && y==10 && v==10) || ( (0<=x && x<=8)&&(0<=y && y<=8)&&(0<=v && v<=9) ) ));
    if (b[x][y]){
      continue;
    }
    if (x==10){
      pRed("\n\n Exit...");
      return 0;
    }
    a[x][y] = v;
  }while(!end(a , b));
  pGreen("\n\n You win...");
  return 0;
}