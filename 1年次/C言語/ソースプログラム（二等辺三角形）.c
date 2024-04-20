#include <stdio.h>

int main() {
  int height; /* 三角形の高さ */
  int i, j;   /* ループ用変数 */

  printf("三角形の高さ：");
  scanf("%d", &height);
  for( i = 0; i < height; i++ ) {
    /* i行目は */
    /* 空白を(高さ-i-1)個描画する */
    for( j = 0; j < height-i-1; j++ ) {
      printf(" ");
    }
    /* *を(2*i+1)個描画する */
    for( j = 0; j < 2*i+1; j++ ) {
      printf("*");
    }
    /* 改行する */
    printf("\n");
  }
  return 0;
}

