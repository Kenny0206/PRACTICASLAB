#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 30

int dp[MAX][MAX][MAX];


bool Anagrama(const char *s1, const char *s2, int i1, int i2, int len) {
    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        count[s1[i1 + i] - 'a']++;
        count[s2[i2 + i] - 'a']--;
    }
    for (int i = 0; i < 26; i++)
        if (count[i] != 0)
            return false;
    return true;
}

bool Scramble(const char *s1, const char *s2, int i1, int i2, int len) {
    if (strncmp(s1 + i1, s2 + i2, len) == 0)
        return true;

    if (!Anagrama(s1, s2, i1, i2, len))
        return false;

    if (dp[i1][i2][len] != -1)
        return dp[i1][i2][len];

    for (int i = 1; i < len; i++) {
        
        if (Scramble(s1, s2, i1, i2, i) &&
            Scramble(s1, s2, i1 + i, i2 + i, len - i))
            return dp[i1][i2][len] = 1;

        if (Scramble(s1, s2, i1, i2 + len - i, i) &&
            Scramble(s1, s2, i1 + i, i2, len - i))
            return dp[i1][i2][len] = 1;
    }

    return dp[i1][i2][len] = 0;
}

bool isScramble(const char *s1, const char *s2) {
    int len = strlen(s1);
    if (len != strlen(s2))
        return false;

    memset(dp, -1, sizeof(dp));
    return Scramble(s1, s2, 0, 0, len);
}

int main() {
    char s1[MAX], s2[MAX];

    printf("Ingresa la primera cadena: ");
    scanf("%s", s1);
    printf("Ingresa la segunda cadena: ");
    scanf("%s", s2);

    if (isScramble(s1, s2))
        printf("Es Verdadeo \n", s2, s1);
    else
        printf("Es Falso \n", s2, s1);

    return 0;
}

