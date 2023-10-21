#pragma once

#include <vector>

#include "../geometry/Rect.h"
#include "../geometry/ShapeOverlap.h"

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
			Rect area;
			QTRegion *children[4] = { nullptr };
			std::vector<QTElement> elements;
			bool subdivided = false;

			QTRegion(const Rect &area)
				: area(area) {}

			~QTRegion()
			{
				if (subdivided)
					for (QTRegion *child : children)
						delete child;
			}

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

					for (QTRegion *child : children)
					{
						if (child->addElement(element))
							return true;
					}
				}

				elements.push_back(element);
				return true;
			}

			template <ShapeDerived S>
			std::vector<T> getElements(const S &shape)
			{
				std::vector<T> result;

				if (checkOverlap(area, shape))
					return result;

				for (const QTElement &element : elements)
				{
					if (shape.containsPoint(element.position))
						result.push_back(element.element);
				}

				if (subdivided)
				{
					for (QTRegion *child : children)
					{
						std::vector<T> childResult = child->getElements(shape);
						result.reserve(result.size() + childResult.size());
						result.insert(result.end(), childResult.begin(), childResult.end());
					}
				}

				return result;
			}

		private:
			void subdivide()
			{
				for (char i = 0; i < 4; ++i)
				{
					children[i] = new QTRegion(Rect(
						Vector2<>(
							area.origin.x + area.size.x / 2 * (i & 0b1),
							area.origin.y + area.size.y / 2 * ((i & 0b10) >> 1)
						),
						area.size / 2
					));
				}
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

		const QTRegion& getRegion() const { return m_primaryRegion; }

	private:
		QTRegion m_primaryRegion;
	};
}