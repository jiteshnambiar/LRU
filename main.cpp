#include <iostream>
#include <stdlib.h>
#include "shapes.h"
using std::cout;
using std::endl;


int main()
{
  tri1(6);
  cout << endl << "---------------------" << endl;
  tri2(6);
  cout << endl << "---------------------" << endl;
  trap(5,3);
  cout << endl << "---------------------" << endl;
  rect(6,5);  
  cout << endl << "---------------------" << endl;
  circle(5);  
  cout << endl << "---------------------" << endl;
  circle(8);  
  return 0;
}
