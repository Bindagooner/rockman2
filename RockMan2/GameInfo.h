#pragma once

#include "Global.h"
class CGameInfo
{
	CGameInfo();

	~CGameInfo();

	static CGameInfo* _instance;

	//-----------------------------------------------------------------------------
	// 	Màn chơi hiện tại của Game. Mặc định là ID_LEVEL_1 - Màn kéo
	//-----------------------------------------------------------------------------
	int	_idLevelGame;

	//-----------------------------------------------------------------------------
	// 	Điểm số người chơi
	//-----------------------------------------------------------------------------
	int _score;

	//-----------------------------------------------------------------------------
	// 	Giá trị mỗi bonus
	//-----------------------------------------------------------------------------
	int _bonusValue;

	//-----------------------------------------------------------------------------
	// 	tổng số bonus rockman lấy được
	//-----------------------------------------------------------------------------
	unsigned	int _totalBonus;

	//vector<Skill> _skills;

public:
	static CGameInfo* getInstance();

	void setScore(int score);
	int getScore();

	void setBonusValue(int bonusvalue);
	int getBonusValue();

	void setBonus(unsigned int totalBonus);
	int getTotalBonus();

	void setLevel(int level);
	int getLevel();

	/*vector<Skill> getSkills();
	void addSkill(Skill skill);
	bool hasSkill(Skill skill);*/

	string to_string(unsigned int score, unsigned int lenght = 0);

	//-----------------------------------------------------------------------------
	// 	Tải thông tin game lên từ file
	//-----------------------------------------------------------------------------
	void load();

	//-----------------------------------------------------------------------------
	// 	Lưu thông tin game xuống từ file
	//-----------------------------------------------------------------------------
	void save();
};

