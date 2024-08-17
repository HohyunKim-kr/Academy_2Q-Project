#pragma once
#include "../D2DEngine/Collider.h"
#include <unordered_set>
class EnemyColliderNotify;
class ComosusLightSelector : public Component, public IColliderNotify
{
	std::unordered_set<EnemyColliderNotify*> container;
public:
	void ClearContainer();
	std::unordered_set<EnemyColliderNotify*> GetContainer();
	// IColliderNotify��(��) ���� ��ӵ�
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

};

