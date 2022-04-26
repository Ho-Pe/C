/* ==
* @brief 파일 검색 알고리즘
* @Description 재귀함수를 이용한 파일 검색 알고리즘
* @reporting date 20/04/15
* @last modified 22/04/26 (주석 추가)
* @dev by Windows 10 (encoding : utf-8)
== */

#include <stdio.h> 
#include <dirent.h> // 디렉토리
#include <string.h> // 문자열
#include <sys/stat.h> // 파일 정보 읽기


/* ==
* @brief 디렉토리를 열어 파일을 검색(재귀함수)
* @param const char *$검색하고 싶은 파일 경로
* @return 0
== */
int research(const char *path){
// init line
	DIR *dr = NULL; 
    struct dirent *de = NULL;
    struct stat buf;
    char fn[1024];

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
		printf("%s\n", fn);
		
		// 파일 정보 저장(struct)
		if(stat(fn, &buf) == -1){
			continue;
		}
		
		// 파일인지 디렉토리인지 분류
		if(S_ISDIR(buf.st_mode)){
		//	Debug : printf("%s\n", fn);
			re(fn); // 디렉토리면 재귀함수
		} else if(S_ISREG(buf.st_mode)){ // 파일일때
		//	Debug : (printf("%s\n", fn);
		}
	}
  
    closedir(dr); // 디렉토리 닫기
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