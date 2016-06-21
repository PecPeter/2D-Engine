#ifndef COLLPAIR_HPP
#define COLLPAIR_HPP

#include <memory>

#include "mathVector.hpp"
#include "collObject.hpp"

enum class eCollType {
	NO_COLLISION,
	CONTACT,
	COLLISION
};

class cCollPair {
	public:
		cCollPair (std::shared_ptr<cCollObj> object1,
				std::shared_ptr<cCollObj> object2);
		~cCollPair (void);

		std::weak_ptr<cCollObj> obj1 (void) const;
		std::weak_ptr<cCollObj> obj2 (void) const;
		void setObjOverlap (const cVector2& overlap);
		const cVector2& getObjOverlap (void) const;
		void setCollType (const eCollType& collType);
		eCollType getCollType (void) const;
	private:
		std::weak_ptr<cCollObj> object1_,
								object2_;
		cVector2 overlap_; // Overlap if wrt what obj1 has to do
						   // to get out of collision
		eCollType collType_;
};

#endif
