#include "WinApp4.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/PublicData.h"

#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/TextRenderer.h"
#include "../D2DEngine/Button.h"
#include "../D2DEngine/ImageUIRenderer.h"

#include "DataManager.h"
#include "TestDropDown.h"

#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "GamePlayManager.h"

void WinApp4::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y)
{
	// �⺻ �ʱ�ȭ + ī�޶� ����
	__super::Initialize(hInstance, nCmdShow, x, y);
	scene = new Scene();
	auto camera = scene->CreateGameObject<GameObject>();
	auto pCam = camera->CreateComponent<Camera>();
	scene->SetMainCamera(pCam);

	// ���� �Ŵ��� �巡�׿� ���, ���ξ��� ��ġ, �ͷ� ���ξ��� �� ������ ���� ������.
	auto gmObj = scene->CreateGameObject<GameObject>();
	auto GamaManager = gmObj->CreateComponent<GamePlayManager>();

	// �ڸ𼭽� ���ξ��� (�̳� ŭ)
	auto paObj = scene->CreateGameObject<GameObject>();
	paObj->transform->pos.worldPosition = { 0.f, -200.f };
	auto pineApple = paObj->CreateComponent<MainPineApple>();

	auto turretTest = scene->CreateGameObject<GameObject>();
	auto drop = turretTest->CreateComponent<TestDropDown>();
	drop->camera = scene->camera;
	auto circle = turretTest->CreateComponent<CircleCollider>();
	circle->SetRadius(100.f);

	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { -200.f, 200.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 0;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 0.f, 200.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 1;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 200.f, 200.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 2;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { -100.f, 100.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 3;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 100.f, 100.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 4;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { -200.f, 0.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 5;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 0.f, 0.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 6;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
	{
		// ���ξ��� Ÿ�ϵ�
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 200.f, 0.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 7;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);
	}
}

void WinApp4::Update(float deltaTime)
{
	__super::Update(deltaTime);

	scene->Update(deltaTime);
}

void WinApp4::Render(D2DRenderer* _render)
{
	__super::Render(_render);
	scene->Render(_render);
}

void WinApp4::Uninitialize()
{
	__super::Uninitialize();
}
