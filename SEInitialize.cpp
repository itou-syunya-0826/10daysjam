#include "SEInitialize.h"
#include "Novice.h"

SEHandler SEInitialize(SEHandler soundEffect) {

	soundEffect.audio[0] = Novice::LoadAudio("./resources/sound/SE/Itemget.mp3");
	soundEffect.t[0] = 5;
	soundEffect.count[0] = 5;

	soundEffect.audio[1] = Novice::LoadAudio("./resources/sound/SE/PlayerMaru.mp3");
	soundEffect.t[1] = 5;
	soundEffect.count[1] = 5;

	soundEffect.audio[maru] = Novice::LoadAudio("./resources/sound/SE/PlayerMaru.mp3");
	soundEffect.t[maru] = 5;
	soundEffect.count[maru] = 5;

	soundEffect.audio[square] = Novice::LoadAudio("./resources/sound/SE/PlayerSquare.mp3");
	soundEffect.t[square] = 5;
	soundEffect.count[square] = 5;

	soundEffect.audio[triangle] = Novice::LoadAudio("./resources/sound/SE/PlayerTriangle.wav");
	soundEffect.t[triangle] = 5;
	soundEffect.count[triangle] = 5;

	soundEffect.audio[5] = Novice::LoadAudio("./resources/sound/SE/Enemylazer.mp3");
	soundEffect.t[5] = 5;
	soundEffect.count[5] = 5;

	soundEffect.audio[6] = Novice::LoadAudio("./resources/sound/SE/enemyshot3.wav");
	soundEffect.t[6] = 5;
	soundEffect.count[6] = 5;

	soundEffect.audio[7] = Novice::LoadAudio("./resources/sound/SE/Damage.wav");
	soundEffect.t[7] = 5;
	soundEffect.count[7] = 5;

	soundEffect.audio[8] = Novice::LoadAudio("./resources/sound/SE/Heal.wav");
	soundEffect.t[8] = 5;
	soundEffect.count[8] = 5;

	return soundEffect;
}