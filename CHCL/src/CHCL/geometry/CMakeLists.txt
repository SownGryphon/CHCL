target_sources(CHCL
	PRIVATE
		AlignedRect.cpp
		Circle.cpp
		Quaternion.cpp
		Rect.cpp
		ShapeOverlap.cpp
)

target_sources(CHCL
	PUBLIC
		FILE_SET HEADERS
		FILES
			AlignedRect.h
			Circle.h
			DynamicVector.h
			Quaternion.h
			Rect.h
			Shape.h
			ShapeOverlap.h
			Vector2.h
			Vector3.h
			Vector4.h
			VectorN.h
)