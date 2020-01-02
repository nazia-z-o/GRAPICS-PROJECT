#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <bits/stdc++.h>
#include<GL/gl.h>
#include<windows.h>
#include "RGBpixmap.cpp"
using namespace std;

float degree_x = 0;
float degree_y = 0;
float degree_z = 0;
float tx = 0;
float ty = 0;
float tz = 0;
float zm = 1;

static int slices = 32;
static int stacks = 32;
int light0=1;
int light1=1;
static int lev=1;
static GLdouble camRadius = 20;
static GLdouble camTheta = 0;
static GLdouble camHeight = 0;
static GLdouble camRoll = 90;

static GLdouble camCenterX = 0;
static GLdouble camCenterY = 0;
static GLdouble camCenterZ = 0;
float upX = 0, upY = 7, upZ = 1.0;
float yaw = 0.0, pitch = 0.0, roll = 90.0;
RGBpixmap pix[6];

#define PI 3.14159265
GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat white_emission[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat no_emission[] = {0.0f,0.0f,0.0f,1.0f};
const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 3.0f, 18.0f, 5.0f, 1.0f };

const GLfloat light_ambient1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position1[] = { 5.0f, 18.0f, 18.0f, 1.0f };

const GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };

const GLfloat spot_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat spot_diffuse[]  = { 1.0f, 1.0f, 0.5f, 1.0f };
const GLfloat spot_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat spot_position[] = { -1.0f, 4.0f, -1.0f, 1.0f };

