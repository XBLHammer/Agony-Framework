#include <time.h>

int Fadetime;
float Fade[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float FadeSpeed = 0.008f;
bool ToggleFade;

void FadeStart()
{
	Fadetime = clock();
	Fade[0] > 0.0f && Fade[2] <= 0.0f ? Fade[0] = Fade[0] - FadeSpeed, Fade[1] = Fade[1] + FadeSpeed : false;
	Fade[1] > 0.0f && Fade[0] <= 0.0f ? Fade[1] = Fade[1] - FadeSpeed, Fade[2] = Fade[2] + FadeSpeed : false;
	Fade[2] > 0.0f && Fade[1] <= 0.0f ? Fade[0] = Fade[0] + FadeSpeed, Fade[2] = Fade[2] - FadeSpeed : false;
}