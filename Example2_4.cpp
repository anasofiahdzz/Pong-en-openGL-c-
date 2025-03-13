//Example2_4.cpp : A bouncing ball 

#include <stdio.h>
//#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>

float xpos, ypos, xdir, ydir; // x and y position for house to be drawn

#define PI 3.1415926535898 

// Score variables
int scoreLeft = 0;
int scoreRight = 0;
// Function to display text
void renderBitmapString(float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
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
    //clear all pixels with the specified clear color
    glClear(GL_COLOR_BUFFER_BIT);
xpos = xpos + xdir * 4.5;  // Aumentamos la velocidad horizontal
// Colisión con paleta derecha
  if (xpos >= (620 - anchoPaleta - RadiusOfBall) &&  ////Verifica si la pelota está en la posición X de la paleta derecha
      xpos <= (620 - RadiusOfBall) && //checa que la pelota no haya pasado el borde derecho de la paleta
      ypos >= (paletaDerechaY - alturaPaleta/2 - RadiusOfBall) && //checa que la pelota está por encima del borde inferior de la paleta
      ypos <= (paletaDerechaY + alturaPaleta/2 + RadiusOfBall)) { //checa si la pelota está por debajo del borde superior de la paleta
      xdir = -1;
      // Añadir variación al ángulo basado en dónde golpea la pelota
      float relativeIntersectY = (paletaDerechaY - ypos)/(alturaPaleta/2);
      ydir = -relativeIntersectY;
  }
  // Colisión con paleta izquierda 
  else if (xpos <= (20 + anchoPaleta + RadiusOfBall) && 
           xpos >= (20 + RadiusOfBall) &&
           ypos >= (paletaIzquierdaY - alturaPaleta/2 - RadiusOfBall) && 
           ypos <= (paletaIzquierdaY + alturaPaleta/2 + RadiusOfBall)) { 
      xdir = 1;
      float relativeIntersectY = (paletaIzquierdaY - ypos)/(alturaPaleta/2);
      ydir = -relativeIntersectY;
  }
  // Colisión con bordes laterales (cuando no choca con ninguna paleta)
// Colisión con bordes laterales (cuando no choca con ninguna paleta)
else if (xpos >= 640-RadiusOfBall) {
      scoreLeft++; // Incrementar puntuación izquierda
      xpos = 320; // Reset ball position to center
      ypos = 240;
      xdir = -1; // Start moving towards left player
      ydir = (float)(rand() % 100 - 50) / 100.0f; // Dirección Y aleatoria
  } else if (xpos <= RadiusOfBall) {
      scoreRight++; // Incrementar puntuación derecha
      xpos = 320; // Reset ball position to center
      ypos = 240;
      xdir = 1; // Start moving towards right player
      ydir = (float)(rand() % 100 - 50) / 100.0f; // Dirección Y aleatoria
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
ypos = ypos + ydir * 4.5;  // Aumentamos la velocidad vertical
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
  
  // Display scores
  glColor3f(1.0, 1.0, 1.0); // White color for text
  char scoreStr[32];
  sprintf(scoreStr, "%d", scoreLeft);
  renderBitmapString(220, 440, GLUT_BITMAP_HELVETICA_18, scoreStr);
  sprintf(scoreStr, "%d", scoreRight);
  renderBitmapString(400, 440, GLUT_BITMAP_HELVETICA_18, scoreStr);
  
glutSwapBuffers();
}
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // 60 FPS aproximadamente (1000ms/60 ≈ 16ms)
}
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // keep our logical coordinate system constant
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y) {
    float velocidadPaleta = 50.0f;
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
  glClearColor(0.0,0.0,0.0,1.0);
  // initial position set to 0,0
// initial position and direction
  xpos = 320; ypos = 240; // Comenzar en el centro
  xdir = (rand() % 2) * 2 - 1; // Dirección inicial aleatoria (-1 o 1)
  ydir = (rand() % 2) * 2 - 1;
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
    glutTimerFunc(0, timer, 0);  // Iniciar el timer inmediatamente
    glutMainLoop();
    return 0;
}