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
		std::unique_ptr<cCollShape> collShape_;

		std::weak_ptr<sCollShapeNode> parentNode_;
		std::vector<std::shared_ptr<sCollShapeNode>> childrenNodeList_;
};

#endif
