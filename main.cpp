#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
#define sqrt2 (sqrt(2))

typedef struct point
{
    double x,y,z;
} Point;

bool drawAxes = true;
float gateAngle = 0;
float winAngle = 0;
float windowAngle =0;
float doorAngle = 0;
float quadAngle = 0;
float boxAngle = 0;
float tyreAngle = -2;
float boxScaleFactor = 1;
float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float background = 0;
int q=0;
Point pos, u, r, l;

void displayAxes()
{
    if(drawAxes)
    {
        glBegin(GL_LINES);
        {
            glColor3f(1.0, 0, 0);

            glVertex3f( 500,0,0); //  pos x axis
            glVertex3f(-500,0,0); //  neg x axis

            glColor3f(0, 1.0, 0);

            glVertex3f(0,-500,0); //  pos y axis
            glVertex3f(0, 500,0); //  neg y axis

            glColor3f(0, 0, 1.0);

            glVertex3f(0,0, 500);  //  pos z axis
            glVertex3f(0,0,-500);   // neg z axis
        }
        glEnd();
    }
}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {
    case '1':
    {
        Point l1 = func(l, r, -1);
        r = func(r, l, 1);
        l = l1;
        break;
    }
    case '2':
    {
        Point l1 = func(l, r, 1);
        r = func(r, l, -1);
        l = l1;
        break;
    }

    case '3':
    {
        Point u1 = func(u, l, -1);
        l = func(l, u, 1);
        u = u1;
        break;
    }
    case '4':
    {
        Point u1 = func(u, l, 1);
        l = func(l, u, -1);
        u = u1;
        break;
    }
    case '5':
    {
        Point r1 = func(r, u, -1);
        u = func(u, r, 1);
        r = r1;
        break;
    }
    case '6':
    {
        Point r1 = func(r, u, 1);
        u = func(u, r, -1);
        r = r1;
        break;
    }
    case '7':
    {
        tyreScaleFactor += 0.2;
        break;
    }
    case '8':
    {
        tyreScaleFactor -= 0.2;
        break;
    }
    case '9':
    {
        if (windowAngle < 25  )
            windowAngle += 5;
        else
            windowAngle = 25;
        break;
    }
    case '0':
    {
        if (windowAngle > 0  )
            windowAngle -= 5;

        break;
    }

    case  'l' :
    case  'L' :
    {
        boxAngle -= 3;
        break;
    }

    case  'r' :
    case  'R' :
    {
        boxAngle += 3;
        break;
    }


    default:
        break;
    }
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN: // down arrow
    {

        pos.x+=2.12;
        pos.y+=2.12;
        break;
    }

    case GLUT_KEY_UP:   // up arrow
    {

        pos.x-=2.12;
        pos.y-=2.12;
        break;
    }

    case GLUT_KEY_RIGHT:    // right arrow
    {

        pos.x+=2.12;
        pos.y-=2.12;
        break;
    }

    case GLUT_KEY_LEFT:     // left arrow
    {

        pos.x-=2.12;
        pos.y+=2.12;
        break;
    }

    case GLUT_KEY_PAGE_UP:
    {

        pos.z-=3;
        break;
    }

    case GLUT_KEY_PAGE_DOWN:
    {

        pos.z+=3;
        break;
    }

    case GLUT_KEY_HOME:   //Front Door open
    {
        if (gateAngle > -50  )
            gateAngle -= 5;
        else
            gateAngle = -50;
        break;
    }

    case GLUT_KEY_END:  //Front door close
    {
        if (gateAngle < 0)
            gateAngle += 5;
        else
            break;
    }
    default:
        break;
    }
}

void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
        {
            printf("Mouse Left Button Clicked\n");
        }
        else if(state == GLUT_UP)
        {
            printf("Mouse Left Button Released\n");
        }
        break;
    default:
        break;
    }
}

