#include "partSys.h"

static const double BKGND_RED = 0.0;
static const double BKGND_GREEN	= 0.0;
static const double BKGND_BLUE = 0.0;

static const std::string WINDOW_TITLE = "OpenGL Picking";

static const unsigned int KEY_ESC = 27;
static const unsigned int KEY_ENTER = 13;
static const unsigned int KEY_SPACE = 32;
static const unsigned int KEY_DELETE = 127;
static const unsigned int KEY_BACKSPACE = 8;

static const bool IGNORE_REPEATS = true;

static const unsigned int WINDOW_WIDTH	=	600;
static const unsigned int WINDOW_HEIGHT	=	600;
static const unsigned int WINDOW_POS_X	=	100;
static const unsigned int WINDOW_POS_Y	=	100;

static const int PICK_BUFFER_SIZE = 10;
static const int PICK_HEIGHT = 5;
static const int PICK_WIDTH = 5;

const int ID_RECT = 0;
const int ID_TRI = 1;
const int ID_NONE = -1;

int g_width1 = 500 ;
int g_height1 = 500 ;





partSys::partSys( const std::string& name ):
	BaseSystem( name ),
	m_sx( 0.5f ),	
	m_sy( 0.5f ),
	m_sz( 0.5f )
{ 
	// create the system and init to zero size
	system1.p = NULL;
	system1.n = 0;
	system1.t = 0.0;
	spring1 = NULL;
	num_Springs = 0;

	m_selPartIdx = -1;
    m_selPartX = 0;
    m_selPartY = 0;
    m_selPartZ = 0;
    m_bPartSelected = 0;
}	
void partSys::setPartPos(int x, int y)
{
	Vector result;
	pickFromXYPlane(result, x, y);

    double mouseX(result[0]*2000);
    double mouseY(result[1]*2000);
	if(m_selPartIdx >=0 && m_selPartIdx < system1.n)
	{
		system1.p[m_selPartIdx].p = VectorObj(mouseX/1000, mouseY/1000, system1.p[m_selPartIdx].p.z());
		system1.p[m_selPartIdx].prev_p = VectorObj(mouseX/1000, mouseY/1000, system1.p[m_selPartIdx].p.z());
	}
}
void partSys::getState( double* p )
{ 

}	

void partSys::setState( double  *p )
{ 

}	

void partSys::reset( double time ) 
{ 
	
}	

void partSys::pickObject(int x, int y, GLint *pickedObject)
{
	GLdouble modelMatrix[16];
    GLdouble projMatrix[16];
    GLint    viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    if (glGetError())
    {
        animTcl::OutputMessage("Error: glGetDoublev(GL_MODELVIEW_MATRIX,*).\n");
        return;
    }

    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    if (glGetError())
    {
        animTcl::OutputMessage("Error: glGetDoublev(GL_PROJECTION_MATRIX,*).\n");
        return;
    }

    glGetIntegerv(GL_VIEWPORT, viewport);
    if (glGetError())
    {
        animTcl::OutputMessage("Error: glGetIntegerv(GL_VIEWPORT,*).\n");
        return;
    }    
    
    //
    // Mouse x- and y-coordinate
    //
	Vector result;
	pickFromXYPlane(result, x, y);

    double mouseX(result[0]*2000);
    double mouseY(result[1]*2000);
	
	// FOR DEBUGGING
	//animTcl::OutputMessage("Error: glGetIntegerv(GL_VIEWPORT,*). %d,%d\n",(int)(mouseX*1000),(int)(mouseY*1000));
    
    VectorObj pos;
    VectorObj w;
    VectorObj w2;

    m_selPartIdx = -1;
    m_selPartX = mouseX;
    m_selPartY = mouseY;
    m_selPartZ = 0;
    m_bPartSelected = false;

    //
    // Find topmost selected particle
    //
    for (size_t i(0); i< system1.n ; i++)
    {
        //
        // Get i-th particle position
        //

		pos = VectorObj(system1.p[i].p.x()*1000, system1.p[i].p.y()*1000, system1.p[i].p.z()*1000);
        //
		animTcl::OutputMessage("I'th particle position %d, %d, %d, %d\n", i, (int)pos.x(), (int)pos.y(), (int)pos.z());

		double radius = 200.0; //approximate width in system coordiantes * 1000

        //
        // Find the distance of mouse from the center of particle in window coordinates
        //
        double dx = pos.x() - mouseX;
        double dy = pos.y() - mouseY;
        double dist = sqrt(dx*dx + dy*dy);

        if (dist <= radius)
        {
            if (!m_bPartSelected)
            {
                m_selPartIdx = i;
				//animTcl::OutputMessage("Particle Selected %d\n",i);
                m_selPartZ = pos.z();
                m_bPartSelected = true;
            }
            else
            {
                if (pos.z() > m_selPartZ)
                {
                    m_selPartIdx = i;
                    m_selPartZ = pos.z();
                }
            }
        }
    }
    
}	// pickObject

int partSys::selectedIndex()
{
	return m_selPartIdx;
}

