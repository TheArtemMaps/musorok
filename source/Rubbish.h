
#pragma once
#include "CVehicle.h"

//enum {
//	NUM_RUBBISH_SHEETS = 64
//};

class COneSheet {
public:
	CVector m_basePos;
	CVector m_animatedPos;
	float m_targetZ;
	int8_t m_state;
	int8_t m_animationType;
	uint32_t m_moveStart;
	uint32_t m_moveDuration;
	float m_animHeight;
	float m_xDist;
	float m_yDist;
	float m_angle;
	bool m_isVisible;
	bool m_targetIsVisible;
	COneSheet* m_next;
	COneSheet* m_prev;

public:
	void AddToList(COneSheet* list);
	void RemoveFromList();
};

class CRubbish {
public:
	static bool bRubbishInvisible;
	static int RubbishVisibility;
	//static bool invisibility;
	static COneSheet aSheets[512];
	static COneSheet StartEmptyList;
	static COneSheet EndEmptyList;
	static COneSheet StartStaticsList;
	static COneSheet EndStaticsList;
	static COneSheet StartMoversList;
	static COneSheet EndMoversList;

	static int RubbishTotalTexturesCount;
	static int RubbishTotalTexturesCount2;
	static int RubbishAlpha;
	static int RubbishAlphaNight;
	static int NUM_RUBBISH_SHEETS;
	static float RUBBISH_MAX_DIST;
	static float RUBBISH_FADE_DIST;

	static float widthScale[63];
	static float heightScale[63];

public:
	static void Render();
	static void StirUp(CVehicle* veh);
	static void Update();
	static bool GetWaterLevelNoWaves(float x, float y, float z, float* pOutWaterLevel, float* fUnkn1, float* fUnkn2);
	static void SetVisibility(bool visible);
	static void Init();
	static void Shutdown();
};
