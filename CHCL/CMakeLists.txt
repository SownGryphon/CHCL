add_library("CHCL")

target_include_directories(CHCL
	PUBLIC
		src
)

target_compile_features(CHCL
	PUBLIC
		cxx_std_20	
)

add_subdirectory(src/CHCL)