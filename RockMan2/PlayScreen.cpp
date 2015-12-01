#include "PlayScreen.h"


CPlayScreen::CPlayScreen() : CScreen()
{
	_rockman = new CRockman();
	_rockman->init();
	loadMap();

	_typeID = ID_SCREEN_PLAY;
}


CPlayScreen::~CPlayScreen()
{
}

void CPlayScreen::updateInput(CInput* input)
{
	_rockman->updateInput(input);
}

void CPlayScreen::update(CGameTime* gametime)
{
	_rockman->update(gametime);

	//Kiểm tra và dời khung màn hình
	if (_cameraPath->isHorizontalLine())
	{
		_screenPosition.x = _rockman->_position.x;
		_screenPosition = _cameraPath->calculatePointOnPathWith(_screenPosition);
	}
	
	_camera->setCamPosition(Vector2(_screenPosition.x - SCREEN_WIDTH / 2, _screenPosition.y + SCREEN_HEIGHT / 2 ));
}

void CPlayScreen::render(CGameTime* gametime, CGraphic* graphic)
{
	graphic->beginDraw(_camera);	
	renderBackground(graphic, _camera->getViewport());
	vector<CGameObject*>* objectInViewPort = new vector<CGameObject*>();
	_quadNodeCollision.getObjectInVP(_camera->getViewport(), objectInViewPort);

	for (int i = 0; i < objectInViewPort->size(); i++)
	{
		(*objectInViewPort)[i]->render(gametime, graphic);
	}


	_rockman->render(gametime, graphic);
	graphic->endDraw();
}

