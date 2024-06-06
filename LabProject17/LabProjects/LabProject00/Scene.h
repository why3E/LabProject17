#pragma once

#include "Timer.h"
#include "Shader.h"
#include "Camera.h"

class CScene
{
public:
	CScene();
	~CScene();

	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

	void ReleaseUploadBuffers();

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

public:
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;

	int m_nShaders = 0;
	CObjectsShader* m_pShaders = NULL;

public:
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera *pCamera);
};

