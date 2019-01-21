# 간단한 슈팅 게임 (절차지향)
## 📢 개요
 ``절차적(procedural) 프로그래밍``이 순차적 프로그래밍과 혼동하는 경우가 있다.
 절차지향 프로그래밍에서 'Procedural'은 단어 그대로 '절차지향'을 의미하는 것이 아니라 프로시저 호출(procedure call)을 의미한다.
 여기서 프로시저란 반환값이 없는 함수라고 보면 된다.
  
## 💻 슈팅 게임
 캐릭터를 방향키로 움직이고 스페이스바로 투사체를 발사하여 적을 섬멸

  ![capture](https://github.com/kbm0996/SimpleShootingGame-Procedural-/blob/master/GIF.gif?raw=true)
  
  **figure 1. Shooting Game(animated)*


## 📐 워크플로우

  ![workflow](https://github.com/kbm0996/SimpleShootingGame-Procedural-/blob/master/flowchart.jpg?raw=true)
  
  **figure 2. Workflow*
  
## 📑 구성
### 📋 _main.cpp
  프로그램이 실행되는 메인 함수
  
### 📋 Draw.h - Draw.cpp
  Player, Enemy, Boss, Bullet, Scene등을 Buffer에 반영
  
### 📋 Logic.h - Logic.cpp
  Player와 Enemy, Boss, Bullet의 행동을 실행시키고 Scene의 특수효과 등을 정의
  
### 📋 KeyProcess.h - KeyProcess.cpp
  키보드 조작을 Queue에 push
  
### 📋 Console.h - Console.cpp
  Buffer를 Console에 출력
  
### 📋 Queue.h - Queue.cpp
  매우 간단한 Queue. 키 입력에 사용