void CPlayScreen::loadMap()
{
	wchar_t* mapData;
	wchar_t* mapImage;
	/*switch (CGameInfo::getInstance()->getLevel())
	{
	case ID_LEVEL_CUT:
		mapData = MAP_DATA_CUT_MAN;
		mapImage = MAP_IMAGE_CUT_MAN;
		break;
	case ID_LEVEL_GUTS:
		mapData = MAP_DATA_GUTS_MAN;
		mapImage = MAP_IMAGE_GUTS_MAN;
		break;
	case ID_LEVEL_BOOM:
		mapData = MAP_DATA_BOOM_MAN;
		mapImage = MAP_IMAGE_BOOM_MAN;
		break;
	default:return;
	}*/

	mapData = MAP_DATA_CUT_MAN;
	mapImage = MAP_IMAGE_CUT_MAN;
	_tteBackground = CTexture(mapImage, D3DCOLOR_XRGB(255, 255, 255));

#pragma region Chuẩn bị một số biến cần thiết cho việc đọc dữ liệu từ file .txt

	ifstream fs;		// Luồng đọc file map
	string line;		// Chuỗi đọc file map

	// Mở file và đọc, nếu không được thì out
	fs.open(mapData, ios::in);
	if (!fs.is_open())
	{
		OutputDebugString(L"Can not open map file");
		return;
	}

	istringstream iss;								// Luồng string đọc từ file
	int countObj, countNode = 0;					// Số lượng phần tử đối tượng trên màn hình
	map<int, CGameObject*> objects;						// Danh sách các đối tượng trên màn hình
	map<int, CQuadNode*> lstNodes;
	vector<int> objectIDs;							// Danh sách các objectID
	// Các biến lưu giá trị được lưu trữ của một CObject
	int nodeID, objID, typeID, posX, posY, width, height, posXCollide, posYCollide, widthCollide, heightCollide;

#pragma endregion

#pragma region Tiến hành đọc dữ liệu từ file .txt

#pragma region Lấy thông tin ma trận tile

	getline(fs, line);
	if (line.compare("#Tile_Matrix") == 0)
	{
		getline(fs, line);								// Bỏ qua dòng "Total_Row	Total_Column	Total_Tile"
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> _countRow >> _countColumn >> _totalTile;	// Đẩy giá trị tổng số dòng, cột, tổng số tile vào biến
		getline(fs, line);								// Bỏ qua dòng "#Tile_Matrix_Value"

		// Tạo mảng hai chiều lưu ma trận tile
		for (int i = 0; i < _countRow; i++)
		{
			vector<int> row;
			row.resize(_countColumn);
			_tileMatrix.push_back(row);
		}

		// Tiến hành đọc dữ liệu
		for (int i = 0; i < _countRow; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			for (int j = 0; j < _countColumn; j++)
				iss >> _tileMatrix[i][j];
		}
		getline(fs, line);					// Bỏ qua dòng "#Tile_Matrix_End"
	}

#pragma endregion
#pragma region Lấy danh sách các đối tượng

	vector<Vector2> fallingPoints;

	getline(fs, line);
	if (line.compare("#Objects") == 0)
	{
		getline(fs, line);					// Bỏ quan dòng "ObjCount"
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> countObj;
		getline(fs, line);					// Bỏ qua dòng "ObjID	TypeID	PosX	PosY	Width	Height PosXCollide	PosYCollide	WidthCollide	HeightCollide"

		// Đọc danh sách các đối tượng
		for (int i = 0; i < countObj; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			iss >> objID >> typeID >> posX >> posY >> width >> height >> posXCollide >> posYCollide >> widthCollide >> heightCollide;
			CGameObject* obj;
			switch (typeID)
			{
				//TODO tao moi doi tuong game
			case ID_FALLING_POINT:
				obj = new CBlock();
				obj->_id = objID;
				obj->_idType = typeID;
				obj->_position = Vector2((float)posX, (float)posY);
				obj->_size = Vector2((float)width, (float)height);
				obj->init();
				/*obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);*/
				objects.insert(pair<int, CGameObject*>(objID, obj));

				// Lọc lấy danh sách các điểm rơi
				fallingPoints.push_back(obj->_position);
				break;
			case ID_ROCK:
				obj = new CRock();
				obj->_id = objID;
				obj->_idType = typeID;
				obj->_position = Vector2((float)posX, (float)posY);
				obj->_size = Vector2((float)width, (float)height);
				obj->init();
				/*obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);*/
				objects.insert(pair<int, CGameObject*>(objID, obj));

			default:
				break;
			}
		}
		getline(fs, line);					// Bỏ qua dòng "#Objects_End"
	}
#pragma endregion

#pragma region Đọc thông tin ma trận ma chạm

	getline(fs, line);
	if (line.compare("#Quadtree_Collision") == 0)
	{
		getline(fs, line);						// Bỏ qua dòng "NodeCount"
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> countNode;

		getline(fs, line);						// Bỏ qua dòng "NodeID	PosX	PosY	Width	Height	ObjectCount	ObjectIDs"
		for (int i = 0; i < countNode; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			iss >> nodeID >> posX >> posY >> width >> height >> countObj;
			for (int j = 0; j < countObj; j++)
			{
				iss >> objID;
				objectIDs.push_back(objID);
			}
			CQuadNode *tmpNode = new CQuadNode(nodeID, Vector2(posX, posY), Vector2(width, height), objectIDs, objects);
			lstNodes.insert(pair<int, CQuadNode*>(nodeID, tmpNode));
			objectIDs.clear();
		}
	}
	getline(fs, line);							// Bỏ qua dòng "#Quadtree_Collision_End"

#pragma endregion

#pragma region Đọc thông tin Camera Paths

	getline(fs, line);
	if (line.compare("#Camera_Path_Point") == 0)
	{
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> countNode;		// Đếm số lượng camera path node
		vector<Vector2> cameraPaths;
		for (int i = 0; i < countNode; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			iss >> posX >> posY;
			cameraPaths.push_back(Vector2(posX, posY));
		}
		if (cameraPaths.size()>0)
			_cameraPath->setPaths(cameraPaths);

		getline(fs, line);	// Bỏ qua dòng #Camera_Path_Point_End

		// Dựng cảnh màn chơi
		/*_sceneInfo.buildScene(fallingPoints, cameraPaths);

		findScene(0);*/
	}

#pragma endregion
	
	fs.close();

#pragma region Dựng lại cây tứ phân va chạm

	map<int, CQuadNode*>::iterator it;

	for (it = lstNodes.begin(); it != lstNodes.end(); it++)
	{
		if (it == lstNodes.begin())
			_quadNodeCollision = *it->second;
		else if (it != lstNodes.end())
			_quadNodeCollision.addNode(it->second);
	}
#pragma endregion

#pragma endregion

	/*switch (CGameInfo::getInstance()->getLevel())
	{
	case ID_LEVEL_CUT:
		CResourceManager::stopSound(ID_SOUND_STAGE_SELECT);
		CResourceManager::playASound(ID_SOUND_CUTMAN_STAGE);
		break;
	case ID_LEVEL_GUTS:
		CResourceManager::stopSound(ID_SOUND_STAGE_SELECT);
		CResourceManager::playASound(ID_SOUND_GUTSMAN_STAGE);
		break;
	case ID_LEVEL_BOOM:
		CResourceManager::stopSound(ID_SOUND_STAGE_SELECT);
		CResourceManager::playASound(ID_SOUND_BOMBMAN_STAGE);
		break;
	default:return;
	}*/
}

