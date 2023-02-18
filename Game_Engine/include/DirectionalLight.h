#pragma once

#include "Light.h"

namespace Muscle
{

	class DirectionalLight : public Light
	{
		public:
			DirectionalLight(std::shared_ptr<GameObject> _GameObject);
			~DirectionalLight();

			MuscleGrapics::DirectionalLightInfo _directionalLightInfo;
		public:
			virtual void Start() override;

			virtual void Update() override; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.

			virtual void Render() override; // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����

			void SetDirectional(DUOLMath::Vector3 directional);
	};
}