#ifndef MY_PARTSIM_H
#define MY_PARTSIM_H

#include <GLModel/GLModel.h>
#include <shared/defs.h>
#include <util/util.h>
#include "animTcl.h"
#include "BaseSimulator.h"
#include "BaseSystem.h"
#include "partSys.h"


#include <string>

using namespace std;

class partSim : public BaseSimulator 
{
public:

	partSim( const std::string& name, partSys* target );
	~partSim();

	int step(double time);
	int init(double time) 
	{ 
		return 0;
	};

	int command(int argc, char **argv);
	spring* getSprings();
	int numSprings();
	void forceAccum();

protected:

	int num_Springs;
	spring *springs;
	partSys* m_object;

	int integration; // 1 = Forward Euler, 2 = Symplectic Euler, 3 = Verlet

	double timestep; // timestep of the integration
	double prev_time;

	VectorObj normal;

	double g_ks, g_kd, g_g; // elasticity and viscosity parameters of the ground constraint



};


#endif