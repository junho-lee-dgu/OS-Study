### 실습 목표
- `pipe()`를 이용해 부모-자식 간 message passing 관찰
- shared variable 없이 데이터 전달 확인
- blocking read 감각 확인

### 관찰 결과
- 부모가 `write()`로 문자열 전송
- 자식이 `read()`로 문자열 수신
- 부모/자식은 같은 메모리를 직접 공유하지 않았음
- parent sleep 추가 시 child가 먼저 read에서 대기하는 현상 확인

### 해석
- `pipe`는 OS가 제공하는 로컬 IPC 메커니즘
- message passing의 구체적 구현으로 이해 가능
- `read()`는 데이터가 없으면 blocking될 수 있음
- 사용하지 않는 pipe end를 닫는 것이 중요함

---

## 6-5. `assets/`에 저장할 캡처
이번 실습에서 최소 2장 권장:

- `01_pipe_demo_basic.png`
- `02_pipe_demo_blocking_read.png`

### `assets/README.md`
```md
# Assets Guide

- `01_pipe_demo_basic.png`
  - 기본 실행 결과
  - parent write / child read 흐름 확인

- `02_pipe_demo_blocking_read.png`
  - parent에 sleep 추가 후 실행 결과
  - child가 read에서 대기하다가 데이터 도착 후 복귀하는 blocking 관찰