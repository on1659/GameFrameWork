# DX12 GameFrameWork

DirectX 12 기반 게임 렌더링 프레임워크. Geometry Shader를 활용한 큐브 데모 포함.

## 빌드 환경

- **IDE**: Visual Studio 2017+
- **Platform**: Windows 10/11 (x64)
- **Graphics API**: DirectX 12
- **SDK**: Windows SDK 10.x

## 빌드 방법

1. `src/Client/Client.sln`을 Visual Studio로 열기
2. 구성: `Debug` 또는 `Release` / `x64`
3. 빌드 (F7) 후 실행 (F5)

## 프로젝트 구조

```
GameFrameWork-master/
├── bin/                          # 런타임 리소스
│   ├── resource/                 # 텍스처 (DDS/PNG)
│   ├── shader/                   # 컴파일된 셰이더 바이너리
│   │   ├── Before/               # DX11 시절 셰이더
│   │   ├── Light/                # 라이트 셰이더 (Directional/Point/Spot/Capsule)
│   │   └── Render/               # 렌더링 셰이더
│   └── sound/                    # 사운드 (BGM/Effect)
│
└── src/
    ├── Client/                   # 메인 클라이언트
    │   ├── Radar/                # 게임 프레임워크 코어
    │   │   ├── GameFrameWork.*   #   DX12 초기화, 렌더 루프
    │   │   ├── GBuffer/          #   G-Buffer (Deferred Rendering)
    │   │   ├── GameObject/       #   게임 오브젝트
    │   │   └── Scene/            #   씬 관리
    │   ├── rengine/              # 렌더링 엔진
    │   │   ├── DX12/             #   d3dx12.h, DDSTextureLoader
    │   │   ├── DXObject/         #   DX 오브젝트 래퍼
    │   │   ├── Shader/           #   셰이더 컴파일/관리
    │   │   ├── Mesh/             #   메시 데이터
    │   │   ├── Camera/           #   카메라 (일반/자유시점)
    │   │   ├── Buffer/           #   상수 버퍼
    │   │   ├── Manager/          #   입력/타이머 관리자
    │   │   └── Util/             #   유틸리티, UploadBuffer
    │   ├── hlsl/                 # HLSL 셰이더 소스
    │   └── docs/                 # 문서
    ├── Script/                   # 스크립트 파싱 모듈
    ├── Share/                    # 공유 헤더 (열거형, 구조체, 타입)
    └── props/                    # MSBuild 속성 파일
```

## 아키텍처

```
CGameFrameWork (싱글톤)
├── Initialize      → Device, SwapChain, CommandQueue, RTV/DSV 생성
├── Update          → 입력 처리, 게임 로직
└── Render          → Command List 기록 → GPU 실행 → Present
    └── GBuffer     → Deferred Rendering 파이프라인

CGlobalData (싱글톤)
└── Device, CommandList 등 전역 DX12 리소스 관리

CCamera / CFreeCamera
└── View/Projection 행렬, 자유 시점 이동
```

## 주요 기능

- **DX12 렌더링 파이프라인**: SwapChain, Fence 기반 동기화, Double Buffering
- **Geometry Shader 큐브 생성**: 점 하나로부터 큐브 메시를 GS에서 생성
- **Deferred Rendering**: G-Buffer 기반 지연 렌더링
- **다중 라이트**: Directional, Point, Spot, Capsule Light (Hull/Domain Shader)
- **입력 시스템**: 키보드/마우스 입력 관리
- **카메라**: 일반 카메라 + 자유 시점 카메라
- **DDS 텍스처 로딩**: DDSTextureLoader12 기반
- **스크립트 파싱**: 외부 스크립트 파일 로딩

## 라이선스

Copyright (c) radar92.tistory.com / on1659@naver.com
