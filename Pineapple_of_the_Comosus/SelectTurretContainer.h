#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
#include <unordered_set>
class Turret;
class SelectTurretContainer : public Component, public IColliderNotify
{
private:
	std::unordered_set<Turret*> container;
public:
	SelectTurretContainer() {}
	virtual ~SelectTurretContainer() {}

	virtual void Update(float delta);

	// ������ GamePlayManager�� �����̳� Ž�� �� �Ұ���.
	void ClearContainer();
	std::unordered_set<Turret*> GetContainer();

	// IColliderNotify��(��) ���� ��ӵ�
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

};

