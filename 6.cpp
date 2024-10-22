#include <stdio.h>
#include <stdlib.h>

int mod(int a, int m) {
    return (a % m + m) % m;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    a = mod(a, m);
    for (int x = 1; x < m; x++) {
        if (mod(a * x, m) == 1) {
            return x;
        }
    }
    return -1;  
}

void breakAffineCipher(char mostFreq1, char mostFreq2) {
    int P_B = mostFreq1 - 'A'; 
    int P_U = mostFreq2 - 'A'; 
    int P_E = 'E' - 'A';        
    int P_T = 'T' - 'A';  
    for (int a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1) { 
            int b1 = mod(P_E - mod(a * P_B, 26), 26); 
            int b2 = mod(P_T - mod(a * P_U, 26), 26); 

           
            if (b1 == b2) {
                printf("Possible key found: a = %d, b = %d\n", a, b1);
            }
        }
    }
}

int main() {
    char mostFrequent1 = 'B'; 
    char mostFrequent2 = 'U'; 

    breakAffineCipher(mostFrequent1, mostFrequent2);

    return 0;
}