const GLfloat mat_ambient1[]    = { 0.3f, 0.1f, 0.3f, 1.0f };
const GLfloat mat_diffuse1[]    = { 1.0f, 0.2f, 1.0f, 1.0f }; //helicopter
const GLfloat mat_specular1[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess1[] = { 100.0f };

const GLfloat mat_ambient2[]    = { 0.1f, 0.3f, 0.3f, 1.0f };
const GLfloat mat_diffuse2[]    = { 0.1f, 0.5f, 1.0f, 1.0f }; //jack
const GLfloat mat_specular2[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess2[] = { 150.0f };

const GLfloat mat_ambient3[]    = { 0.2f, 0.5f, 0.3f, 1.0f };
const GLfloat mat_diffuse3[]    = {0.8f, 1.0f, 0.0f, 1.0f }; //wall1
const GLfloat mat_specular3[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess3[] = { 200.0f };

const GLfloat mat_ambient4[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_diffuse4[]    = { 1.0f, 0.0f, 1.0f, 1.0f };   //table
const GLfloat mat_specular4[]   = { 0.0f, 1.0f, 0.0f, 1.0f };
const GLfloat high_shininess4[] = { 100.0f };

const GLfloat mat_ambient5[]    = { 0.5f, 0.1f, 0.2f, 1.0f };
const GLfloat mat_diffuse5[]    = { 0.2f, 0.0f, 0.1f, 1.0f };
const GLfloat mat_specular5[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess5[] = { 150.0f };

const GLfloat mat_ambient6[]    = { 0.5f, 0.5f, 0.3f, 1.0f };
const GLfloat mat_diffuse6[]    = { 1.0f, 1.0f, 0.0f, 1.0f };   //jack + table base
const GLfloat mat_specular6[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess6[] = { 100.0f };

const GLfloat mat_ambient7[]    = { 0.9f, 0.9f, 0.9f, 1.0f };
const GLfloat mat_diffuse7[]    = { 1.0f, 1.0f, 0.0f, 1.0f };   //wall_picture
const GLfloat mat_specular7[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess7[] = { 100.0f };

const GLfloat mat_ambient8[]    = { 0.1f, 0.1f, 0.1f, 1.0f };
const GLfloat mat_diffuse8[]    = { 0.1f, 0.1f, 0.1f, 1.0f };   //light_off
const GLfloat mat_specular8[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess8[] = { 100.0f };

int wid1, hei1;
static void resize(int width, int height)
{
    wid1 = width;
    hei1 = height;
    const float ar = (float) width / (float) height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


static GLfloat gasket_bg_mat_color[] = { 1, 1, 1, 1 };
static GLfloat gasket_bg_mat_spec[] = { 0, 0, 0, 1 };
static GLfloat gasket_bg_mat_shininess[] = { 120 };

static GLfloat gasket_mat_color[] = { 0, 0, 1, 1 };
static GLfloat gasket_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat gasket_mat_shininess[] = { 120 };


static inline void set_material(GLfloat c[], GLfloat s[], GLfloat sh[])
{
    GLfloat a[4] = { c[0]*0.1f, c[1]*0.1f, c[2]*0.1f, c[3] };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s);
    glMaterialfv(GL_FRONT, GL_SHININESS, sh);
}
static void _gasket_recursive(int level, GLdouble t, GLdouble b, GLdouble l, GLdouble r)
{

        glVertex3d(l, t, 0.01);/// top middle vertex

        glVertex3d(l, b, 0.01);        /// bottom left vertex
        glVertex3d(r, b, 0.01);        /// bottom right vertex
        glVertex3d(r, t, 0.01);

    if(level<=0)
        return;



    GLdouble hBy4 = (t-b)/4.0;
    GLdouble wBy4 = (r-l)/4.0;

    GLdouble x[2]={l,r};
    GLdouble y[2]={b,t};
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        _gasket_recursive(level-1, y[i]+hBy4, y[i]-hBy4, x[j]-wBy4, x[j]+wBy4);

}

static void gasket(int level)
{
    set_material(gasket_bg_mat_color, gasket_bg_mat_spec, gasket_bg_mat_shininess);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-0.8, -0.8, 0);
        glVertex3f(0.8, -0.8, 0);
        glVertex3f(0.8, 0.8, 0);
        glVertex3f(-0.8, 0.8, 0);
      //  glVertex3f(-0.5, 0.5, 0);
    glEnd();

    set_material(gasket_mat_color, gasket_mat_spec, gasket_mat_shininess);
    glBegin(GL_QUADS);
       // glNormal3f(0, 0, 1);
        _gasket_recursive(level, 0.4, -0.4, -0.4, 0.4);
    glEnd();
}
void ownscale(GLfloat sx, GLfloat sy, GLfloat sz)
{
    GLfloat m[16];
    m[0]=sx;
    m[1]=0;
    m[2]=0;
    m[3]=0;
    m[4]=0;
    m[5]=sy;
    m[6]=0;
    m[7]=0;
    m[8]=0;
    m[9]=0;
    m[10]=sz;
    m[11]=0;
    m[12]=0;
    m[13]=0;
    m[14]=0;
    m[15]=1;
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
}



void Trap(double r, double g, double b)
{
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex3f(0.2, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(1.8, 1, 0);

    glColor3f(r, g, b);
    glVertex3f(0.2, 1, 0);
    glVertex3f(1.8, 1, 0);
    glVertex3f(1.8, 1, 1);
    glVertex3f(0.2, 1, 1);

    glColor3f(r, g, b);
    glVertex3f(0.2, 1, 0);
    glVertex3f(0.2, 1, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);

    glColor3f(r, g, b);

    glVertex3f(0, 0, 1);
    glVertex3f(2, 0, 1);
    glVertex3f(2,0,0);
    glVertex3f(0, 0, 0);

    glColor3f(r, g, b);
    glVertex3f(2,0,0);
    glVertex3f(2, 0, 1);
    glVertex3f(1.8, 1, 1);
    glVertex3f(1.8, 1, 0);

    glColor3f(r, g, b);
    glVertex3f(1.8, 1, 1);
    glVertex3f(2, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0.2, 1, 1);
    glEnd();
}
double angle = -5;

void ownScaled(double x, double y, double z)
{
    GLfloat mat[] =
    {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(mat);
}
void circle(double r, double g, double b)
{
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for(double i = 360; i >=0; i--)

    {
        double theta = 2.0f * 3.1415926f * i / 360;

        double x = 2 * cosf(theta);
        double y = 2 * sinf(theta);

        glVertex3f(x, y, -.1);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for(double i = 0; i <= 360; i++)
    {
        double theta = 2.0f * 3.1415926f * i / 360;

        double x = 2 * cosf(theta);
        double y = 2 * sinf(theta);

        glVertex3f(x, y, .1);
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    for(double i = 0; i <= 360; i++)
    {
        double theta = 2.0f * 3.1415926f * i / 360;
        double theta2 = 2.0f * 3.1415926f * (i == 360? 0: i + 1) / 360;

        double x = 2 * cosf(theta);
        double y = 2 * sinf(theta);
        double nx = 2 * cosf(theta2);
        double ny = 2 * sinf(theta2);

        glVertex3f(x, y, .1);
        glVertex3f(x, y, -.1);
        glVertex3f(nx, ny, -.1);
        glVertex3f(nx, ny, .1);
    }
    glEnd();
}

void circle2(double r, double g, double b)
{
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for(double i = 360; i >=0; i--)

    {
        double theta =  3.1415926f * i / 360;

        double x = 2 * cosf(theta);
        double y = 2 * sinf(theta);

        glVertex3f(x, y, -.1);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for(double i = 0; i <= 360; i++)
    {
        double theta =  3.1415926f * i / 360;

        double x = 2 * cosf(theta);
        double y = 2 * sinf(theta);

        glVertex3f(x, y, .1);
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    for(double i = 0; i <= 360; i++)
    {
        double theta = 3.1415926f * i / 360;
        double theta2 = 3.1415926f * (i == 360? 0: i + 1) / 360;

        double x = 2 * cosf(theta);
        double y = 2 * sinf(theta);
        double nx = 2 * cosf(theta2);
        double ny = 2 * sinf(theta2);

        glVertex3f(x, y, .1);
        glVertex3f(x, y, -.1);
        glVertex3f(nx, ny, -.1);
        glVertex3f(nx, ny, .1);
    }
    glEnd();
}





void triangle()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(0.0,1.0,0.0);

    glVertex3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glEnd();
}
void heli_base()
{
    glBegin(GL_QUADS);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(1.0,0.0,0.0);

    glVertex3f(0.0,1.0,0.0);
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,0.0);

    glVertex3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(0.0,0.0,1.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(0.0,1.0,0.0);

    glVertex3f(0.0,0.0,1.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(0.0,1.0,1.0);

    glEnd();

}

void cube()
{
    heli_base();
}

void wall_win()
{
    glPushMatrix();
    glPushMatrix();
        ownscale(1, 0.3, 1);
        cube();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,0.3,0);
        ownscale(0.3, 0.4, 1);
        cube();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.7,0.3,0);
        ownscale(0.3, 0.4, 1);
        cube();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,0.7,0);
        ownscale(1, 0.3, 1);
        cube();
    glPopMatrix();
    glPopMatrix();
}

void heli_base2()
{
    glBegin(GL_QUADS);
    glVertex3f(1.0,2.5,0.0);
    glVertex3f(1.0,2.5,1.0);
    glVertex3f(1.0,1.5,1.0);
    glVertex3f(1.0,1.5,0.0);

    glVertex3f(0.0,1.0,0.0);
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(1.0,2.5,1.0);
    glVertex3f(1.0,2.5,0.0);

    glVertex3f(0.0,1.0,0.0);
    glVertex3f(1.0,2.5,0.0);
    glVertex3f(1.0,1.5,0.0);
    glVertex3f(0.0,0.0,0.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,1.5,0.0);
    glVertex3f(1.0,1.5,1.0);
    glVertex3f(0.0,0.0,1.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(0.0,1.0,0.0);

    glVertex3f(0.0,0.0,1.0);
    glVertex3f(1.0,1.5,1.0);
    glVertex3f(1.0,2.5,1.0);
    glVertex3f(0.0,1.0,1.0);

    glEnd();

}

void heli_side()
{
    glBegin(GL_POLYGON);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(0.4,1.0,0.0);
    glVertex3f(0.0,0.3,0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.0,0.3,0.0);
    glVertex3f(0.4,1.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(0.0,0.3,-1.0);
    glVertex3f(0.4,1.0,-1.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(0.0,0.0,-1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.0,0.0,-1.0);
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(0.4,1.0,-1.0);
    glVertex3f(0.0,0.3,-1.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,1.0,0.0);

    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(1.0,0.0,0.0);

    glVertex3f(0.4,1.0,-1.0); //2
    glVertex3f(0.4,1.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,1.0,-1.0);

    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(0.4,1.0,0.0);
    glVertex3f(0.4,1.0,-1.0);

    glVertex3f(0.0,0.0,-1.0); //3
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,0.0,-1.0);
    glVertex3f(0.0,0.0,-1.0);

    glVertex3f(0.0,0.3,-1.0); //4
    glVertex3f(0.0,0.0,-1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.3,0.0);

    glVertex3f(0.0,0.3,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,-1.0);
    glVertex3f(0.0,0.3,-1.0);

    glVertex3f(0.3,0.825,0.0); //5
    glVertex3f(0.3,0.825,-1.0);
    glVertex3f(0.0,0.3,-1.0);
    glVertex3f(0.0,0.3,0.0);

    glVertex3f(0.0,0.3,0.0);
    glVertex3f(0.0,0.3,-1.0);
    glVertex3f(0.3,0.825,-1.0);
    glVertex3f(0.3,0.825,0.0);

    glEnd();
}



static void cameraMagic()
{
    GLdouble angleInRadians = camTheta * PI / 180.0;
    GLdouble cosAngle = cos(angleInRadians);
    GLdouble sinAngle = sin(angleInRadians);
    GLdouble camZ = camRadius * cosAngle;
    GLdouble camX = camRadius * sinAngle;
    GLdouble camY = camHeight;
    gluLookAt(camX, camY, camZ, camCenterX, camCenterY, camCenterZ, upX, upY, upZ);
}




void wall(int f)
{
    glPushMatrix();
    int scale = 20;
    glPushMatrix();
    if(f==1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,5);
        glEnable(GL_TEXTURE_2D);
        glTranslated(0,1,0); //floor
        glRotated(90,1,0,0);
        ownscale(scale,scale,1);
        cube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    else{
        glPushMatrix();
        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess2);
        glPopMatrix();
        glPushMatrix();
        glTranslated(0,1,0);
        glRotated(90,1,0,0);
        ownscale(scale,scale,1);
        cube();
        glPopMatrix();
        glPopMatrix();
    }

    glPopMatrix();


    glPushMatrix();
    if(f==1){
        glPushMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,6); //wall_1
        glEnable(GL_TEXTURE_2D);
        glTranslated(0,1,0);
        ownscale(scale,scale,1);
        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient7);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse7);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular7);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess7);
        glPopMatrix();
        cube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient7);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse7);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular7);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess7);
        glBindTexture(GL_TEXTURE_2D,4);
        glEnable(GL_TEXTURE_2D);
        glTranslated(7,13,1);
        ownscale(scale/3,scale/3,1);
        cube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient7);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse7);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular7);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess7);
        /*glBindTexture(GL_TEXTURE_2D,4);
        glEnable(GL_TEXTURE_2D);
        glTranslated(7,13,1);                                   /////pattern
        ownscale(scale/3,scale/3,1);
        cube();
        glDisable(GL_TEXTURE_2D);*/
        glTranslated(17,15,1);
        ownscale(scale/5,scale/5,scale/2);
        gasket(lev);

        glPopMatrix();

        glPushMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        glTranslated(3,18,1);
        ownscale(0.35,0.25,4);
        cube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPopMatrix();
        if(light0 == 1){
        glMaterialfv(GL_FRONT, GL_EMISSION, white_emission);
        glPushMatrix();
        glTranslated(3,18,5);
        glutSolidSphere(1,slices,stacks);
        glPopMatrix();
        }
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
        glPopMatrix();
    }
    else{
        glPushMatrix();
        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess5);
        glPopMatrix();
        glPushMatrix();
        glTranslated(0,1,0);
        ownscale(scale,scale,1);
        cube();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();

 glPushMatrix();

    if(f==1){
        glPushMatrix();

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,6);
        glEnable(GL_TEXTURE_2D);
        glTranslated(0,1,20);
        glRotated(90,0,1,0);
        ownscale(scale-1,scale,1);//wall_2
        wall_win();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient7);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse7);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular7);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess7);
        glBindTexture(GL_TEXTURE_2D,3);
        glEnable(GL_TEXTURE_2D);
        glTranslated(-5,1,22);
        glRotated(90,0,1,0);
        ownscale(scale-1,scale,1);
        glPushMatrix();
        glPopMatrix();
        cube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        glTranslated(0,18,18);
        glRotated(90,0,1,0);
        ownscale(0.35,0.25,4);
        cube();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        if(light1 == 1){
        glMaterialfv(GL_FRONT, GL_EMISSION, white_emission);
        glPushMatrix();
        glTranslated(4,18,18);
        glutSolidSphere(0.75,slices,stacks);
        glPopMatrix();
        }
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
        glPopMatrix();
    }
    else{
        glPushMatrix();
        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess2);
       // glMaterialfv(GL_FRONT, GL_EMISSION,mat_ambient1);
        glPopMatrix();
        glPushMatrix();
        glTranslated(0,1,20);
        glRotated(90,0,1,0);
        ownscale(scale-1,scale,1);
        wall_win();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-5,1,22);
        glRotated(90,0,1,0);
        ownscale(scale-1,scale,1);
        glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient3);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse3);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular3);
        glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess3);
       // glMaterialfv(GL_FRONT, GL_EMISSION,mat_ambient4);
        glPopMatrix();
        cube();
        glPopMatrix();
        glPopMatrix();
    }

    glPopMatrix();
    glPopMatrix();
}

