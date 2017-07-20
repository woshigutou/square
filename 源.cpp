#include<glut.h>
#include<math.h>
#define  IWIDTH  400 
#define  IHEIGHT 400
#define ColoredVertex(c,v)do{glColor3fv(c);glVertex3fv(v);}while(0)

GLfloat angle = 0.0f;

void setNormal(GLfloat* Point1, GLfloat* Point2, GLfloat* Point3)
{
	GLfloat normal[3];
	int i;
	for (i = 0; i<3; ++i)
		normal[i] = (Point1[i] + Point2[i] + Point3[i]) / 3;
	glNormal3fv(normal);
}

void myDisplay(void)
{   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//光源
	GLfloat light_pos[] = { 0,0,10,1 };
	GLfloat light_amb[] = { 0,0,0,1 };
	GLfloat light_diff[] = { 1,1,1,1 };
	GLfloat light_spec[] = { 1,1,1,1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	static int list = 0;
	if (list == 0)
	{//显示列表不存在的时候创建一个原型
		GLfloat
			PointA[] = { 0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointB[] = { -0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointC[] = { 0.0f, -sqrt(6.0f) / 12, sqrt(3.0f) / 3 },
			PointD[] = { 0.0f, sqrt(6.0f) / 4, 0 };
		GLfloat
			ColorR[] = { 1, 0, 0 },
			ColorG[] = { 0, 1, 0 },
			ColorB[] = { 0, 0, 1 },
			ColorY[] = { 1, 1, 0 };
		/*GLfloat
			mat_amb[] = { 0,0,0,1 },
			mat_diff[] = { 0,0,0,1 },
			mat_spec[] = { 0,0,0,1 },
			mat_emis[] = {0,0,1,1},
			mat_shin = 0.2f;*/


		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		/*glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emis);
		glMaterialf(GL_FRONT, GL_SHININESS, mat_shin);*/
		
		//ABC
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorB, PointC);
		setNormal(PointA, PointB, PointC);
		//ACD
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorY, PointD);
		setNormal(PointA, PointC, PointD);
		// 平面 CBD
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorY, PointD);
		setNormal(PointC, PointB, PointD);
		// 平面 BAD
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorY, PointD);
		setNormal(PointB, PointA, PointD);
		glEnd();
		glEndList();


		
	}
	
	

	glPushMatrix();
	glRotatef(angle, 1, 0.5, 0);
	glCallList(list);
	glPopMatrix();
	glutSwapBuffers();//实现双缓存
}

void myIdle(void)
{
	++angle;
	if (angle >= 360.0f)
		angle = 0.0f;
	myDisplay();
}


int main(int argc, char*argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(IWIDTH, IHEIGHT);
	glutCreateWindow("旋转锥");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}