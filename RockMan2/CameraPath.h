#pragma once
#include "Global.h"
class CCameraPath
{
public:
	CCameraPath();
	~CCameraPath();
	Vector2 calculatePointOnPathWith(Vector2 newPosition);
	Vector2 getCameraPointOnPath();
	void setCameraPointOnPath(Vector2 pointOnPath);
	Vector2 getStartPoint();
	Vector2 getEndPoint();
	Vector2 getNextPoint();
	Vector2 getNextOfNextPoint();
	Vector2 getPreviousPoint();
	Vector2 getPrevOfPreviousPoint();
	int  getStartIndex();
	void setStartIndex(int startIndex);
	int  getEndIndex();
	void setEndIndex(int endIndex);
	void setPaths(vector<Vector2> paths);
	vector<Vector2> getPaths();
	bool isHorizontalLine();
	bool isVerticalLine();
	bool canMoveLeft();
	bool canMoveRight();
	bool canMoveUp();
	bool canMoveDown();
private:

	Vector2 _pointOnPath;			// biến thể hiện tọa độ
	vector<Vector2>	_paths;			// Ma trận điểm tâm camera
	int _startIndex, _endIndex;		// Các chỉ số truy cập path, _pointOnPath sẽ nằm giữa cặp giá trị theo 2 chỉ số này
};

