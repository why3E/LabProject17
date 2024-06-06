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

	IDXGIFactory4* m_pdxgiFactory;  // DXGI 팩토리 인터페이스에 대한 포인터
	IDXGISwapChain3* m_pdxgiSwapChain;  // 스왑 체인 인터페이스에 대한 포인터, 주로 디스플레이를 제어하기 위해 필요
	ID3D12Device* m_pd3dDevice;  // Direct3D 디바이스 인터페이스에 대한 포인터, 주로 리소스를 생성하기 위해 필요

	bool m_bMsaa4xEnable = false;  // MSAA 다중 샘플링을 활성화
	UINT m_nMsaa4xQualityLevels = 0;  // 다중 샘플링 레벨을 설정

	static const UINT m_nSwapChainBuffers = 2;  // 스왑 체인의 후면 버퍼 개수
	UINT m_nSwapChainBufferIndex;  // 현재 스왑 체인의 후면 버퍼 인덱스

	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];  // 렌더 타겟 버퍼
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;  // 서술자 힙 인터페이스 포인터
	UINT m_nRtvDescriptorIncrementSize;  // 렌더 타겟 서술자의 크기

	ID3D12Resource* m_pd3dDepthStencilBuffer;  // 깊이-스텐실 버퍼
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;  // 서술자 힙 인터페이스 포인터
	UINT m_nDsvDescriptorIncrementSize;  // 깊이-스텐실 서술자의 크기

	ID3D12CommandQueue* m_pd3dCommandQueue;  // 명령 큐 인터페이스 포인터
	ID3D12CommandAllocator* m_pd3dCommandAllocator; // 명령 할당자 인터페이스 포인터
	ID3D12GraphicsCommandList* m_pd3dCommandList;  // 명령 리스트 인터페이스 포인터

	ID3D12PipelineState* m_pd3dPipelineState;  // 그래픽스 파이프라인 상태 객체에 대한 인터페이스 포인터

	ID3D12Fence* m_pd3dFence;  // 펜스 인터페이스 포인터
	UINT64 m_nFenceValues[m_nSwapChainBuffers];  // 펜스의 값, 후면 버퍼마다 관리
	HANDLE m_hFenceEvent;  // 이벤트 핸들

	CScene* m_pScene;

	CCamera* m_pCamera = NULL;

	CPlayer* m_pPlayer = NULL;

	CGameTimer m_GameTimer;
	_TCHAR m_pszFrameRate[50];

	POINT m_ptOldCursorPos;

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);  // 프레임워크를 초기화하는 함수, 주 윈도우 생성 시 호출
	void OnDestory();

	void CreateDirect3DDevice();  // 디바이스 생성

	void CreateSwapChain();  // 스왑 체인 생성
	void ChangeSwapChainState();

	void CreateCommandQueueAndList();  // 명령 큐, 할당자, 리스트 생성

	void CreateRtvAndDsvDescriptorHeaps();  // 서술자 힙 생성
	void CreateRenderTargetViews();  // 렌더 타겟 뷰 생성
	void CreateDepthStencilView();  // 깊이-스텐실 뷰 생성

	void BuildObjects();  // 렌더링할 메쉬와 게임 객체를 생성
	void ReleaseObjects();  // 렌더링할 메쉬외 게임 객체를 소멸

	void ProcessInput();  // 사용자 입력
	void AnimateObjects();  // 애니메이션

	void FrameAdvance(); 
	void MoveToNextFrame();

	void WaitForGpuComplete();  // CPU와 GPU 동기화

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);  // 윈도우의 마우스 메시지 처리
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);  // 윈도우의 키보드 메시지 처리
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	CGameObject* m_pSelectedObject = NULL;

public:
	void ProcessSelectedObject(DWORD dwDirection, float cxDelta, float cyDelta);
};