void table()
{
    int tabh = 10; //table height
    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient6);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse6);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular6);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess6);//1
    glTranslated(5,tabh,5);
    ownscale(10,1,10);
    cube();
    glPopMatrix();

    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient6);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse6);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular6);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess6);
    glPushMatrix();
    glTranslated(5,0.001,5);
    ownscale(1,tabh,1);
    cube();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient6);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse6);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular6);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess6);
  //  glMaterialfv(GL_FRONT, GL_EMISSION,mat_ambient6);
    glPushMatrix();
    glTranslated(14,0.001,5);
    ownscale(1,tabh,1);
    cube();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient6);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse6);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular6);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess6);
    glPushMatrix();
    glTranslated(5,0.001,14);
    ownscale(1,tabh,1);
    cube();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient6);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse6);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular6);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess6);

    glPushMatrix();
    glTranslated(14,0.001,14);
    ownscale(1,tabh,1);
    cube();
    glPopMatrix();
    glPopMatrix();
}

void jack_leg()
{
    glPushMatrix();
    ownscale(1,1,7);
    glutSolidSphere(3,slices,stacks);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,21);
    glutSolidSphere(3,slices,stacks);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,-21);
    glutSolidSphere(3,slices,stacks);
    glPopMatrix();
}
void fireMan()
{
    glPushMatrix();

      ownScaled(1, .6, 1);
       // glRotated(degreex, 1, 0, 0);
       // glRotated(degreey, 0, 1, 0);
       // glRotated(degreez, 0, 0, 1);

        // Robot matha
        glPushMatrix();

        glTranslated(0,4.3,1);
        ownScaled(.6,.8,.6);
        //head
        {

glPushMatrix();
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess5);
        glPushMatrix();
        glTranslated(0,1,0);
        glRotated(90,1,0,0);
        ownScaled(.3, .3,6);
        circle(1,1,0);
        glPopMatrix();

        glPushMatrix();
        glRotated(90,1,0,0);
        ownScaled(.5, .5, 12);
        circle(1,1,0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0,-1,0);
        glRotated(90,1,0,0);
        ownScaled(.3, .3, 6);
        circle(1,1,0);
        glPopMatrix();

        //eye
        glPushMatrix();
        glTranslated(-.35,.2,1);
        ownScaled(.08, .08, .08);
        circle(0,0,0);
        glPopMatrix();

        glPushMatrix();
        glTranslated(.35,.2,1);
        ownScaled(.08, .08, .08);
        circle(0,0,0);
        glPopMatrix();

        //smile


        glPushMatrix();
        glRotated(180,1,0,0);
        glTranslated(0,.5,-1);
        ownScaled(.3, .1, .3);
        circle2(0,0,0);
        glPopMatrix();

        glPopMatrix();
        // Matha sesh
glPopMatrix();
        }
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular1);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess1);
        //Robot Body

        glPushMatrix();
        glTranslated(-1,0,0);
        ownScaled(1,3,1.5);
        Trap(0,1,0);
        glPopMatrix();

        //Robot Hand

        glPushMatrix();
        glTranslated(-.21,0,-.25);
        glRotated(-5,0,0,1);
        glTranslated(-0.9,2.5,1);
        ownScaled(.5,.2,.2);
        glRotated(90,0,1,0);
        circle(1,0,0);

        glPopMatrix();

        glPushMatrix();
        glTranslated(.21,0,-.25);
        glRotated(5,0,0,1);
        glTranslated(0.9,2.5,1);
        ownScaled(.5,.2,.2);
        glRotated(90,0,1,0);
        circle(1,0,0);

        glPopMatrix();

        // Armsss

       {

       glPushMatrix();

         glRotatef(angle, 1, 0, 0);
        glPushMatrix();
        glRotated(-4.5,0,1,0);
        glRotated(-8,0,0,1);
        glTranslated(-1.4,1.5,1);
        glRotated(90,1,0,0);
        ownScaled(.1, .1,12);

        circle(1,0,0);

        glPopMatrix();



        glPushMatrix();
        glRotated(4.5,0,1,0);
        glRotated(8,0,0,1);
        glTranslated(1.4,1.5,1);
        glRotated(90,1,0,0);
        ownScaled(.1, .1,12);

        circle(1,0,0);

        glPopMatrix();


        //Arms 22


            glPushMatrix();

           // glTranslated(0,0,2);

        glTranslated(-1.4,0.2,.9);
        glRotated(90,1,0,0);
        ownScaled(.1, .1,5);

        circle(1,0,0);

        glPopMatrix();



          glPushMatrix();
       // glRotated(-15,1,0,0);
        glTranslated(1.4,.2,.9);
        glRotated(90,1,0,0);
        ownScaled(.1, .1,5);

        circle(1,0,0);

        glPopMatrix();

        glPopMatrix();
       }
       //arm22 last
        //Robot leg parts
        glPushMatrix();
        glTranslated(-1.22,-.8,0);
        ownScaled(1.24,.8,1.5);
        Trap(0,0,1);
        glPopMatrix();


        glPushMatrix();
        glTranslated(0,-1,.75);
        ownScaled(12.5, .22, .4);
        glRotated(90,0,1,0);

        circle(0,0,1);
        glPopMatrix();

        glPushMatrix();

        glTranslated(-.7,-1.8,.75);
        glColor3f(0,0,1);
        ownScaled(.5,2.7,.5);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();

        glTranslated(.7,-1.8,.75);
        glColor3f(0,0,1);
        ownScaled(.5,2.7,.5);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslated(.7,-3,.75);
        glColor3f(0,0,1);
        ownScaled(.65,.65,.65);
        glutSolidCube(1);
        glPopMatrix();


        glPushMatrix();
        glTranslated(-.7,-3,.75);
        glColor3f(0,0,1);
        ownScaled(.65,.65,.65);
        glutSolidCube(1);
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

    }






