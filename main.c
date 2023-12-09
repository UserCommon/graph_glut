#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float x;
  float y;
} PointF;

PointF *arr = NULL;
int cnt;
float scaleY = 1.0;
float scaleModifier = 1.5;

void Init(float start, float finish, int count, double (*functor)(double)) {
  cnt = count;
  arr = realloc(arr, sizeof(*arr) * cnt);
  float dx = (finish - start) / (cnt - 1);
  for (int i = 0; i < cnt; i++) {
    arr[i].x = start;
    arr[i].y = (float)functor(start);
    start += dx;
  }
}

void Show() {
  float sx = 2.0 / (arr[cnt - 1].x - arr[cnt - 1].y);
  float dx = (arr[cnt - 1].x + arr[0].x) * 0.5;
  glPushMatrix();
  glScalef(sx, scaleY, 1);
  glTranslatef(-dx, 0, 0);

  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < cnt; i++) {
    glVertex2f(arr[i].x, arr[i].y);
  }
  glEnd();

  glPopMatrix();
}

void drawAxis(float angle) {
  static float d = 0.05;
  glPushMatrix();
  glRotatef(angle, 0, 0, 1);
  glBegin(GL_LINES);
  glVertex2f(-1, 0);
  glVertex2f(1, 0);
  glVertex2f(1, 0);
  glVertex2f(1 - d, 0 + d);
  glVertex2f(1, 0);
  glVertex2f(1 - d, 0 - d);
  glEnd();
  glPopMatrix();
}

double linear(double x) { return x / 1.05; } // wtf? y = x not working!
double parabolic(double x) { return (x * x); }
double hyperbolic(double x) { return 1 / x; }

void display() { // Display function will draw the image.

  glClearColor(0, 0.0f, 0.0f, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glLineWidth(2);

  // x
  glColor3f(1, 0, 0);
  drawAxis(0);
  // y
  glColor3f(0, 1, 0);
  drawAxis(90);

  printf("DISPLAYED\n");
  Init(-10, 10, 10000, hyperbolic);
  Show();

  glutSwapBuffers(); // Required to copy color buffer onto the screen.
}

void mouseProcessing(int button, int state, int x, int y) {
  if (button == 3 && state == GLUT_UP) {
    scaleY *= scaleModifier;
  } else if (button == 4 && state == GLUT_UP) {
    scaleY /= scaleModifier;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(800, 100);
  glutCreateWindow("Windooow");
  glutMouseFunc(mouseProcessing);
  glutDisplayFunc(display);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glutMainLoop();
  return 0;
}
