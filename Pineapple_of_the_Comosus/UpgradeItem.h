#pragma
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class UpgradeItem : public Component
{
private:
public:
	UpgradeItem();
	// �ͷ��� ��ġ�� Ÿ�� ��Ŭ�� 

	// ��ȭ ���� ���� üũ 
	bool UpgradeAble();

	// �ͷ� ��ȭ
	void UpgradeTurret();

	// ��ȭ ���� ������Ʈ 
	void Update(float deltaTime);
};

