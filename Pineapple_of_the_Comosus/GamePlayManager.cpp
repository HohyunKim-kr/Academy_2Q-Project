#include "GamePlayManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "PineAppleTile.h"
#include "Turret.h"
#include "../D2DEngine/BoxCollider.h"

std::wstring hmm;
void GamePlayManager::Update(float deltaTime)
{
	// �ͷ� ��ġ��
	if (isDrag == true) {
		if (!InputManager::GetInstance().GetPrevMouseState().right && InputManager::GetInstance().GetMouseState().right) {
			isDrag = false;
			dragObj->SetActive(false);
		}

		auto curWorldObject = EventSystem::GetInstance().GetCurrWorldObject();
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

		dragObj->transform->pos.worldPosition = camera->ScreenToWorldPosition(mousePos);

		if (curWorldObject != nullptr) {
			auto pTile = curWorldObject->GetComponent<PineAppleTile>();
			if (pTile != nullptr) {
				if (pTile->IsPlaceable() == false) return;
				dragObj->transform->pos.worldPosition.x = pTile->gameObject->transform->m_WorldTransform.dx;
				dragObj->transform->pos.worldPosition.y = pTile->gameObject->transform->m_WorldTransform.dy;

				if ((!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left))
				{
					//��ġ ������ �� ��Ŭ�� �� ��ġ.
					isDrag = false;
					dragObj->SetActive(false);

					// �ͷ� Ȱ��ȭ
					pTile->turret->SetActive(true);
					pTile->SetActivateTurret(hmm);
				}
			}
		}
	}

	// �ͷ� ���ÿ�
	else if (isDrag == false && EventSystem::GetInstance().GetCurrUIObject() == nullptr) {
		if (isSelect == true) {
			Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
			mousePos = camera->ScreenToWorldPosition(mousePos);

			Vector2 center = (mousePos + startPos) * 0.5f;
			Vector2 extent = (mousePos - startPos) * 0.5f;
			extent.x = std::abs(extent.x);
			extent.y = std::abs(extent.y);

			multiSelectBox->SetCenter(center);
			multiSelectBox->SetExtent(extent);
			if (InputManager::GetInstance().GetPrevMouseState().left && !InputManager::GetInstance().GetMouseState().left) {
				// todo?
				isSelect = false;
				selectBoxObj->SetActive(false);
			}
		}
		else if (!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left) {
			Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

			startPos = camera->ScreenToWorldPosition(mousePos);
			isSelect = true;
			selectBoxObj->SetActive(true);
			multiSelectBox->SetCenter({0.f, 0.f});
			multiSelectBox->SetExtent({ 0.f, 0.f });
		}
	}
}
void GamePlayManager::StartBatch(int type)
{
	isDrag = true;
	dragObj->SetActive(true);
	auto spr = dragObj->GetComponent<SpriteRenderer>();
	hmm = type == 0 ? L"../Resource/Sun.png" : L"../Resource/Earth.png";
	spr->LoadTexture(hmm);
}
