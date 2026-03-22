# Lab 05 - File Copy with System Calls

## What I observed
- System call categories I learned:
1. Process control
2. File management
3. Device management
4. Information maintenance
5. Communications

- File copy flow I understood:
source file 열기 -> destination file 만들기/열기 -> 반복적으로 읽기 - 반복적으로 쓰기 - EOF 감지 - 에러 처리 -> 자원 정리
- `open` result: file descriptor(fd)라는 정수 번호를 받음 -> 파일 이름이 아니라 fd 번호로 read,write, close 진행
- `read` behavior: 파일에서 데이터를 메모리 버퍼로 읽어옴; 디스크/파일 쪽에서 프로그램 메모리 쪽으로 가져오는 동작
- `write` behavior: 메모리 버퍼에 있는 데이터를 fd가 가리키는 대상에 써 넣는 동작
- `close` behavior: 더 이상 안 쓸 파일 닫는 동작
- `strace` showed:
- Error case I tested:

## What I learned
- A file descriptor is: OS가 "열린 파일"을 프로세스 안에서 관리하기 위해 주는 작은 정수 핸들
- EOF means: End Of File
- Why `read()` and `write()` return values must be checked:
- Why one `write()` may not write everything: #partial write: 파이프, 소켓, 특수 상황에서 생기는 현상
- Why file copy is a good OS example: 겉으로는 간단하지만 OS service 사용의 표준 패턴을 알기 좋음

## Questions
-