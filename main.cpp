#include<iostream>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<GL/freeglut.h>
#include<cstdio>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<sstream>
#include<time.h>
#include "imageloader.h"


using namespace std;

#define WIDTH 1200
#define HEIGHT 700
#define PI 3.14/180

// screen coordinates=  X)max = 700   Y)max = 400
// origin at left bottom corner
float zoom_in=0.0;
float zoom = 1;
float X=0,Y=0;
float vx,vy;
int start = 0;
float _angleOfCannon = 0.0f;		//angle made by the ball with X-Axis
float v = 7.0;				//initial velocity
float gravity = 0.2;
float friction = 0.1;
float Ymax = 0.1;			//for applying friction to X
float e = 0.8;				//coeffeciant of restitution for collision with the baseline
int lengthSpeed = 20;
float _angle = 0.1f;
char defaultMessage[] = "GLUT means OpenGL.";
char *message = defaultMessage;
int radiusBall = 10;
int radiusObstacle = 10;
int score = 0;
int flagObstacle = 0;
int numOfBalls = 0;
//void *font = GLUT_STROKE_ROMAN;

	
/*void selectMessage(int msg)
{
	switch (msg) {
	case 1:
	message = "abcdefghijklmnop";
	break;
	case 2:
	message = "ABCDEFGHIJKLMNOP";
	break;
	}
	}
 */
void update(int);

void shape()
{
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-350-zoom_in,350+zoom_in,-140-(10/16)*zoom_in,140+(10/16)*zoom_in);
}
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
bool detectcollision(int x1, int y1,int radius1, int x2, int y2, int radius2)
{
	int xd, yd, Distance;

	//2d
	xd = x2-x1;
	yd = y2-y1;     
	Distance = sqrt(xd*xd + yd*yd);

	if( radius1 + radius2 >= Distance)
		return true; //collision
	return false;    //no collision    
}


void handleKeypress(unsigned char key, int x, int y)
{
	if(key == 27)
		exit(0);
	if(key == ' ' && start == 0)
	{
		numOfBalls ++;
		X = 0.0;
		Y = 0.0;
		start = 0;
		//	v = 7.0;
		Ymax = 0.1;
		start = 1;
		vx=v*cos(_angleOfCannon*PI);
		vy=v*sin(_angleOfCannon*PI);
		glutTimerFunc(25,update,0);
	}
	if(key == 'z')
	{
		zoom += 0.2;
	}
	if(key == 'x')
	{
		zoom -= 0.2;
	}
/*	
	if(key=='z')
	{
		zoom_in=zoom_in+1.0;
//		glMatrixMode(GL_PROJECTION);
//		gluOrtho2D(-1.8-zoom_in,1.8+zoom_in,-1.0-(9/16)*zoom_in,1.0+(9/16)*zoom_in);

	}
	if(key=='x')
	{
		zoom_in=zoom_in-1.0;
	}
*/
}

void keyBoard(int key, int, int)			//for special keys like arrow keys
{
	if(key == GLUT_KEY_UP)
	{
		_angleOfCannon += 5.0;
	}
	if(key == GLUT_KEY_DOWN)
	{
		_angleOfCannon -= 5.0;
	}
	if(key == GLUT_KEY_LEFT)
	{
		v -= 0.5;
		lengthSpeed -= 2;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		v += 0.5;
		lengthSpeed += 2;
	}

}

void processMouse(int button, int state, int Mx, int My)
{

	if(state == GLUT_DOWN)
	{
		if(button == GLUT_LEFT_BUTTON)
		{
			if(start == 0)
			{
				numOfBalls ++;
				X = 0.0;
				Y = 0.0;
				start = 0;
				//	v = 7.0;
				Ymax = 0.1;
				start = 1;
				vx=v*cos(_angleOfCannon*PI);
				vy=v*sin(_angleOfCannon*PI);
				glutTimerFunc(25,update,0);
			}
		}
		if(button == 3)
			_angleOfCannon += 5.0;
		if(button == 4)
			_angleOfCannon -= 5.0;

	}
}
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
/*
	Image* image = loadBMP("vtr.bmp");
	_textureId = loadTexture(image);
	delete image;
	*/
}


