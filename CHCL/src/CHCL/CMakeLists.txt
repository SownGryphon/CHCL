target_sources(CHCL
	PRIVATE
		Prints.cpp
)

target_sources(CHCL
	PUBLIC
		FILE_SET HEADERS
		FILES
			Formatter.h
			Prints.h
)

add_subdirectory("dataStorage")
add_subdirectory("geometry")
add_subdirectory("maths")