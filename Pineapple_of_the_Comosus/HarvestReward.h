#pragma once
#include <vector>
#include <string>


struct reward
{
    std::wstring name;
};


class HarvestReward
{
public:
    // ���� ���� ������ ����
    std::vector<int> rewards; // ������ ����Ʈ

public:
    HarvestReward();
    ~HarvestReward();

    // ���� �������� �ʱ�ȭ�ϴ� �Լ�
    void InitializeRewards();


    // UI�� ���� �������� ǥ���ϴ� �Լ� (������ UI �ý��ۿ� ����)
    void DisplayRewardsUI();


};

