#include "pch.h"
#include "DescriptorHeap.h"
#include "SwapChain.h"

void DescriptorHeap::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	_swapChain = swapChain;

	// Descriptor (DX12) = View (~DX11)
	// [������ ��]���� RTV ����
	// DX11�� RTV(RenderTargetView), DSV(DepthStencilView), 
	// CBV(ConstantBufferView), SRV(ShaderResourceView), UAV(UnorderedAccessView)�� ����!


	// View = GPU�� ���ҽ��� ����� �� �ٷ� ��ü�� �����ϴ� ���� �ƴ�, �� ��ü�� ������ ������
	// �ִ� View ��ü�� ���ļ� ���� �� ����� �ϰ� �ȴ�. ��ü�� �������̰� View �Ŵ����� ���� ����
	// ��ó(https://velog.io/@rehpe/Direct-2D-06.-Render-Target-View-Depth-Stencil-View-ViewPort-%EC%84%A4%EC%A0%95-%EC%8A%A4%EB%A7%88%ED%8A%B8-%ED%8F%AC%EC%9D%B8%ED%84%B0)

	_rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// 11������ �ʿ��� View�� ������ �ߴµ� ������ �ؿ� �ִ� ���ڰ��� �����ؼ� ��밡��
	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc; 
	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;  // ���ҽ��� �뵵.
	rtvDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;  // ���ҽ��� � �ִ���
	rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvDesc.NodeMask = 0;

	// ���� ������ �����ͳ��� �迭�� ����
	// RTV ��� : [ ] [ ] (���� ������ ������ ����)
	device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&_rtvHeap));

	// CreateDescriptorHeap -> GPU [[           ] [           ]] �ش� ������ ���ҽ� ����
	// CreateRenderTargetView -> GPU [[?????] [?????]] ������ �ʱ�ȭ 

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapBegin = _rtvHeap->GetCPUDescriptorHandleForHeapStart();

	// �ش� �κ��� ������ �ʱ�ȭ  
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