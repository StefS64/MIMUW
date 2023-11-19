#include <stdio.h>
#include <stdbool.h>

bool are_palindromes(char *s1, char *s2) {
   int digits = 10;
   int cnt[11];
   for (int i = 0; i < digits; i++) {
      cnt[i] = 0;
   }
   char *p = s1;
   while (*p != '\0') {
      cnt[*(p++) - '0']++;
   }
   p = s2;
   while (*p != '\0') {
      cnt[*(p++) - '0']--;
   }
   for (int i = 0; i < digits; i++) {
      if (cnt[i]) return false;
   }
   return true;
}
int main(){
   char a[3],b[3];
   int input = scanf(" %s %s", a, b);
   input++;
   printf("%s %s %d %d \n", a, b, input, are_palindromes(a,b));
}