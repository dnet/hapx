#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "AppState.h"
#include "SinkInput.h"
#include <unistd.h>
#include <string.h>

class Protocol {
protected:
	int m_fd;
	AppState *m_as;
public:
	Protocol(const int fd, AppState *as);
	void sendChannelName(unsigned int ch);
	void sendSignalLevels();
	void recv();
	void setVolume(unsigned int ch, unsigned int vol);
	void setMute(unsigned int ch, bool mute);
	void changeChannel(unsigned int ch);
};

#endif
