#pragma once

// CPU���� �ݺ������� ó���Ǿ��� ���(����)�� ���ؼ� GPU�� �����ָ�
// �ش� �۾��� GPU���� �����Ѵ�...�ణ �η� �繫�Ұ��� ����?

// CPU (����), RAM (CPU�� �����ġ)
// GPU(����), VRAM(GPU�� �����ġ)



// Device�� GPU(DirectX)�� ����Ǵ� �Ű�ü(?) Ȥ�� ��ġ�̴�.
class Device
{
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// COM(Component Object Model)
	// - DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���
	// - COM ��ü(COM �������̽�)�� ���. ���λ����� �츮���� ������
	// - ComPtr ������ ����Ʈ ������
	ComPtr<ID3D12Debug>			_debugController;
	ComPtr<IDXGIFactory>		_dxgi; // ȭ�� ���� ��ɵ�
	ComPtr<ID3D12Device>		_device; // ���� ��ü ����
};

