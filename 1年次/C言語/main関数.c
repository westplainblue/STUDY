#include <stdio.h>
#include "myHeader.h"

int main() {
  double x, y;
  double answerAdd, answerSubtract, answerMultiply, answerDivide;

  printf("一番目の数：");
  scanf("%lf", &x);
  printf("二番目の数：");
  scanf("%lf", &y);
  answerAdd = add(x, y);
  answerSubtract = subtract(x, y);
  answerMultiply = multiply(x, y);
  if( y != 0.0 ) {
    answerDivide = divide(x, y);
    printf("和：%f, 差：%f, 積：%f, 商：%f\n", answerAdd, answerSubtract, answerMultiply, answerDivide);
  } else {
    printf("和：%f, 差：%f, 積：%f\n", answerAdd, answerSubtract, answerMultiply);
    printf("割算は、二番目の数が0の為出来ません。\n");
  }
  return 0;
}

