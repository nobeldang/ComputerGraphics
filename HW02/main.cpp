#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <vector>
void init();
void display();
void keyboard(unsigned char key, int x, int y);
bool isPersp = true;
int init_fov = 30;
int fov = 30;

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);
  GLfloat length = 1.0;
  // back
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  1.0,  1.0  );
  glVertex3f(  length*0.5, -length*0.5, -length*0.5 );
  glVertex3f(  length*0.5,  length*0.5, -length*0.5 );
  glVertex3f( -length*0.5,  length*0.5, -length*0.5 );
  glVertex3f( -length*0.5, -length*0.5, -length*0.5 );
  glEnd();
  // front
  glBegin(GL_POLYGON);
  glColor3f( 0.0,  1.0,  0.0 );
  glVertex3f(  length*0.5, -length*0.5, length*0.5 );
  glVertex3f(  length*0.5,  length*0.5, length*0.5 );
  glVertex3f( -length*0.5,  length*0.5, length*0.5 );
  glVertex3f( -length*0.5, -length*0.5, length*0.5 );
  glEnd();
  // left
  glBegin(GL_POLYGON);
  glColor3f(  0.0,  0.0,  1.0 );
  glVertex3f( -length*0.5, -length*0.5,  length*0.5 );
  glVertex3f( -length*0.5,  length*0.5,  length*0.5 );
  glVertex3f( -length*0.5,  length*0.5, -length*0.5 );
  glVertex3f( -length*0.5, -length*0.5, -length*0.5 );
  glEnd();
  // right
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.5,  0.5 );
  glVertex3f( length*0.5, -length*0.5, -length*0.5 );
  glVertex3f( length*0.5,  length*0.5, -length*0.5 );
  glVertex3f( length*0.5,  length*0.5,  length*0.5 );
  glVertex3f( length*0.5, -length*0.5,  length*0.5 );
  glEnd();
  // top
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.5, 1.0 );
  glVertex3f(  length*0.5,  length*0.5,  length*0.5 );
  glVertex3f(  length*0.5,  length*0.5, -length*0.5 );
  glVertex3f( -length*0.5,  length*0.5, -length*0.5 );
  glVertex3f( -length*0.5,  length*0.5,  length*0.5 );
  glEnd();
  // bottom
  glBegin(GL_POLYGON);
  glColor3f(   0.5,  0.5, 1.0 );
  glVertex3f(  length*0.5, -length*0.5, -length*0.5 );
  glVertex3f(  length*0.5, -length*0.5,  length*0.5 );
  glVertex3f( -length*0.5, -length*0.5,  length*0.5 );
  glVertex3f( -length*0.5, -length*0.5, -length*0.5 );
  glEnd();

  glFlush();

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  GLfloat temp[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, temp);
  printf("Modelview Matrix: ");
  for (int i = 0; i < 16; i++) {
      printf("%f ", temp[i]);
  }
  printf("\n");
  glPopMatrix();

  // apply transformations to the currect matrix
  switch (key) {
    case 'w':
      glTranslatef(0.0, 0.2, 0.0);
      break;
    case 's':
      glTranslatef(0.0, -0.2, 0.0);
      break;
    case 'a':
      glTranslatef(-0.2, 0.0, 0.0);
      break;
    case 'd':
      glTranslatef(0.2, 0.0, 0.0);
      break;
    case 'q':
      glTranslatef(0.0, 0.0, -0.2);  //away from screen
      break;
    case 'e':
      glTranslatef(0.0, 0.0, 0.2);  //closer to the screen
      break;
    // rotations
    case 'x':
      glRotatef(10, 1.0, 0.0, 0.0);
      break;
    case 'y':
      glRotatef(10, 0.0, 1.0, 0.0);
      break;
    case 'z':
      glRotatef(10, 0.0, 0.0, 1.0);
      break;
    // scaling
    case 'j':
      glScalef(2.0, 1.0, 1.0);
      break;
    case 'k':
      glScalef(1.0, 2.0, 1.0);
      break;
    case 'l':
      glScalef(1.0, 1.0, 2.0);
      break;
    case 'c':
      fov = 30;
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluPerspective(fov, 1.0/1.0, 1.0, 400);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
      break;
    case 'p':
      if (isPersp){
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(-50, 50, -50, 50, 1.0, 400);  //l, r, b, t, n, f
        isPersp = false;
        // maybe add view and model transformation: not sure
      }
      else{
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluPerspective(fov, 1.0/1.0, 1.0, 400);  // fov, aspect, n, f
        isPersp = true;
      }
      break;

    // translate camera
    case '8':
      glTranslatef(0.0, -0.2, 0.0);
      break;
    case '2':
      glTranslatef(0.0, 0.2, 0.0);
      break;
    case '4':
      glTranslatef(0.2, 0.0, 0.0);
      break;
    case '6':
      glTranslatef(-0.2, 0.0, 0.0);
      break;
    case '+':
      glTranslatef(0.0, 0.0, 0.2); //clsoe to origin
      break;
    case '-':
      glTranslatef(0.0, 0.0, -0.2); // away from the origin
      break;
    case 'n':
      fov += 10;
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluPerspective(fov, 1.0/1.0, 1.0, 400);  // fov, aspect, n, f
      isPersp = true;
      break;
    default:
      break;
  }
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(temp);
  glPopMatrix();

  glFlush();
  //redisplay
  glutPostRedisplay();
}


void init() {

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);

  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(init_fov, 1.0/1.0, 1.0, 400);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 800);
  glutCreateWindow("ASSIGNMENT 3");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
}