void jack()
{
    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess2);
   // glMaterialfv(GL_FRONT, GL_EMISSION,mat_ambient2);
    glTranslated(8,11,10);

    ownscale(0.1,0.1,0.1);
    glTranslated(0,17.84,0);
    //first leg
    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess2);
 //   glMaterialfv(GL_FRONT, GL_EMISSION,mat_ambient2);
    glRotated(45,1,0,0);
    jack_leg();
    glPopMatrix();

    //Second leg
    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess2);
   // glMaterialfv(GL_FRONT, GL_EMISSION,mat_ambient2);
    glRotated(60,0,1,0);
    glRotated(-45,1,0,0);
    jack_leg();
    glPopMatrix();

    //Third leg
    glPushMatrix();
    glRotated(120,0,1,0);
    glRotated(45,1,0,0);
    jack_leg();
    glPopMatrix();


    glPopMatrix();
}
void environment(int f)
{
    glPushMatrix();
    glPushMatrix();
    wall(f);
    glPopMatrix();

    glPushMatrix();
    if(f==1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,2);
        glEnable(GL_TEXTURE_2D);
        table();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    else{
        glPushMatrix();
        table();
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();
}
void full_setup(int f)
{

    glPushMatrix();
    glTranslated(-10,-10,-10);
    glPushMatrix();
    glTranslated(22,23,20);
    //ownscale(.5,.5,.5);
    fireMan();
    glPopMatrix();

    glPushMatrix();
    environment(f);
    glPopMatrix();

    glPushMatrix();
    //glRotated(60,0,1,1);
    jack();
    glPopMatrix();
    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    cameraMagic();
    glPushMatrix();

    glViewport(0, 0, wid1/2, hei1-100);
    glTranslated(tx-5,ty-5,-12+tz);
    ownscale(.6*zm,.6*zm,.6*zm);
    glRotated(10+degree_x,1,0,0);
    glRotated(degree_y,0,1,0);
    glRotated(degree_z,0,0,1);
    glPushMatrix();
    full_setup(0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glViewport(wid1/2, 0, wid1/2, hei1-100);
    glTranslated(tx-5,ty-5,-12+tz);
    ownscale(.6*zm,.6*zm,.6*zm);
    glRotated(10+degree_x,1,0,0);
    glRotated(degree_y,0,1,0);
    glRotated(degree_z,0,0,1);
    glPushMatrix();
    full_setup(1);
    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case '<':
        glDisable( GL_LIGHT0);
        light0 = 0;
        break;

    case '>':
        glDisable( GL_LIGHT1);
        light1 = 0;
        break;

    case '[':
        glEnable(GL_LIGHT0);
        light0 = 1;
        break;

    case ']':
        glEnable(GL_LIGHT1);
        light1 = 1;
        break;

    case '(':
        glEnable(GL_LIGHT2);
        break;

    case ')':
        glDisable(GL_LIGHT2);
        break;

    case 'K':
        glLightfv(GL_LIGHT0, GL_AMBIENT,  no_light);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  no_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        break;
    case 'L':
        glLightfv(GL_LIGHT1, GL_AMBIENT,  no_light);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  no_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, no_light);
        break;

    case 'm':
        degree_x+=3;
        break;

    case 'n':
        degree_x-=3;
        break;

    case 'k':
        degree_y+=3;
        break;

    case 'l':
        degree_y-=3;
        break;

    case 'y':
        degree_z+=3;
        break;

    case 'z':
        degree_z-=3;
        break;

    case '+':
        zm+=0.25;
        break;

    case '-':
        zm-=0.25;
        break;
    case 'a':
        tx-=0.5;
        break;

    case 'd':
        tx+=0.5;
        break;

    case 'w':
        ty+=0.5;
        break;

    case 's':
        ty-=0.5;
        break;

    case 'o':
        tz+=0.5;
        break;

    case 'p':
        tz-=0.5;
        break;

    case 'W':
        camRadius -= 1;
        break;
    case 'S':
        camRadius += 1;
        break;
    case 'Q':
        camTheta -= 5;
        break;
    case 'R':
        camTheta += 5;
        break;

    case '1': //yaw
        pitch -= 5;
        yaw -= 5;
        camCenterX = cos((pitch*3.1416)/180) + sin((yaw*3.1416)/180);
        camCenterY = 0;
        camCenterZ = cos((pitch*3.1416)/180) - sin((yaw*3.1416)/180);
        break;

    case '2': //pitch
        pitch -= 5;
        yaw -= 5;
        camCenterX = 0;
        camCenterY = sin((pitch*3.1416)/180);
        camCenterZ = cos((yaw*3.1416)/180);
        break;

    case '3': //roll clock wise
        roll += 5;
        upX = cos((roll*3.1416)/180);
        upY = sin((roll*3.1416)/180);
        if (roll > 360)
        {
            roll = 0;
        }
        break;
    case '4': //roll anti clock wise
        roll -= 5;
        upX = cos((roll*3.1416)/180);
        upY = sin((roll*3.1416)/180);
        if (roll < 0)
        {
            roll = 360;
        }
        break;

    case '8':
        lev+=1;
        break;
    case '9':
        lev-=1;
        break;
    }

    glutPostRedisplay();
}

