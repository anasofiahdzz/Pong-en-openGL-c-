//Example2_4.cpp : A bouncing ball 

//#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>

#define PI 3.1415926535898 

double xpos, ypos, ydir, xdir;         // x and y position for house to be drawn
// Paddle dimensions and positions
float alturaPaleta = 90.0f;
float anchoPaleta = 20.0f;
float paletaIzquierdaY = 240.0f;   // Posición inicial para la paleta izquierda en Y
float paletaDerechaY = 240.0f;  // Posición inicial para la paleta derecha en Y
double sx, sy, squash;          // xy scale factors
GLfloat T1[16] = {1.,0.,0.,0.,\
                  0.,1.,0.,0.,\
                  0.,0.,1.,0.,\
                  0.,0.,0.,1.};
GLfloat S[16] = {1.,0.,0.,0.,\
                 0.,1.,0.,0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};
GLfloat T[16] = {1.,0.,0.,0.,\
                 0., 1., 0., 0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};



#define PI 3.1415926535898 
GLint circle_points = 100; 
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius){
  GLint i;
  GLdouble angle;
  glBegin(GL_POLYGON); 
  for (i = 0; i < circle_points; i++) {    
    angle = 2*PI*i/circle_points; 
    glVertex2f(centerx+radius*cos(angle), centery+radius*sin(angle)); 
  } 
  glEnd();
}

GLfloat RadiusOfBall = 20.0f;
// Draw the ball, centered at the origin
void draw_ball() {
  glColor3f(1.0,1.0,1.0); //blanco
  MyCircle2f(0.,0.,RadiusOfBall);
}
void paletas() {
    // Draw left paddle
    glColor3f(1.0f, 1.0f, 1.0f);  // Color blanco
    glBegin(GL_QUADS);
        glVertex2f(20, paletaIzquierdaY - alturaPaleta/2);
        glVertex2f(20 + anchoPaleta, paletaIzquierdaY - alturaPaleta/2);
        glVertex2f(20 + anchoPaleta, paletaIzquierdaY + alturaPaleta/2);
        glVertex2f(20, paletaIzquierdaY + alturaPaleta/2);
    glEnd();
    // Draw right paddle
    glBegin(GL_QUADS);
        glVertex2f(620 - anchoPaleta, paletaDerechaY - alturaPaleta/2);
        glVertex2f(620, paletaDerechaY - alturaPaleta/2);
        glVertex2f(620, paletaDerechaY + alturaPaleta/2);
        glVertex2f(620 - anchoPaleta, paletaDerechaY + alturaPaleta/2);
    glEnd();
}
void display(void) {
  // swap the buffers
  glutSwapBuffers(); 
  //clear all pixels with the specified clear color
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Actualizar posición X
  xpos = xpos + xdir * 1.5;
  // Rebotar en los bordes laterales
// Colisión con paleta derecha
  if (xpos >= (620 - anchoPaleta - RadiusOfBall) &&  //Verifica si la pelota está en la posición X de la paleta derecha
      ypos >= (paletaDerechaY - alturaPaleta/2) && //Comprueba si la pelota está dentro del rango vertical de la paleta
      ypos <= (paletaDerechaY + alturaPaleta/2)) { //Comprueba si la pelota está dentro del rango vertical de la paleta 
      xdir = -1; //Invierte la dirección horizontal si hay colisión
  }
  // Colisión con paleta izquierda 
  else if (xpos <= (20 + anchoPaleta + RadiusOfBall) && //Verifica si la pelota está en la posición X de la paleta izquierda  
           ypos >= (paletaIzquierdaY - alturaPaleta/2) && //Comprueba si la pelota está dentro del rango vertical de la paleta
           ypos <= (paletaIzquierdaY + alturaPaleta/2)) { //Comprueba si la pelota está dentro del rango vertical de la paleta
      xdir = 1; //Invierte la dirección horizontal si hay colisión
  }
  // Colisión con bordes laterales (cuando no choca con ninguna paleta)
  else if (xpos >= 640-RadiusOfBall) {
      xdir = -1;
  } else if (xpos <= RadiusOfBall) {
      xdir = 1;
  }
  
  // Shape has hit the ground! Stop moving and start squashing down and then back up 
  if (ypos == RadiusOfBall && ydir == -1  ) { 
      sy = sy*squash; 
      if (sy < 0.8)
          squash = 1.1;
      else if (sy > 1.) {
          sy = 1.;
          squash = 0.9;
          ydir = 1;
      }
      sx = 1./sy;
  } 
  else {
      ypos = ypos+ydir *1.5 - (1.-sy)*RadiusOfBall;
      // Rebotar en el techo
      if (ypos >= 480-RadiusOfBall)
          ydir = -1;
      // Rebotar en el suelo
      else if (ypos < RadiusOfBall)
          ydir = 1;
  }
  //Translate the bouncing ball to its new position
  T[12]= xpos;
  T[13] = ypos;
  glLoadMatrixf(T);
  T1[13] = -RadiusOfBall;
  // Translate ball back to center
  glMultMatrixf(T1);
  S[0] = sx;
  S[5] = sy;
  // Scale the ball about its bottom
  glMultMatrixf(S);
  T1[13] = RadiusOfBall;
  // Translate ball up so bottom is at the origin
  glMultMatrixf(T1);
  
  draw_ball();
  
  // se colocan las paletas en las coordenadas que se dieron
  glLoadIdentity();
  paletas();
  
  glutPostRedisplay();
}


void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   // keep our logical coordinate system constant
   gluOrtho2D(0.0, 640.0, 0.0, 480.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

}
void keyboard(unsigned char key, int x, int y) {
    float velocidadPaleta = 15.0f;
    switch(key) {
        case 'a':  // Mover paleta izquierda arriba, a porque queda comoda en posicion con la mano izquierda
            if(paletaIzquierdaY < 480 - alturaPaleta/2)
                paletaIzquierdaY += velocidadPaleta;
            break;
        case 'z':  // Mover paleta izquierda abajo, z porque queda comoda en posicion con la mano izquierda
            if(paletaIzquierdaY > alturaPaleta/2)
                paletaIzquierdaY -= velocidadPaleta;
            break;
        case 'k':  // Mover paleta derecha arriba, k porque queda comoda en posicion con la mano derecha
            if(paletaDerechaY < 480 - alturaPaleta/2)
                paletaDerechaY += velocidadPaleta;
            break;
        case 'm':  // Mover paleta derecha abajo, m porque queda comoda en posicion con la mano derecha
            if(paletaDerechaY > alturaPaleta/2)
                paletaDerechaY -= velocidadPaleta;
            break;
    }
    glutPostRedisplay();
}
void init(void) {
  //set the clear color to be white
  glClearColor(0.0,0.8,0.0,1.0);
  // initial position set to 0,0
  xpos = 60; ypos = RadiusOfBall; xdir = 1; ydir = 1;
  sx = 1.; sy = 1.; squash = 0.9;
}


int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Pong Game");

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
