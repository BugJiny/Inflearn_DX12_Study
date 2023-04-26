#include "pch.h"
#include "DescriptorHeap.h"
#include "SwapChain.h"

void DescriptorHeap::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	_swapChain = swapChain;

	// Descriptor (DX12) = View (~DX11)
	// [서술자 힙]으로 RTV 생성
	// DX11의 RTV(RenderTargetView), DSV(DepthStencilView), 
	// CBV(ConstantBufferView), SRV(ShaderResourceView), UAV(UnorderedAccessView)를 전부!


	// View = GPU가 리소스를 사용할 때 바로 객체에 접근하는 것이 아닌, 그 객체의 정보를 가지고
	// 있는 View 객체를 거쳐서 접근 및 사용을 하게 된다. 객체가 연애인이고 View 매니저와 같은 느낌
	// 출처(https://velog.io/@rehpe/Direct-2D-06.-Render-Target-View-Depth-Stencil-View-ViewPort-%EC%84%A4%EC%A0%95-%EC%8A%A4%EB%A7%88%ED%8A%B8-%ED%8F%AC%EC%9D%B8%ED%84%B0)

	_rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// 11까지는 필요한 View를 만들어야 했는데 지금은 밑에 있는 인자값을 조절해서 사용가능
	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc; 
	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;  // 리소스의 용도.
	rtvDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;  // 리소스가 몇개 있는지
	rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvDesc.NodeMask = 0;

	// 같은 종류의 데이터끼리 배열로 관리
	// RTV 목록 : [ ] [ ] (현재 공간만 생성된 상태)
	device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&_rtvHeap));

	// CreateDescriptorHeap -> GPU [[           ] [           ]] 해당 공간은 리소스 갯수
	// CreateRenderTargetView -> GPU [[?????] [?????]] 데이터 초기화 

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapBegin = _rtvHeap->GetCPUDescriptorHandleForHeapStart();

	// 해당 부분이 공간을 초기화  
	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		_rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeapBegin, i * _rtvHeapSize);
		device->CreateRenderTargetView(swapChain->GetRenderTarget(i).Get(), nullptr, _rtvHandle[i]);
	}
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetBackBufferView()
{
	return GetRTV(_swapChain->GetCurrentBackBufferIndex());
}