<div align = left>
  
![콜로세움_검투사싸우는 사진](https://github.com/user-attachments/assets/e455c47f-424a-411b-acee-37826c93b247)



<br>

## 목적
- 객체지향과 디자인패턴을 의미있게 적용
- 원활환 협업을 위한 Wiki 작성된 깃 컨벤션 및 코드컨벤션 적용
- 템플릿을 활용하여 블루프린트, C++ 을 이용해 게임확장
- GameSession, RPC, Replecates를 이용하여 Network 환경조성 
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
- MultiPlayGame like HyperActionFight 
- Direction, Network, UI, Gameflow, Optimization : 지성현 /  <br>
- Character, Animation, SkillSystem : 정우영  /  <br>
- Character, Animation, SkillSystem : 정혜창 / [개발블로그](https://velog.io/@hch9097/posts)<br>
- GameMode, Network, GameSession, Gameflow  : 최원석 /  <br>
- UI, Weapon, Character, Movie, SkillSystem  : 한가윤 /  <br>
- UI, ShopSystem, EconomySystem  : 최세훈 /  <br>

<br>

## Project Part Directory And Main Features <br>
<details>
  <summary> Network GameSession </summary>
  
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

### Network GameSession
- C++ 기반의 플레이어 로직 설계
  - Enhanced Input System을 사용한 입력 액션
  - CharacterMovement Component을 사용한 캐릭터 로직 설계
  - Tick을 사용하지 않은 이벤트 기반의 플레이어 로직 구현
  - GameInstance와 연동한 레벨 전환시 플레이어 정보 저장/불러오기 기능
</details>

<details>
  <summary> Character </summary>
### Character      
</details>

<details>
  <summary> GameMode </summary> 
### GameMode
</details>

<details>
  <summary> Weapon </summary>
### Weapon
</details>

<details>
  <summary> Animation </summary>
### Animation
</details>

<details>
  <summary> Shop </summary>
### Shop
</details>

<details>
  <summary> UI </summary>
### UI
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

## Network GameSession
<details>
<summary>Network GameSession UML Diagram</summary>    
![GameModeUML](https://github.com/user-attachments/assets/4e7303c4-9e41-4588-89bf-7ade03a08a87)
</details>

## Character
<details>
<summary>Character UML Class Diagram</summary>
</details>

## GameMode
<details>
<summary>GameMode UML Class Diagram</summary>
</details>

## Weapon
<details>
<summary>Weapon UML Class Diagram</summary>
</details>

## Animation
<details>
<summary>Animation UML Class Diagram</summary>
</details>

## Shop
<details>
<summary>Shop UML Class Diagram</summary>
</details>

## UI
<details>
<summary>UI UML Class Diagram</summary>
</details>