void displayTyre(float tyreRadius, float tyreWidth,int q)
{
    int tyreSlices = 10;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;
    if(q==1)
    {
        for(int i=0; i<tyreSlices; i++)
        {

            glPushMatrix();
            glRotatef(sliceAngle*i, 1, 0, 0);
            glBegin(GL_QUADS);
            {
                glColor3f(1, 0, 1);
                glVertex3f(halfTyreWidth,-((tyreRadius/2)-8), 0);
                glVertex3f(-halfTyreWidth,-((tyreRadius/2)-8), 0);
                glColor3f(0, 0.2, 0.8);
                glVertex3f(-halfTyreWidth, -tyreRadius, 0);
                glVertex3f(halfTyreWidth, -tyreRadius, 0);
            }
            glEnd();
            glPopMatrix();
        }
    }
    else {}


    for(int i=0; i<tyreSlices; i++)
    {
        glColor3f(0, 0, 1);
        if(i%2)
        glColor3f(0.25, 0.5, 1);

        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);

        }
        glEnd();
        glPopMatrix();
    }
}

void displayBox1(float boxLength, float boxWidth, float boxHeight)     // length -> x axis, width -> y axis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 0.6);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox2(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();

}
void displayBox3(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.8, 0.8, 0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox4(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.4, 1, 0.8);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox5(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0, 0.6, 0.14);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

    }
    glEnd();

}

void displayBox6(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0, 0.6, 0.14);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

    }
    glEnd();

}

void displayBox7(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.2, 0.8, 0.8);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

    }
    glEnd();

}

void displayBox8(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.2, 0.8, 0.8);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

    }
    glEnd();

}
void displayBox9(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.8, 0.8, 0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void Door(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0.2, 0.8);
        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(0, 1, 1);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

    }
    glEnd();
}

void Door2(float quadLength2, float quadWidth2) // width along x axis, length along z axis
{
    float halfQuadWidth2 = quadWidth2 / 2, halfQuadLength2 = quadLength2 / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0, 1, 0);
        glVertex3f(halfQuadWidth2, 0, halfQuadLength2);
        glVertex3f(halfQuadWidth2, 0, -halfQuadLength2);

        glColor3f(0, 1, 1);
        glVertex3f(-halfQuadWidth2, 0, -halfQuadLength2);
        glVertex3f(-halfQuadWidth2, 0, halfQuadLength2);

    }
    glEnd();
}

void displaywiBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.8, 0.8, 0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displaywiBox1(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(0.8, 0.8, 0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void Window() // width along x axis, length along z axis
{
    float halfQuadWidth = 40, halfQuadLength =45;

    glBegin(GL_QUADS);
    {
        glColor3f(0,1,0);
        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

    }
    glEnd();
}

void Window2() // left
{
    float halfQuadWidth = 40, halfQuadLength =45;
    glBegin(GL_QUADS);
    {
        glColor3f(0,1,1);
        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);
    }
    glEnd();
}
void displayScene()
{
    float quadLength = 130, quadWidth = 55;      //front door
    float quadLength1 = 110, quadWidth1 = 10,quadHeight1=10;    //front door upside
    float quadLength2 = 130, quadWidth2 = 55;    //back door
    float quadLength3 = 110, quadWidth3 = 10,quadHeight3=10;;   //back door upside
    float largeBoxLength = 300, largeBoxWidth = 300, largeBoxHeight = 30;
    float smallBoxLength = 250, smallBoxWidth = 250, smallBoxHeight = 200;
    float sBoxLength = 100, sBoxWidth = 70, sBoxHeight = 10;
    float sBoxLength1 = 110, sBoxWidth1 = 80, sBoxHeight1 = 10;
    float sBoxLength2 = 120, sBoxWidth2 = 90, sBoxHeight2 = 10;
    float uBoxLength = 260, uBoxWidth = 270, uBoxHeight = 8;
    float uBoxLength1 = 140, uBoxWidth1 = 70, uBoxHeight1 = 100;
    float tyreRadius = 15, tyreWidth = 15;
    //float tyreRadius1 = tyreRadius*3, tyreWidth1 = tyreWidth*3;
    float wBoxLength = 10, wBoxWidth = 80, wBoxHeight = 10; //window box
    float wBoxLength1 = 10, wBoxWidth1 = 80, wBoxHeight1 = 10;

    displayAxes();

//rotation house
    glRotatef(boxAngle, 0, 0, 1);  // roytate with respect to z axis
    displayBox1(largeBoxLength, largeBoxWidth, largeBoxHeight);

    glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox1(largeBoxLength, largeBoxWidth, largeBoxHeight); // blue box
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the red box on top of the blue box
    displayBox2(smallBoxLength, smallBoxWidth, smallBoxHeight); // red box
    glPopMatrix();

    //stairs
    glPushMatrix();
    glTranslatef(0, (largeBoxWidth/2), ((largeBoxHeight/2)-6) );
    displayBox3(sBoxLength,sBoxWidth, sBoxHeight);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, (largeBoxWidth/2), 0 );
    displayBox4(sBoxLength1,sBoxWidth1, sBoxHeight1);
    glPopMatrix();

    //upsideBox
    glPushMatrix();
    glTranslatef(0, (largeBoxWidth/2), -((largeBoxHeight/2)-6) );
    displayBox5(sBoxLength2,sBoxWidth2, sBoxHeight2);
    displayBox5(sBoxLength2,sBoxWidth2, sBoxHeight2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, smallBoxHeight+21 );
    displayBox6(uBoxLength,uBoxWidth, uBoxHeight);
    glPopMatrix();

//front door1   //right
    glPushMatrix();
    glTranslatef( -26,(quadLength/2.5) + (smallBoxHeight/2.5), 84);
    glTranslatef (gateAngle,0.0,0.0);
    glRotatef(doorAngle=-180, 0,0,1); //clr
    Door(quadLength, quadWidth);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 26,(quadLength/2.5) + (smallBoxHeight/2.5), 84);
    glTranslatef (-gateAngle,0.0,0.0);
    Door(quadLength, quadWidth);
    glPopMatrix();

//frontdoor upside
    glPushMatrix();
    glTranslatef(0, quadWidth+75, quadLength+24 );
    displayBox7(quadLength1,quadWidth1, quadHeight1);
    glPopMatrix();

//back door2
    glPushMatrix();   //right part
    glTranslatef( 26,-((quadLength2/2.5) + (smallBoxHeight/2.5)),84);
    glRotatef(doorAngle=-180, 0,0,1);
    glRotatef(quadAngle, 0.0, 0.0,1.0);
    Door2(quadLength2, quadWidth2);
    glPopMatrix();

    glPushMatrix();    //left part
    glTranslatef( -26,-((quadLength2/2.5) + (smallBoxHeight/2.5)),84);
    glRotatef(quadAngle, 0,0,-1);
    Door2(quadLength2, quadWidth2);
    glPopMatrix();


//backdoor upside
    glPushMatrix();
    glTranslatef(0, -(quadWidth+75), quadLength+24 );
    displayBox8(quadLength3,quadWidth3, quadHeight3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, ((smallBoxHeight+uBoxHeight1)-10) );
    displayBox9(uBoxLength1, uBoxWidth1, uBoxHeight1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 60, smallBoxHeight+(largeBoxHeight)+70); // places the tyre
    glRotatef(quadAngle-80, 0.0, 0.0,-1);
    glRotatef(tyreAngle, 1, 0, 0);
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    q=1;
    displayTyre(tyreRadius*3,tyreWidth,q); // tyre
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 60, smallBoxHeight+(largeBoxHeight)+70); // places the tyre
    glRotatef(quadAngle-80, 0.0, 0.0,-1.0);
    glRotatef(tyreAngle, 1, 0, 0);
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    q=0;
    displayTyre(tyreRadius, tyreWidth,q); // tyre
    glPopMatrix();

