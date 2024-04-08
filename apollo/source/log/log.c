#include "APpch.h"
#include "log/log.h"

#define APINT_MAX_PATH_TOKENS 100
#define APINT_MAX_PATH_LENGTH 512

static void APint_tokenize_path(const char *path, char *segments[]) {
	// write the delimiter token
	const char *delimiter = "/\\";

	// copy over the path into local variable
	char fpath[APINT_MAX_PATH_LENGTH + 1];
	strncpy(fpath, path, sizeof(fpath));

	// null terminate fpath manually
	fpath[APINT_MAX_PATH_LENGTH] = '\0';

	// start tokenizing the path
	char *token = strtok(fpath, delimiter);

	// iterate through the entire string and put the tokens into segments
	APi32 i = 0;

	while (token != NULL && i < APINT_MAX_PATH_TOKENS - 1) {
		// input the token into segment
		segments[i++] = token;

		// get the next token
		token = strtok(NULL, delimiter);
	}

	// since token is NULL, end the segment with null ptr
	segments[i] = NULL;
}

static char *APint_extract_filepath(const char *path) {
	// find where in path Apollo is first seen
	char *segments[APINT_MAX_PATH_TOKENS];

	// divide the path into segments
	APint_tokenize_path(path, segments);

	// iterate through the segment and find out where apollo is
	APi32 apollo_index = 0;

	const char *apollostr = "apollo";

	while (
			strcmp(
				apollostr,
				segments[apollo_index++]) !=
			0) {
		if (apollo_index == APINT_MAX_PATH_TOKENS - 1) {
			apollo_index = -1;
			break;
		}
	}

	char *final_path;

	if (apollo_index == -1) {
		// we did not find apollo, just send back the path as is
		return strdup(path);
	}

	APu32 path_index = 0;

	for (APi32 i = 0; i < apollo_index; i++) 
		path_index += strlen(segments[i]);
	path_index++;

	return strdup(path + path_index);
}

void APOLLO_API AP_log(
		const char *file,
		const char *func,
		APi32 line,
		apLogSeverity severity,
		const char *format,
		...) {
	// get the console handle
	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

	APi32 color = 
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	char *c = "log";

	switch (severity) {
		case AP_LOG: 
			// keep it bright white and log as log
			break;

		case AP_TRACE: 
			// keep it green
			color = FOREGROUND_GREEN;
			c = "trace";
			break;

		case AP_INFO: 
			// keep it purple
			color = FOREGROUND_RED | FOREGROUND_BLUE;
			c = "info";
			break;

		case AP_WARN: 
			// keep it yellow
			color = FOREGROUND_RED | FOREGROUND_GREEN;
			c = "warn";
			break;

		case AP_FATAL: 
			// keep it red
			color = FOREGROUND_RED;
			c = "fatal";
			break;
	}

    // change text color to red
    SetConsoleTextAttribute(h_console, color);

	/* char *file_path = APint_extract_filepath(file); */
	// todo

	printf("(%s)\n", __TIME__);
	printf("(<F:%s , f:%s , l:%d)", file, func, line);
	printf("[%s]: ", c);

	// to print the variable arguments
	// intialize va_list to hold all variable arguments
	va_list args;
	va_start(args, format); // format is first optional argument

	// call vprintf instead of printf for the formatted message
	vprintf(format, args);

	// end the va_list
	va_end(args);

	// add a new line
	printf("\n");

    // restore default text color
    SetConsoleTextAttribute(h_console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
