#include "AppState.h"

AppState::AppState() {
	for (int i = 0; i < NUMCHANS; i++)
		m_channels[i] = NULL;
}

SinkInput* AppState::channel(unsigned int ch) {
	return m_channels[ch];
}

void AppState::setChannel(unsigned int ch, SinkInput* value) {
	m_channels[ch] = value;
}
