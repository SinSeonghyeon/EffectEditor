#pragma once

#include "dllExport.h"
#include "util/STLInclude.h"
#include "util/TypeDefine.h"

#include "../../DUOLMath/include/DUOLMath/DUOLMath.h"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace PrevVersion
{
	enum class RASTERIZER_STATE
	{
		SOLID = 0,
		WIREFRAME = 1,
	};
	/**
			@enum  RenderingData_Particle
			@brief ver_0.2 �������� ������ �������.
		**/
	enum class Space
	{
		Local,
		World
	};
	/**
		@struct Particle_CommonInfo
		@brief  Ŀ�������� ��� ��ƼŬ�� ����ϴ� ���� �⺻���� ���, ������ �����Ų��.
	**/
	struct Particle_CommonInfo
	{
		enum class Option_Particle
		{
			Constant,
			Curve, // Ŀ��� �ļ����� �̷���..!
			RandomBetweenTwoConstant,
			RandomBetweenTwoCurve // Ŀ��� �ļ����� �̷���..!
		};
		Particle_CommonInfo() :
			_useModule(true),
			_firstRun(true),
			_duration(5.0f),
			_looping(true),
			_startDelayOption(Option_Particle::Constant),
			_startDelay{ 0,0 },
			_startLifeTimeOption(Option_Particle::Constant),
			_startLifeTime{ 5.0f,5.0f },
			_startSpeedOption(Option_Particle::Constant),
			_startSpeed{ 4.0f,4.0f },
			_startSizeOption(Option_Particle::Constant),
			_startSize{ DUOLMath::Vector2(1.0f, 1.0f),DUOLMath::Vector2(1.0f, 1.0f) },
			_startRotationOption(Option_Particle::Constant),
			_startRotation{ 0,0 },
			_startColorOption(Option_Particle::Constant),
			_startColor{ DUOLMath::Vector4(1.0f, 1.0f, 1.0f,1.0f),DUOLMath::Vector4(1.0f, 1.0f, 1.0f,1.0f) },
			_gravirtModifierOption(Option_Particle::Constant),
			_gravityModifier{ 0.0f,0.0f },
			_maxParticles(1000),
			_transformMatrix(DUOLMath::Matrix::Identity),
			_simulationSpeed(1.0f),
			_space(Space::World),
			_deltaMatrix(DUOLMath::Matrix::Identity)
		{}
		bool operator==(const Particle_CommonInfo& other) const
		{
			if (
				_useModule != other._useModule ||
				_firstRun != other._firstRun ||
				_duration != other._duration ||
				_looping != other._looping ||
				_startDelayOption != other._startDelayOption ||
				_startDelay[0] != other._startDelay[0] ||
				_startDelay[1] != other._startDelay[1] ||
				_startLifeTimeOption != other._startLifeTimeOption ||
				_startLifeTime[0] != other._startLifeTime[0] ||
				_startLifeTime[1] != other._startLifeTime[1] ||
				_startSpeedOption != other._startSpeedOption ||
				_startSpeed[0] != other._startSpeed[0] ||
				_startSpeed[1] != other._startSpeed[1] ||
				_startSizeOption != other._startSizeOption ||
				_startSize[0] != other._startSize[0] ||
				_startSize[1] != other._startSize[1] ||
				_startRotationOption != other._startRotationOption ||
				_startRotation[0] != other._startRotation[0] ||
				_startRotation[1] != other._startRotation[1] ||
				_startColorOption != other._startColorOption ||
				_startColor[0] != other._startColor[0] ||
				_startColor[1] != other._startColor[1] ||
				_gravirtModifierOption != other._gravirtModifierOption ||
				_gravityModifier[0] != other._gravityModifier[0] ||
				_gravityModifier[1] != other._gravityModifier[1] ||
				_maxParticles != other._maxParticles ||
				_transformMatrix != other._transformMatrix ||
				_simulationSpeed != other._simulationSpeed ||
				_space != other._space ||
				_deltaMatrix != other._deltaMatrix

				)
				return false;
			else
				return true;
		}
		bool _useModule;
		//																					ShaderCode					   ImGui						
		bool _firstRun;					// �����ΰ��� ..?										O							O

		float _duration;				// �� �� ���� ��ƼŬ ��ü�� ����� ��.						X							O

		bool _looping;					// �ݺ�����.												X							O

		Option_Particle _startDelayOption;	//													X							X

		float _startDelay[2];				// �� �� �ڿ� ��ƼŬ�� ����� ��.						X							O

		Option_Particle _startLifeTimeOption;	//												X							X

		float _startLifeTime[2];				// �� ��ƼŬ�� ���� �ð�.							O							O

		Option_Particle _startSpeedOption;//													X							X

		float _startSpeed[2];				// ��ƼŬ ������ ���� �ӵ�.							O							O

		Option_Particle _startSizeOption;//														X							X

		DUOLMath::Vector2 _startSize[2];				// ��ƼŬ�� ���� ũ��.								O							O

		Option_Particle _startRotationOption;//													X							X

		float _startRotation[2];			// ��ƼŬ�� ���� ȸ��.								X							O

		Option_Particle _startColorOption;//													X							X

		DUOLMath::Vector4 _startColor[2];			// ��ƼŬ�� ���� ����										X							O

		Option_Particle _gravirtModifierOption;//												X							X

		float _gravityModifier[2];			// ��ƼŬ�� �������� �߷�.							O							O

		int _maxParticles;				// ��ƼŬ �ִ� ��� ������.								X							O
		// ContantBuffer 16���� �� ��� �Ϸ�..

		DUOLMath::Matrix _transformMatrix;		// ��ƼŬ�� ���� ��ġ �� ���� ����							X							X

		float _playTime;				// play ������ �帥 �ð�.

		float _simulationSpeed;

		Space _space; // ������ ��ƼŬ�� Mitter�� ���� ������ ������ �ȹ�����. ����� ������ �ȹް� �����̸� ������ �޴´�.

		DUOLMath::Matrix _deltaMatrix;		// ��ƼŬ�� ���� ��ġ �� ���� ����	
	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _firstRun;

			ar& _duration;

			ar& _looping;

			ar& _startDelayOption;

			ar& _startDelay;

			ar& _startLifeTimeOption;

			ar& _startLifeTime;

			ar& _startSpeedOption;

			ar& _startSpeed;

			ar& _startSizeOption;

			ar& _startSize;

			ar& _startRotationOption;

			ar& _startRotation;

			ar& _startColorOption;

			ar& _startColor;

			ar& _gravirtModifierOption;

			ar& _gravityModifier;

			ar& _maxParticles;

			ar& _transformMatrix;

			ar& _playTime;

			ar& _simulationSpeed;

			ar& _space;

			ar& _deltaMatrix;
		}

	};
	struct Particle_Emission
	{
		Particle_Emission() : _useModule(true),
			_emissiveCount{ 1,1 }, _emissiveTime(0.1f), _emissiveTimer(0),
			_isRateOverDistance(false),
			_emissionOption(Particle_CommonInfo::Option_Particle::Constant)
		{
		}
		bool operator==(const Particle_Emission& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Emission)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		int _emissiveCount[2];			// �ѹ��� ��� ���� ��ų��.

		float _emissiveTime;			// ���� ������� �ɸ��� �ð�.

		bool _isRateOverDistance;			// ������ �� ��ƼŬ ����.

		float _emissiveTimer;			// ���� Ÿ�̸�.

		Particle_CommonInfo::Option_Particle _emissionOption;

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;
			ar& _emissiveCount;
			ar& _emissiveTime;
			ar& _isRateOverDistance;
			ar& _emissiveTimer;
		}
	};
	struct Particle_Shape
	{
		Particle_Shape() :
			_useModule(true),
			_shape(Shape::Cone),
			_angle(3.141592f / 6.0f), _radius(1.0f), _donutRadius(0), _arc(3.141592f * 2.0f),
			_position(0, 0, 0),
			_rotation(0, 0, 0),
			_scale(1, 1, 1),
			_radiusThickness(1.0f),
			_edgeMode_flags(0),
			_edgeMode(EdgeMode::Random),
			_speed(1.0f),
			_spread(0.0f),
			pad3()
		{
		}
		bool operator==(const Particle_Shape& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Shape)) == 0)
				return true;
			else
				return false;
		}
		enum class Shape
		{
			Sphere,
			Hemisphere,
			Cone,
			Donut,
			Box,
			Circle,
			Rectangle,
			Edge

		};
		enum class EdgeMode
		{
			Random,
			Loop,
			PingPong,
			BurstSpread
		};
		bool _useModule;

		Shape _shape;

		EdgeMode _edgeMode;

		float _angle;
		float _radius;
		float _donutRadius;
		float _arc;

		DUOLMath::Vector3 _position;
		float _radiusThickness;

		DUOLMath::Vector3 _rotation;
		float pad1;

		DUOLMath::Vector3 _scale;
		float pad2;

		unsigned int _edgeMode_flags;
		float _speed;
		float _spread;
		float pad3;


	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _shape;

			ar& _edgeMode;

			ar& _angle;
			ar& _radius;
			ar& _donutRadius;
			ar& _arc;

			ar& _position;
			ar& _radiusThickness;

			ar& _rotation;
			ar& pad1;

			ar& _scale;
			ar& pad2;

			ar& _edgeMode_flags;
			ar& _speed;
			ar& _spread;
			ar& pad3;
		}

	};
	struct Particle_Velocity_over_Lifetime
	{
		Particle_Velocity_over_Lifetime() : _useModule(false),
			_linearVelocity(0, 0, 0), _space(Space::Local),
			_orbital(0, 0, 0), _offset(0, 0, 0), _isGravity(1)
		{
		}
		bool operator==(const Particle_Velocity_over_Lifetime& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Velocity_over_Lifetime)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		DUOLMath::Vector3 _linearVelocity;
		Space _space;

		DUOLMath::Vector3 _orbital;
		unsigned int _isGravity;

		DUOLMath::Vector3 _offset;
		float pad2;


	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _space;

			ar& _linearVelocity;

			ar& _orbital;
			ar& _isGravity;

			ar& _offset;
			ar& pad2;
		}
	};
	struct Particle_Limit_Velocity_Over_Lifetime
	{
		Particle_Limit_Velocity_Over_Lifetime() : _useModule(false),
			_pointA(0, 0),
			_pointB(0.3333f, 0.3333f),
			_pointC(0.6666f, 0.6666f),
			_pointD(1.0f, 1.0f),
			_speed(1.0f),
			_dampen(1.0f)
		{
		}
		bool operator==(const Particle_Limit_Velocity_Over_Lifetime& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Limit_Velocity_Over_Lifetime)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		DUOLMath::Vector2 _pointA;

		DUOLMath::Vector2 _pointB;

		DUOLMath::Vector2 _pointC;

		DUOLMath::Vector2 _pointD;

		float _speed;
		float _dampen;
		DUOLMath::Vector2 pad;
	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _pointA;

			ar& _pointB;

			ar& _pointC;

			ar& _pointD;

			ar& _speed;

			ar& _dampen;

			ar& pad;
		}
	};
	struct Particle_Force_over_LifeTime
	{
		Particle_Force_over_LifeTime() :_useModule(false), _force(0, 0, 0),
			_space(Space::Local)
		{
		}
		bool operator==(const Particle_Force_over_LifeTime& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Velocity_over_Lifetime)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		DUOLMath::Vector3 _force;

		Space _space;

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _force;

			ar& _space;
		}
	};
	struct Particle_Color_over_Lifetime
	{
		/**
			@brief Cpu���� ���� ���� �̸� ���ؼ� ������ �ʴ� ������ ��ƼŬ���� ������Ÿ���� �ٸ��� �����̴�.
			gpu �ȿ��� ����� �� �ִ� ����� �����غ���.
		**/
		Particle_Color_over_Lifetime() : _useModule(false)
		{
			for (int i = 0; i < 8; i++)
			{
				_alpha_Ratio[i] = DUOLMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
				_color_Ratio[i] = DUOLMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			}


		}
		bool operator==(const Particle_Color_over_Lifetime& other) const
		{
			for (int i = 0; i < 8; i++)
			{
				if (_alpha_Ratio[i] != other._alpha_Ratio[i])
					return false;

				if (_alpha_Ratio[i] != other._alpha_Ratio[i])
					return false;

			}
			if (_useModule != other._useModule)
				return false;
			return true;
		}
		bool _useModule;

		DUOLMath::Vector4 _alpha_Ratio[8];

		DUOLMath::Vector4 _color_Ratio[8];

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _alpha_Ratio;

			ar& _color_Ratio;
		}
	};
	struct Particle_Size_Over_Lifetime
	{
		Particle_Size_Over_Lifetime() :
			_useModule(false),
			_pointA(0, 0),
			_pointB(0.333f, 0.333f),
			_pointC(0.666f, 0.666f),
			_pointD(1.0f, 1.0f)
		{
		}
		bool operator==(const Particle_Size_Over_Lifetime& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Size_Over_Lifetime)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		DUOLMath::Vector2 _pointA;
		DUOLMath::Vector2 _pointB;
		DUOLMath::Vector2 _pointC;
		DUOLMath::Vector2 _pointD;

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _pointA;

			ar& _pointB;

			ar& _pointC;

			ar& _pointD;
		}
	};
	struct Particle_Rotation_Over_Lifetime
	{
		Particle_Rotation_Over_Lifetime() :
			_useModule(false),
			_AngularVelocity(0)
		{
		}
		bool operator==(const Particle_Rotation_Over_Lifetime& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Rotation_Over_Lifetime)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		float _AngularVelocity;

		DUOLMath::Vector3 pad0;

		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _AngularVelocity;

			ar& pad0;
		}
	};
	struct Particle_Texture_Sheet_Animation
	{
		Particle_Texture_Sheet_Animation() :
			_useModule(false),
			_grid_XY{ 1, 1 },
			_timeMode(0)
		{
		}
		bool operator==(const Particle_Texture_Sheet_Animation& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Texture_Sheet_Animation)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		int _grid_XY[2];

		int _timeMode;

		float pad0;

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _grid_XY;

			ar& _timeMode;

			ar& pad0;
		}
	};
	struct Particle_Noise
	{
		enum class Quality
		{
			Low,
			Middle,
			High
		};
		Particle_Noise() : _useModule(false),
			_strength(1.0f), _frequency(0.5f), _scrollSpeed(0), _damping(true), _octaves(1),
			_octaveMultiplier(0.5), _octaveScale(2), _quality(Quality::High), _positionAmount(1), _rotationAmount(0),
			_sizeAmount(0)
		{}
		bool operator==(const Particle_Noise& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Noise)) == 0)
				return true;
			else
				return false;
		}
		bool _useModule;

		float _strength;
		float _frequency;
		float _scrollSpeed;
		bool _damping;
		int _octaves;
		float _octaveMultiplier;
		float _octaveScale;
		Quality _quality;

		float _positionAmount;
		float _rotationAmount;
		float _sizeAmount;

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;
			ar& _strength;
			ar& _frequency;
			ar& _scrollSpeed;
			ar& _damping;
			ar& _octaves;
			ar& _octaveMultiplier;
			ar& _octaveScale;
			ar& _quality;

			ar& _positionAmount;
			ar& _rotationAmount;
			ar& _sizeAmount;
		}
	};
	struct Particle_Collision
	{
		Particle_Collision() : _useModule(false),
			_planeCount(0), _boundce(1), _lifeTimeLoss(0)
		{

			for (int i = 0; i < 8; i++)
			{
				_planePos[i] = DUOLMath::Vector4();
				_planeNormalVec[i] = DUOLMath::Vector4(0, 1, 0, 0);
			}
		}
		bool operator==(const Particle_Collision& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Collision)) == 0)
				return true;
			else
				return false;
		}

		bool _useModule;

		int _planeCount; // �ִ� ������ ���س���. 8��? ������ �ȸ�ü�� �����߱� ����.

		float _boundce;

		float _lifeTimeLoss;

		float _pad;

		DUOLMath::Vector4 _planePos[8]; // ��°�� Vector4�ΰ�! 16����Ʈ ������ ���ϰ� �ϱ� ����.

		DUOLMath::Vector4 _planeNormalVec[8];


	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _planeCount;

			ar& _boundce;

			ar& _lifeTimeLoss;

			ar& _pad;

			ar& _planePos;

			ar& _planeNormalVec;
		}
	};
	struct Particle_Trails
	{
		Particle_Trails() :_useModule(false), _ratio(1.0f), _lifeTime(1.0f), _minimumVertexDistance(0.1f),
			_worldSpace(false), _dieWithParticle(false), _textureMode(TextureMode::Stretch),
			_sizeAffectsWidth(false), _sizeAffectsLifeTime(false),
			_inheritParticleColor(true), _widthOverTrail{ 1.0f,1.0f },
			_generateLightingData(false),
			_shadowBias(0), _trailVertexCount(15),
			_widthModifierOption(Particle_CommonInfo::Option_Particle::Constant),
			_scrollXSpeed{ 0,0 }, _scrollYSpeed{ 0,0 },
			_condition(Conditional::And), _recordTime(0),
			_scrollModifierOption(Particle_CommonInfo::Option_Particle::Constant)
		{
			for (int i = 0; i < 8; i++)
			{
				_alpha_Ratio_Lifetime[i] = DUOLMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
				_color_Ratio_Lifetime[i] = DUOLMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);

				_alpha_Ratio_Trail[i] = DUOLMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
				_color_Ratio_Trail[i] = DUOLMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			}

		}
		bool operator==(const Particle_Trails& other) const
		{
			if (memcmp(this, &other, sizeof(Particle_Trails)) == 0)
				return true;
			else
				return false;
		}
		enum class TextureMode
		{
			Stretch,
			Tile,
			DistributePerSegment,
			RepeatPerSegment

		};
		enum class Conditional
		{
			And,
			Or
		};
		bool _useModule;

		float _ratio; // 0 ~ 1 ��
		float _lifeTime; // 0 ~ 1 ��
		float _minimumVertexDistance;
		bool _worldSpace;

		bool _dieWithParticle;
		TextureMode _textureMode;
		bool _sizeAffectsWidth;
		bool _sizeAffectsLifeTime;

		bool _inheritParticleColor;
		DUOLMath::Vector4 _alpha_Ratio_Lifetime[8];
		DUOLMath::Vector4 _color_Ratio_Lifetime[8];

		Particle_CommonInfo::Option_Particle _widthModifierOption;
		float _widthOverTrail[2];

		DUOLMath::Vector4 _alpha_Ratio_Trail[8];
		DUOLMath::Vector4 _color_Ratio_Trail[8];

		bool _generateLightingData;
		float _shadowBias;

		int _trailVertexCount;

		Particle_CommonInfo::Option_Particle _scrollModifierOption;
		float _scrollXSpeed[2];
		float _scrollYSpeed[2];

		Conditional _condition;
		float _recordTime;
	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _ratio;
			ar& _lifeTime;
			ar& _minimumVertexDistance;
			ar& _worldSpace;

			ar& _dieWithParticle;
			ar& _textureMode;
			ar& _sizeAffectsWidth;
			ar& _sizeAffectsLifeTime;

			ar& _inheritParticleColor;

			ar& _alpha_Ratio_Lifetime;
			ar& _color_Ratio_Lifetime;

			ar& _widthModifierOption;
			ar& _widthOverTrail;

			ar& _alpha_Ratio_Trail;
			ar& _color_Ratio_Trail;

			ar& _generateLightingData;
			ar& _shadowBias;

			ar& _trailVertexCount;

			ar& _scrollModifierOption;
			ar& _scrollXSpeed;
			ar& _scrollYSpeed;

			ar& _condition;
			ar& _recordTime;
		}

	};
	struct Particle_Renderer
	{
		Particle_Renderer() :_useModule(true),
			_renderMode(RenderMode::Billboard), _blendState(BlendState::OIT_Default),
			_meshName(_T("")), _texturePath(_T("")), _traillTexturePath(_T("")),
			_renderAlignment(RenderAlignment::View), _speedScale(0), _lengthScale(2)
		{
		}
		bool operator==(const Particle_Renderer& other) const
		{
			if (
				_useModule != other._useModule ||
				_renderMode != other._renderMode ||
				_blendState != other._blendState ||
				_meshName != other._meshName ||
				_texturePath != other._texturePath ||
				_traillTexturePath != other._traillTexturePath ||
				_renderAlignment != other._renderAlignment ||
				_speedScale != other._speedScale ||
				_lengthScale != other._lengthScale ||
				_masking != other._masking
				)
				return false;
			return true;
		}
		enum class RenderMode
		{
			Billboard,
			StretchedBillboard,
			HorizontalBillboard,
			VerticalBillboard,
			Mesh,
			None
		};
		enum class BlendState
		{
			OIT_Default,
			OIT_Additive,
			Foward
		};
		enum class RenderAlignment
		{
			View,
			World,
			Local,
			Velocity
		};
		enum class Masking
		{
			NoMasking,
			VisibleInsideMask,
			OutsideMask
		};
		bool _useModule;

		RenderMode _renderMode;

		BlendState _blendState;

		tstring _meshName;

		tstring _texturePath;			// ��ƼŬ ����Ʈ�� �ؽ����� �ּ�.

		tstring _traillTexturePath;			// ��ƼŬ ����Ʈ�� �ؽ����� �ּ�.

		RenderAlignment _renderAlignment;

		float _speedScale;

		float _lengthScale;

		Masking _masking;

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _useModule;

			ar& _renderMode;

			ar& _blendState;

			ar& _meshName;

			ar& _texturePath;

			ar& _traillTexturePath;

			ar& _renderAlignment;

			ar& _speedScale;

			ar& _lengthScale;

			ar& _masking;
		}
	};
	// ��ƼŬ �ý����� ����ϱ� ���� �������̽�
	// �� ���� ���� �ý����� �����Ѵ�.
	struct RenderingData_Particle
	{
		RenderingData_Particle() :
			_commonInfo(),
			_emission(),
			_color_Over_Lifetime(),
			_velocity_Over_Lifetime(),
			_size_Over_Lifetime(),
			_rotation_Over_Lifetime(),
			_texture_Sheet_Animaition(),
			_objectID(0),
			_isDelete(false),
			_childrens()
			, shaderName(),
			_rasterizerState(RASTERIZER_STATE::SOLID),
			_particleCount(0)
		{}
		~RenderingData_Particle()
		{
			memset(this, 0, sizeof(RenderingData_Particle));
		}
		//------------------------------------------------ ��� -------------------------------------------
		Particle_CommonInfo _commonInfo;

		Particle_Emission _emission;

		Particle_Shape _shape;

		Particle_Velocity_over_Lifetime _velocity_Over_Lifetime;

		Particle_Limit_Velocity_Over_Lifetime _limit_Velocity_Over_Lifetime;

		Particle_Force_over_LifeTime _force_Over_Lifetime;

		Particle_Color_over_Lifetime _color_Over_Lifetime;

		Particle_Size_Over_Lifetime _size_Over_Lifetime;

		Particle_Rotation_Over_Lifetime _rotation_Over_Lifetime;

		Particle_Noise _noise;

		Particle_Collision _collision;

		Particle_Texture_Sheet_Animation _texture_Sheet_Animaition;

		Particle_Trails _trails;

		Particle_Renderer _renderer;
		//------------------------------------------------ ��� -------------------------------------------

		unsigned int _objectID; // ��ƼŬ ID ���ҽ� �Ŵ����� ������ ���̵�, ������Ʈ ID�� �������.

		std::vector<std::string> shaderName; // � ���̴��� ����ϴ���.

		std::vector<RenderingData_Particle> _childrens;

		bool _isDelete; // ��ƼŬ�� �� ��������� �Ҵ� ���� �ϱ� ����. ��ƼŬ�� ���ο��� ������Ʈ Ǯ ������ ���� ���ϴ� ������ ��ƼŬ���� ������ ũ�Ⱑ �ٸ��� �����̴�.

		RASTERIZER_STATE _rasterizerState;

		unsigned int _particleCount; // ���� ����� ��ƼŬ�� ����.
		/**
		* \brief ���� ���� ��ǥ��
		* \brief RenderingData, Common.hlsli �� �����ϵ��� ����..!
		*/
		unsigned int GetFlag()
		{
			unsigned int flag = 0;

			if (_commonInfo._useModule) flag |= 1 << 0;
			if (_emission._useModule) flag |= 1 << 1;
			if (_shape._useModule) flag |= 1 << 2;
			if (_velocity_Over_Lifetime._useModule) flag |= 1 << 3;
			if (_force_Over_Lifetime._useModule) flag |= 1 << 4;
			if (_color_Over_Lifetime._useModule) flag |= 1 << 5;
			if (_size_Over_Lifetime._useModule) flag |= 1 << 6;
			if (_rotation_Over_Lifetime._useModule) flag |= 1 << 7;
			if (_noise._useModule) flag |= 1 << 8;
			if (_collision._useModule) flag |= 1 << 9;
			if (_texture_Sheet_Animaition._useModule) flag |= 1 << 10;
			if (_trails._useModule) flag |= 1 << 11;
			if (_renderer._useModule) flag |= 1 << 12;

			if (_shape._shape == Particle_Shape::Shape::Sphere) flag |= 1 << 13;
			if (_shape._shape == Particle_Shape::Shape::Hemisphere) flag |= 1 << 14;
			if (_shape._shape == Particle_Shape::Shape::Cone) flag |= 1 << 15;
			if (_shape._shape == Particle_Shape::Shape::Donut) flag |= 1 << 16;
			if (_shape._shape == Particle_Shape::Shape::Box) flag |= 1 << 17;
			if (_shape._shape == Particle_Shape::Shape::Circle) flag |= 1 << 18;
			if (_shape._shape == Particle_Shape::Shape::Rectangle) flag |= 1 << 19;

			if (_renderer._renderMode == Particle_Renderer::RenderMode::Billboard) flag |= 1 << 20;
			if (_renderer._renderMode == Particle_Renderer::RenderMode::StretchedBillboard) flag |= 1 << 21;
			if (_renderer._renderMode == Particle_Renderer::RenderMode::HorizontalBillboard) flag |= 1 << 22;
			if (_renderer._renderMode == Particle_Renderer::RenderMode::VerticalBillboard) flag |= 1 << 23;
			if (_renderer._renderMode == Particle_Renderer::RenderMode::Mesh) flag |= 1 << 24;

			if (_commonInfo._space == Space::World) flag |= 1 << 25;

			if (_limit_Velocity_Over_Lifetime._useModule) flag |= 1 << 26;

			return flag;
		}

	protected:
		friend class boost::serialization::access;
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& _commonInfo;

			ar& _emission;

			ar& _shape;

			ar& _velocity_Over_Lifetime;

			ar& _limit_Velocity_Over_Lifetime;

			ar& _force_Over_Lifetime;

			ar& _color_Over_Lifetime;

			ar& _size_Over_Lifetime;

			ar& _rotation_Over_Lifetime;

			ar& _noise;

			ar& _collision;

			ar& _texture_Sheet_Animaition;

			ar& _trails;

			ar& _renderer;

			ar& _objectID;

			ar& shaderName;

			ar& _childrens;

			ar& _isDelete;

			ar& _rasterizerState;

			ar& _particleCount;
		}
	};
}