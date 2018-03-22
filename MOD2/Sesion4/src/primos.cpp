
#include <iostream>
#include <cmath>

using namespace std;

bool esPrimo(unsigned int n){
  if(n==0 || n==1)
    return false;

  for(int i=2; i<=sqrt(n); i++)
    if(n%i == 0)
      return false;

  return true;
}

int main(){

  int inf, sup;

  cout << "\nIntroduce cota inferior del rango: ";
  do{
    cin >> inf;
  }while(inf<0);
  cout << "\nIntroduce cota superior del rango: ";
  do{
    cin >> sup;
  }while(sup<0);

  for(int i=inf; i<=sup; i++)
    if (esPrimo(i))
      cout << i << ", ";

  return 0;
}
