#ifndef BULLETKINEMATICCHARACTERCONTROLLER_HPP
#define BULLETKINEMATICCHARACTERCONTROLLER_HPP

#include <bullet/LinearMath/btMotionState.h>

class cKinematicCharMotionState: public btMotionState {
	public:
		cKinematicCharMotionState (const btTransform &initialPos);
		virtual ~cKinematicCharMotionState (void);

		virtual void getWorldTransform (btTransform& worldTrans) const;
		virtual void setWorldTransform (const btTransform& worldTrans);
		void setKinematicPos (const btTransform &currentPos);
	protected:
		btTransform pos_;
};
/*
class cKinematicCharController {
	public:
	private:
};
*/
#endif
