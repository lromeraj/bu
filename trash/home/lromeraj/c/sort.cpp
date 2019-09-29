#include <iostream>
using namespace std;

#define MAX_N 3

int main() {

  int ns[MAX_N] = {}; //array that will contian the numbers

  for (int i=0; i<MAX_N;i++) { //request for the numbers
    printf("Enter number %d: ",i+1);
    scanf("%d",&ns[i]); //store ther value in the array
  }

  int a;

  for (int j=0; j<MAX_N; j++) { //run over ns

    for ( int k=j+1; k<MAX_N; k++) { //run from j+1 (we do not want to check the number with itself)

      if (ns[k] < ns[j]) { //check if any of the following values is lower than ns at j, so
        a = ns[j]; //store temp value of ns at j
        ns[j] = ns[k]; //now we store the lowest found value in ns at j
        ns[k] = a; //we need to restore value of ns at j that is was stored in var a
      }

    }

  }

  for (int i=0; i<MAX_N; i++) {
    printf("%d ",ns[i]);
  }

  printf("\n");

  return 0;
}

/* Full explanation
If our array is {5,8,3} ...

First bucle will run over each number of the array
Lets check the first iteration:

  {5, 8,3}
   ^
  the value of j will be 0, so we are looking for the number 5

  now we have a nested loop, and we start at the value of j+1, k will be 1,
  so we are goint to check all the numbers inside the ns array from k=1, there are {8,3}
  Thus we compare each of the avobe numbers with the current number that it is 5,
  who of {8,3} are lower than 5? Obviusly it is the number 3, so:

  a = ns[j]; => a = 5
  ns[j] = ns[k]; => ns[0] = 3
  ns[k] = a; => ns[1] = 5

  So our array after the first iteration looks like this {3,8,5}


*/
