//
//  Name : RSA module
//  Date : 2019. 10. 04.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CIPHER 20

//  함수 선언
int get_public_key(int tot);
int get_private_key(int e, int tot);
int gcd(int p, int q);
int *encryption(int e, int n, char *m);
char *decryption(int d, int n, int *cipher);
void reset_m(char *m);
void reset_cipher(int *cipher);

int main(int argc, const char *argv[]) {
    //  2개의 소수
    int p=13, q=23;
    int n=0, totient=0, e=0, d=0;
    char *m = malloc(sizeof(char) *CIPHER);
    int *cipher = malloc(sizeof(int) *CIPHER);
    char *plain = malloc(sizeof(char) *CIPHER);
    
    printf("Two Prime Number : %d and %d\n", p, q);
    
    //  암호화할 메세지 입력
    printf("Enter the plaintext : ");
    reset_m(m);
    scanf("%[^\n]s", m);
    
    //  두 키의 소수 구하기
    n = p * q;
    printf("n = p * q = %d * %d = %d\n", p, q, n);
    
    //  오일러 함수 값 구하기
    totient = (p-1)*(q-1);
    printf("totient = (p-1) * (q-1) = (%d-1) * (%d-1) = %d\n", p, q, totient);
    
    //  Public Key 구하기
    e=get_public_key(totient);
    printf("public key = (%d, %d)\n", n, e);
    
    //  Private Key 구하기
    d = get_private_key(e, totient);
    printf("private key = (%d, %d)\n", n, d);
    
    //  암호화
    reset_cipher(cipher);
    cipher = encryption(e, n, m);
    for(int i = 0; i<CIPHER; i++){
        if(cipher[i]==0)
            break;
        printf("%d", cipher[i]);
    }
    printf("\n");
    
    //  복호화
    plain = decryption(d, n, cipher);
    printf("%s\n", plain);
    
    return 0;
}

//  gcd 연산 함수
int gcd(int p, int q){
    if(q==0)
        return p;
    else
        return gcd(q, p % q);
}

//  공개키
int get_public_key(int tot){
    int e=2;
    
    do{
        e += 1;
    }while(e<tot && (gcd(e, tot)!=1));
    
    return e;
}

//  개인키
int get_private_key(int e, int tot){
    int k = 1;
    
    do{
        k += 1;
    }while((e*k)%tot != 1 || k==e);
    
    return k;
}

//  암호화
int *encryption(int e, int n, char *m){
    int i=0, j=0;
    static int cipher[CIPHER] = {0};
    static int cp_cipher[CIPHER] = {0};
    
    for(i = 0; i<CIPHER; i++)
        cipher[i] = (int) m[i];
    
    memcpy(cp_cipher, cipher, sizeof(cipher));
    
    for(i = 0; i<CIPHER; i++){
        if(cipher[i]==0)
            break;
        for(j = 0; j<e-1; j++)
            cipher[i] = cipher[i] * cp_cipher[i] % n;
    }
    return cipher;
}

//  복호화
char *decryption(int d, int n, int *cipher){
    int i=0, j=0;
    static int plain[CIPHER] = {0};
    static int pl_plain[CIPHER] = {0};
    static char plaintext[CIPHER] = {0};
    
    for(i = 0; i<CIPHER; i++)
        plain[i] = cipher[i];
    
    memcpy(pl_plain, plain, sizeof(plain));
    
    for(i = 0; i<CIPHER; i++){
        if(plain[i]==0)
            break;
        for(j = 0; j<d-1; j++)
            plain[i] = plain[i] * pl_plain[i] % n;
    }
    
    for(i = 0; i<CIPHER; i++)
        plaintext[i] = (char) plain[i];
    
    return plaintext;
}

//  포인터 초기화
void reset_m(char *m){
    int i=0;
    
    for(i=0; i<CIPHER; i++)
        m[i] = 0;
}

//  포인터 초기화
void reset_cipher(int *cipher){
    int i=0;
    
    for(i=0; i<CIPHER; i++)
        cipher[i] = 0;
}
