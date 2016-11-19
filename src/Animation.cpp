#include "Animation.h"

Animation::Animation() {
	m_isFinished = false;
}

bool Animation::isFinished() {
	return m_isFinished;
}