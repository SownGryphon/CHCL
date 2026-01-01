target_sources(CHCL
	PRIVATE
		BinaryFile.cpp
		BitStream.cpp
		BitStreamView.cpp
		JSON_Parser.cpp
		OctBool.cpp
		OctBoolArray.cpp
)

target_sources(CHCL
	PUBLIC
		FILE_SET HEADERS
		FILES
			BinaryFile.h
			BinaryHeap.h
			BitStream.h
			BitStreamView.h
			HuffmanTree.h
			JSON_Integration.h
			JSON_Parser.h
			OctBool.h
			OctBoolArray.h
			QuadTree.h
)