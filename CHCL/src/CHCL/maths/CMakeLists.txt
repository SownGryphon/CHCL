target_sources(CHCL
	PRIVATE
		Common.cpp
		Continuous.cpp
		Mat2.cpp
		Mat3.cpp
		Mat4.cpp
)

target_sources(CHCL
	PUBLIC
		FILE_SET HEADERS
		FILES
			ColumnMatrix.h
			Common.h
			Continuous.h
			DynamicMatrix.h
			Mat2.h
			Mat3.h
			Mat4.h
			Matrix.h
			SquareMatrix.h
)