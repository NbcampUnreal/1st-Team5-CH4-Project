<div align = left>
  
![콜로세움_검투사싸우는 사진](https://github.com/user-attachments/assets/e455c47f-424a-411b-acee-37826c93b247)



<br>

## 목적
- 객체지향과 디자인패턴을 의미있게 적용
- 원활환 협업을 위한 Wiki 작성된 깃 컨벤션 및 코드컨벤션 적용
- 템플릿을 활용하여 블루프린트, C++ 을 이용해 게임확장
- GameSession, RPC, Replecates를 이용하여 Multiplayer Game 환경조성 
- 멀티플레이 환경에서 작동하기 위해 게임 최적화 적용
- 유효성검사 및 로깅을 통한 유지보수성 및 안정성을 향상시킨 코드 및 블루프린트 작성

<br>

## 기술 스택
[![My Skills](https://skillicons.dev/icons?i=cpp,visualstudio,git,github,unreal,notion&theme=light)](https://skillicons.dev)

<br>

## 프로젝트 소개
### Project : Gladiators Fantasy <br>
### Duration : 2025.03.31 ~ 2025.04.18 <br>
### Project Convention <br>
- Code   : PascalCase
- Git    : Rebase And Merge
- Directory && Commit && Unreal
- Wiki https://github.com/NbcampUnreal/1st-Team5-CH4-Project

### Desctiption Part / Email or Blog Link <br>
- Multi Player  Rogue-Like
- Direction, Package, UI, Gameflow  :  /  <br>
- Character, Animation, SkillSystem : 정우영  /  <br>
- Character, Animation, SkillSystem : 정혜창 / [개발블로그](https://velog.io/@hch9097/posts)<br>
- GameMode, MultiplayEV, Package,   :  /  <br>
- UI, Weapon, Character, Movie      : 한가윤 /  <br>

## Project Part Directory And Main Features <br>
<details>
  <summary> Player </summary>
  
    | -- Source
      | -- Player
        | -- PlayerCharacter.h // 플레이어 캐릭터의 상태 및 무기 장착, 입력 처리
        | -- MyPlayerController.h // 플레이어 입력 및 마우스 감도 조정, UI 모드 전환 관리

    | -- Content
      | -- Blueprnits
        | -- ABP_PlayerCharacter // 플레이어 애니메이션 블루프린트, 1인칭 및 3인칭 애니메이션 관리

### Player
- C++ 기반의 플레이어 로직 설계
  - Enhanced Input System을 사용한 입력 액션
  - CharacterMovement Component을 사용한 캐릭터 로직 설계
  - Tick을 사용하지 않은 이벤트 기반의 플레이어 로직 구현
  - GameInstance와 연동한 레벨 전환시 플레이어 정보 저장/불러오기 기능

</details>

<details>
  <summary> Actor </summary>

    | -- Source
      | -- Actor
        | -- BulletPool // ObjectPooling 기법을 사용하여 BulletBase Class들을 재사용하는 최적화 구현
        | -- Bullet
          | -- BulletBase // Projectile 공통적인 기능을 구현한 AActor를 상속한 상위 클래스
          | -- BombBullet // Overlap시 범위 공격을 가하는 Bullet
          | -- NormalBullet // 기본적인 Bullet
          | -- PierceBullet // 특정 횟수만큼 Monster를 관통하는 Bullet
        | -- Trap
          | -- TrapBase // 함정 활성화, 충돌, 데미지 등의 공통 로직을 구현한 클래스
          | -- SpikeTrap // 특정 시간마다 돌출되는 바닥 설치형 함정
          | -- RollingTrap // 특정 시간마다 바닥으로 굴러오는 함정
          | -- ArrowTrap // MoveToActor를 활용한 유도형 함정
          | -- MovingSpotLight // 플레이어를 따라다니는 스포트라이트
          | -- SharkSpawner // Arrow형 Trap을 최적화를 위해 구현한 스포너
        | -- Weapon
          | -- CGunBase // Fire, Ovelap, Speed 무기 공통기능을 구현한 상위 클래스
          | -- Gun_Rifle // NoramlBullet를 발사하는 무기
          | -- Gun_Rocket // BombBullet를 발사하는 무기
          | -- Gun_Shotgun // NormalBullet를 동시에 Pellets수만큼 발사하는 무기
          | -- Gun_Sniper // PierceBullet를 발사하는 무기

### Actor 
 - BulletPool
   - ObjectPooling 기법을 사용한 Bullet 클래스 관련 재사용성 중심의 최적화 설계
 - Bullet && Weapon && Trap
   - 객체지향의 특징 다형성 및 추상화를 통한 높은응집도, 낮은 결합성, 확장성 향상
          
</details>

<details>
  <summary> GameMode </summary>

    | -- Source
      | -- GameMode
        | -- FPSGameMode  // 레벨 전환시마다 실행되는 로직 관리
        | -- FPSGameInstance  // 게임 종료시까지 유지되어야하는 데이터 관리
        | -- AIEnemySpawnObjectPool // ObjectPooling 기법을 사용한 AI Sapwn 재사용성 및 최적화 설계
        | -- SpawnVolume // WeaponDrop, EnemySpawn을 담당하는 C++ 기반의 스폰 불륨
        | -- TrapPortal  // 함정반 포탈 관련 클래스
          | -- TrapPortalPoint // TrapPortal의 위치생성기
          | -- TrapPortalAction // TrapPortal 의 Type을 지정해주는 EnumClass
          | -- TrapPortalType // TrapPortalPoint 의 Type을 지정해주는 EnumClass
        | -- ClearPortal // 클리어 포탈 관련 클래스
          | -- ClearPortalPoint // ClearPortal의 위치 생성기
        | -- DataTables   // 레벨 전환시마다 생성되는 Enemy, Instance에 저장할 데이터등 SRP를 지향한 데이터테이블
          | -- InitializeTable // ObjectPooling Initialize 를 위한 DataTable
          | -- GetPoolForStageTable // Satge마다 적 종류, 개체수를 저장한 DataTable
          | -- CardDataTable // 패시브카드의 타입, 레어도, 적용값을 저장한 DataTable
### GameMode
 - EnemyObjectPool
   - ObjectPooling 및 DataTable을 사용한 재사용성 및 최적화 기반의 설계
   - SpawnVolum을 활용하여 안전한 위치 생성, 에디터내 스폰 위치 변경
 - GameMode && GameInstance
   - 레벨 전환 시 런타임 환경에서 동적으로 생성하는 기능 구현 및 게임 진행시 영구적 데이터 관리
   - 공통 로직들을 함수화한 객체지향적 설계
   - 런타임 내 전체적인 GameFlow 관리
 - Portal
   - Overlap, Timer를 사용한 레벨 전환 설계
   - TargetPoint를 활용하여 에디터내 편리한 설계
   - EnumClass를 활용한 TrapPortal 클래스 재사용, 코드 간결화
</details>

<details>
  <summary> AI </summary>

    | -- Source
      | -- AI
        | -- AIController
          | -- BaseEnemyAIController // Perception, Pov, OnPossess등을 사용한 AI 행동 제어 관련 컨트롤러
          | -- BossAIController // BossEnemy만의 특정 로직을 추가한 AI 행동 제어 관련 컨트롤러
        | -- Enemy
          | -- BaseEnemy // AI관련 공통 로직을 구현한 상위 클래스
          | -- BossEnemy // BaseEnemy 기반의 하위 클래스, 보스 AI Character, 게임 클리어 조건
          | -- EliteMeleeEnemy // 특정 레벨마다 등장하는 근거리 공격 AI Character
          | -- EliteRangeEnemy // 특정 레벨마다 등장하는 원거리 공격 AI Character
          | -- NormalMeleeEnemy // 근거리 공격 AI Character
          | -- NormalRangeEnemy // 원거리 공격 AI Character
        | -- AnimNotify
          | -- AnimNotify_... // AI의 공격 관련 애니메이션 몽타주와 연동한 Notify 관련 설정
        | -- BT
          | -- BTT_... // BehaviorTree에 사용할 C++ 기반의 커스텀 Task 클래스
          | -- BTD_... // Task 노드 실행 조건을 결정하는 C++ 기반의 Decorator 클래스
        | -- Projectile
          | -- Projectiles... // 보스 및 원거리 공격 AI들이 사용할 Projectile 클래스

    | -- Content
      | -- Blueprint
        | -- AI
          | -- Enemy
            | -- BossEnemy
              | -- AI
                | -- EQS // 언리얼 엔진 내 EQS 시스템을 활용해 주변 환경 탐색 후 조건에 맞는 최적의 데이터 생성
        | -- Cinematic
          | -- Trigger Volume를 활용한 시네마틱 연출 구현

### AI
 - Enemy
   - BB/BT를 사용해, 현재 AI의 상태에 적합한 시퀀스를 선택해 자연스러운 행동을 실행하는 로직 구현
   - ABP, Montage Notify, 델리게이트를 사용해 애니메이션과 실제 공격 로직 연동
   - Aim Offset를 사용해 특정 Bone을 따라 Z축 Rotation을 변경, 더 정밀한 AI의 Range Attack 구현
   - Player Character의 현재 이동 방향과 속도를 고려한 예측 사격 구현
 - Cinematic
   - Trigger Volume 및 Level Blueprint를 활용한 시네마틱 연출 구현 
              
</details>

<details>
  <summary> UI </summary>

    | -- Source
      | -- Widgets
        | -- DataAssets
          | -- DataAsset/DataTable // DA/DT를 활용한 데이터 관리, SRP 원칙을 지향한 각각의 데이터 분리 및 불필요한 메모리 할당 방지
        | -- InGame
          | -- IngameMainWidget // MVVM패턴 기반의 VM을 담당하는 위젯 클래스. 델리게이트 기반의 이벤트 수신, View에게 데이터 전달
          | -- IngameMiniampWidget // 미니맵 관련 View 위젯
          | -- IngameMiniampIcon // 미니맵에 렌더링할 Icon관련 위젯
          | -- IngamePlayerStatus // 플레이어 체력, 실드, 텍스처등 관련된 View 위젯
          | -- IngameWeaponWidget // 장착중인 무기 관련 View 위젯
          | -- IngameCrossHairs // 플레이어 조준점 및 히트마커 관련 View 위젯
          | -- IngameTargetHUD // WidgetComponent에게 전송받은 데이터를 사용한 View 위젯. Enemy의 체력 관련 담당 위젯
          | -- IngameSelectWidget // SelectObjectBaseWidget 기반의 클래스들을 관리하는 VM 위젯 클래스
          | -- SelectObjectBaseWidget // 레벨업/레벨 클리어/상점 방문 등 공통 로직 및 프로퍼티들을 설정한 상위 클래스
          | -- CardWidget // 레벨업/레벨 클리어 경우 보여줄 능력치 강화 관련 위젯
        | -- Lobby
          | -- LobbyWidget // NativeOnKeyDown을 활용한 PressAnyKey 기능 구현, GameMode와 연동한 게임 시작시 레벨 변경 관리
        | -- Utility
          | -- MinimapTracker   // ActorComponent를 활용한 월드 배치 Monster 3D좌표를 Widget에게 전송하는 컴포넌트
          | -- MonsterWidgetComponent  // WidgetComponent를 활용한 Enemy의 현재 상태를 보여주는 HUD 관련 MVC기반의 Controller

    | -- Plugin
      | -- ASync Loading Screen Plugin
        | -- 비동기 로딩 스크린방식의 플러그인을 활용한 비동기 로딩 연출
        | -- 인트로 영상 기능 추가

### UI
 - UI
   - GameMode/Instance등과 유연한 연동을 하기위한 UUserWidget 기반의 C++ 생성, WBP 디자이너탭을 활용한 디자인
   - MVVM,MVC 패턴을 적용한 낮은결합성 및 확장성 보장
   - 객체지향 추상화 및 다형성을 적용한 특정 클래스 구조 설계
   - 특정 조건에 연출되는 2D Animation 구현
   - 델리게이트를 사용한 이벤트 기반의 로직, 옵저버 패턴 적용 및 최적화 설계
</details>


<br>

## 개발 환경 / 개발 도구
- C++ 17 (v14.38)
- MSVC v143
- Unreal Engine 5.5
- Visual Studio 2022
- Git LFS

<br>
</div>

## GameMode
<details>
<summary>GameMode UML Diagram</summary>  
  
![GameModeUML](https://github.com/user-attachments/assets/4e7303c4-9e41-4588-89bf-7ade03a08a87)

</details>

## Player

## AIMonster
<details>
<summary>Enemy AI UML Class Diagram</summary>
  
  ![Enemy AI](https://github.com/user-attachments/assets/9b2bd2c0-862f-47c0-8fb5-28ad9cb03b6c)

</details>

## Actor

## Object

## UI
<details>
<summary>InGame UI UML Class Diagram</summary>  

  ![다이어그램 인게임 UI](https://github.com/user-attachments/assets/05ae29ff-0989-4f0b-acd8-216f980428a6)

</details>
