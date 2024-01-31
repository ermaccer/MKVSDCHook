#include "MKCamera.h"

MKCamera* GetCamera()
{
	 return *(MKCamera**)MKCAMERA_OBJ;
}

FMatrix MKCamera::GetMatrix()
{
	FRotator rot = this->camRot;
	FMatrix mat(&rot);
	return mat;
}

void MKCamera::SetStatus(int status)
{
	this->update = status;
}