# CLIENT-EMBED 파트

## 기능

- CCTV와 같이 WebRTC가 지원되지 않는 디바이스들에서 추출한 미디어 스트림을 WebRTC를 지원하는 클라이언트로 보낸다.

### 구현

- C++로 코드를 짰으며,

### 실행방식

1. 'main' 응용프로그램을 실행시키려는 컴퓨터에 boost와 opencv 라이브러리를 설치한다.

- mac 기준 homebrew를 통해 설치한다.

```bash
brew install boost

brew install opencv
```

- ./main 프로그램을 실행시키기 위해서는 다음의 경로에 boost와 opencv 라이브러리가 설치 되어 있어야 한다.

```bash
# opencv 설치 경로
/opt/homebrew/Cellar/opencv

# boost 설치 경로
/opt/homebrew/Cellar/boost
```

2. 터미널에서 응용 프로그램을 실행한다.

- WebRTC Client 와의 연결을 위해서는 CLIENT-SERVER 리포지토리에 있는 코드가 동작중인 IP 주소와 Port 번호를 입력해야 한다.

- 이를 위해서는 CLIENT-SERVER 리포지토리의 코드를 실행 시킨 뒤, IP주소와 Port 번호를 콘솔 창이나, localhost:3000으로 접속하여 알아내어야 한다.

```bash
./main IP주소 Port번호

# 예 : ./main 192.0.0.1 3001
```

## 개선이 필요한 지점

- main.cpp 프로그램이 include 하고 있는 boost, opencv 라이브러리의 위치를 동일 디렉터리 내의 boost, opencv 폴더로 지정하여 컴파일하여, 어떤 컴퓨터에서 실행시키더라도 추가적인 라이브러리 설치를 필요로 하지 않게끔 구현하지는 못하였다.
