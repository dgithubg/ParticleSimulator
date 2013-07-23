#ifndef MY_PARTSYS_H
#define MY_PARTSYS_H



#include "BaseSystem.h"
#include <shared/defs.h>
#include <util/util.h>
#include "animTcl.h"
#include <GLmodel/GLmodel.h>
#include <GL/glut.h>
#include "ParticleStructs.h"
#include "anim.h"
#include "animTcl.h"
#include "BaseSimulator.h"


class partSys : public BaseSystem
{ 

public:
	partSys( const std::string& name );
	virtual void getState( double *p );
	virtual void setState( double  *p );
	inline particleSystem* getSystem() {return &system1;}
	void reset( double time );

	void display( GLenum mode = GL_RENDER );

	int command(int argc, char **argv) ;
	void setSpring(spring *s, int num);
	void pickObject(int mouseX, int mouseY, GLint *pickedObject);
	void processHits(int hits, unsigned int buffer[], GLint *pickedObject);

	int selectedIndex();

	void setPartPos(int x, int y);

protected:

	float m_sx;
	float m_sy;
	float m_sz;

	particleSystem system1;

	spring *spring1;
	int num_Springs;

	int m_selPartIdx;
    int m_selPartX;
    int m_selPartY;
    int m_selPartZ;
    int m_bPartSelected;


} ;
#endif