#include "IsPlaySE.h"


void IsPlaySE(int Audio, int handle, float count, float second) {
	if (count<= second) {
		if (Novice::IsPlayingAudio(handle) <= 0) {
			handle = Novice::PlayAudio(Audio, false, 1.0f / 4.0f);
		}
	}
	if (count <= 0) {
		Novice::StopAudio(handle);
	}
}