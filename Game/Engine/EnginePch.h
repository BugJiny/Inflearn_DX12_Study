#pragma once
// 각종 include
#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
using namespace std;


// DX관련
#include "d3dx12.h"  // MS 공식 Directx12 지원 라이브러리
#include <d3d12.h>
#include <wrl.h>    // Window Runtime Library(Com객체의 수명관리를 위해) -> Com객체를 위한 스마트포인터             
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;


// 각종 lib
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")


// 각종 typedef(재정의)
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vec2 = XMFLOAT2;
using Vec3 = XMFLOAT3;
using Vec4 = XMFLOAT4;
using Matrix = XMMATRIX;


enum class CBV_REGISTER
{
	b0,
	b1,
	b2,
	b3,
	b4,

	END
};

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2,
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	REGISTER_COUNT = CBV_REGISTER::END,
};

struct WindowInfo
{
	HWND	hwnd;    // 윈도우 핸들
	int32	width;   // 너비
	int32	height;  // 높이
	bool	windowed; // 창모드 or 전체화면
};

struct Vertex
{
	Vec3 pos;
	Vec4 color;
};

struct Transform
{
	Vec4 offset;
};

// 헬퍼 매크로
#define DEVICE			GEngine->GetDevice()->GetDevice()
#define CMD_LIST		GEngine->GetCmdQueue()->GetCmdList()
#define ROOT_SIGNATURE	GEngine->GetRootSignature()->GetSignature()

extern unique_ptr<class Engine> GEngine;