void handleResize(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(45.0,(double)w/(double)h,1.0,200.0);
}
void update(int value)
{

/*	if(vx <= 0 && vy <= 0)
	{
		X = 0.0;
		Y = 0.0;
		start = 0;
		v = 7.0;
		_angleOfCannon = 0.0f;
		Ymax = 0.1;

		}
 */

	if(numOfBalls == 4)						// num of chances == 3
	{
/*		start = 1;
		radiusBall = 0;
		char sc[100];
		glColor3f(1.0f,0,0);
		sprintf(sc,"Score : %d",score);
		glRasterPos3d(200,280 ,0.0);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
		*/
		exit(0);
	}
	_angle += 2.0f;
	if(_angle > 360)
		_angle -=360;
	if(X <= -10)
		vx*= -1;
	if(Ymax < Y)
		Ymax = Y;
	if(Y < -10)					//-10 for baseline
	{
		vy*= -e;			
		if(vx>0)
		{
			vx-=friction;			//only if the ball is moving on ground(i.e.Y<0) and vx>0(obviously)
		}
		else
		{
			vx = 0;				//stop vx once it reaches < 0 else it wud go in -X direction
		}
	}
	else
		vy=vy-gravity;
	X+=vx;
	Y+=vy;
	X -= 0.01;				//air friction
	if(vx > 0 || vy > 0)
	{
		glutPostRedisplay();
		glutTimerFunc(25,update,0);
	}
	else
	{
		start = 0;
		X = 0;
		Y = 0;
	}
// to make ball disappear once it goes out of the screen
	if(X > 700)
	{
		start = 0;
		X = 0;
		Y = 0;
		vx = 0;
		vy = 0;
	}
		glutPostRedisplay();
}

class obstacle
{
	public:
		int ox;
		int oy;
		int osize;
		obstacle()
		{
			osize = 1;
		}
		void omake()
		{
			float distance;
			int ocentreX = ox;
			int ocentreY = oy;
			distance = sqrt((X-ocentreX)*(X-ocentreX) + (Y-ocentreY)*(Y-ocentreY));
			glPushMatrix();
			glTranslatef(ox,oy,0);
			ox = 0,oy = 0;
			glBegin(GL_POLYGON);
			glColor3f(2.1,0.0f,0.0f);
			for(int i=0;i<360;i++)
			{
				glVertex2f(ox+radiusObstacle*cos(i*(3.14/180)),oy+radiusObstacle*sin(i*(3.14/180)));
			}
			if(radiusBall + radiusObstacle >= distance)
			{
		//		printf("%d\n",score);
				X = 0;
				Y = 0;
				vx =0 ;
				vy =0;
				flagObstacle = 1;
			}

			/*			glVertex2f(ox,oy);
						glVertex2f(ox,oy+10);
			glVertex2f(ox+10,ox+10);
			glVertex2f(ox+10,oy);
*/
			glEnd();
			glPopMatrix();
		}
};
obstacle oobj[100];

//squares
class kill
{
	public:
		int kx;
		int ky;
		int ksize;
		kill()
		{
			ksize = 2;
		}
		void kmake()
		{
			float distance;
			int kcentreX = kx;
			int kcentreY = ky;
			distance = sqrt((X-kcentreX)*(X-kcentreX) + (Y-kcentreY)*(Y-kcentreY));
//			int kcentreX = kx+5*ksize;
//			int kcentreY = ky+5*ksize;

//			p=sqrt((X-(sx+5))*(X-(sx+5)) + (Y-(sy+5))*(Y-(sy+5)));


			
			glPushMatrix();
			glTranslatef(kx,ky,0);
			kx = -10;
			ky = -10;
			glBegin(GL_POLYGON);				
			glColor3f(0.0f,0.0f,0.0f);
			glVertex2f(kx,ky);
			glVertex2f(kx+10*ksize,ky);
			glVertex2f(kx+10*ksize,ky+10*ksize);
			glVertex2f(kx,ky+10*ksize);
			if(radiusBall + 2>= distance)
			{
				X = 0;
				Y = 0;
				vx = 0;
				vy = 0;
				score -= 20;
			}
			glEnd();
			glPopMatrix();
		}
};
kill kobj[10];
		