int partSys::command(int argc, char **argv) 
{
	if( argc < 1 )
	{
		animTcl::OutputMessage("system %s: wrong number of params.", m_name) ;
		return TCL_ERROR ;
	}
	else if( strcmp(argv[0], "dim") == 0 )
	{
		if( argc == 2 )
		{

			// initialize all the Particles in the system to zero
			particle *P = new particle[(int)atof(argv[1])];
			for(int i = 0; i < (int)atof(argv[1]); i++)
			{
				P[i].p = VectorObj(0,0,0);
				P[i].prev_p = VectorObj(0,0,0);
				P[i].v = VectorObj(0,0,0);
				P[i].v_0 = VectorObj(0,0,0);
				P[i].f = VectorObj(0,0,0);
				P[i].mass = 0.0;
			}

			// initialize the particle System
			system1.p = P;
			system1.n = (int)atof(argv[1]);
			system1.t = 0.0;

		}
		else 
		{
			animTcl::OutputMessage("Usage: dim <Number of Particles>") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "particle") == 0 )
	{
		if( argc == 9 )
		{
			int index = (int)atof(argv[1]);

			//set positions and velocities
			if(index < system1.n)
			{
				system1.p[index].p = VectorObj(atof(argv[3]), atof(argv[4]), atof(argv[5]));
				system1.p[index].v = VectorObj(atof(argv[6]), atof(argv[7]), atof(argv[8]));
				system1.p[index].v_0 = VectorObj(atof(argv[6]), atof(argv[7]), atof(argv[8]));
				system1.p[index].mass = (float)atof(argv[2]);
				system1.p[index].prev_p = system1.p[index].p;	//set initial prev_position to same as initial position
			}
			else
			{
				animTcl::OutputMessage("Specified index out of range") ;
				return TCL_ERROR ;
			}
		}
		else
		{
			animTcl::OutputMessage("Usage: particle <index> <mass> <x y z vx vy vz> ") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "all_velocities") == 0 )
	{
		if( argc == 4 )
		{
			for(int i = 0; i < system1.n; i++)
			{
				system1.p[i].v = VectorObj(atof(argv[1]), atof(argv[2]), atof(argv[3]));
			}
		}
		else
		{
			animTcl::OutputMessage("Usage: all_velocities <vx vy vz>") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "scale") == 0 )
	{
		if( argc == 4 )
		{
			m_sx = (float)atof(argv[1]) ;
			m_sy = (float)atof(argv[2]) ;
			m_sz = (float)atof(argv[3]) ;
		}
		else
		{
			animTcl::OutputMessage("Usage: scale <sx> <sy> <sz> ") ;
			return TCL_ERROR ;

		}
	}
	else if( strcmp(argv[0], "reset") == 0)
	{
		particle *P = new particle[(int)atof(argv[1])];
			for(int i = 0; i < (int)atof(argv[1]); i++)
			{
				P[i].p = VectorObj(0,0,0);
				P[i].v = VectorObj(0,0,0);
				P[i].f = VectorObj(0,0,0);
				P[i].mass = 0.0;
			}

			// initialize the particle System
			system1.p = P;
			system1.n = (int)atof(argv[1]);
			system1.t = 0.0;
	}
	return TCL_OK ;

}	
void partSys::setSpring(spring *s, int num)
{
	spring1 = s;
	num_Springs = num;
}
void partSys::display( GLenum mode ) 
{
	glEnable(GL_LIGHTING) ;
	glMatrixMode(GL_MODELVIEW) ;
	glPushMatrix() ;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable ( GL_COLOR_MATERIAL );

	glScalef(m_sx,m_sy,m_sz) ;

	glEnable(GL_POINT_SMOOTH); 
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10.0);
	glBegin(GL_POINTS);

	for(int i = 0; i < system1.n; i++)
	{
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(system1.p[i].p.x(), system1.p[i].p.y(), system1.p[i].p.z()) ;
	}
	

	glEnd();


	// draw the infinite plane y = 0
	glBegin(GL_QUADS);
	glColor3f(0.0f,0.3f,0.0f);
	glVertex3f(-100, 0, -100);
	glColor3f(0.0f,0.3f,0.0f);
	glVertex3f(-100, 0, 100);
	glColor3f(0.0f,0.3f,0.0f);
	glVertex3f(100, 0, 100);
	glColor3f(0.0f,0.3f,0.0f);
	glVertex3f(100, 0, -100);

	glEnd();

	
	// draw X Y and Z axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	for(int i = 0; i < num_Springs; i++)
	{
		if(spring1[i].init)
		{
				glVertex3f(system1.p[spring1[i].p1].p.x(), 
							system1.p[spring1[i].p1].p.y(),
								system1.p[spring1[i].p1].p.z() );

				glVertex3f(system1.p[spring1[i].p2].p.x(), 
							system1.p[spring1[i].p2].p.y(),
								system1.p[spring1[i].p2].p.z() );
		}
	}



	glEnd();
	
	glPopMatrix();
	glPopAttrib();

}	
