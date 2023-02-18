#include "ObjectManager.h"
#include "QuadTree.h"
namespace Muscle
{
	ObjectManager::ObjectManager() :_isStart(false), _gameObjects(), m_DeleteObjects(), m_InsertObjects(), m_Colliders()
	{
		_QuadTree = std::make_shared<QuadTree>();
	}

	ObjectManager::~ObjectManager()
	{
		DeleteAll();

		_QuadTree.reset();

	}
	std::shared_ptr<GameObject> ObjectManager::GetGameObject(unsigned int objectID)
	{
		if (_gameObjects.find(objectID) != _gameObjects.end())
			return _gameObjects[objectID];
		else
			return nullptr;
	}

	//��ü �߰�
	void ObjectManager::InsertObject(std::shared_ptr<GameObject> obj)
	{
		if (_isStart)
		{
			m_InsertObjects.emplace_back(obj);

			return;
		}

		if (!obj) return;
		_gameObjects.insert({ obj->GetObjectID(),obj });
	}

	//Ư�� ��ü ����
	void ObjectManager::DeleteObject(std::shared_ptr<GameObject> obj)
	{
		if (!obj) return;

		m_DeleteObjects.push_back(obj);

		obj->_isDelete = true;

		if (!obj->GetChildrens().empty())
		{
			for (auto& iter : obj->GetChildrens())
			{
				DeleteObject(iter);
			}
		}

	}

	//������Ʈ�� �ݶ��̴� ���� ����
	void ObjectManager::DeleteAll()
	{
		for (auto& iter : _gameObjects)
		{
			iter.second->Finalize();
			iter.second.reset();
		}
		_gameObjects.clear();

		for (auto& iter : m_Colliders)
		{
			iter.second->Finalize();
			iter.second.reset();
		}
		m_Colliders.clear();

		for (auto& iter : m_DeleteObjects)
		{
			iter->Finalize();
			iter.reset();
		}
		m_DeleteObjects.clear(); //���� ���� ������Ʈ��.

		for (auto& iter : m_InsertObjects)
		{
			iter->Finalize();
			iter.reset();
		}
		m_InsertObjects.clear(); //�߰� ���� ������Ʈ��.

		_QuadTree->ClearNode();
	}

	void ObjectManager::Start()
	{
		_isStart = true;

		for (auto& iter : _gameObjects)
		{
			iter.second->Start();

			std::shared_ptr<Collider> _Collider = iter.second->GetComponent<Collider>();

			if (_Collider)
				m_Colliders.insert({ _Collider->_ColliderID ,_Collider });
		}
	}

	void ObjectManager::Update()
	{
		//��� ������Ʈ ������Ʈ ������
		for (auto& iter : _gameObjects)
		{
			if (iter.second->GetIsEnable())
				iter.second->Update();
		}

		//��� ������Ʈ ������Ʈ ������
		for (auto& iter : _gameObjects)
		{
			if (iter.second->GetIsEnable())
				iter.second->LateUpdate();
		}

		// �浹 ���� ���� ������Ʈ
		ColliderUpdate();

	}

	//��� ������Ʈ ����
	void ObjectManager::Render()
	{
		for (auto& iter : _gameObjects)
		{
			if (iter.second->GetIsRender())
				iter.second->Render();
		}
	}
	void ObjectManager::DeleteInsertUpdate()
	{
		// ������Ʈ ����. Update �����̳� Render ���߿� �����Ǹ� �̻��� �߻�������.. ��� �۾��� ���� ���� �ڿ��� �Ѵ�.



		for (auto iter : m_DeleteObjects)
		{

			if (iter->GetIsEnable())
			{
				iter->SetIsEnable(false);
			}
			auto temp = _gameObjects.find(iter->GetObjectID());
			if (temp != _gameObjects.end())
			{
				std::shared_ptr<Collider> _Collider = temp->second->GetComponent<Collider>();
				if (_Collider)
				{
					m_Colliders.erase(_Collider->_ColliderID);
				}
				temp->second->SetParent(nullptr);

				temp->second->Finalize();

				_gameObjects.erase(temp);
			}
			iter.reset();
		}
		m_DeleteObjects.clear();
		// ������Ʈ �߰�.
		for (auto& iter : m_InsertObjects)
		{
			_gameObjects.insert({ iter->GetObjectID(),iter });

			iter->Start();

			std::shared_ptr<Collider> _Collider1 = iter->GetComponent<Collider>();
			if (_Collider1)
				m_Colliders.insert({ _Collider1->_ColliderID ,_Collider1 });

		}
		if (!m_InsertObjects.empty())
			m_InsertObjects.clear();
	}
	void ObjectManager::ColliderUpdate()
	{
		// y���� ���� ��� ���ҵ� �ϴ� ����Ʈ���� �ϰڴ�!
		//
		// ��ǥ�� �� �����Ӹ��� �޶�������??
		_QuadTree->StartSplit(m_Colliders);


		for (auto& iter : m_Colliders)
		{
			// ������ ����Ʈ ������ �����ϴ� ����� ã�ƾ��Ѵ�..! Todo : 
			iter.second->m_isCollided = false;
			iter.second->m_PrevColliders = iter.second->m_CurColliders;
			iter.second->m_CurColliders.clear();
		}
		for (auto& iter : _QuadTree->GetLeafNodes())
		{

			for (auto Col1 = iter->_values.begin(); Col1 != iter->_values.end(); Col1++)
			{
				if (!Col1->second->GetIsEnable()) continue;
				int a = 0;
				for (auto Col2 = Col1; Col2 != iter->_values.end(); Col2++)
				{
					if (!Col1->second->GetIsEnable()) continue;
					if (!Col2->second->GetIsEnable()) continue;
					if (Col1 == Col2)
						continue;
					const std::string& col1tag = (*Col1).second->GetGameObject()->GetTag();
					const std::string& col2tag = (*Col2).second->GetGameObject()->GetTag();
					if (col1tag == "" || col2tag == "" || // �±װ� ����ְų�,
						col1tag != col2tag // �±װ� �ٸ��� �浹.
						)
					{
						(*Col1).second->ColliderCheck(Col2->second);
					}
				}
			}
		}
		for (auto& iter : m_Colliders)
		{
			for (auto& prev : iter.second->m_PrevColliders)
			{
				prev.second->m_CurColliders;

				const auto& check = iter.second->m_CurColliders.find(prev.first); // ���� ������ �浹�� �ݶ��̴��� �ִ��� �˻�.
				if (check == iter.second->m_CurColliders.end()) // �浹 ���ϴ� ��!
				{
					prev.second->ExitEvent(iter.second);
					iter.second->ExitEvent(prev.second);
				}
				else
				{
					prev.second->StayEvent(iter.second);
					iter.second->StayEvent(prev.second);
				}
				// Enter�Լ��� �ݶ��̴����� �浹 �˻��� �� ȣ���ϰ��ִ�.
			}

		}

	}



}