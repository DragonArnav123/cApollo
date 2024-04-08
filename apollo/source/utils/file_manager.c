#include "APpch.h"
#include "utils/file_manager.h"
#include "log/log.h"

char APOLLO_API *AP_fm_read_from_file(const APfilepath_t file_path) {
	// open the file
	FILE *handle = fopen(file_path, "r");

	// check the validity of the file
	if (handle == NULL) {
		AP_LOG_WARN("%s %s %s", "Could not open file: ", file_path, " \t for reading!");
		fclose(handle);
		return NULL;
	}

	// get the file size
	APu32 size;

	fseek(handle, 0, SEEK_END);

	size = ftell(handle);

	fseek(handle, 0, SEEK_SET);

	// allocate the buffer
	char *buffer = (char *) malloc(sizeof(char) * ( 1 + size )); // + 1 for '\0'

	// read into the buffer
	APu32 read = fread(buffer, sizeof(char), size, handle);
	buffer[size] = '\0';

	// check if the buffer is valid
	if (buffer == NULL) {
		AP_LOG_WARN("%s %s %s", "Error in reading file: ", file_path, " . Could not read into the buffer.");
		fclose(handle);
		free(buffer);
		return NULL;
	}

	// check if all contents were read
	if (read != size) {
		AP_LOG_WARN("%s %s %s", "Could not read file: ", file_path, "\t completely.");
		fclose(handle);
		return buffer;
	}

	return buffer;
}
