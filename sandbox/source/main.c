#include "sandbox.h"

int main(int argc, const char *argv[]) {
	// initialize the engine
	initialize();

	// create sandbox app
	struct Sandbox *app;

	on_begin(argc, argv, &app);

	// run the app
	run_app(app);
	
	// end the app
	on_end(app);

	// terminate the engine
	terminate();
}