class star
{
	public:
		int sx;
		int sy;
		int ssize;
		star()
		{
		
	//		x=rand()%300+300;
	//		y=rand()%250+100;
			ssize=1;
		}
		void smake()
		{
			float distance;
			int scentreX = sx+5*ssize;
			int scentreY = sy+5*ssize;
			distance = sqrt((X-scentreX)*(X-scentreX) + (Y-scentreY)*(Y-scentreY));
			if(radiusBall + 7>= distance && ssize!=0)
			{
				ssize = 0;
				score += 5;
			}
			glPushMatrix();
			glTranslatef(sx,sy,0);
			glRotatef(_angle,0.0f,0.0f,1.0f);
			sx = -5,sy=-5;

			glBegin(GL_POLYGON);				
			glColor3f(2.1f,1.2f,0.4f);
			glVertex2f(sx,sy);
			glVertex2f(sx+10*ssize,sy);
			glVertex2f(sx+5*ssize,sy+10*ssize);
			glEnd();

			glBegin(GL_POLYGON);				
			glColor3f(2.1f,1.2f,0.4f);
			glVertex2f(sx,sy+7*ssize);
			glVertex2f(sx+10*ssize,sy+7*ssize);
			glVertex2f(sx+5*ssize,sy-3*ssize);
			glEnd();

			glPopMatrix();
		}
/*			glBegin(GL_POLYGON);				
			glColor3f(2.1f,1.2f,0.4f);
			glVertex2f(x,y);
			glVertex2f(x+10*size,y);
			glVertex2f(x+5*size,y+10*size);
			glEnd();

			glBegin(GL_POLYGON);				
			glColor3f(2.1f,1.2f,0.4f);
			glVertex2f(x,y+7*size);
			glVertex2f(x+10*size,y+7*size);
			glVertex2f(x+5*size,y-3*size);
			glEnd();
			glPopMatrix();
			}
 */
};
star sobj[180];
/*
string convertInt(int number)
{
	stringstream ss (stringstream::in | stringstream::out);

	//stringstream ss;					//create a stringstream
	ss << number;						//add number to the stream
	return ss.str();					//return a string with the contents of the stream
}
*/
void bitmap_output(int ax, int ay, char *string, void *font)
{
	int alen;

	glRasterPos2f(ax, ay);
	alen = (int) strlen(string);
	for (int i = 0; i < alen; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}
//	char buffer[100];
//	strcpy(buffer,convertInt(Score));
//	cout << buffer << "\n";
//	itoa(Score,buffer,10);
/*	alen = (int) strlen(buffer);
	for(int i=0;i<alen;i++)
	{
	glutBitmapCharacter(font, buffer);
	}
 */
}
void drawScene(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glScalef(zoom,zoom,1);

	glClearColor(0.0,0.0,.2,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glScalef(0.01,0.01,0.01);
	glTranslatef(-350,-200,-500);				//moving origin to left bottom corner

	
/*	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 300.0f,- 5.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(300.0f, 300.0f, -5.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(300.0f, 0.0f, -5.0f);

	glEnd();
 */	
/*	glColor3f(1.0f,1.0f,1.0f);
	bitmap_output(500,40 ,"ABHINAV SINGI (201001051)",GLUT_BITMAP_HELVETICA_18);
*/	glColor3f(1.0f,0,0);

	char sc[100];
	sprintf(sc,"balls left : %d     Score : %d",3-numOfBalls,score);
	glRasterPos3d(500,380 ,0.0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
	sprintf(sc,"ABHINAV SINGI  201001051");
	glRasterPos3d(500,40 ,0.0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );

	//	bitmap_output(300, 390, "This is written in a GLUT bitmap font.",
	//			    GLUT_BITMAP_TIMES_ROMAN_24);
	//STAR
	int a=100,b=100;
	int i1=0,i2=0;
	for(int i=0;i<180;i++)
	{
		int flagObstacle = 0,flagKill = 0;
		if((a == 190 && b == 220) || (a==490 && b == 220) || (a == 340 && b== 340) || (a==340 && b == 100) )
			flagObstacle = 1;
		else if((a==340 && b == 220) )
			flagKill = 1;
		
		if(flagKill == 1)
		{
			kobj[i1].kx = a;
			kobj[i1].ky = b;
			kobj[i1].kmake();
			i1++;
		}
		else if(flagObstacle == 1)
		{
			oobj[i2].ox = a;
			oobj[i2].oy = b;
			oobj[i2].omake();
			i2++;
		}
		else
		{
			sobj[i].sx=a;
			sobj[i].sy=b;
			sobj[i].smake();
		}
		
		a += 30;
		if(a >=700)
		{
			a = 100;
			b += 30;
		}

	}

//SPEED BAR
	int lengthBar=150,widthBar=20,heightBar=360;
	
	if(lengthSpeed > lengthBar || lengthSpeed < 0)
	{
		v = 0;
		lengthSpeed = 0;
	}
	glBegin(GL_QUADS);
	glColor3f(0.1f,0.5f,0.3f);
	glVertex2f(0,heightBar);
	glColor3f(0.2f,0.1f,0.3f);
	glVertex2f(0,heightBar+widthBar);
	glColor3f(0.7f,0.5f,0.4f);
	glVertex2f(lengthSpeed,heightBar+widthBar);
	glColor3f(0.2f,0.3f,0.1f);
	glVertex2f(lengthSpeed,heightBar);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(3.1f,5.2f,6.3f);
	glVertex2f(0,heightBar);
	glVertex2f(0,heightBar+widthBar);
	glVertex2f(lengthBar,heightBar+widthBar);
	glVertex2f(lengthBar,heightBar);
	glEnd();


//GROUND	
	glBegin(GL_POLYGON);				//ground
	glColor3f(0.0f,1.2f,0.0f);
	
	glVertex2f(-10,10);
	glVertex2f(800,10);
	glVertex2f(800,-10);
	glVertex2f(-10,-10);
	
	glEnd();
	glTranslatef(0,20,0);				// baseline i.e. ground
	
	glTranslatef(20,10,0);				//canon position wrt to new origin
	

//CANNON
	int lc = 20;						// length of the cannon's base (here a hexagon)
	glColor3f(0.5f,0.0f,0.8f);
	//glPushMatrix();
	int lengthCannon=25,widthCannon=10;			//dimensions of cannon tube


	//ball
	glBegin(GL_POLYGON);
	glColor3f(0.8f,0.0f,0.1f);
	for(int i=0;i<360;i++)
	{
		glVertex2f(X+radiusBall*cos(i*(3.14/180)),Y+radiusBall*sin(i*(3.14/180)));
	}
	glEnd();

	
	//cannon tube
	glPushMatrix();					
	glRotatef(_angleOfCannon,0.0f,0.0f,1.0f);
	glColor3f(0.5f,0.0f,0.8f);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(lengthCannon,0);
	glVertex2f(lengthCannon,widthCannon);
	glVertex2f(0,widthCannon);
	glEnd();
	glPopMatrix();
	
	
	//base of cannon (here - hexagon)
	glColor3f(0.0f,0.0f,0.8f);
	glBegin(GL_POLYGON);
				//	glBegin(GL_LINE_LOOP);
	glVertex2f(lc*cos(30*(3.14/180)),lc*sin(30*(3.14/180)));
	glVertex2f(lc*cos(90*(3.14/180)),lc*sin(90*(3.14/180)));
	glVertex2f(lc*cos(150*(3.14/180)),lc*sin(150*(3.14/180)));
	glVertex2f(lc*cos(210*(3.14/180)),lc*sin(210*(3.14/180)));
	glVertex2f(lc*cos(270*(3.14/180)),lc*sin(270*(3.14/180)));
	glVertex2f(lc*cos(330*(3.14/180)),lc*sin(330*(3.14/180)));
	glEnd();


	glPopMatrix();					// for zooming
	
	glutSwapBuffers();
//	shape();						// for zooming in and zooming out
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);

	glutCreateWindow("GET THE STARS");
	initRendering();
//	shape();
	glutKeyboardFunc(handleKeypress);
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutSpecialFunc(keyBoard);
	glutMouseFunc(processMouse);
//	glutMotionFunc(processMouseActiveMotion);
//	glutPassiveMotionFunc(processMousePassiveMotion);
//	if(start == 1)
//		glutTimerFunc(25,update,0);

	glutMainLoop();

	return 0;
}


