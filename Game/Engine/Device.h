#pragma once

// CPU에서 반복적으로 처리되야할 계산(외주)을 정해서 GPU에 보내주면
// 해당 작업을 GPU에서 실행한다...약간 인력 사무소같은 느낌?

// CPU (연산), RAM (CPU의 기억장치)
// GPU(연산), VRAM(GPU의 기억장치)



// Device는 GPU(DirectX)와 연결되는 매개체(?) 혹은 장치이다.
class Device
{
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// COM(Component Object Model)
	// - DX의 프로그래밍 언어 독립성과 하위 호환성을 가능하게 하는 기술
	// - COM 객체(COM 인터페이스)를 사용. 세부사항은 우리한테 숨겨짐
	// - ComPtr 일종의 스마트 포인터
	ComPtr<ID3D12Debug>			_debugController;
	ComPtr<IDXGIFactory>		_dxgi; // 화면 관련 기능들
	ComPtr<ID3D12Device>		_device; // 각종 객체 생성
};

