/************************************************************************/
/*                                                                      */
/* This file is part of VDrift.                                         */
/*                                                                      */
/* VDrift is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* VDrift is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with VDrift.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                      */
/************************************************************************/

#ifndef _MOTIONSTATE_H
#define _MOTIONSTATE_H

#include "LinearMath/btMotionState.h"
#include "tobullet.h"

struct MotionState : public btMotionState {
	btQuaternion rotation;
	btVector3 position;
	btQuaternion massCenterRotation;
	btVector3 massCenterOffset;

	MotionState() : rotation(0,0,0,1), position(0,0,0),
		massCenterRotation(0,0,0,1), massCenterOffset(0,0,0)
	{
		// ctor
	}

	void updatePostion(float vx, float vy, float vz){
			//std::cout << "[VDRIFT][POS][+][" << vx <<"][" << vy <<"][" << vz << "]" << std::endl;
			position.setX(position.x()+vx);
			position.setY(position.y()+vy);
			position.setZ(position.z()+vz);
	}
	void updateYaw(float yaw){
		  Quat rot = ToQuaternion<float>(rotation);
			float _yaw;
			float _pitch;
			float _roll;
			rot.GetEulerZYX(_yaw,_pitch,_roll);
			rotation.setEuler(_yaw,_pitch,_roll+yaw);
	}

	/// from user to physics
	virtual void getWorldTransform(btTransform& centerOfMassWorldTrans) const
	{
		//centerOfMassWorldTrans = m_graphicsWorldTrans * m_centerOfMassOffset.inverse();
		btQuaternion rot = rotation * massCenterRotation.inverse();
		btVector3 pos = position - quatRotate(rot, massCenterOffset);
		centerOfMassWorldTrans.setRotation(rot);
		centerOfMassWorldTrans.setOrigin(pos);
	}

	/// from physics to user (for active objects)
	// updates position and rotation of car
	virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans)
	{
		//m_graphicsWorldTrans = centerOfMassWorldTrans * m_centerOfMassOffset;
		rotation = centerOfMassWorldTrans * massCenterRotation;
		position = centerOfMassWorldTrans * massCenterOffset;
	}
};

#endif
