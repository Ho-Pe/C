//
//  이름 : 쓰레드 공유변수 문맥교환
//  날짜 : 2019. 11. 14.
//  설명 : 다수의 쓰레드가 공통의 변수를 공유할 때
//        임계영역에서의 문맥교환의 문제점
//  last modified : 22/04/26
//  dev by Linux(Ubuntu)
//
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//  공유 변수
static volatile int counter = 0;

void *thread_one(void *arg){
    //  출력 및 카운트
    for(int i = 0; i<1000000; i++){
        counter += 1;
        printf("[%s] 100 usec\n", (char *)arg);
        usleep(100);
    }
    
    //  끝나면 출력
    printf("[%s] : done\n", (char *) arg);
    printf("counter : %d\n", counter);
    
    return NULL;
}

void *thread_two(void *arg){
    //  출력 및 카운트
    for(int i = 0; i<1000000; i++){
        counter += 1;
        printf("[%s] 50 usec\n", (char *)arg);
        usleep(50);
    }
    
    //  끝나면 출력
    printf("[%s] : done\n", (char *) arg);
    printf("counter : %d\n", counter);
    
    return NULL;
}

void *thread_three(void *arg){
    //  출력 및 카운트
    for(int i = 0; i<1000000; i++){
        counter += 1;
        printf("[%s] 30 usec\n", (char *)arg);
        usleep(30);
    }
    
    //  끝나면 출력
    printf("[%s] : done\n", (char *) arg);
    printf("counter : %d\n", counter);
    
    return NULL;
}

void *thread_four(void *arg){
    //  출력 및 카운트
    for(int i = 0; i<1000000; i++){
        counter += 1;
        printf("[%s] 30 usec\n", (char *)arg);
        usleep(30);
    }
    
    // 끝나면 출력
    printf("[%s] : done\n", (char *) arg);
    printf("counter : %d\n", counter);
    
    return NULL;
}

void *thread_five(void *arg){
    //  출력 및 카운트
    for(int i = 0; i<1000000; i++){
        counter += 1;
        printf("[%s] 10 usec\n", (char *)arg);
        usleep(10);
    }
    
    // 끝나면 출력
    printf("[%s] : done\n", (char *) arg);
    printf("counter : %d\n", counter);
    
    return NULL;
}

int main(int argc, const char *argv[]){
    pthread_t t1, t2, t3, t4, t5;
    
    printf("main : begin (counter = %d)\n", counter);
    
    //  쓰레드 생성
    pthread_create(&t1, NULL, thread_one, "A");
    pthread_create(&t2, NULL, thread_two, "B");
    pthread_create(&t3, NULL, thread_three, "C");
    pthread_create(&t4, NULL, thread_four, "D");
    pthread_create(&t5, NULL, thread_five, "E");
    
    //  쓰레드 대기
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    
    printf("main : done (counter = %d)\n", counter);
    
    return 0;
}
