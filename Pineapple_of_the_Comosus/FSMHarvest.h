//#pragma once
//#include "../D2DEngine/FiniteStateMachine.h"
//#include <iostream>
//
//// �⺻ ���� (��� ����)
//class TentacleDefault : public FSMState
//{
//public:
//    TentacleDefault(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Tentacle is in default state..." << std::endl;
//        // �⺻ ���¿����� �ʱ�ȭ �۾�
//    }
//
//    void Update(float deltaTime) override {
//        // �⺻ ���¿����� ���� ó��
//        // Ư�� ������ �����Ǹ� ���� ���·� ����
//        if () {
//            fsm->SetState("TentacleDownState");
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Exiting default state." << std::endl;
//        // �⺻ ���� ���� �� ó���� �ڵ�
//    }
//};
//
//// �˼��� �������� ����
//class TentacleDownState : public FSMState
//{
//public:
//    TentacleDownState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Tentacle is moving down..." << std::endl;
//        // �˼��� �������� �ִϸ��̼� ���� �ڵ�
//    }
//
//    void Update(float deltaTime) override {
//        // �˼��� �������� ���� ���� ó��
//        if (/* �˼��� �� �����Դٸ� */) {
//            fsm->SetState("TentacleUpState");
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Tentacle has reached the pineapple." << std::endl;
//        // ���� ���� �� ó���� �ڵ�
//    }
//};
//
//// ���ξ����� �������� ����
//class TentacleUpState : public FSMState
//{
//public:
//    TentacleUpState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Tentacle is moving up with the pineapple..." << std::endl;
//        // �˼��� �ö󰡴� �ִϸ��̼� ���� �ڵ�
//    }
//
//    void Update(float deltaTime) override {
//        // �˼��� �ö󰡴� ���� ���� ó��
//        if (/* �˼��� �� �ö󰬴ٸ� */) {
//            // ���ξ��� ��ġ�� ȭ������ ������� ���ξ��� ��������Ʈ ����
//            // ��� �ͷ� ȯ�� ��� = ��� + ȯ�� �ݾ� 
//            // ��Ȯ ���� �˾� ���·� ��ȯ
//            fsm->SetState("ShowPopupState");
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Tentacle has taken the pineapple." << std::endl;
//        // ���� ���� �� ó���� �ڵ�
//    }
//};
//
//// �˾��� �ߴ� ����
//class ShowPopupState : public FSMState
//{
//public:
//    ShowPopupState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Showing popup..." << std::endl;
//        // �˾� ǥ�� �ڵ�
//    }
//
//    void Update(float deltaTime) override {
//        // �˾��� ǥ�õǴ� ������ ���� ó��
//        if (/* �˾��� �� ���ٸ� */) {
//            // �˾� ǥ�� �� �ٸ� ���·� ��ȯ�ϰų� ����
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Popup has been shown." << std::endl;
//        // ���� ���� �� ó���� �ڵ�
//    }
//};
//
//// ���ξ��� �������� ���� 
//class ShowPopupState : public FSMState
//{
//public:
//    ShowPopupState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Showing popup..." << std::endl;
//        // �˾� ǥ�� �ڵ�
//    }
//
//    void Update(float deltaTime) override {
//        // �˾��� ǥ�õǴ� ������ ���� ó��
//        if (/* �˾��� �� ���ٸ� */) {
//            // �˾� ǥ�� �� �ٸ� ���·� ��ȯ�ϰų� ����
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Popup has been shown." << std::endl;
//        // ���� ���� �� ó���� �ڵ�
//    }
//};
//
//// FSMHarvest Ŭ���� ����
//class FSMHarvest : public FSMState
//{
//public:
//    FSMHarvest(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {
//        
//    }
//
//    void Enter() override {
//        // �ʱ� ���·� ����
//        fsm->SetState("TentacleDefault");
//    }
//
//    void Update(float deltaTime) override {
//        if (fsm->m_pCurrState) {
//            fsm->m_pCurrState->Update(deltaTime);
//        }
//    }
//
//    void Exit() override {
//        // ���� ���� �� ó���� �ڵ�
//    }
//};
