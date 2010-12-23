#include <pulse/pulseaudio.h>
#include <stdio.h>
#include <unistd.h>
#include "SinkInput.h"
#include "Protocol.h"

void sinklist(pa_context* /*c*/, const pa_sink_input_info* i, int eol, void* userdata) {
	if (eol == 1) {
		pa_mainloop_quit((pa_mainloop*)userdata, 0);
		return;
	}
	SinkInput si(i);
	printf("[*] %s\n", si.desc());
}

int main() {
	printf("Creating main loop\n");
	pa_mainloop* m = pa_mainloop_new();
	printf("Creating context\n");
	pa_context* c = pa_context_new(pa_mainloop_get_api(m), "HAPX");
	printf("Connecting to server\n");
	if (pa_context_connect(c, NULL, PA_CONTEXT_NOFLAGS, NULL)) {
		printf("error: %s\n", pa_strerror(pa_context_errno(c)));
		return 1;
	}
	printf("Waiting for context to become ready\n");
	while (pa_context_get_state(c) != PA_CONTEXT_READY) {
		pa_mainloop_iterate(m, 1, NULL);
	}
	pa_operation *o;
	printf("Getting sink input list\n");
	o = pa_context_get_sink_input_info_list(c, sinklist, m);
	if (!o) {
		printf("error: %s\n", pa_strerror(pa_context_errno(c)));
		return 1;
	}
	pa_operation_unref(o);
	pa_mainloop_run(m, NULL);
	pa_context_unref(c);
	pa_mainloop_free(m);
}
