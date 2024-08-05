#pragma once

// ignore layer�� tag�� ����� eventSystem�� ������� �ʰ� ������ ������
class GameObject;
class Scene;

struct IPointerEnter {

};
struct IPointerStay {

};
struct IPointerExit {

};
struct IClickDown {

};
struct IClick {

};
struct IClickUp {

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

