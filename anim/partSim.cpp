#include "partSim.h"
#include <sstream>


partSim::partSim( const std::string& name, partSys* target ):
	BaseSimulator( name ),
	m_object( target )
{
	// initialize all member variables to default values

	num_Springs = 0;
	springs = NULL;
	integration = 1;
	timestep = 1;
	prev_time = 0.0;

	normal = VectorObj(0,1,0);
	g_ks = 100.0;
	g_kd = 10.0;
	g_g = -9.8;
}	

partSim::~partSim()
{
}	
spring* partSim::getSprings()
{
	return springs;
}
int partSim::numSprings()
{
	return num_Springs;
}
int partSim::command(int argc, char **argv)
{
	if( argc < 1 )
	{
		animTcl::OutputMessage("system %s: wrong number of params.", m_name) ;
		return TCL_ERROR ;
	}
	else if( strcmp(argv[0], "link") == 0 )
	{
		if( argc == 3 )
		{
			num_Springs = (int)atof(argv[2]);
			springs = new spring[num_Springs];

			// no springs are hokked up to particles yet
			for(int i = 0; i < num_Springs; i++)
				springs[i].init = false;
			
		}
		else
		{
			animTcl::OutputMessage("Usage: link <sys name> <Number of Springs>", m_name) ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "spring") == 0 )
	{
		if( argc == 7 )
		{
			int sindex = (int)atof(argv[1]);

			if(sindex < num_Springs)
			{
				//particleSystem *curSys = m_object->getSystem();


				//set the spring at sindex with the specifies parameters
				springs[sindex].p1		= (int)atof(argv[2]);
				springs[sindex].p2		= (int)atof(argv[3]);
				springs[sindex].ks		= atof(argv[4]);
				springs[sindex].kd		= atof(argv[5]);
				springs[sindex].length	= atof(argv[6]);
				springs[sindex].init	= true;
			}
			else
			{
				animTcl::OutputMessage("Spring index out of bounds", m_name) ;
				return TCL_ERROR ;
			}
			m_object->setSpring(springs, num_Springs);
		}
		else if( argc == 6 )
		{
			// copy old spring array to a new array that is larger by 1
			spring *springs_temp = new spring[num_Springs+1];
			for(int i = 0; i < num_Springs; i++)
				springs_temp[i] = springs[i];

			// insert new spring with sindex num_Springs (aka the new num_Springs - 1)
			springs_temp[num_Springs].p1		= (int)atof(argv[1]);
			springs_temp[num_Springs].p2		= (int)atof(argv[2]);
			springs_temp[num_Springs].ks		= atof(argv[3]);
			springs_temp[num_Springs].kd		= atof(argv[4]);
			springs_temp[num_Springs].length	= atof(argv[5]);
			springs_temp[num_Springs].init		= true;

			delete springs;
			num_Springs++;
			springs = springs_temp;
			m_object->setSpring(springs, num_Springs);
		}
		else
		{
			animTcl::OutputMessage("Usage: spring <sindex> <pindex1> <pindex2> <ks> <kd> <length>   OR\n spring <pindex1> <pindex2> <ks> <kd> <length>", m_name) ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "integration") == 0 )
	{
		if( argc == 3 )
		{

			//set the integration technique
			string integration_technique = argv[1];
			if(integration_technique == "euler")
				integration = 1;
			else if(integration_technique == "symplectic")
				integration = 2;
			else if(integration_technique == "verlet")
				integration = 3;
			else
			{
				animTcl::OutputMessage("Usage: integration <euler | symplectic | verlet> <timestep>", m_name) ;
				return TCL_ERROR ;
			}

			timestep = atof(argv[2]);
		}
		else
		{
			animTcl::OutputMessage("Usage: integration <euler | symplectic | verlet> <timestep>", m_name) ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "ground") == 0 )
	{
		if( argc == 3 )
		{
			g_ks = atof(argv[1]);
			g_kd = atof(argv[2]);
		}
		else
		{
			animTcl::OutputMessage("Usage: ground <ks> <kd>", m_name) ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "gravity") == 0 )
	{
		if( argc == 2 )
		{
			g_g = atof(argv[1]);
		}
		else
		{
			animTcl::OutputMessage("Usage: gravity <g>", m_name) ;
			return TCL_ERROR ;
		}
	}

	return TCL_OK ;
}
// Calculate the accumulated forces on each particle
//		-Forces from Spring/dampers
//		-Force from gravity given my F = m*g_g
//		-Force from collision with ground
void partSim::forceAccum()
{
	particleSystem *curSys = m_object->getSystem();

	// zero out the force accumulators of all the particles in the system
	for(int i = 0; i < curSys->n; i++)
		curSys->p[i].f = VectorObj(0,0,0);

	// spring force accumulator
	// update the two particles connected by the spring at each iteration
	for(int i = 0; i < num_Springs; i++)
	{
		//check to see if the spring was ever hooked up to particles
		if(springs[i].init)
		{
			particle *p1 = &(curSys->p[springs[i].p1]);
			particle *p2 = &(curSys->p[springs[i].p2]);
			double p_distance = (p2->p - p1->p).length();
			VectorObj p_force = (springs[i].ks*((p_distance - springs[i].length)) + springs[i].kd*(p2->v - p1->v).dot((p2->p - p1->p)/p_distance)) * ((p2->p - p1->p)/p_distance) ;
			p1->f += p_force;
			p2->f -= p_force;
		}
	}
	// gravity force accumulator
	// force of gravity is just g_g * mass * vectorObj(0, 1, 0);
	for(int i = 0; i < curSys->n; i++)
	{
		curSys->p[i].f += VectorObj(0, g_g*curSys->p[i].mass, 0);
	}
	// collision force accumulator
	for(int i = 0; i < curSys->n; i++)
	{
		if(curSys->p[i].p.y() <= 0)
		{
			curSys->p[i].f += (g_ks*(VectorObj(0,0,0) - curSys->p[i].p).dot(normal))*normal - g_kd*(curSys->p[i].v.dot(normal))*normal;
		}
	}

}

