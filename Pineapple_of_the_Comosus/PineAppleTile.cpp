#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "../D2DEngine/GameObject.h"
void PineAppleTile::Update(float deltaTime)
{
}

void PineAppleTile::IPointerEnter()
{
	pApple->PrintIndex(index);
}

void PineAppleTile::IPointerStay()
{
}

void PineAppleTile::IPointerExit()
{
}

bool PineAppleTile::IsPlaceable()
{
	// �ͷ��� Ȱ��ȭ�Ǿ����� �ʴٸ� ��ġ������ Ÿ��.
	return turret->isActive == false;
}
