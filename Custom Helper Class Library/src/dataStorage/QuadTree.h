#pragma once

#include <vector>

#include "../geometry/Rect.h"
#include "../geometry/ShapeOverlap.h"

namespace chcl
{
	template <typename T, size_t maxElements = 1>
	class QuadTree
	{
		struct QTElement
		{
			const T element;
			Vector2 position;
		};

		struct QTRegion
		{
			Rect area;
			QTRegion *children[4] = { nullptr };
			std::vector<QTElement> elements;

			QTRegion(const Rect& area)
				: area(area) {}

			void addElement(const QTElement &element)
			{
				if (elements.size() == maxElements)
				{
					if (children[0] == nullptr)
						for (char i = 0; i < 4; ++i)
						{
							children[i] = new QTRegion(Rect(
								Vector2(
									area.origin.x() + area.size.x() / 2 * (i & 0b1),
									area.origin.y() + area.size.y() / 2 * ((i & 0b10) >> 1)
								),
								area.size / 2
							));
						}

					for (QTRegion *child : children)
						if (child->area.containsPoint(element.position))
						{
							child->addElement(element);
							return;
						}
				}

				elements.push_back(element);
			}

			template <ShapeDerived S>
			std::vector<T> getElements(const S &shape)
			{
				std::vector<T> result;

				for (const QTElement &element : elements)
				{
					if (shape.containsPoint(element.position))
						result.push_back(element.element);
				}

				if (children[0])
					for (QTRegion *child : children)
						if (checkOverlap(shape, child->area))
						{
							std::vector<T> childResult = child->getElements(shape);
							result.reserve(result.size() + childResult.size());
							result.insert(result.end(), childResult.begin(), childResult.end());
						}

				return result;
			}

			~QTRegion()
			{
				for (QTRegion *child : children)
						delete child;
			}
		};

		QTRegion primaryRegion;

	public:
		QuadTree(const Rect& area)
			: primaryRegion(area) {};

		template <ShapeDerived S>
		std::vector<T> getElements(const S &shape)
		{
			return primaryRegion.getElements(shape);
		}

		void addElement(const T& element, const Vector2 &position)
		{
			if (primaryRegion.area.containsPoint(position))
				primaryRegion.addElement(QTElement(element, position));
		}
	};
}