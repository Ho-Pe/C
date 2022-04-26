//
//  Name : 2생산자 1소비자 동기화
// 	Description : 2생산자 1소비자가 공유버퍼, 공유변수를 사용할 때 문제점 해결
//  Date : 2019. 11. 22.
//  last modified : 22/04/26
//  dev by Linux(Ubuntu)
//

#include <stdio.h>
#include <pthread.h>
#include <ctype.h>

pthread_cond_t empty, fill;
pthread_mutex_t mutex;

#define MAX 10
#define loops 51
#define MAXLOOPS 102

// 공유버퍼 및 공유변수
char buffer[MAX];
int count = 0, num1 = 0, num2 = 0;
char c = 'A';

//  A ~ Z 그리고 a ~ z 까지 버퍼에 넣는 함수
void put(){
    
    //  Z 부터 a까지 건너뛰기
    if(c=='Z')
        c+=7;
    
    buffer[num2] = c;
    num2++;
    c++;
    count++;
    
    if(num2==10)
        num2=0;
}

//  1 ~ 50 까지 버퍼에 넣는 함수
void put2(int value){
    buffer[num2] = value;
    num2++;
    count++;
    if(num2==10)
        num2=0;
}

//  화면에 출력하는 함수
void get(){
    
    if(isalpha(buffer[num1])==1)        //  문자인지 검사
        printf("%c\t", buffer[num1]);
    else                                //  아니면 숫자
        printf("%d\t", buffer[num1]);
    num1++;
    count --;
    if(num1==10){
        printf("\n");
        num1 = 0;
    }
}

//  쓰레드 1 : A ~ Z / a ~ z (생산자)
void *producer(void *arg){
    int i;

    for(i = 0; i<loops; i++){
        pthread_mutex_lock(&mutex);
        while(count==MAX)
            pthread_cond_wait(&empty, &mutex);
        put();
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

//  쓰레드 2 : 1 ~ 50 (생산자)
void *producer2(void *arg){
    int i;
    
    for(i = 0; i<loops; i++){
        pthread_mutex_lock(&mutex);
        while(count==MAX)
            pthread_cond_wait(&empty, &mutex);
        put2(i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

//  쓰레드 3 : 화면 출력 (소비자)
void *consumer(void *arg){
    int i;

    for(i = 0; i<MAXLOOPS; i++){
        pthread_mutex_lock(&mutex);
        while(count == 0 && i!=101)
            pthread_cond_wait(&fill, &mutex);
        get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    pthread_t p1, p2, c1;
    
    //  mutex, cond 초기화
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&fill, NULL);
    
    //  쓰레드 생성
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, producer2, NULL);
    pthread_create(&c1, NULL, consumer, NULL);
    
    //  쓰레드 대기
    pthread_join(c1, NULL);
    
    return 0;
}
