# Include directories helps to include header files
include_directories(".")
include_directories("../compile-time-regular-expressions/single-header")
include_directories(${INCLUDE_DIR})

# Get the source filenames to compile
file(GLOB_RECURSE SOURCES *.cxx)

add_definitions("${CFLAGS}")
link_libraries("${LINK_LIBS}")

# Creating object file list from the sources ignoring main file
foreach(filename ${SOURCES})
	if("${filename}" MATCHES "main.cxx")
	else("${filename}" MATCHES "main.cxx")
		list(APPEND OBJECTS ${filename})
	endif("${filename}" MATCHES "main.cxx")
endforeach(filename ${SOURCES})

if(${PRJ_TYPE_EXECUTABLE})
	# Create executable if the project type is PRJ_TYPE_EXECUTABLE
	add_executable(${PRJ_NAME} ${SOURCES})

	# Always create libraries if PRJ_BUILD_LIBRARY defined
	if(${PRJ_BUILD_LIBRARY})
		add_library(${PRJ_NAME}-static STATIC ${OBJECTS})
		add_library(${PRJ_NAME}-shared SHARED ${OBJECTS})
	endif(${PRJ_BUILD_LIBRARY})
else(${PRJ_TYPE_EXECUTABLE})
	# Creating libraries if not a executable project
	add_library(${PRJ_NAME}-static STATIC ${OBJECTS})
	add_library(${PRJ_NAME}-shared SHARED ${OBJECTS})
endif(${PRJ_TYPE_EXECUTABLE})

