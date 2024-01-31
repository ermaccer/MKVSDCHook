#include "mk8.h"
#include "core.h"
#include <xtl.h>
#include "MemoryMgr_X360.h"


void MK8_UpdateThread()
{
	while (true)
	{
		XINPUT_STATE state;
		memset(&state, 0, sizeof(XINPUT_STATE));
		XInputGetState(TheMenu->m_nCurrentPad, &state);

		WORD buttons = state.Gamepad.wButtons;

		MKCamera* TheCamera = GetCamera();

		if (buttons& XINPUT_GAMEPAD_BACK)
		{
			TheMenu->m_nCurrentPad = !TheMenu->m_nCurrentPad;

			XNotifyQueueUI(0, 0, XNOTIFY_SYSTEM, TheMenu->m_nCurrentPad ? L"Switched to second pad" : L"Switched to first pad", nullptr);
			memset(&state, 0, sizeof(XINPUT_STATE));
		}

		if (buttons &  XINPUT_GAMEPAD_LEFT_THUMB)
		{
			TheMenu->m_bFreeCam = true;
			if (TheCamera)
				TheCamera->SetStatus(TheMenu->m_bFreeCam);
		}

		if (buttons &  XINPUT_GAMEPAD_RIGHT_THUMB)
		{
			TheMenu->m_bFreeCam = false;
			if (TheCamera)
				TheCamera->SetStatus(TheMenu->m_bFreeCam);
		}

		if (TheMenu->m_bFreeCam)
		{
			if (TheCamera)
			{
				TheCamera->SetStatus(0);


				if (buttons &  XINPUT_GAMEPAD_A)
					TheMenu->m_fFreeCameraSpeed = 25.0f;
				else if (buttons &  XINPUT_GAMEPAD_B)
					TheMenu->m_fFreeCameraSpeed = 1.0f;
				else
					TheMenu->m_fFreeCameraSpeed = 5.25f;

				FMatrix mat(&TheMenu->camRot);
				FVector fwd = mat.GetForward();
				FVector strafe = mat.GetRight();
				FVector up = mat.GetUp();

				// forward
				if (!(state.Gamepad.sThumbLY == 0))
				TheMenu->camPos += fwd * TheMenu->m_fFreeCameraSpeed * ((float)state.Gamepad.sThumbLY / 32767.0f);
				if (!(state.Gamepad.sThumbLX == 0))
				TheMenu->camPos += strafe * TheMenu->m_fFreeCameraSpeed * ((float)state.Gamepad.sThumbLX / 32767.0f);

				// up

				if (buttons & XINPUT_GAMEPAD_LEFT_SHOULDER)
					TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed / 2.0f * -1;

				if (buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed / 2.0f * 1;

				TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed * ((float)state.Gamepad.sThumbRX / 32767.0f);
				TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed * ((float)state.Gamepad.sThumbRY / 32767.0f);
				
				TheCamera->camPos = TheMenu->camPos;
				TheCamera->camRot = TheMenu->camRot;
			}

		}
		else
		{
			if (TheCamera)
			{
				TheMenu->camPos = TheCamera->camPos;
				TheMenu->camRot = TheCamera->camRot;
			}
		}


		Sleep(1);
	}
}