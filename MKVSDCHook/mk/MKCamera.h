#pragma once
#include "..\unreal\FRotator.h"
#include "..\unreal\FVector.h"
#include "..\unreal\FMatrix.h"


#define MKCAMERA_OBJ 0x83005AC8

class MKCamera{
public:
	char _pad[292];
	FVector camPos;
	char __pad[12];
	FRotator camRot;
	char ___pad[752];
	int update;

	FMatrix GetMatrix();

	void SetStatus(int status);
};


MKCamera* GetCamera();