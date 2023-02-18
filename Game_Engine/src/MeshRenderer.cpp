#include "MeshRenderer.h"
#include "Camera.h"
#include "MuscleEngine.h"
#include "GraphicsManager.h"
#include "Transform.h"

namespace Muscle
{
	MeshRenderer::MeshRenderer(std::shared_ptr<GameObject> _GameObject) :RendererBase(_GameObject)
	{
	}

	MeshRenderer::~MeshRenderer()
	{

	}


	void MeshRenderer::Start()
	{
		_renderingData->_objectInfo._objectID = m_GameObject.lock()->GetObjectID();
	}

	void MeshRenderer::Update()
	{


	}

	void MeshRenderer::Render()
	{
		// ���� ������ ī�޶� ���� ������ ������Ʈ�ؼ� �׷��Ƚ� �Ŵ������� �����͸� �۽��Ѵ�.
		std::shared_ptr<Camera> mainCam = MuscleEngine::GetInstance()->GetMainCamera();

		DUOLMath::Matrix worldTM = _transform->GetWorldTM();

		_renderingData->_geoInfo._world = worldTM;

		_renderingData->_geoInfo._texTransform = DUOLMath::Matrix::Identity;

		_renderingData->_geoInfo._worldViewProj = worldTM * mainCam->View() * mainCam->Proj();

		_renderingData->_geoInfo._worldInvTranspose = (worldTM.Invert()).Transpose();

		// �׷��Ƚ� �Ŵ������� ������ �����͸� ������.
		MuscleEngine::GetInstance()->GetGraphicsManager()->PostRenderingData_3D(_renderingData);

	}


}