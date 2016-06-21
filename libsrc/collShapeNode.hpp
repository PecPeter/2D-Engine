#ifndef COLLSHAPENODE_HPP
#define COLLSHAPENODE_HPP

#include <memory>
#include <vector>

class cCollShape;

struct sCollShapeNode {
	public:
		cVector2 posOffset_;	// The position offset from the centroid
								// position of the parent node shape.
		double rotnOffset_;
		std::weak_ptr<cCollShape const> collShape_;

		std::weak_ptr<sCollShapeNode const> parentNode_;
		std::vector<std::weak_ptr<sCollShapeNode const>> childrenNodeList_;
};

#endif
