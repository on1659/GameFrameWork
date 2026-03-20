# DX12 GameFrameWork - 수정내역

## [Initial Commit] - 2026-03-20

**커밋**: `5b565bd` | **작성자**: Young-tae. Kim

### 개요

DirectX 12 기반 렌더링 프레임워크 초기 구축. Geometry Shader를 활용한 큐브 데모 포함.

### 주요 버그 수정

- **GPU Device Hung 수정 (DXGI_ERROR_DEVICE_HUNG)**
  - 원인: Upload Buffer의 생명주기 문제로 GPU가 아직 참조 중인 버퍼가 해제됨
  - 해결: Upload Buffer 생명주기를 프레임 렌더링 완료까지 유지하도록 수정

- **RTV/DSV 생성 누락 수정**
  - 원인: 초기화 과정에서 Render Target View / Depth Stencil View 생성 단계 누락
  - 해결: 초기화 시퀀스에 RTV/DSV 생성 로직 추가

### 추가된 소스 코드 (45개 파일, 10,312줄)

#### 엔진 코어 (`rengine/`)
| 파일 | 줄 수 | 설명 |
|------|-------|------|
| `DX12/d3dx12.h` | 2,040 | DirectX 12 헬퍼 헤더 |
| `DX12/DDSTextureLoader12.cpp/h` | 1,723 | DDS 텍스처 로더 |
| `Manager/input/InputManager.cpp/h` | 990 | 입력 관리자 (키보드/마우스) |
| `Util/Util.cpp/h` | 658 | 유틸리티 함수 모음 |
| `Shader/Shader.cpp/h` | 451 | 셰이더 관리 |
| `Camera/Camera.cpp/h` | 355 | 카메라 시스템 |
| `Mesh/Mesh.cpp/h` | 272 | 메시 데이터 관리 |
| `DXObject/DXObject.cpp/h` | 191 | DX 오브젝트 래퍼 |
| `safe_delete.hpp` | 135 | 안전한 메모리 해제 매크로 |
| `Util/UploadBuffer.h` | 121 | GPU 업로드 버퍼 |
| `Camera/FreeCamera.cpp/h` | 131 | 자유 시점 카메라 |
| `Object.h` | 104 | 오브젝트 기본 클래스 |
| `Globalvariable.h` | 86 | 전역 변수 정의 |
| `Manager/time/Timer.cpp/h` | 148 | 타이머/FPS 관리 |
| `Buffer/CRBuffer.cpp/h` | 58 | 상수 버퍼 |
| `SingleTon.h` | 33 | 싱글톤 패턴 템플릿 |

#### 게임 프레임워크 (`Radar/`)
| 파일 | 줄 수 | 설명 |
|------|-------|------|
| `GameFrameWork.cpp/h` | 1,247 | 메인 프레임워크 (초기화, 렌더 루프) |
| `GBuffer/GBuffer.cpp/h` | 435 | G-Buffer (Deferred Rendering) |
| `GameObject/GameObject.cpp/h` | 229 | 게임 오브젝트 클래스 |
| `Scene/Scene.cpp/h` | 136 | 씬 관리 |

#### 셰이더 (`hlsl/`)
| 파일 | 줄 수 | 설명 |
|------|-------|------|
| `GSShader.hlsl` | 296 | Geometry Shader (큐브 생성) |
| `Shader.hlsl` | 52 | 기본 VS/PS 셰이더 |

#### 프로젝트 설정
| 파일 | 설명 |
|------|------|
| `Client.sln` | Visual Studio 솔루션 |
| `Client.vcxproj` | 프로젝트 설정 (DX12, x64) |

### 리소스 (바이너리)

- **텍스처**: `bin/resource/` - DDS 텍스처 8종 + 기본 텍스처
- **셰이더 바이너리**: `bin/shader/` - 컴파일된 셰이더 (VS/PS/GS/HS/DS)
  - Deferred Shading, Billboard, Particle, Skinned Model, SkyBox, UI 등
  - Light 셰이더: Directional, Point, Spot, Capsule
- **사운드**: `bin/sound/` - BGM 6종, Effect 15종
