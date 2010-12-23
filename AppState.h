#ifndef _APPSTATE_H_
#define _APPSTATE_H_

#include "SinkInput.h"
#define NUMCHANS 2

class AppState {
private:
	SinkInput* m_channels[NUMCHANS];
public:
	AppState();
	SinkInput* channel(unsigned int ch);
	void setChannel(unsigned int ch, SinkInput* value);
};

#endif
