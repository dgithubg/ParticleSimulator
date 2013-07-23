#include <util/util.h>

typedef struct particle_struct {
		VectorObj	p;
		VectorObj	prev_p;
		VectorObj	v;
		VectorObj	v_0;
		VectorObj	f;
		float		mass;
} particle;

typedef struct particleSystem_struct {
		particle   *p;	// array particle information
		int			n;	// number of particles
		float		t;	// current time (age) of the particle system
} particleSystem;

typedef struct spring_struct {
		// bool if initialized
		bool		init;
		int			p1;
		int			p2;
		double		ks;
		double		kd;
		double		length;

		
} spring;