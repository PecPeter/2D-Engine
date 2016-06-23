#ifndef COLLCOMPONENT_HPP
#define COLLCOMPONENT_HPP

#include <memory>

#include "collObject.hpp"

enum class eObjType {
	STATIC,
	DYNAMIC
};

struct sCollObjNode {
	public:
		std::weak_ptr<cCollObj> collObj;
};
class cCollObjNode {
	public:
	private:
};

class cCollComponent {
	public:
		cCollComponent (void);
		~cCollComponent (void);
	private:
		eObjType objType_;
};

#endif
