#include "UpgradeItem.h"

UpgradeItem::UpgradeItem()
{
}

bool UpgradeItem::UpgradeAble()
{
	/*if (������� > ��ȭ���)
	{
		return true;
	}
	*/
	return false;
}

void UpgradeItem::UpgradeTurret()
{
	if (UpgradeAble())
	{
		// �ش��ϴ� �ͷ� ������Ʈ lv++;

		// curGold -= �ͷ� ��ȭ cost 
	}
}

void UpgradeItem::Update(float deltaTime)
{
}