int partSim::step(double time)
{
	// check to see if enough simulation time has passed for the timestep

		particleSystem *curSys = m_object->getSystem();
		// check the desired integration technique
	
		if(integration == 1)		// Forward Euler
		{

			forceAccum();

			//FOR DEBUGGING
			stringstream s;
			s << curSys->p[0].v.y();
			string t = s.str();
			animTcl::OutputMessage((char*)t.c_str(), m_name) ;

			for(int i = 0; i < curSys->n; i++)
			{
				VectorObj new_pos;
				new_pos = curSys->p[i].p + curSys->p[i].v * timestep + (0.5)*(curSys->p[i].f / curSys->p[i].mass) * (timestep * timestep);
				curSys->p[i].p = new_pos;
				curSys->p[i].v += ((curSys->p[i].f / curSys->p[i].mass) * timestep);
			}
		}
		else if(integration  == 2)	// Symplectic Euler	
		{
			forceAccum();

			for(int i = 0; i < curSys->n; i++)
			{
				VectorObj new_pos, new_vel;

				new_vel = curSys->p[i].v + ((curSys->p[i].f / curSys->p[i].mass) * timestep);
				new_pos = curSys->p[i].p + (new_vel * timestep);
				curSys->p[i].p = new_pos;
				curSys->p[i].v = new_vel;
			}
		}
		else				// Verlet Integration
		{
			forceAccum();

			for(int i = 0; i < curSys->n; i++)
			{
				VectorObj new_pos;

				new_pos = ((curSys->p[i].p) * 2) - curSys->p[i].prev_p + ((curSys->p[i].f / curSys->p[i].mass) * (timestep * timestep));
				//update previous position
				curSys->p[i].prev_p = curSys->p[i].p;
				//update current position
				curSys->p[i].p = new_pos;

				curSys->p[i].v = ((curSys->p[i].p - curSys->p[i].prev_p)/timestep);
			}
		}
		prev_time = time;

	return 0;

}	
