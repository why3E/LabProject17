#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

ID3D12RootSignature* CScene::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
{
	ID3D12RootSignature* pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[2];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[0].Constants.Num32BitValues = 16;
	pd3dRootParameters[0].Constants.ShaderRegister = 0;
	pd3dRootParameters[0].Constants.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 1;
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob* pd3dSignatureBlob = NULL;
	ID3DBlob* pd3dErrorBlob = NULL;
	::D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void**)&pd3dGraphicsRootSignature);

	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return pd3dGraphicsRootSignature;
}

ID3D12RootSignature* CScene::GetGraphicsRootSignature()
{
	return m_pd3dGraphicsRootSignature;
}

//void CScene::CreateGraphicsPipelineState(ID3D12Device* pd3dDevice)
//{
//	ID3DBlob* pd3dVertexShaderBlob = NULL;
//	ID3DBlob* pd3dPixelShaderBlob = NULL;
//
//	D3DCompileFromFile(L"Shaders.hlsl", NULL, NULL, "VSMain", "vs_5_1", 0, 0, &pd3dVertexShaderBlob, NULL);
//	D3DCompileFromFile(L"Shaders.hlsl", NULL, NULL, "PSMain", "ps_5_1", 0, 0, &pd3dPixelShaderBlob, NULL);
//
//	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
//	::ZeroMemory(&d3dRasterizerDesc, sizeof(d3dRasterizerDesc));
//	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
//	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
//	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
//	d3dRasterizerDesc.DepthClipEnable = TRUE;
//	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
//	d3dRasterizerDesc.DepthBias = 0;
//	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
//	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
//	d3dRasterizerDesc.MultisampleEnable = FALSE;
//	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
//	d3dRasterizerDesc.ForcedSampleCount = 0;
//
//	D3D12_BLEND_DESC d3dBlendDesc;
//	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
//	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
//	d3dBlendDesc.IndependentBlendEnable = FALSE;
//	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
//	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
//	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
//	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
//	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
//	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
//	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
//	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
//	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
//	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
//
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
//	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
//	d3dPipelineStateDesc.pRootSignature = m_pd3dGraphicsRootSignature;
//	d3dPipelineStateDesc.VS.pShaderBytecode = pd3dVertexShaderBlob->GetBufferPointer();
//	d3dPipelineStateDesc.VS.BytecodeLength = pd3dVertexShaderBlob->GetBufferSize();
//	d3dPipelineStateDesc.PS.pShaderBytecode = pd3dPixelShaderBlob->GetBufferPointer();
//	d3dPipelineStateDesc.PS.BytecodeLength = pd3dPixelShaderBlob->GetBufferSize();
//	d3dPipelineStateDesc.RasterizerState = d3dRasterizerDesc;
//	d3dPipelineStateDesc.BlendState = d3dBlendDesc;
//	d3dPipelineStateDesc.DepthStencilState.DepthEnable = FALSE;
//	d3dPipelineStateDesc.DepthStencilState.StencilEnable = FALSE;
//	d3dPipelineStateDesc.InputLayout.pInputElementDescs = NULL;
//	d3dPipelineStateDesc.InputLayout.NumElements = 0;
//	d3dPipelineStateDesc.SampleMask = UINT_MAX;
//	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//	d3dPipelineStateDesc.NumRenderTargets = 1;
//	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
//	d3dPipelineStateDesc.SampleDesc.Count = 1;
//	d3dPipelineStateDesc.SampleDesc.Quality = 0;
//	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void**)&m_pd3dPipelineState);
//
//	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
//	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
//}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
}

void CScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	;
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);

	m_nShaders = 1;
	m_pShaders = new CObjectsShader[m_nShaders];

	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	for (int i = 0; i < m_nShaders; i++) {
		m_pShaders[i].ReleaseShaderVariables();
		m_pShaders[i].ReleaseObjects();
	}
	if (m_pShaders) delete[] m_pShaders;
}

bool CScene::ProcessInput(UCHAR* pKeysBuffer)
{
	return false;
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	for (int i = 0; i < m_nShaders; i++) {
		m_pShaders[i].AnimateObjects(fTimeElapsed);
	}
}

//void CScene::PrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
//{
//	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
//	pd3dCommandList->SetPipelineState(m_pd3dPipelineState);
//	pd3dCommandList->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//}

void CScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);
	
	for (int i = 0; i < m_nShaders; i++) {
		m_pShaders[i].Render(pd3dCommandList, pCamera);
	}
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return false;
}

CGameObject* CScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{
	if (!pCamera) return(NULL);

	XMFLOAT4X4 xmf4x4View = pCamera->GetViewMatrix();
	XMFLOAT4X4 xmf4x4Projection = pCamera->GetProjectionMatrix();

	D3D12_VIEWPORT d3dViewport = pCamera->GetViewport();

	XMFLOAT3 xmf3PickPosition;

	xmf3PickPosition.x = (((2.0f * xClient) / d3dViewport.Width) - 1) / xmf4x4Projection._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / d3dViewport.Height) - 1) / xmf4x4Projection._22;
	xmf3PickPosition.z = 1.0f;

	int nIntersected = 0;
	float fHitDistance = FLT_MAX, fNearestHitDistance = FLT_MAX;

	CGameObject* pIntersectedObject = NULL, * pNearestObject = NULL;
	
	for (int i = 0; i < m_nShaders; i++) {
		pIntersectedObject = m_pShaders[i].PickObjectByRayIntersection(xmf3PickPosition, xmf4x4View, &fHitDistance);

		if (pIntersectedObject && (fHitDistance < fNearestHitDistance)) {
			fNearestHitDistance = fHitDistance;
			pNearestObject = pIntersectedObject;
		}
	}

	return(pNearestObject);
}
