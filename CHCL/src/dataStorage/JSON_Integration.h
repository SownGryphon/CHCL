#pragma once

#include "JSON_Parser.h"

#include "geometry/VectorN.h"
#include "geometry/DynamicVector.h"

#include "maths/Matrix.h"
#include "maths/DynamicMatrix.h"

namespace chcl
{
	template <size_t dims, typename T>
	JSON_Stream& operator<<(JSON_Stream &stream, const VectorN<dims, T> &vec)
	{
		JSON_Object vecInfo;
		vecInfo.writeElement("size", dims);
		vecInfo.writeElement("components", vec.toStdVector());
		stream << vecInfo;
		return stream;
	}

	template <size_t dims, typename T>
	JSON_Stream& operator>>(JSON_Stream &stream, VectorN<dims, T> &vec)
	{
		JSON_Object vecInfo;
		stream >> vecInfo;

		if (vecInfo.readElement<size_t>("size") != dims) return stream;

		std::vector<T> components = vecInfo.readElement<std::vector<T>>("components");
		if (components.size() == dims)
		{
			for (size_t i = 0; i < dims; ++i)
				vec[i] = components[i];
		}

		return stream;
	}

	template <size_t rows, size_t cols, typename T>
	JSON_Stream& operator<<(JSON_Stream &stream, const Matrix<rows, cols, T> &mat)
	{
		JSON_Object matInfo;
		matInfo.writeElement("rows", rows);
		matInfo.writeElement("cols", cols);
		matInfo.writeElement("values", mat.dataVector());
		stream << matInfo;
		return stream;
	}

	template <size_t rows, size_t cols, typename T>
	JSON_Stream& operator>>(JSON_Stream &stream, Matrix<rows, cols, T> &mat)
	{
		JSON_Object matInfo;
		stream >> matInfo;

		if (matInfo.readElement<size_t>("rows") != rows) return stream;
		if (matInfo.readElement<size_t>("cols") != cols) return stream;
		
		std::vector<T> values = matInfo.readElement<std::vector<T>>("values");
		if (values.size() == mat.Count())
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					mat.at(i, j) = values[mat.IndexOf(i, j)];
		}

		return stream;
	}

	template <typename T>
	JSON_Stream& operator<<(JSON_Stream &stream, const DynamicVector<T> &vec)
	{
		JSON_Object vecInfo;
		vecInfo.writeElement("size", vec.size());
		vecInfo.writeElement("components", vec.toStdVector());
		stream << vecInfo;
		return stream;
	}

	template <typename T>
	JSON_Stream& operator>>(JSON_Stream &stream, DynamicVector<T> &vec)
	{
		JSON_Object vecInfo;
		stream >> vecInfo;

		size_t size = vecInfo.readElement<size_t>("size");
		std::vector<T> components = vecInfo.readElement<std::vector<T>>("components");
		if (components.size() == size)
		{
			vec = std::move(DynamicVector<T>(components));
		}

		return stream;
	}

	template <typename T>
	JSON_Stream& operator<<(JSON_Stream &stream, const DynamicMatrix<T> &mat)
	{
		JSON_Object matInfo;
		matInfo.writeElement("rows", mat.rows());
		matInfo.writeElement("cols", mat.cols());
		matInfo.writeElement("values", mat.dataVector());
		stream << matInfo;
		return stream;
	}

	template <typename T>
	JSON_Stream& operator>>(JSON_Stream &stream, DynamicMatrix<T> &mat)
	{
		JSON_Object matInfo;
		stream >> matInfo;

		size_t rows = matInfo.readElement<size_t>("rows");
		size_t cols = matInfo.readElement<size_t>("cols");
		std::vector<T> values = matInfo.readElement<std::vector<T>>("values");
		if (values.size() == rows * cols)
		{
			mat = std::move(DynamicMatrix<T>(rows, cols, values));
		}

		return stream;
	}
}