#pragma once
#include "Vector.h"
// ignore layer�� tag�� ����� eventSystem�� ������� �ʰ� ������ ������
class GameObject;
class Scene;

struct IPointer {
	virtual void IPointerEnter() = 0;
	virtual void IPointerStay() = 0;
	virtual void IPointerExit() = 0;

};

struct IClick {
	virtual void IClickDown() = 0;
	virtual void IClickUp() = 0;
};

struct PointerEventData {
	bool isLeftClick;
	Vector2 delta; // ���� �����Ӱ� ���� �������� ���콺 ��ġ ����
	Vector2 position; // ���콺 ���� ��ġ
	Vector2 pressPosition; // ���� ���콺 ���� ��ġ

	GameObject* pointerDrag; // �巡������ ������Ʈ
	GameObject* pointerEnter;
	GameObject* pointerPress;
};

class EventSystem
{
private:
	EventSystem() {};
	~EventSystem() {};


	GameObject* currentWorldObject = nullptr;
	GameObject* currentUIObject = nullptr;
	GameObject* currentObject = nullptr;

	GameObject* prevWorldObject = nullptr;
	GameObject* prevUIObject = nullptr;
	GameObject* prevObject = nullptr;

	IPointer* curPointer = nullptr;
	IPointer* prevPointer = nullptr;

public:
	static EventSystem& GetInstance();

	void Update(Scene* scene, float delta);
	void ResetUpdate();

	GameObject* GetCurrWorldObject(); // ���� �տ��ִ� ������ ������Ʈ�� ������.
	GameObject* GetCurrUIObject();	// ���� �տ��ִ� UI�� ������Ʈ�� ������.
	GameObject* GetCurrObject();	// ���� �տ��ִ� UI�� ������Ʈ�� ������.
};

