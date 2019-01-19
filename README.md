# 간단한 슈팅 게임 (절차지향)
## 📢 개요
 ``절차적(procedural) 프로그래밍``이 순차적 프로그래밍과 혼동하는 경우가 있다.
 절차지향 프로그래밍에서 'Procedural'은 단어 그대로 '절차지향'을 의미하는 것이 아니라 프로시저 호출(procedure call)을 의미한다.
 여기서 프로시저란 반환값이 없는 함수라고 보면 된다.
  
## 💻 슈팅게임
 간단한 오목 게임. _config.h의 define들을 변경하면 말(piece)의 모양, 판(map)의 넓이 등을 변경할 수 있다.
커서의 위치는 방향키를 입력하여 제어 가능하며, 엔터 입력 시 말(piece)을 놓음과 동시에 상대방에게 차례(turn)을 넘긴다.

  ![capture](https://github.com/kbm0996/Procedural-Code-Example/blob/master/capture.jpg?raw=true)
  
  **figure 1. Gomoku*

  ○ - Player1
  ● - Player2
  ◎ - Cursor


## 📐 워크플로우
 객체지향형 프로그램의 구조와 작동 순서

  ![workflow](https://github.com/kbm0996/Procedural-Code-Example/blob/master/workflow.JPG?raw=true)
  
  **figure 2. Workflow*
  
## 📑 구성
### 📋 Hashtable.h - Hashtable.cpp
  해시테이블(Hashtable) 클래스의 선언부와 정의부
  
  
### 📋 SinglyLinkedlist.h
  해시테이블 클래스의 내부 클래스인 버킷(Bucket) 클래스 구현에 필요한 링크드 리스트 선언 및 정의


### 📋 Config.h
  해시테이블 내 버킷 개수와 입력할 수 있는 문자열의 최대 길이를 하드코딩으로 지정
  
  

## 📌 주요 소스
### 📋 Hashtable.h/cpp
    class Hashtable
    {
    protected:
      struct stSLOT
      {
        char chKey[df_LEN_MAX];	// ID
        char chValue[df_LEN_MAX];	// NAME
      };

      class Bucket : protected Linkedlist<stSLOT*>
      {
      public:
        Bucket() {}
        virtual ~Bucket() {}

        bool Insert(char* chKey, char* chValue);
        bool Delete(char* chKey);

        void Print();
        bool SearchKey(char* chKey, stSLOT * chOutAccount = nullptr);  // Key로 Value 검색
        bool SearchValue(char* chValue, stSLOT * chOutAccount = nullptr); // Value로 Key 검색

      private:
        friend class Hashtable;
        // TODO: ID의 ASCII의 총합을 시드값으로 사용. 출력값을 리스트의 인덱스로 사용
        static void Hashing(char* szString, int *OutHashCode);
      };

    public:
      Hashtable(int iHashTable_Cnt = df_BUCKET_CNT);
      virtual ~Hashtable();

      bool Insert(char* szInID, char* szInName);
      bool Delete(char* szInID);
      // Hashtable 내 모든 Bucket에 있는 Slot의 Data를 콘솔창에 출력
      void Print();
      bool Search(char* szInID);

    private:
      int _iHashTable_Cnt;
      Bucket* _pBucket[df_BUCKET_CNT];

    };



### 📋 SinglyLinkedlist.h
  편의상 싱글 링크드리스트를 사용함. 이미 검증된 STL의 list를 사용해도 됨.


 ## 📌 출처 
 
 개요 - https://coding-factory.tistory.com
