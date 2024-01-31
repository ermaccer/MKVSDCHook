#include "mk8menu.h"


 MK8Menu* TheMenu = new MK8Menu();

 MK8Menu::MK8Menu()
 {
	 this->m_bFreeCam = false;
	 this->m_bIsActive = false;
	 this->camFOV = 0.0f;
	 this->camPos.X = 0;
	 this->camPos.Y = 0;
	 this->camPos.Z = 0;
	 this->camRot.Pitch = 0;
	 this->camRot.Roll = 0;
	 this->camRot.Yaw = 0;

	 this->m_nCurrentPad = 0;

	 this->m_fFreeCameraSpeed = 5.25f;
	 this->m_nFreeCameraRotationSpeed = 60;
 }