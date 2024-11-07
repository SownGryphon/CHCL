#pragma once

#include <vector>

#include "chcl/geometry/AlignedRect.h"
#include "chcl/geometry/ShapeOverlap.h"

namespace chcl
{
	template <typename T, size_t maxElements = 1>
	class QuadTree
	{
	public:
		struct QTElement
		{
			const T element;
			Vector2<> position;
		};

		struct QTRegion
		{
			AlignedRect area;
			std::vector<QTRegion> children;
			std::vector<QTElement> elements;
			bool subdivided = false;

			QTRegion(const Rect &area)
				: area(area) {}

			bool addElement(const QTElement &element)
			{
				if (!area.containsPoint(element.position))
					return false;

				if (elements.size() == maxElements)
				{
					if (!subdivided)
					{
						subdivide();
					}

					for (QTRegion &child : children)
					{
						if (child.addElement(element))
							return true;
					}
				}

				elements.push_back(element);
				return true;
			}

			template <ShapeDerived S>
			std::vector<T> getElements(const S &shape) const
			{
				std::vector<T> result;

				if (!checkOverlap(area, shape))
					return result;

				for (const QTElement &element : elements)
				{
					if (shape.containsPoint(element.position))
						result.push_back(element.element);
				}

				if (subdivided)
				{
					for (const QTRegion &child : children)
					{
						std::vector<T> childResult = child.getElements(shape);
						result.reserve(result.size() + childResult.size());
						result.insert(result.end(), childResult.begin(), childResult.end());
					}
				}

				return result;
			}

			void clear()
			{
				elements.clear();
				if (subdivided)
				{
					bool childrenUsed = false;
					for (QTRegion &child : children)
					{
						if (!child.elements.empty())
							childrenUsed = true;

						child.clear();
					}

					if (!childrenUsed)
					{
						children.clear();
						subdivided = false;
					}
				}
			}

		private:
			void subdivide()
			{
				children.reserve(4);
				for (char i = 0; i < 4; ++i)
				{
					children.push_back(QTRegion({
						{
							area.origin.x + area.size.x / 2 * (i & 0b1),
							area.origin.y + area.size.y / 2 * ((i & 0b10) >> 1)
						},
						area.size / 2
					}));
				}
				subdivided = true;
			}
		};

		QuadTree(const Rect &area)
			: m_primaryRegion(area) {};

		template <ShapeDerived S>
		std::vector<T> getElements(const S &shape)
		{
			return m_primaryRegion.getElements(shape);
		}

		void addElement(const T &element, const Vector2<> &position)
		{
			m_primaryRegion.addElement({ element, position });
		}

		void clear()
		{
			m_primaryRegion.clear();
		}

		const QTRegion& getRegion() const { return m_primaryRegion; }

	private:
		QTRegion m_primaryRegion;
	};
}