//right window
    glPushMatrix();
    glTranslatef( -128,0, 110);
    glTranslatef (0.0,0.0,winAngle);
    glRotatef(doorAngle=90, 0,0,1);
    Window();
    glPopMatrix();

//right window upside
    glPushMatrix();
    glTranslatef(((largeBoxLength/2)-20), 0, ((largeBoxHeight+130)) );
    displaywiBox(wBoxLength, wBoxWidth, wBoxHeight);
    glPopMatrix();

//left window  //
    glPushMatrix();
    glTranslatef( 128,0, 118);
    glRotatef(doorAngle=-90, 0,0,1);
    glTranslatef (0.0,windowAngle,0.0);
    glRotatef(windowAngle,1.0,0.0,0.0);
    Window2();
   glPopMatrix();

    //left window upside
    glPushMatrix();
    glTranslatef(-((largeBoxLength/2)-20), 0, ((largeBoxHeight+130)) );
    displaywiBox1(wBoxLength1, wBoxWidth1, wBoxHeight1);
    glPopMatrix();

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background, background, background,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction
    displayScene();
    glutSwapBuffers();
    glutPostRedisplay();
}

void init()
{
    glClearColor(background, background, background,0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);

    double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu1(int id) //right window open and close
{
    switch(id)
    {
    case 1: //slide up
        glutPostRedisplay();
        glutTimerFunc (10,subMenu1,1) ;
        winAngle +=0.5;
        if(winAngle >40)
        {
            winAngle = 40;
        }

        break;

    case 2:  //slide down
        glutPostRedisplay();
        glutTimerFunc (10,subMenu1,2) ;
        winAngle -=0.5;
        if(winAngle < 0)
        {
            winAngle = 0;
        }
        break;
    }
}

void subMenu2(int id) //back door open and close
{
    switch(id)
    {
    case 3: //open
        glutPostRedisplay();
        glutTimerFunc (10,subMenu2,3) ;
        quadAngle +=0.5;
        if(quadAngle >120)
        {
            quadAngle = 120;
        }
        break;

    case 4:  //close
        glutPostRedisplay();
        glutTimerFunc (10,subMenu2,4) ;
        quadAngle -=0.5;
        if(quadAngle < 0)
        {
            quadAngle = 0;
        }
        break;
    }

}

void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }
}

void subMenu3(int id)
{
    switch(id)
    {
    case 5:
        glutPostRedisplay();
        glutTimerFunc (10,subMenu3,5) ;

        if( tyreAngle <100)
        {
            tyreAngle -=0.5;
        }

        break;

    case 6:
        glutPostRedisplay();
        glutTimerFunc (10,subMenu3,6) ;

        if( tyreAngle <0)
        {
            tyreAngle +=0.5;
        }
        break;

    case 7:
    {
        glutPostRedisplay();
        glutTimerFunc (10,subMenu3,7) ;
        tyreAngle =0;
        break;
    }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("3D HOUSE");
    init();
    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
    glutDisplayFunc(display);	//display callback function
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    int subMenuNo1 = glutCreateMenu(subMenu1);
    glutAddMenuEntry("Slide Up", 1);
    glutAddMenuEntry("Slide Down", 2);

    int subMenuNo2 = glutCreateMenu(subMenu2);
    glutAddMenuEntry("open", 3);
    glutAddMenuEntry("close", 4);

    int subMenuNo3 = glutCreateMenu(subMenu3);
    glutAddMenuEntry("Clockwise",5);
    glutAddMenuEntry("Anti-Clockwise",6);
    glutAddMenuEntry("Stop",7);

    glutCreateMenu(mainMenu);
    glutAddSubMenu("Sliding Window", subMenuNo1);
    glutAddSubMenu("Rotating Door", subMenuNo2);
    glutAddSubMenu("Exhaust Fan", subMenuNo3);
    glutAddMenuEntry("Orginal Size ", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
