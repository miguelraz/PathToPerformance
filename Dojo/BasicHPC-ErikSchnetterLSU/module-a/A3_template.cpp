#include <GL/glut.h> 

// Angle of model rotation
float angle = 0.0;

// This function is called every time the scene is rendered
void renderScene(void) {
  // Clear old buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Save the previous settings, in this case save 
  // the camera settings.
  glPushMatrix();
  
  // Perform a rotation around the y axis (0,1,0) 
  // by the amount of degrees defined in the variable angle
  glRotatef(angle, 0.0, 1.0, 0.0);

  // Draw triangle
  glColor3f(0.9, 0.9, 0.9);
  glBegin(GL_TRIANGLES);
    glVertex3f(-0.5,-0.5,0.0);
    glVertex3f(0.5,0.0,0.0);
    glVertex3f(0.0,0.5,0.0);
  glEnd();

  // Forget about the current transformation matrix
  glPopMatrix();
  
  // Swapping the buffers causes the rendering above to be 
  // shown
  glutSwapBuffers();
  
  // Finally increase the angle for the next frame
  angle+=0.1;
}

int main(int argc, char **argv) {
  // Initialize GLUT library
  glutInit(&argc, argv);
  // Set display modes
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  // Define initial window position and size
  glutInitWindowPosition(100,100);
  glutInitWindowSize(320,320);
  // Set some title
  glutCreateWindow("CSC 7700 example");

  // Tell Glut which function does the initial and animation rendering
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene);
  // Enable depth testing
  glEnable(GL_DEPTH_TEST);
  // Start Glut main loop. This will call our callbacks
  glutMainLoop();
  return 0;
}