void CPlayScreen::renderBackground(CGraphic* graphic, Rect viewport)
{
	int startRow = floor(viewport.bottom / TILE_SIZE);
	int endRow = floor(viewport.top / TILE_SIZE) + 1;
	int startColumn = floor(viewport.left / TILE_SIZE);
	int endColumn = floor(viewport.right / TILE_SIZE) + 1;

	int bitmapColumn = (int)sqrt((double)_totalTile) + 1;

	if (startColumn < 0)
		startColumn = 0;
	if (startRow < 0)
		startRow = 0;
	if (endColumn > _countColumn)
		endColumn = _countColumn;
	if (endRow > _countRow)
		endRow = _countRow;

	Vector2 startDrawPos = Vector2(startColumn*TILE_SIZE + TILE_SIZE / 2, endRow*TILE_SIZE - TILE_SIZE / 2) /*+ _shakePointRand*/;

	for (int i = endRow; i > startRow; i--)
	{
		for (int j = startColumn; j < endColumn; j++)
		{
			Rect desRect;
			desRect.top = (_tileMatrix[_countRow - i][j] / bitmapColumn)* TILE_SIZE;
			desRect.left = (_tileMatrix[_countRow - i][j] % bitmapColumn)*TILE_SIZE;
			desRect.right = desRect.left + TILE_SIZE;
			desRect.bottom = desRect.top + TILE_SIZE;

			graphic->draw(_tteBackground.getTexture(), desRect, startDrawPos, true, Vector2(1.0f, 1.0f), SpriteEffects::NONE);

			startDrawPos.x += TILE_SIZE;
		}
		startDrawPos.y -= TILE_SIZE;
		startDrawPos.x -= TILE_SIZE*abs(startColumn - endColumn);
	}
}

void CPlayScreen::findScene(unsigned int startIndex)
{
	// Build lại camera path và lấy điêm rơi thích hợp
	map<int, Vector2> sceneInfo = _sceneInfo.getScene(startIndex);
	_cameraPath->setStartIndex(sceneInfo.begin()->first);
	_cameraPath->setEndIndex(sceneInfo.begin()->first + 1);

	// Chọn điểm đặt màn hình và rockman
	int distanceY = _cameraPath->getStartPoint().y - _cameraPath->getEndPoint().y;
	if (distanceY == 0)
	{
		_cameraPath->setCameraPointOnPath(_cameraPath->getPaths()[sceneInfo.begin()->first]);

		//_rockman->ResetAll();
		_rockman->_position = sceneInfo.begin()->second;
		_rockman->_position.y += SCREEN_HEIGHT / 2;

		_screenPosition = _rockman->_position;
		_screenPosition = _cameraPath->calculatePointOnPathWith(_screenPosition);
		_camera->setCamPosition(Vector2(_screenPosition.x - SCREEN_WIDTH / 2, _screenPosition.y + SCREEN_HEIGHT / 2));
		
	}
	else if (distanceY > 0)
	{
		Vector2 pointOnPath = _cameraPath->getEndPoint();
		pointOnPath.y += SCREEN_HEIGHT / 2;
		_cameraPath->setCameraPointOnPath(pointOnPath);

		//_rockman.ResetAll();
		_rockman->_position = sceneInfo.begin()->second;
		_rockman->_position.y += SCREEN_HEIGHT;

		_screenPosition = pointOnPath;
		_camera->setCamPosition(Vector2(_screenPosition.x - SCREEN_WIDTH / 2, _screenPosition.y + SCREEN_HEIGHT / 2));
	}
	else {
		Vector2 pointOnPath = _cameraPath->getStartPoint();
		pointOnPath.y += SCREEN_HEIGHT / 2;
		_cameraPath->setCameraPointOnPath(pointOnPath);

		//_rockman.ResetAll();
		_rockman->_position = sceneInfo.begin()->second;
		_rockman->_position.y += SCREEN_HEIGHT;

		_screenPosition = pointOnPath;
		_camera->setCamPosition(Vector2(_screenPosition.x - SCREEN_WIDTH / 2, _screenPosition.y + SCREEN_HEIGHT / 2));
	}
}