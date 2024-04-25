# Define the archive name
ZIP_NAME=source_code_group_10.zip

# Files to include in the zip archive
FILES=1-2.cpp 1-4.cpp 1-5.cpp ev3dev.h README.md

# Default make target
all: zip

# Target to zip source files
zip:
	zip $(ZIP_NAME) $(FILES)

# Clean up the zip file
clean:
	rm -f $(ZIP_NAME)

.PHONY: all zip clean
