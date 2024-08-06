#pragma once
#include "Vector.h"
// ignore layer�� tag�� ����� eventSystem�� ������� �ʰ� ������ ������
class GameObject;
class Scene;

struct IPointer {

};

struct IClick {

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
public:
	static EventSystem& GetInstance();

	void Update(Scene* scene, float delta);
	void ResetUpdate();

	GameObject* GetCurrWorldObject(); // ���� �տ��ִ� ������ ������Ʈ�� ������.
	GameObject* GetCurrUIObject();	// ���� �տ��ִ� UI�� ������Ʈ�� ������.
};

