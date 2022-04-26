/* ==
* @brief 파일 진단 알고리즘
* @Description 재귀함수를 이용한 파일 검색 후 진단
* @reporting date 20/04/15
* @last modified 22/04/26 (주석 추가)
* @dev by Windows 10 (encoding : utf-8)
== */

#include <stdio.h> 
#include <dirent.h> // 디렉토리 관련 
#include <string.h> // 문자열 관련
#include <sys/stat.h> // 파일 정보 관련
#include <unistd.h> // 여러 자료형 관련

#define BUF_SIZE 1024

/* ==
* @brief 디렉토리 열어서 검색 후 진단(재귀함수)
* @param const char *$검색하고 싶은 파일 경로
* @return 0
== */
int research(const char *path){
// init line
	DIR *dr = NULL;
    struct dirent *de = NULL;
    struct stat fi;
    char fn[BUF_SIZE];
    char buf[BUF_SIZE];
    FILE *fp;
    
// 디렉토리 열기(pointer of DIR type)
    if((dr = opendir(path)) == NULL){
        printf("Could not open current directory" ); 
        return -1;
	}

// 디렉토리 읽기
	while((de = readdir(dr)) != NULL){
		// "." ".."은 정보를 읽지 않고 넘김
		if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		
		// 파일 경로 저장
		sprintf(fn, "%s/%s", path, de->d_name);
		
		// 파일 정보 저장(struct)
		if(stat(fn, &fi) == -1){
			continue;
		}
		
		// 파일인지 디렉토리인지 분류
		if(S_ISDIR(fi.st_mode)){
			re(fn); // 디렉토리면 재귀함수
		} else if(S_ISREG(fi.st_mode)){ // 파일일때
			printf("File Scannig : %s\n", fn);
			fp = fopen(fn, "rb"); // "바이너리 읽기"모드
			
			// 파일 열기 실패
			if(fp == NULL){
				perror("File open failed\n");
				exit(0);
			}
			
			// 파일 내용 읽어서 저장
			fread(buf, sizeof(buf), 1, fp);
			fclose(fp);
			
			// 준비한 값과 파일의 내용이 일치할 때
			if(!strncmp(buf, "X5O", 3)){
				printf("Malware Founded!!\n");
				chmod("malware/1.txt", 0777);
				printf("Complete!\n");
			}
		}
	}
 
	// 디렉토리 닫기
    closedir(dr);
    return 0; 
}

/* ==
* @mainpage
* @brief 파일 경로 설정 및 함수 동작
== */
int main(int argc, char *argv[]){
	char st[100] = "vac";
	
	research(st);
} 