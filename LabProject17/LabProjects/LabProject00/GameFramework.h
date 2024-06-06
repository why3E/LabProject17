#pragma once

#include "Timer.h"
#include "Scene.h"
#include "Camera.h"
#include "Player.h"

class CGameFramework
{
public:
	void BuildObjects_change();
private:
	HINSTANCE m_hInstace;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	IDXGIFactory4* m_pdxgiFactory;  // DXGI ���丮 �������̽��� ���� ������
	IDXGISwapChain3* m_pdxgiSwapChain;  // ���� ü�� �������̽��� ���� ������, �ַ� ���÷��̸� �����ϱ� ���� �ʿ�
	ID3D12Device* m_pd3dDevice;  // Direct3D ����̽� �������̽��� ���� ������, �ַ� ���ҽ��� �����ϱ� ���� �ʿ�

	bool m_bMsaa4xEnable = false;  // MSAA ���� ���ø��� Ȱ��ȭ
	UINT m_nMsaa4xQualityLevels = 0;  // ���� ���ø� ������ ����

	static const UINT m_nSwapChainBuffers = 2;  // ���� ü���� �ĸ� ���� ����
	UINT m_nSwapChainBufferIndex;  // ���� ���� ü���� �ĸ� ���� �ε���

	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];  // ���� Ÿ�� ����
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;  // ������ �� �������̽� ������
	UINT m_nRtvDescriptorIncrementSize;  // ���� Ÿ�� �������� ũ��

	ID3D12Resource* m_pd3dDepthStencilBuffer;  // ����-���ٽ� ����
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;  // ������ �� �������̽� ������
	UINT m_nDsvDescriptorIncrementSize;  // ����-���ٽ� �������� ũ��

	ID3D12CommandQueue* m_pd3dCommandQueue;  // ��� ť �������̽� ������
	ID3D12CommandAllocator* m_pd3dCommandAllocator; // ��� �Ҵ��� �������̽� ������
	ID3D12GraphicsCommandList* m_pd3dCommandList;  // ��� ����Ʈ �������̽� ������

	ID3D12PipelineState* m_pd3dPipelineState;  // �׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� ������

	ID3D12Fence* m_pd3dFence;  // �潺 �������̽� ������
	UINT64 m_nFenceValues[m_nSwapChainBuffers];  // �潺�� ��, �ĸ� ���۸��� ����
	HANDLE m_hFenceEvent;  // �̺�Ʈ �ڵ�

	CScene* m_pScene;

	CCamera* m_pCamera = NULL;

	CPlayer* m_pPlayer = NULL;

	CGameTimer m_GameTimer;
	_TCHAR m_pszFrameRate[50];

	POINT m_ptOldCursorPos;

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);  // �����ӿ�ũ�� �ʱ�ȭ�ϴ� �Լ�, �� ������ ���� �� ȣ��
	void OnDestory();

	void CreateDirect3DDevice();  // ����̽� ����

	void CreateSwapChain();  // ���� ü�� ����
	void ChangeSwapChainState();

	void CreateCommandQueueAndList();  // ��� ť, �Ҵ���, ����Ʈ ����

	void CreateRtvAndDsvDescriptorHeaps();  // ������ �� ����
	void CreateRenderTargetViews();  // ���� Ÿ�� �� ����
	void CreateDepthStencilView();  // ����-���ٽ� �� ����

	void BuildObjects();  // �������� �޽��� ���� ��ü�� ����
	void ReleaseObjects();  // �������� �޽��� ���� ��ü�� �Ҹ�

	void ProcessInput();  // ����� �Է�
	void AnimateObjects();  // �ִϸ��̼�

	void FrameAdvance(); 
	void MoveToNextFrame();

	void WaitForGpuComplete();  // CPU�� GPU ����ȭ

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);  // �������� ���콺 �޽��� ó��
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);  // �������� Ű���� �޽��� ó��
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	CGameObject* m_pSelectedObject = NULL;

public:
	void ProcessSelectedObject(DWORD dwDirection, float cxDelta, float cyDelta);
};

