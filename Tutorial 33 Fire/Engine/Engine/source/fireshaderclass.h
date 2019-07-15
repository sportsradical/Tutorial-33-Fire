////////////////////////////////////////////////////////////////////////////////
// Filename: fireshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FIRESHADERCLASS_H_
#define _FIRESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <fstream>
#include <d3dcompiler.h>
#include <DirectXMath.h>
using namespace DirectX;
using namespace std;


#pragma comment(lib, "d3dcompiler.lib")


////////////////////////////////////////////////////////////////////////////////
// Class name: FireShaderClass
////////////////////////////////////////////////////////////////////////////////
class FireShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct NoiseBufferType
	{
		float frameTime;
		XMFLOAT3 scrollSpeeds;
		XMFLOAT3 scales;
		float padding;
	};

	struct DistortionBufferType
	{
		XMFLOAT2 distortion1;
		XMFLOAT2 distortion2;
		XMFLOAT2 distortion3;
		float distortionScale;
		float distortionBias;
	};

public:
	FireShaderClass();
	FireShaderClass(const FireShaderClass&);
	~FireShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
				XMMATRIX projectionMatrix, ID3D11ShaderResourceView* fireTexture,
				ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture, float frameTime,
				XMFLOAT3 scrollSpeeds, XMFLOAT3 scales, XMFLOAT2 distortion1, XMFLOAT2 distortion2,
				XMFLOAT2 distortion3, float distortionScale, float distortionBias);
private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
							 XMMATRIX projectionMatrix, ID3D11ShaderResourceView* fireTexture,
							 ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture,
							 float frameTime, XMFLOAT3 scrollSpeeds, XMFLOAT3 scales, XMFLOAT2 distortion1,
							 XMFLOAT2 distortion2, XMFLOAT2 distortion3, float distortionScale,
							 float distortionBias);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_noiseBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11SamplerState* m_sampleState2;
	ID3D11Buffer* m_distortionBuffer;
};

#endif