void Init()
{
    pix[0].makeCheckImage();
	pix[0].setTexture(1);
	pix[1].readBMPFile("C:\\Users\\Ohida Amin Ohi\\Desktop\\Nazia\\newwwww\\table.bmp");
	pix[1].setTexture(2);
	pix[2].readBMPFile("C:\\Users\\Ohida Amin Ohi\\Desktop\\Nazia\\newwwww\\kuet.bmp");
	pix[2].setTexture2(3);
	pix[3].readBMPFile("C:\\Users\\Ohida Amin Ohi\\Desktop\\Nazia\\newwwww\\mona.bmp");
	pix[3].setTexture2(4);
    pix[4].readBMPFile("C:\\Users\\Ohida Amin Ohi\\Desktop\\Nazia\\newwwww\\down_load.bmp");
	pix[4].setTexture(5);
    pix[5].readBMPFile("C:\\Users\\Ohida Amin Ohi\\Desktop\\Nazia\\newwwww\\008briques.bmp");
	pix[5].setTexture(6);
}

static void idle(void)
{
    glutPostRedisplay();
}
static int cc=1;
void spin()
{

   // angle = angle - .1;
    if (angle <=-10 && cc==1)
    {
        cc=0;

    }
    else if(angle>=10 &&cc==0)
    {
        cc=1;

    }
    if(cc==0)
        angle+=.1;
    else
        angle-=.1;
    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Robot 1507016");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(spin);

    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT2, GL_AMBIENT,  spot_ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE,  spot_diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, spot_specular);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
        glLightfv(GL_LIGHT2, GL_POSITION, spot_position);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 5.5f);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1000.0f);
        printf("< dis Light0,> dis light1,[ en light0,] en light1, ( light 2,) dis lig2, K light0,L light1\n");
        printf("m,n x-axis; k,l y-axis, y,z Z-axis; + zm,- zm\n");
        printf("a,d tx,w,s ty,o,p tz,  1 yaw,2 pitch, 3 roll clock,4 roll anticlock;\n");

        printf("cam W,S,Q,R");
    Init();
    glutMainLoop();

    return EXIT_SUCCESS;
}
