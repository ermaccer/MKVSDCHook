#pragma once
#include "unreal\FVector.h"
#include "unreal\FRotator.h"



class MK8Menu{
public:
	bool m_bIsActive;
	bool m_bFreeCam;

	float camFOV;
	float m_fFreeCameraSpeed;
	int m_nFreeCameraRotationSpeed;
	int m_nCurrentPad;

	FVector camPos;
	FRotator camRot;

	MK8Menu();
};
extern MK8Menu* TheMenu;