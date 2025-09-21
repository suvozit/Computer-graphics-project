#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <ctime>


const int WIN_W = 1200;
const int WIN_H = 686;

// Rain settings
bool isRaining = true;
const int NUM_DROPS = 500;
float rainX[NUM_DROPS];
float rainY[NUM_DROPS];

// Animation variables
float cloudOffset = -300.0f;   // clouds move left -> right (increase)
float busOffset = 1200.0f;     // bus moves right -> left (decrease)
const float CLOUD_SPEED = 1.0f;
const float BUS_SPEED = 4.0f;

bool isseen_one=true;
bool isseen_two=false;
bool isseen_three=false;
// Circle helper

float boatPosX = -900.0f;   // starting X position of the boat
float cloudPosX = 0.0f;   // cloud movement
bool moveCloud = false;   // toggle cloud movement


///seen two///

float yort1X = 1200.0f;   // start at right side
float yort1Speed = -2.0f;

float birdX = 0.0f;          // Bird’s X position
float birdSpeed = 0.0f;



void initRain() {

    srand((unsigned)time(nullptr));

    for (int i = 0; i < NUM_DROPS; ++i) {

        rainX[i] = (rand() / (float)RAND_MAX) * WIN_W;

        rainY[i] = (rand() / (float)RAND_MAX) * WIN_H;

    }

}



// helper to draw a cloud cluster


// draw the bus using the same coordinates as original, but translated by current modelview




void drawCircle(float cx, float cy, float r, int num_segments) {

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= num_segments; i++) {

        float theta = 2.0f * 3.1415926f * i / num_segments;

        float x = r * cosf(theta);

        float y = r * sinf(theta);

        glVertex2f(cx + x, cy + y);

    }

    glEnd();

}

void drawCloudCluster(float baseX, float baseY, float scale = 1.0f) {

    glColor3f(1.0f, 1.0f, 1.0f);

    drawCircle(baseX + 0.0f * scale, baseY + 0.0f, 42.0f * scale, 70);

    drawCircle(baseX + 45.0f * scale, baseY + 5.0f, 56.0f * scale, 70);

    drawCircle(baseX + 110.0f * scale, baseY + 0.0f, 42.0f * scale, 70);

}

void drawBus() {

    // bus red body (left part)

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(414,422);

        glVertex2f(470,422);

        glVertex2f(473,437);

        glVertex2f(481,447);

        glVertex2f(490,452);

        glVertex2f(500,453);

        glVertex2f(510,451);

        glVertex2f(519,445);

        glVertex2f(526,434);

        glVertex2f(528,422);

        glVertex2f(586,422);

        glVertex2f(597,526);

        glVertex2f(414,526);

    glEnd();

    // bus red body (right part)

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(586,422);

        glVertex2f(674,422);

        glVertex2f(675,432);

        glVertex2f(680,441);

        glVertex2f(686,447);

        glVertex2f(694,451);

        glVertex2f(700,453);

        glVertex2f(708,452);

        glVertex2f(715,450);

        glVertex2f(721,446);

        glVertex2f(727,439);

        glVertex2f(730,432);

        glVertex2f(732,422);

        glVertex2f(790,422);

        glVertex2f(789,526);

        glVertex2f(597,526);

    glEnd();

    // small black cabin/front area

   glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(414,454);

        glVertex2f(422,461);

        glVertex2f(423,514);

        glVertex2f(414,514);

    glEnd();

    // bus door (black) and inner green

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(431,443);

        glVertex2f(464,443);

        glVertex2f(464,514);

        glVertex2f(431,514);

    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(435,448);

        glVertex2f(458,448);

        glVertex2f(458,508);

        glVertex2f(435,508);

    glEnd();

    // big window band (black)

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);

        glVertex2f(472,468);

        glVertex2f(780,468);

        glVertex2f(780,514);

        glVertex2f(472,514);

    glEnd();

    // seven yellow windows (as in original)

    glColor3f(1.0f, 1.0f, 0.0f);

    // 1

    glBegin(GL_POLYGON);

     glVertex2f(478,474);

      glVertex2f(515,474);

      glVertex2f(515,508);

      glVertex2f(478,508);

      glEnd();

    // 2

    glBegin(GL_POLYGON);

     glVertex2f(520,474);

     glVertex2f(560,474);

      glVertex2f(560,508);

       glVertex2f(520,508);

       glEnd();

    // 3

    glBegin(GL_POLYGON);

    glVertex2f(564,474);

    glVertex2f(602,474);

     glVertex2f(602,508);

     glVertex2f(564,508);

     glEnd();

    // 4

    glBegin(GL_POLYGON);

     glVertex2f(607,474);

      glVertex2f(646,474);

       glVertex2f(646,508);

       glVertex2f(607,508);

       glEnd();

    // 5

    glBegin(GL_POLYGON);

    glVertex2f(652,474);

    glVertex2f(690,474);

    glVertex2f(690,508);

    glVertex2f(652,508);

    glEnd();

    // 6

    glBegin(GL_POLYGON);

     glVertex2f(694,474);

      glVertex2f(732,474);

      glVertex2f(732,508);

      glVertex2f(694,508);

      glEnd();

    // 7

    glBegin(GL_POLYGON);

    glVertex2f(739,474);

    glVertex2f(775,474);

    glVertex2f(775,508);

    glVertex2f(739,508);

    glEnd();

    // bus lights

    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_POLYGON);

    glVertex2f(785,439);

    glVertex2f(790,439);

    glVertex2f(790,454);

     glVertex2f(785,454);

     glEnd();

    glBegin(GL_POLYGON);

    glVertex2f(414,439);

    glVertex2f(419,439);

    glVertex2f(419,450);

    glVertex2f(414,450);

    glEnd();

    // wheels (outer black, inner white)

    glColor3f(0.0f, 0.0f, 0.0f);

    drawCircle(703,422,26,100);

    drawCircle(500,422,26,100);

    glColor3f(1.0f, 1.0f, 1.0f);

    drawCircle(703,422,20,100);

    drawCircle(500,422,20,100);

    // Draw "AIUB" text in white

    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(570, 450);

    const char *text = "AIUB";

    for (const char *c = text; *c != '\0'; c++) {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    }

}


void drawRain() {

      glColor4f(0.8f, 0.8f, 0.9f, 0.6f); // pale gray/blue

    glPointSize(3.0f);                 // drop diameter in pixels

    glBegin(GL_POINTS);

    for (int i = 0; i < NUM_DROPS; i++)

    {

        glVertex2f(rainX[i], rainY[i]);

    }

    glEnd();

}


/*void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}*/


void seen_one(){
    // SKY

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.8f, 1.0f);  // Light blue at top
    glVertex2f(0, 440);
    glVertex2f(1200, 440);
    glColor3f(0.2f, 0.4f, 0.8f);  // Dark blue at bottom
    glVertex2f(1200, 750);
    glVertex2f(0, 750);
    glEnd();

    // SUN
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(1050, 650, 45, 80);

    // CLOUDS
    glPushMatrix();
    glTranslatef(cloudPosX, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(225, 625, 42, 70);
    drawCircle(270, 625, 56, 70);
    drawCircle(330, 625, 42, 70);


    drawCircle(150, 550, 30, 70);
    drawCircle(190, 550, 40, 70);
    drawCircle(230, 550, 30, 70);


    drawCircle(750, 700, 35, 70);
    drawCircle(790, 700, 45, 70);
    drawCircle(840, 700, 35, 70);


    drawCircle(900, 650, 35, 70);
    drawCircle(945, 650, 50, 70);
    drawCircle(1005, 650, 35, 70);

    glPopMatrix();


    // FIELD

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.8f, 0.5f);
    glVertex2f(0, 187);//187
    glVertex2f(1200, 187);
    glColor3f(0.3f, 0.6f, 0.3f);  // Medium green
    glVertex2f(1200, 440);//375
    glVertex2f(0, 440);
    glEnd();


    // BUSHES (behind fence)
    glColor3f(0.0f, 0.5f, 0.0f);  // dark green
    drawCircle(920, 460, 35, 50);
    drawCircle(960, 470, 60, 50);
    drawCircle(1000, 480, 55, 50);
    drawCircle(1040, 470, 60, 50);
    drawCircle(1080, 465, 55, 50);
    drawCircle(1120, 470, 60, 50);
    drawCircle(1160, 480, 55, 50);

    glColor3f(0.2f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(1200,400);
    glVertex2f(1200,440);
    glVertex2f(900,440);
    glVertex2f(900,400);
    glEnd();

    // FENCE (right side)

    glColor3f(0.6f, 0.3f, 0.0f); // brown color
    glLineWidth(6.0f);           // thick fence rails
    glBegin(GL_LINES);
    // Horizontal rails
    glVertex2f(900, 400);
    glVertex2f(1200, 400);
    glVertex2f(900, 440);
    glVertex2f(1200, 440);
    glVertex2f(900, 460);
    glVertex2f(1200, 460);
    // Vertical posts
    for (int x = 900; x <= 1200; x += 50)
    {
        glVertex2f(x, 400);
        glVertex2f(x, 460);
    }
    glEnd();



    // HAY inside the cart

    glColor3f(0.93f, 0.79f, 0.25f); // golden yellow hay color
    glBegin(GL_POLYGON);
    glVertex2f(885, 420); // left top near cart
    glVertex2f(910, 450);
    glVertex2f(940, 460);
    glVertex2f(970, 455);
    glVertex2f(1000, 470);
    glVertex2f(1040, 460);
    glVertex2f(1080, 465);
    glVertex2f(1110, 450);
    glVertex2f(1145, 420); // right end of cart
    glVertex2f(880, 420);  // close back to start
    glEnd();

// Optional: hay edges (lines to look like straws sticking out)
    glColor3f(0.8f, 0.6f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(900, 450);
    glVertex2f(890, 470);
    glVertex2f(950, 460);
    glVertex2f(945, 480);
    glVertex2f(1000, 470);
    glVertex2f(1005, 490);
    glVertex2f(1080, 465);
    glVertex2f(1095, 485);
    glEnd();
//hay square
    glColor3f(0.8f, 0.6f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(1145, 350); // left top near cart
    glVertex2f(1145, 420);
    glVertex2f(885, 420);
    glVertex2f(885,350);

    glEnd();


    // BULLOCK CART (wooden style, slim wheel, line body)


    // Cart horizontal bars (long wide lines)
    glLineWidth(12.0f);
    glColor3f(0.36f, 0.25f, 0.20f); // dark brown
    glBegin(GL_LINES);
    glVertex2f(880, 420);//
    glVertex2f(1180, 420); // top bar
    glVertex2f(880, 385);
    glVertex2f(1150, 385); // middle bar
    glVertex2f(880, 350);
    glVertex2f(1150, 350); // bottom bar
    glEnd();

    // Vertical posts of the cart
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    for (int x = 900; x <= 1120; x += 50)
    {
        glVertex2f(x, 350);
        glVertex2f(x, 420);
    }
    glEnd();

    // Slim wooden wheel (outer rim only)
    glLineWidth(10.0f);
    glColor3f(0.36f, 0.25f, 0.20f); // dark brown
    glBegin(GL_LINE_LOOP);
    for (int angle = 0; angle < 360; angle++)
    {
        float x = 950 + 35 * cos(angle * M_PI / 180.0);
        float y = 340 + 35 * sin(angle * M_PI / 180.0);
        glVertex2f(x, y);
    }
    glEnd();

    // Wheel spokes
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    for (int angle = 0; angle < 360; angle += 30)
    {
        float x = 950 + 35 * cos(angle * M_PI / 180.0);
        float y = 340 + 35 * sin(angle * M_PI / 180.0);
        glVertex2f(950, 340);
        glVertex2f(x, y);
    }
    glEnd();

    // Cart handles (front sticks to tie bulls)
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glVertex2f(1110, 305);
    glVertex2f(1120, 350);

    glVertex2f(1140, 305);
    glVertex2f(1120, 350);
    glEnd();



    // RIVER gradient: deep blue (bottom) to lighter blue (top)
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.7f);  // Darker blue at bottom
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glColor3f(0.3f, 0.6f, 1.0f);  // Lighter blue at top
    glVertex2f(1200, 300);
    glVertex2f(0, 300);
    glEnd();



    // TREE 1
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(30,425);
    glVertex2f(30,562.5);
    glVertex2f(60,562.5);
    glVertex2f(60,425);
    glEnd();
    //glColor3f(0.0f, 0.6f, 0.0f);
    glColor3f(0.0f, 0.27f, 0.13f);
    drawCircle(30,587.5, 56, 70);
    drawCircle(120,587.5, 50, 70);
    drawCircle(75,650, 70, 70);
    drawCircle(15,675,60, 70);



// HOUSE 2


// top front part
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.1f, 0.1f);
    glVertex2f(660,515);
    glColor3f(0.9f, 0.3f, 0.3f);
    glVertex2f(600,575);
    glVertex2f(375,575);
    glVertex2f(375,515);
    glEnd();

// upper house
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.5f, 0.5f);
    glVertex2f(495,575);
    glColor3f(1.0f, 0.7f, 0.6f);
    glVertex2f(495,625);
    glVertex2f(330,625);
    glVertex2f(375,575);
    glEnd();

    // Side lines for upper house
    glColor3f(0.1f, 0.1f, 0.1f);  // Dark color
    glLineWidth(5.0f);             // Slightly wide

    glBegin(GL_LINES);
// Vertical line (right side of upper house)
    glVertex2f(495+80, 575);
    glVertex2f(495+80, 610);

// Horizontal line (top side of upper house)
    glVertex2f(495+80, 610);
    glVertex2f(330+165, 610);

// vertical line (left side of upper house)
    glVertex2f(330+165, 575);
    glVertex2f(330+165, 610);

    glVertex2f(330+175, 575);
    glVertex2f(330+175, 610);

    glVertex2f(330+185, 575);
    glVertex2f(330+185, 610);

    glVertex2f(330+195, 575);
    glVertex2f(330+195, 610);


    glVertex2f(330+205, 575);
    glVertex2f(330+205, 610);

    glVertex2f(330+215, 575);
    glVertex2f(330+215, 610);

    glVertex2f(330+225, 575);
    glVertex2f(330+225, 610);

    glVertex2f(330+235, 575);
    glVertex2f(330+235, 610);

    glVertex2f(330+245, 575);
    glVertex2f(330+245, 610);


    glEnd();




// roof
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.0f, 0.0f);
    glVertex2f(510,625);
    glColor3f(0.9f, 0.2f, 0.2f);
    glVertex2f(480,662.5);
    glVertex2f(315,662.5);
    glVertex2f(300,640);
    glVertex2f(315,640);
    glVertex2f(330,625);
    glEnd();

// house body
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.6f, 0.4f);
    glVertex2f(640,450);
    glVertex2f(640,515);
    glColor3f(1.0f, 0.85f, 0.65f);
    glVertex2f(375,515);
    glVertex2f(375,450);
    glEnd();

// house entry
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.2f, 0.1f);
    glVertex2f(660,437.5);
    glVertex2f(660,450);
    glVertex2f(375,450);
    glVertex2f(375,437.5);
    glEnd();

// door
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.15f, 0.05f);
    glVertex2f(555,450);
    glVertex2f(555,500);
    glVertex2f(465,500);
    glVertex2f(465,450);
    glEnd();
// door split
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(510,450);
    glVertex2f(510,500);
    glEnd();
// handles
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(500,475);
    glVertex2f(520,475);
    glEnd();

// window 1
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(615,462.5);
    glVertex2f(615,487.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(585,487.5);
    glVertex2f(585,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(615,462.5);
    glVertex2f(615,487.5);
    glVertex2f(585,487.5);
    glVertex2f(585,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(600,462.5);
    glVertex2f(600,487.5);
    glEnd();

// window 2
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(435,462.5);
    glVertex2f(435,487.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(405,487.5);
    glVertex2f(405,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(435,462.5);
    glVertex2f(435,487.5);
    glVertex2f(405,487.5);
    glVertex2f(405,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(420,462.5);
    glVertex2f(420,487.5);
    glEnd();

// upper window 1
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(465,587.5);
    glVertex2f(465,612.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(435,612.5);
    glVertex2f(435,587.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(465,587.5);
    glVertex2f(465,612.5);
    glVertex2f(435,612.5);
    glVertex2f(435,587.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(450,587.5);
    glVertex2f(450,612.5);
    glEnd();

// upper window 2
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(390,587.5);
    glVertex2f(390,612.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(360,612.5);
    glVertex2f(360,587.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(390,587.5);
    glVertex2f(390,612.5);
    glVertex2f(360,612.5);
    glVertex2f(360,587.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(375,587.5);
    glVertex2f(375,612.5);
    glEnd();



// HOUSE 1

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.5f, 0.3f);
    glVertex2f(375, 437.5);
    glVertex2f(375,575);
    glColor3f(0.7f, 0.3f, 0.2f);
    glVertex2f(315,637.5);
    glVertex2f(195,637.5);
    glVertex2f(150,575);
    glVertex2f(75,575);
    glVertex2f(75,437.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.6f);
    glVertex2f(375, 437.5);
    glVertex2f(375,562.5);
    glVertex2f(315,625);
    glColor3f(0.85f, 0.55f, 0.3f);
    glVertex2f(195,625);
    glVertex2f(150,562.5);
    glVertex2f(90,562.5);
    glVertex2f(90,437.5);
    glEnd();



// Door
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.15f, 0.05f);
    glVertex2f(315, 437.5);
    glVertex2f(315,512.5);
    glVertex2f(270,512.5);
    glVertex2f(270,437.5);
    glEnd();
// door split
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(292.5,437.5);
    glVertex2f(292.5,512.5);
    glEnd();
// handles
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(285,475);
    glVertex2f(300,475);
    glEnd();

// Window 1
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(165, 462.5);
    glVertex2f(165,515);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(120,515);
    glVertex2f(120,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(165,462.5);
    glVertex2f(165,515);
    glVertex2f(120,515);
    glVertex2f(120,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(142.5,462.5);
    glVertex2f(142.5,515);
    glEnd();

// Window 2
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(240, 462.5);
    glVertex2f(240,515);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(195,515);
    glVertex2f(195,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(240,462.5);
    glVertex2f(240,515);
    glVertex2f(195,515);
    glVertex2f(195,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(217.5,462.5);
    glVertex2f(217.5,515);
    glEnd();

// Window 3
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(300, 562.5);
    glVertex2f(300,607.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(225,607.5);
    glVertex2f(225,562.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(300,562.5);
    glVertex2f(300,607.5);
    glVertex2f(225,607.5);
    glVertex2f(225,562.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(262.5,562.5);
    glVertex2f(262.5,607.5);
    glEnd();
    // Side lines for upper house
    glColor3f(0.1f, 0.1f, 0.1f);  // Dark color
    glLineWidth(3.0f);

    glBegin(GL_LINES);
    glVertex2f(375, 437.5);
    glVertex2f(375,565);
    glEnd();


// house entry
    glBegin(GL_POLYGON);
    glColor3f(0.5f,0.2f,0.1f);
    glVertex2f(390,425);
    glVertex2f(390,440);
    glVertex2f(55,440);
    glVertex2f(55,425);
    glEnd();





    // TREE 2

    glColor3f(0.0f, 0.27f, 0.13f);
    drawCircle(785,590.5, 50, 70);//1
    drawCircle(75+645,640, 60, 70);//2

    drawCircle(725,585,60, 70);//3
    drawCircle(585,590.5, 50, 70);//1.1
    drawCircle(640,570.5, 50, 70);//1.2

    drawCircle(800,650.5,60, 70);//4
    drawCircle(630,650.5, 70, 70);//5
    drawCircle(750,680, 70, 70);//6

    drawCircle(670,695,60, 70);//7
    //glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(580,660.5,60, 70);//8

    drawCircle(590,680.5,50, 70);//8



    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(675,425);
    glVertex2f(675,562.5);
    glVertex2f(705,562.5);
    glVertex2f(705,425);
    glEnd();

    //root
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(675,425);//a
    glVertex2f(630,405);//b
    glVertex2f(675,410);//c
    glVertex2f(720,390);//d
    glVertex2f(705,410);//e
    glVertex2f(740,415);//f
    glVertex2f(705,425);//g
    glEnd();

// grass
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.35f, 0.0f);   // dark green (bottom)
    glVertex2f(645,392.5);//h

    glColor3f(0.0f, 0.55f, 0.0f);   // softer green (top)
    glVertex2f(625,430);//i

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(655,392.5);//k

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(650,440);//j

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(665,392.5);//l

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(690,430);//m

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(675,392.5);//n
    glEnd();

    //tree branch
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(730,470+50);//d
    glVertex2f(730,455+50);//c
    glVertex2f(705,430+50);//a
    glVertex2f(705,460+50);//b
    glEnd();


// grass2
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.35f, 0.0f);   // dark green (bottom)
    glVertex2f(645+70,392.5+10);//h

    glColor3f(0.0f, 0.55f, 0.0f);   // softer green (top)
    glVertex2f(625+70,430+10);//i

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(655+70,392.5+10);//k

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(650+70,440+10);//j

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(665+70,392.5+10);//l

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(690+70,430+10);//m

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(675+70,392.5+10);//n
    glEnd();





    //tree branch 2
    glColor3f(0.36f, 0.16f, 0.09f);
    drawCircle(730,513.5,8, 70);
    glColor3f(0.91f, 0.76f, 0.65f);
    drawCircle(730,513.5,4, 70);



    //tree branch
    glColor3f(0.55f, 0.27f, 0.07f);

    glBegin(GL_POLYGON);
    glVertex2f(705,562.5);//d
    glVertex2f(730,592.5);//c
    glVertex2f(715,592.5);//a
    glVertex2f(690,575);//b
    glVertex2f(700,625);//d
    glVertex2f(690,635);//c
    glVertex2f(675,560);//a
    glVertex2f(615,620);//b
    glVertex2f(605,630);//a
    glVertex2f(675,562.5);//b
    glEnd();





    //Hay hill
    // HAY HILL (in front of first tree)
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.9f, 0.3f);   // bright yellow (top of hill)
    glVertex2f(0, 420);            // left bottom
    glColor3f(0.95f, 0.75f, 0.1f); // golden (bottom side)
    glVertex2f(160, 420);          // right bottom
    glColor3f(1.0f, 0.85f, 0.2f);  // yellow-gold (top curve)
    glVertex2f(150, 480);          // right top
    glVertex2f(140, 500);          // right top
    glVertex2f(120, 520);           // left top
    glVertex2f(100, 540);           // left top
    glVertex2f(80, 560);           // left top
    glVertex2f(60, 540);           // left top
    glVertex2f(40, 520);           // left top
    glVertex2f(20, 500);
    glVertex2f(10, 480);
    //glEnd();

    // Add some hay texture lines (to make it look real)
    glColor3f(0.85f, 0.65f, 0.05f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(30, 440);
    glVertex2f(50, 470);
    glVertex2f(70, 430);
    glVertex2f(90, 465);
    glVertex2f(110, 435);
    glVertex2f(130, 468);
    glEnd();



    //river 1


    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.3f, 0.7f);  // bottom
    glVertex2f(809,282);//n
    glVertex2f(807,327);//m
    glColor3f(0.3f, 0.6f, 1.0f);  // top
    glVertex2f(462,305);//f
    glVertex2f(465,274);//g
    glEnd();

    glColor3f(0.0f, 0.4f, 0.9f);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.3f, 0.7f);  // bottom
    glVertex2f(807,327);//m
    glVertex2f(900,440);//k
    glColor3f(0.3f, 0.6f, 1.0f);  // top
    glVertex2f(490,274);//j
    glVertex2f(685,337);//h
    glEnd();

    //soil
    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(400,265);//g
    glVertex2f(400,300);//f
    glVertex2f(0,300);//d
    glVertex2f(0,265);//e
    glEnd();

    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(625,300);//i
    glVertex2f(625,330);//h
    glVertex2f(400,300);//f
    glVertex2f(400,265);//g
    glEnd();

    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(625,300);//i
    glVertex2f(890,430);//g
    glVertex2f(900,440);//k
    glVertex2f(625,330);//h

    glEnd();
    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(1200,265);//p
    glVertex2f(1200,300);//o
    glVertex2f(840,300);//s
    glVertex2f(807,305);//m
    glVertex2f(807,265);//n
    glEnd();


    // BOAT

    glPushMatrix();                  // Save current coordinate system
    glTranslatef(boatPosX, 0.0f, 0); // Move boat along x-axis

    //SAIL (Right side )
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(630, 125);   // Bottom-left
    glVertex2f(630, 560);   // Much taller mast height
    glVertex2f(880, 300);   // Wider outward point
    glVertex2f(800, 125);   // Bottom-right
    glEnd();

    //SAIL (Left side)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLES);
    glVertex2f(630, 125);   // Bottom-right
    glVertex2f(630, 560);   // Same tall height as mainsail
    glVertex2f(400, 125);   // Much farther left for width
    glEnd();

    // Stick
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(625, 125);
    glVertex2f(635, 125);
    glVertex2f(635, 580);   // Taller mast
    glVertex2f(625, 580);
    glEnd();

    //back body
    glColor3f(0.0f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(855, 100);
    glVertex2f(910, 125);
    glVertex2f(345, 125);
    glVertex2f(390, 100);//365
    glEnd();


    //Human
    // Head (circle)
    glColor3f(0.9f, 0.8f, 0.6f);
    drawCircle(400, 270, 30, 100);

    //hair
    // Hair (polygon on top of head)
    glColor3f(0.1f, 0.1f, 0.1f); // Dark black hair
    glBegin(GL_POLYGON);
    glVertex2f(370, 280);  // left side of head
    glVertex2f(430, 280);  // right side of head
    glVertex2f(440, 300);  // top right
    glVertex2f(400, 320);  // top middle
    glVertex2f(360, 300);  // top left
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f); // Dark black hair
    glBegin(GL_POLYGON);
    glVertex2f(400, 250);  //1
    glVertex2f(400, 280);  // 2
    glVertex2f(370, 280);  //3
    glVertex2f(370, 250);  // 4

    glEnd();


    // Eyes (small black circles)
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    drawCircle(390, 265, 3, 50); // Left eye
    drawCircle(410, 265, 3, 50); // Right eye

    // Eyebrows (thin black rectangles/lines above eyes)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON); // Left eyebrow
    glVertex2f(383, 273);
    glVertex2f(397, 273);
    glVertex2f(397, 276);
    glVertex2f(383, 276);
    glEnd();

    glBegin(GL_POLYGON); // Right eyebrow
    glVertex2f(403, 273);
    glVertex2f(417, 273);
    glVertex2f(417, 276);
    glVertex2f(403, 276);
    glEnd();

    // Lips (smile shape)


    // Lips (just one line)
    glColor3f(0.8f, 0.2f, 0.2f); // Red lips
    glBegin(GL_LINES);
    glVertex2f(420, 250); // left corner
    glVertex2f(410, 250); // right corner
    glEnd();






    // Body (rectangle)
    glColor3f(0.2f, 0.2f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(430, 165);
    glVertex2f(430, 240);
    glVertex2f(370, 240);
    glVertex2f(370, 165);
    glEnd();

    // Arm
    glColor3f(0.9f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(445, 220-40);
    glVertex2f(445, 200-30);
    glVertex2f(380, 200);
    glVertex2f(380, 215);
    glEnd();

    // Leg
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(490, 100);//1
    glVertex2f(470, 150);//2
    glVertex2f(470-30, 170);//3
    glVertex2f(430-30, 170);//4
    glVertex2f(400-30, 165);//5
    glVertex2f(430-70, 130);
    glVertex2f(410-50, 100);//6
    glEnd();

    // Oar (long brown rectangle)
    glColor3f(0.5f, 0.25f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(455, 200);
    glVertex2f(470, 200);
    glVertex2f(350, 70);
    glVertex2f(365, 70);
    glEnd();

// Oar Blade (flat part touching water)
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(330, 60);
    glVertex2f(380, 60);
    glVertex2f(380, 90);
    glVertex2f(330, 90);
    glEnd();




    //boat part
    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(870, 62.5);
    glVertex2f(945, 150);
    glVertex2f(840, 110);
    glVertex2f(340, 110);//365
    glVertex2f(390, 62.5);//960

    glEnd();

    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(430,95);
    glVertex2f(300, 150);
    glVertex2f(350, 100);
    glEnd();

    glPopMatrix();


    //flower

// flower 2
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f); // soft pink
    glVertex2f(75+40,100-40);
    glVertex2f(150+40,155-40);
    glColor3f(1.0f, 1.0f, 1.0f); // white
    glVertex2f(150+40,200-40);
    glVertex2f(75+40,165-40);
    glEnd();

// flower 3
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(75-15,63);
    glVertex2f(50,120);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0,125);
    glVertex2f(30,75);
    glEnd();

// flower 4
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(75-15,38);
    glVertex2f(50,63);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0,40);
    glVertex2f(30,50);
    glEnd();

// flower 1.0
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(75,100);
    glVertex2f(150,188-35);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(150,250-50);
    glVertex2f(75,200-35);
    glEnd();

// flower 3 (near 255,38)
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(255,38);
    glVertex2f(225,63);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(165,75);
    glVertex2f(195,40);
    glEnd();

// grass 1 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90,0);
    glVertex2f(150,125);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,115);
    glVertex2f(120,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(150,125);
    glVertex2f(210,50);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,95);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(0.5f);
    glBegin(GL_LINES);
    glVertex2f(120,0);
    glVertex2f(150,125);
    glEnd();

// grass 2 (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(90+15,0);
    glVertex2f(150+15,125);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(150+15+15,115);
    glVertex2f(120+15,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(150+15,125);
    glVertex2f(210+15,50);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(150+15,95);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(0.5f);
    glBegin(GL_LINES);
    glVertex2f(90+25,0);
    glVertex2f(150+15,125);
    glEnd();

// grass 3 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90,0+35);
    glVertex2f(150,125+35);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,115+35);
    glVertex2f(120,0+35);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(150,125+35);
    glVertex2f(210,50+35);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,95+35);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(100,0+35);
    glVertex2f(150,115+35);
    glEnd();

// grass 4 (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(90,0);
    glVertex2f(150-60,125);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(120,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(100,0);
    glVertex2f(150-60,125);
    glEnd();

// grass 5 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90,0);
    glVertex2f(150-90,125);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(140,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(100,0);
    glVertex2f(150-90,125);
    glEnd();

// grass 6 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(70,0);
    glVertex2f(0,115);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(50,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(10,85);
    glVertex2f(0,125);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(0,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(78,0);
    glVertex2f(0,115);
    glEnd();

// grass 7 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90+15,0);
    glVertex2f(0+15,125);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(50+15,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(90+20,0);
    glVertex2f(0+15,120);
    glEnd();

// grass 7 small (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(45,0);
    glVertex2f(10,25);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(30,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(35,0);
    glVertex2f(10,25);
    glEnd();

// grass 8 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(55,0);
    glVertex2f(0,55);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(40,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(50,0);
    glVertex2f(0,55);
    glEnd();

// grass 9 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(70,0);
    glVertex2f(0,115-35);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(50,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(10,85-20);
    glVertex2f(0,125-40);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(0,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(10,85-20);
    glVertex2f(0,125-40);
    glEnd();

// grass 10 left (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(120,0);
    glVertex2f(50,170);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(85,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(55,150);
    glVertex2f(0,130);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(50,170);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(55,150);
    glVertex2f(0,130);
    glEnd();

// grass 11 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(120-15,0);
    glVertex2f(50-15,170);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(85-15,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(55-15,150-15);
    glVertex2f(0,130-15);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(50-15,170-15);
    glEnd();

// grass 12 left (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(150,0);
    glVertex2f(220,130);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150-20,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(150,0);
    glVertex2f(220,130);
    glEnd();

// grass 13 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(180,0);
    glVertex2f(230,80);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(180-20,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(180,0);
    glVertex2f(230,80);
    glEnd();


}

void seen_two(){
    //sky

glBegin(GL_POLYGON);



    // Top-left vertex: sky blue

    glColor3f(0.53f, 0.81f, 0.92f);

    glVertex2f(0, 686);



    // Bottom-left vertex: white

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0, 460);



    // Bottom-right vertex: white

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1200, 452);



    // Top-right vertex: sky blue

    glColor3f(0.53f, 0.81f, 0.92f);

    glVertex2f(1200, 686);



glEnd();



// CLOUDS

 glColor3f(1.0f, 1.0f, 1.0f);

    drawCircle(225+800, 625-60, 42, 70);

    drawCircle(270+800, 625-55, 56, 70);

    drawCircle(330+800, 625-60, 42, 70);



    drawCircle(900-90, 650-50, 35, 70);

    drawCircle(945-90,  650-50, 50, 70);

    drawCircle(1005-90, 650-50, 35, 70);



//bird 2

glPushMatrix();

glTranslatef(birdX, 0.0f, 0.0f);





glColor3f(0.0f, 0.0f, 0.0f);



glBegin(GL_POLYGON);

         glVertex2f(1038,649);//c2

         glVertex2f(1053,648);//d2

         glVertex2f(1055,648);//e2

         glVertex2f(1058,649);//f2



         glVertex2f(1059,659);//g2

         glVertex2f(1065,651);//h2

         glVertex2f(1059,653);//i2

         glVertex2f(1057,653);//j2



         glVertex2f(1057,654);//k2

         glVertex2f(1060,659);//l2

         glVertex2f(1062,662);//m2

         glVertex2f(1065,665);//n2



         glVertex2f(1065,668);//o2

         glVertex2f(1057,662);//p2

         glVertex2f(1055,660);//q2

         glVertex2f(1052,657);//r2



         glVertex2f(1050,657);//s2

         glVertex2f(1046,663);//t2

         glVertex2f(1041,666);//u2

         glVertex2f(1035,670);//v2



         glVertex2f(1027,674);//w2

         glVertex2f(1025,672);//z2

         glVertex2f(1032,666);//a3

         glVertex2f(1041,658);//b3



         glVertex2f(1044,653);//c3

         glVertex2f(1044,652);//d3

         glVertex2f(1037,651);//e3



glEnd();



//bird 1







glColor3f(0.0f, 0.0f, 0.0f);



glBegin(GL_POLYGON);

         glVertex2f(978,629);  // c2

         glVertex2f(993,628);  // d2

         glVertex2f(995,628);  // e2

         glVertex2f(998,629);  // f2



         glVertex2f(999,639);  // g2

         glVertex2f(1005,631); // h2

         glVertex2f(999,633);  // i2

         glVertex2f(997,633);  // j2



         glVertex2f(997,634);  // k2

         glVertex2f(1000,639); // l2

         glVertex2f(1002,642); // m2

         glVertex2f(1005,645); // n2



         glVertex2f(1005,648); // o2

         glVertex2f(997,642);  // p2

         glVertex2f(995,640);  // q2

         glVertex2f(992,637);  // r2



         glVertex2f(990,637);  // s2

         glVertex2f(986,643);  // t2

         glVertex2f(981,646);  // u2

         glVertex2f(975,650);  // v2



         glVertex2f(967,654);  // w2

         glVertex2f(965,652);  // z2

         glVertex2f(972,646);  // a3

         glVertex2f(981,638);  // b3



         glVertex2f(984,633);  // c3

         glVertex2f(984,632);  // d3

         glVertex2f(977,631);  // e3



glEnd();



//bird 3



glColor3f(0.0f, 0.0f, 0.0f);



glBegin(GL_POLYGON);

         glVertex2f(1087.0,598.5); //c2

         glVertex2f(1109.5,597.0); //d2

         glVertex2f(1112.5,597.0); //e2

         glVertex2f(1117.0,598.5); //f2



         glVertex2f(1118.5,613.5); //g2

         glVertex2f(1127.5,601.5); //h2

         glVertex2f(1118.5,604.5); //i2

         glVertex2f(1115.5,604.5); //j2



         glVertex2f(1115.5,606.0); //k2

         glVertex2f(1120.0,613.5); //l2

         glVertex2f(1123.0,618.0); //m2

         glVertex2f(1127.5,622.5); //n2



         glVertex2f(1127.5,627.0); //o2

         glVertex2f(1115.5,618.0); //p2

         glVertex2f(1112.5,615.0); //q2

         glVertex2f(1108.0,610.5); //r2



         glVertex2f(1105.0,610.5); //s2

         glVertex2f(1099.0,619.5); //t2

         glVertex2f(1091.5,624.0); //u2

         glVertex2f(1082.5,630.0); //v2



         glVertex2f(1070.5,636.0); //w2

         glVertex2f(1067.5,633.0); //z2

         glVertex2f(1078.0,624.0); //a3

         glVertex2f(1091.5,612.0); //b3



         glVertex2f(1096.0,604.5); //c3

         glVertex2f(1096.0,603.0); //d3

         glVertex2f(1085.5,601.5); //e3



glEnd();





//bird 4



glColor3f(0.0f, 0.0f, 0.0f);



glBegin(GL_POLYGON);

         glVertex2f(1138,639); //c2

         glVertex2f(1153,638); //d2

         glVertex2f(1155,638); //e2

         glVertex2f(1158,639); //f2



         glVertex2f(1159,649); //g2

         glVertex2f(1165,641); //h2

         glVertex2f(1159,643); //i2

         glVertex2f(1157,643); //j2



         glVertex2f(1157,644); //k2

         glVertex2f(1160,649); //l2

         glVertex2f(1162,652); //m2

         glVertex2f(1165,655); //n2



         glVertex2f(1165,658); //o2

         glVertex2f(1157,652); //p2

         glVertex2f(1155,650); //q2

         glVertex2f(1152,647); //r2



         glVertex2f(1150,647); //s2

         glVertex2f(1146,653); //t2

         glVertex2f(1141,656); //u2

         glVertex2f(1135,660); //v2



         glVertex2f(1127,664); //w2

         glVertex2f(1125,662); //z2

         glVertex2f(1132,656); //a3

         glVertex2f(1141,648); //b3



         glVertex2f(1144,643); //c3

         glVertex2f(1144,642); //d3

         glVertex2f(1137,641); //e3



glEnd();



glPopMatrix();





//sand



glBegin(GL_POLYGON);



glColor3f(0.55f, 0.45f, 0.30f);



    glVertex2f(0, 0);



    glVertex2f(0, 120);



    glColor3f(0.85f, 0.75f, 0.55f);



    glVertex2f(1200, 100);



    glColor3f(0.96f, 0.90f, 0.65f);



    glVertex2f(1200, 0);



glEnd();





glEnd();



//RIVER

glBegin(GL_POLYGON);



glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0, 186);

glColor3f(0.31f, 0.82f, 0.88f);

    glVertex2f(0, 460);

    glVertex2f(1200,460);

glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1200,140);

glEnd();



glBegin(GL_POLYGON);



glColor3f(0.31f, 0.82f, 0.88f);

    glVertex2f(0 ,150);      //c

    glVertex2f(40,170);      //d

    glVertex2f(90,150);      //e

    glVertex2f(150,135);     //f

    glVertex2f(220,125);     //g



    glVertex2f(300,120);     //h

    glVertex2f(380,125);     //i

    glVertex2f(460,130);     //j

    glVertex2f(540,125);     //k

    glVertex2f(620,120);     //l



    glVertex2f(700,125);     //m

    glVertex2f(780,130);     //n

    glVertex2f(860,128);     //o

    glVertex2f(940,122);     //p

    glVertex2f(1020,120);    //q



    glVertex2f(1100,125);    //r

    glVertex2f(1160,132);    //u

    glVertex2f(1200,140);    //v

    glVertex2f(1200,460);    //

    glVertex2f(0,460);       //



glEnd();





/*

//stream

glBegin(GL_POLYGON);



glColor3f(0.0f, 0.3f, 0.6f);

    glVertex2f(300,311);      //c

    glVertex2f(319,303);      //d

    glVertex2f(335,297);      //e

    glVertex2f(353,295);     //f

    glVertex2f(366,298);     //g



    glVertex2f(379,303);     //h

    glVertex2f(397,309);     //i

    glVertex2f(410,312);     //j

    glVertex2f(423,311);     //k

    glVertex2f(436,307);     //l



    glVertex2f(449,302);     //m

    glVertex2f(463,297);     //n

    glVertex2f(478,294);     //o

    glVertex2f(492,297);     //p

    glVertex2f(507,303);    //q

     glVertex2f(523,312);    //r

    glVertex2f(533,316);    //s

    glVertex2f(543,318);    //t

    glVertex2f(552,317);    //u

    glVertex2f(560,313);    //v

    glVertex2f(570,308);       //w

    glVertex2f(580,302);       //z





     glVertex2f(590,298);    //a1

    glVertex2f(598,295);    //b1

    glVertex2f(608,295);      //c1

    glVertex2f(619,297);      //d1

    glVertex2f(631,303);      //e1

    glVertex2f(638,307);     //f1

    glVertex2f(648,311);     //g1



    glVertex2f(657,315);     //h1

    glVertex2f(668,316);     //i1

    glVertex2f(679,315);     //j1

    glVertex2f(688,311);     //k1

    glVertex2f(698,306);     //l1



    glVertex2f(710,300);     //m1

    glVertex2f(719,295);     //n1

    glVertex2f(728,294);     //o1

    glVertex2f(740,295);     //p1

    glVertex2f(749,298);    //q1



    glVertex2f(756,302);    //r1

    glVertex2f(764,306);    //s1

    glVertex2f(774,313);    //t1

    glVertex2f(779,314);    //u1

    glVertex2f(800,313);    //v1



    glVertex2f(800,333);        //w3

    glVertex2f(789,327);    //v3

    glVertex2f(778,320);    //u3

    glVertex2f(768,318);      //t3

    glVertex2f(761,318);      //s3

    glVertex2f(755,321);      //r3

    glVertex2f(739,328);     //q3

    glVertex2f(725,334);     //p3



    glVertex2f(709,335);     //o3

    glVertex2f(695,335);     //n3

    glVertex2f(680,326);     //m3

    glVertex2f(669,323);     //l3

    glVertex2f(659,322);     //k3



    glVertex2f(647,327);     //j3

    glVertex2f(637,331);     //i3

    glVertex2f(631,334);     //h3

    glVertex2f(621,337);     //g3

    glVertex2f(612,338);    //f3



    glVertex2f(604,337);    //e3

    glVertex2f(596,335);    //d3

    glVertex2f(590,330);    //c3

    glVertex2f(580,326);    //b3

    glVertex2f(572,324);    //a3



     glVertex2f(564,324);     //z2

     glVertex2f(555,323);    //w2

    glVertex2f(547,326);    //v2

    glVertex2f(538,329);    //u2

    glVertex2f(530,331);      //t2

    glVertex2f(516,332);      //s2

    glVertex2f(503,332);      //r2

    glVertex2f(492,330);     //q2

    glVertex2f(483,327);     //p2



    glVertex2f(470,324);     //o2

    glVertex2f(457,321);     //n2

    glVertex2f(447,321);     //m2

    glVertex2f(438,324);     //l2

    glVertex2f(425,330);     //k2



    glVertex2f(410,334);     //j2

    glVertex2f(400,336);     //i2

    glVertex2f(388,334);     //h2

    glVertex2f(377,327);     //g2

    glVertex2f(367,320);    //f2



    glVertex2f(357,316);    //e2

    glVertex2f(348,317);    //d2

    glVertex2f(342,322);    //c2

    glVertex2f(332,331);    //b2

    glVertex2f(323,336);    //a2



    glVertex2f(312,335);    //z1

    glVertex2f(300,331);    //w1



glEnd();



*/

//sun

glBegin(GL_TRIANGLE_FAN);



// Center (bright yellow-white)

glColor3f(1.0f, 0.95f, 0.3f);

glVertex2f(436, 551);



for (int i = 0; i <= 200; i++)

    {

    float theta = 2.0f * 3.1415926f * i / 200;

    float x = 90 * cosf(theta);

    float y = 90 * sinf(theta);



    // Outer edge (soft orange-red glow)

    glColor3f(1.0f, 0.4f, 0.0f);

    glVertex2f(436 + x, 551 + y);

    }



glEnd();



//ball



glColor3f(1.0f, 0.5f, 0.3f);



  drawCircle(550,85,50,100);



glEnd();





//stone



glColor3f(1.0f, 1.0f, 1.0f);



 drawCircle(300,55,10,100);

 drawCircle(313,60,11,100);





 drawCircle(100,50,7,100);

 drawCircle(105,45,5,100);

 drawCircle(90,40,5,100);



 drawCircle(950,60,5,100);

 drawCircle(955,70,5,100);

 drawCircle(960,65,5,100);

 drawCircle(965,70,5,100);



 drawCircle(1100,60-5,5,100);

 drawCircle(1105,70-5,5,100);

 drawCircle(1110,65-5,5,100);

 drawCircle(1115,70-5,5,100);

 drawCircle(1120,70,5,100);



glEnd();



///hill





//hill 1

glColor3f(0.133f, 0.545f, 0.133f);



glBegin(GL_POLYGON);

         glVertex2f(0,529);//i

         glVertex2f(60,552);//w

         glVertex2f(97,525);//a1

         glVertex2f(108,546);//b1

         glVertex2f(72,571);//d1

         glVertex2f(0,540);//c1



glEnd();



//hill corner front



glColor3f(0.0f, 0.8f, 0.2f);



glBegin(GL_POLYGON);



         glVertex2f(35,481);//b

         glVertex2f(97,525);//a1

         glVertex2f(60,552);//w

         glVertex2f(0,529);//i

         glVertex2f(0,460); //a

glEnd();



//hill 6

glColor3f(0.133f, 0.545f, 0.133f);



glBegin(GL_POLYGON);

       glVertex2f(0,460); //a

       glVertex2f(35,481);//b

       glVertex2f(63,496);//j

       glVertex2f(95,515);//k

       glVertex2f(182,608);//l

       glVertex2f(242,554);//f1

       glVertex2f(252,540);//m

       glVertex2f(282,580);//n

       glVertex2f(278,595);//o

       glVertex2f(290,595);//p

       glVertex2f(294,585);//q

       glVertex2f(416,485);//r

       glVertex2f(416,460); //h1



glEnd();





//hill back left green middle



glColor3f(0.565f, 0.933f, 0.565f);



glBegin(GL_POLYGON);

         glVertex2f(0,460); //a

         glVertex2f(35,481);//b

         glVertex2f(63,496);//j



         glVertex2f(95,515);//k

         glVertex2f(182,608);//l

         glVertex2f(108,546);//b1

         glVertex2f(97,525);//a1

glEnd();



//hill 3



glColor3f(0.565f, 0.933f, 0.565f);



glBegin(GL_POLYGON);

         glVertex2f(182,608);//l

         glVertex2f(242,554);//f1

         glVertex2f(253,566);//g1

glEnd();



//hill 4

glColor3f(0.565f, 0.933f, 0.565f);



glBegin(GL_POLYGON);

       glVertex2f(242,554);//f1

       glVertex2f(253,566);//g1



       glColor3f(0.133f, 0.545f, 0.133f);

       glVertex2f(278,595);//o



       glColor3f(0.565f, 0.933f, 0.565f);

       glVertex2f(282,580);//n

       glVertex2f(254,544); //m



glEnd();



//hill 5

glColor3f(0.0f, 0.8f, 0.2f);



glBegin(GL_POLYGON);



 glColor3f(0.133f, 0.545f, 0.133f);

       glVertex2f(416,485);//r

  glColor3f(0.565f, 0.933f, 0.565f);

       glVertex2f(626,570);//s

       glVertex2f(590,570);//u



glEnd();



//hill 6

glColor3f(0.133f, 0.545f, 0.133f);

glBegin(GL_POLYGON);

       glVertex2f(416,485);//r

       glVertex2f(626,570);//s

       glVertex2f(687,562);//u

       glVertex2f(715,547);//v

       glVertex2f(866,460);//t

       glVertex2f(416,460); //a

glEnd();



//hill 5

glColor3f(0.0f, 0.8f, 0.2f);



glBegin(GL_POLYGON);

glColor3f(0.133f, 0.545f, 0.133f);

       glVertex2f(626,570);//s

  glColor3f(0.565f, 0.933f, 0.565f);

       glVertex2f(866,460);//t

       glVertex2f(695,561);



glEnd();





//yort2  small

// ------------------------

// DOWN SIDE (Slate Gray)

glColor3f(0.38f, 0.45f, 0.52f);

glBegin(GL_POLYGON);

    glVertex2f((269 + 600) * 0.8f - 550, (350 + 70) * 0.8f + 100);

    glVertex2f((439 + 600) * 0.8f - 550, (350 + 70) * 0.8f + 100);

    glVertex2f((452 + 600) * 0.8f - 550, (368 + 70) * 0.8f + 100);

    glVertex2f((240 + 600) * 0.8f - 550, (368 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// DOWN SIDE (Slightly darker Slate Gray)

glColor3f(0.34f, 0.42f, 0.49f);

glBegin(GL_POLYGON);

    glVertex2f((240 + 600) * 0.8f - 550, (368 + 70) * 0.8f + 100);

    glVertex2f((452 + 600) * 0.8f - 550, (368 + 70) * 0.8f + 100);

    glVertex2f((456 + 600) * 0.8f - 550, (377 + 70) * 0.8f + 100);

    glVertex2f((232 + 600) * 0.8f - 550, (377 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// MIDDLE SIDE (Soft Teal)

glColor3f(0.32f, 0.60f, 0.58f);

glBegin(GL_POLYGON);

    glVertex2f((232 + 600) * 0.8f - 550, (377 + 70) * 0.8f + 100);

    glVertex2f((456 + 600) * 0.8f - 550, (377 + 70) * 0.8f + 100);

    glVertex2f((464 + 600) * 0.8f - 550, (406 + 70) * 0.8f + 100);

    glVertex2f((220 + 600) * 0.8f - 550, (406 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// UPPER SIDE (Pale Sea Green)

glColor3f(0.50f, 0.80f, 0.60f);

glBegin(GL_POLYGON);

    glVertex2f((294 + 600) * 0.8f - 550, (406 + 70) * 0.8f + 100);

    glVertex2f((454 + 600) * 0.8f - 550, (406 + 70) * 0.8f + 100);

    glVertex2f((439 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

    glVertex2f((323 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// UPPER SIDE (Warm Peach)

glColor3f(0.90f, 0.60f, 0.40f);

glBegin(GL_POLYGON);

    glVertex2f((332 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

    glVertex2f((388 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

    glVertex2f((381 + 600) * 0.8f - 550, (469 + 70) * 0.8f + 100);

    glVertex2f((352 + 600) * 0.8f - 550, (469 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// UPPER SIDE (Muted Chestnut)

glColor3f(0.65f, 0.45f, 0.30f);

glBegin(GL_POLYGON);

    glVertex2f((388 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

    glVertex2f((413 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

    glVertex2f((403 + 600) * 0.8f - 550, (469 + 70) * 0.8f + 100);

    glVertex2f((381 + 600) * 0.8f - 550, (469 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// UPPER SIDE (Light Aqua)

glColor3f(0.50f, 0.90f, 0.90f);

glBegin(GL_POLYGON);

    glVertex2f((413 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

    glVertex2f((431 + 600) * 0.8f - 550, (439 + 70) * 0.8f + 100);

    glVertex2f((424 + 600) * 0.8f - 550, (462 + 70) * 0.8f + 100);

    glVertex2f((404 + 600) * 0.8f - 550, (462 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// UPPER SIDE (Charcoal Gray)

glColor3f(0.12f, 0.12f, 0.12f);

glBegin(GL_POLYGON);

    glVertex2f((363 + 600) * 0.8f - 550, (470 + 70) * 0.8f + 100);

    glVertex2f((397 + 600) * 0.8f - 550, (470 + 70) * 0.8f + 100);

    glVertex2f((392 + 600) * 0.8f - 550, (480 + 70) * 0.8f + 100);

    glVertex2f((373 + 600) * 0.8f - 550, (480 + 70) * 0.8f + 100);

glEnd();



// ------------------------

// CIRCLES (Soft Off-White Gray)

glColor3f(0.85f, 0.85f, 0.88f);

drawCircle((266 + 600) * 0.8f - 550, (390 + 70) * 0.8f + 100, 10, 80);

drawCircle((319 + 600) * 0.8f - 550, (390 + 70) * 0.8f + 100, 10, 80);

drawCircle((371 + 600) * 0.8f - 550, (390 + 70) * 0.8f + 100, 10, 80);

drawCircle((425 + 600) * 0.8f - 550, (390 + 70) * 0.8f + 100, 10, 80);



///yort



glPushMatrix();

glTranslatef(yort1X, 0.0f, 0.0f);

// Upper part

glBegin(GL_POLYGON);





glColor3f(0.7f, 0.0f, 0.0f);

glVertex2f(590,500); // l1

glVertex2f(670,500); // m1





glColor3f(1.0f, 0.3f, 0.3f);

glVertex2f(670,565); // n1

glVertex2f(625,565); // g1



glEnd();





//part2



glBegin(GL_POLYGON);





glColor3f(0.0f, 0.0f, 0.0f);

glVertex2f(590,500); // l1

glVertex2f(670,500); // m1





glColor3f(0.3f, 0.3f, 0.3f);

glVertex2f(670,535); // p1

glVertex2f(608,535); // o1



glEnd();

// Part 3

glBegin(GL_POLYGON);





glColor3f(0.2f, 0.0f, 0.2f);

glVertex2f(515,480); // j1

glVertex2f(730,480); // i1





glColor3f(0.5f, 0.0f, 0.5f);

glVertex2f(730,500); // h1

glVertex2f(515,500); // k1



glEnd();

// Part 4

glBegin(GL_POLYGON);





glColor3f(0.9f, 0.7f, 0.0f);

glVertex2f(485,385); // c1 (495-10)

glVertex2f(730,385); // f1





glColor3f(1.0f, 0.85f, 0.2f);

glVertex2f(720,480); // e1

glVertex2f(530,480); // d1



glEnd();



// Lower part

glBegin(GL_POLYGON);



glColor3f(0.5f, 0.0f, 0.5f);



glVertex2f(400,405); // c

glVertex2f(400,385); // d

glVertex2f(415,335); // e

glVertex2f(440,300); // f

glVertex2f(465,285); // g

glVertex2f(500,275); // h

glVertex2f(625,270); // i

glVertex2f(710,275); // j

glVertex2f(740,280); // k

glVertex2f(750,290); // l

glVertex2f(765,315); // m

glVertex2f(780,350); // n

glVertex2f(780,385); // o

glVertex2f(680,370); // p

glVertex2f(570,370); // q

glVertex2f(485,385); // r



glEnd();







// Lower line

glColor3f(1.0f, 0.0f, 0.0f);

glBegin(GL_POLYGON);



glVertex2f(400,405); // c

glVertex2f(400,385); // d

glVertex2f(405,370); // s

glVertex2f(470,365); // t

glVertex2f(520,360); // u

glVertex2f(575,355); // v

glVertex2f(630,355); // w

glVertex2f(680,355); // z

glVertex2f(735,355); // a1

glVertex2f(780,360); // b1

glVertex2f(780,385); // o

glVertex2f(680,370); // p

glVertex2f(570,370); // q

glVertex2f(485,385); // r



glEnd();

// Window 1

glBegin(GL_POLYGON);





glColor3f(0.0f, 0.3f, 0.6f);

glVertex2f(502,420); // t1

glVertex2f(560,420); // s1



glColor3f(0.4f, 0.7f, 1.0f);

glVertex2f(560,455); // r1

glVertex2f(518,455); // q1



glEnd();







// Window 2

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

glVertex2f(575,420); // d2

glVertex2f(605,420); // c2

glColor3f(0.4f, 0.7f, 1.0f);

glVertex2f(605,455); // b2

glVertex2f(575,455); // a2

glEnd();



// Window 3

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

glVertex2f(620,420); // l2

glVertex2f(650,420); // k2

glColor3f(0.4f, 0.7f, 1.0f);

glVertex2f(650,455); // j2

glVertex2f(620,455); // i2

glEnd();



// Window 4

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

glVertex2f(660,420); // t2

glVertex2f(695,420); // s2

glColor3f(0.4f, 0.7f, 1.0f);

glVertex2f(695,455); // r2

glVertex2f(660,455); // q2

glEnd();



// Window 5

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

glVertex2f(705,420); // w2

glVertex2f(727,420); // z2

glColor3f(0.4f, 0.7f, 1.0f);

glVertex2f(723,455); // v2

glVertex2f(705,455); // u2

glEnd();





// Gas line

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_POLYGON);

glVertex2f(645,565); // j3

glVertex2f(655,565); // k3

glVertex2f(655,575); // i3

glVertex2f(645,575); // h3

glEnd();



// Gas circle 1

glColor3f(0.9f, 0.9f, 0.9f);

drawCircle(650,600,12,100); // c3

drawCircle(670,605,12,100); // d3

drawCircle(680,590,12,100); // e3

drawCircle(665,585,12,100); // f3

drawCircle(647,580,12,100); // g3



// Gas circle 2 -

glColor3f(0.9f,0.9f, 0.9f);

drawCircle(730,610,12,100); // c3

drawCircle(750,615,12,100); // d3

drawCircle(760,600,12,100); // e3

drawCircle(745,595,12,100); // f3

drawCircle(727,590,12,100); // g3





// Circle 1

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

drawCircle(510,320,20,100);

glColor3f(0.4f, 0.7f, 1.0f);

glEnd();



// Circle 2

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

drawCircle(580,320,20,100);

glColor3f(0.4f, 0.7f, 1.0f);

glEnd();



// Circle 3

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

drawCircle(650,320,20,100);

glColor3f(0.4f, 0.7f, 1.0f);

glEnd();



// Circle 4

glBegin(GL_POLYGON);

glColor3f(0.0f, 0.3f, 0.6f);

drawCircle(720,320,20,100);

glColor3f(0.4f, 0.7f, 1.0f);

glEnd();



glPopMatrix();









///man



//head

glColor3f(1.0f, 0.86f, 0.67f);

   drawCircle(800,225,20,100);//be

glEnd();



//HAIR



glColor3f(0.0f,0.0f,0.0f);



glBegin(GL_POLYGON);

    glVertex2f(780,230+15);

    glVertex2f(780,220+15);

    glVertex2f(812,220+15);

    glVertex2f(812,190+15);

    glVertex2f(820,190+15);

    glVertex2f(820,230+15);

glEnd();



//eye

glColor3f(1.0f, 1.0f, 1.0f);



  //drawCircle(810,225,4,100);

  drawCircle(795,225,4,100);

glEnd();



glColor3f(0.0f, 0.0f, 0.0f);



//drawCircle(810,225,2,100);

  drawCircle(795,225,2,100);

glEnd();



// lip

glLineWidth(3.0f);

glColor3f(0.0f, 0.0f, 0.0f);



glBegin(GL_LINES);

    glVertex2f(798, 215);

    glVertex2f(810, 215);

glEnd();







//left hand

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(820,160);//q

         glVertex2f(850,85);//p

         glVertex2f(860,90);//o

         glVertex2f(850,125);//n

         glVertex2f(845,155);//k

         glVertex2f(840,170);//j

         glVertex2f(835,180);//i

         glVertex2f(830,195);//h

         glVertex2f(825,200);//g

         glVertex2f(815,200);//f

         glVertex2f(810,205);//e

         glVertex2f(810,215);//d

glEnd();





//left hand finger

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(850,85);//p

         glVertex2f(855,75);//i3

         glVertex2f(865,70);//j3

         glVertex2f(870,72);//k3

         glVertex2f(871,74);//l3

         glVertex2f(862,78);//m3

         glVertex2f(864,80);//n3



glEnd();





//left hand finger

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(864,80);//n3

         glVertex2f(876,78);//o3

         glVertex2f(886,73);//p3

         glVertex2f(888,75);//q3

         glVertex2f(880,83);//r3

         glVertex2f(870,88);//u3

         glVertex2f(860,90);//o

        glVertex2f(850,85);//p



glEnd();





//right hand

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(770,175);//k1

         glVertex2f(740,165);//m1

         glVertex2f(720,160);//j1

         glVertex2f(710,170);//i1

         glVertex2f(725,180);//l

         glVertex2f(730,185);//h1

         glVertex2f(765,195);//g1

         glVertex2f(780,200);//f1

         glVertex2f(790,202);//e1

         glVertex2f(790,215);//d1



glEnd();



//right hand finger

glColor3f(1.0f, 0.84f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(720,160);//j1

         glVertex2f(712,144);//a4

         glVertex2f(711,126);//z3

         glVertex2f(708,126);//w3

         glVertex2f(708,129);//v3

         glVertex2f(705,129);//r1

         glVertex2f(705,134);//p1

        glVertex2f(705,135);//e2

        glVertex2f(703,156);//m1

        glVertex2f(710,170);//i1



glEnd();







//body



glColor3f(1.0f, 0.86f, 0.67f);

glBegin(GL_POLYGON);

         glVertex2f(770,175);//k1

         glVertex2f(770,140);//l1

         glVertex2f(765,125);//o1

         glVertex2f(780,120);//p1

         glVertex2f(805,120);//q1

         glVertex2f(805,135);//s

         glVertex2f(810,145);//r

         glVertex2f(820,160);//q

         glVertex2f(810,215);//d

         glVertex2f(790,215);//d1





glEnd();



//leg right

glColor3f(1.0f, 0.86f, 0.67f);

glBegin(GL_POLYGON);

         glVertex2f(725,180);//l

         glVertex2f(710,185);//m

         glVertex2f(700,180);//b2

         glVertex2f(650,105);//c2

         glVertex2f(660,95);//d2

         glVertex2f(705,135);//e2



glEnd();



//leg right upper

glColor3f(0.0f,0.0f, 1.0f);



glBegin(GL_POLYGON);

         glVertex2f(740,165);//m1

        glVertex2f(720,160);//j1

         glVertex2f(725,145);//z1

         glVertex2f(730,135);//a2

         glVertex2f(730,130);//w1

         glVertex2f(740,115);//v1

         glVertex2f(750,110);//u1

         glVertex2f(765,110);//n1

         glVertex2f(768,165);//o1

         glVertex2f(770,145);//l1



glEnd();



//leg right finger

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(650,105);//c2

         glVertex2f(625,85);//g2

         glVertex2f(610,80);//h2

         glVertex2f(610,78);//i2

         glVertex2f(620,75);//j2

         glVertex2f(630,75);//k2

         glVertex2f(640,80);//l2

         glVertex2f(660,80);//m2

         glVertex2f(660,95);//d2



glEnd();





//leg left upper

glColor3f(1.0f, 0.86f, 0.67f);

glBegin(GL_POLYGON);

         glVertex2f(765,110);//n1

         glVertex2f(750,110);//u1

         glVertex2f(730,105);//s1

         glVertex2f(705,95);//t1

         glVertex2f(690,95);//f2

         glVertex2f(690,85);//c1

         glVertex2f(735,80);//b1

         glVertex2f(750,85);//a1

         glVertex2f(765,80);//z

         glVertex2f(780,80);//w

         glVertex2f(800,85);//v

         glVertex2f(803,91);//u

         glVertex2f(805,105);//t

         glVertex2f(805,120);//q1

        glVertex2f(780,120);//p1

         glVertex2f(765,125);//o1



glEnd();



//leg left upper pant

glColor3f(0.0f,0.0f, 1.0f);



glBegin(GL_POLYGON);

         glVertex2f(765,110);//n1

         glVertex2f(750,110);//u1

         glVertex2f(750,85);//a1

         glVertex2f(765,80);//z

         glVertex2f(780,80);//w

         glVertex2f(800,85);//v

         glVertex2f(803,91);//u

         glVertex2f(805,105);//t

         glVertex2f(805,120);//q1

        glVertex2f(780,120);//p1

         glVertex2f(765,125);//o1



glEnd();

//leg left foot

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(690,95);//f2

         glVertex2f(670,95);//h3

          glVertex2f(670,90);//p2

        glVertex2f(670,88);//q2

        glVertex2f(662,88);//r2

         glVertex2f(670,80);//d3

         glVertex2f(671,78);//e3

         glVertex2f(670,78);//f3

         glVertex2f(670,76);//g3

         glVertex2f(690,85);//c1

         glVertex2f(690,95);//f2

glEnd();



//leg left finger



//1

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(690,95);//f2

         glVertex2f(662,95);//n2

         glVertex2f(662,90);//o2

         glVertex2f(670,90);//p2

        glVertex2f(670,88);//q2



glEnd();



//2

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(670,88);//q2

         glVertex2f(665,88);//r2

         glVertex2f(665,85);//s2

         glVertex2f(667,85);//t2

         glVertex2f(667,83);//u2



glEnd();



//3

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(667,85);//u2

         glVertex2f(664,83);//v2

         glVertex2f(664,82);//w2

         glVertex2f(668,82);//z2

         glVertex2f(668,80);//a3



glEnd();



//4

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(668,82);//a3

         glVertex2f(666,80);//b3

         glVertex2f(666,78);//c3

         glVertex2f(670,80);//d3

         glVertex2f(670,78);//e3

glEnd();



//5

glColor3f(1.0f, 0.86f, 0.67f);



glBegin(GL_POLYGON);

         glVertex2f(671,78);//e3

         glVertex2f(670,78);//f3

         glVertex2f(670,75);//g3

         glVertex2f(690,85);//c1

          glVertex2f(690,95);//f2

glEnd();





//tree 1

// Tree Body



// 1

glColor3f(0.36f, 0.25f, 0.20f);

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1002 - 80, 1.1 * 42);

    glVertex2f(1.1 * 1010 - 80, 1.1 * 24);

    glVertex2f(1.1 * 1016 - 80, 1.1 * 36);

    glVertex2f(1.1 * 1030 - 80, 1.1 * 46);

    glVertex2f(1.1 * 1022 - 80, 1.1 * 24);

    glVertex2f(1.1 * 1036 - 80, 1.1 * 30);

    glVertex2f(1.1 * 1036 - 80, 1.1 * 50);

    glVertex2f(1.1 * 1006 - 80, 1.1 * 56);

glEnd();



// 2

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1002 - 80, 1.1 * 56);

    glVertex2f(1.1 * 1006 - 80, 1.1 * 56);

    glVertex2f(1.1 * 1036 - 80, 1.1 * 50);

    glVertex2f(1.1 * 1042 - 80, 1.1 * 50);

    glVertex2f(1.1 * 1040 - 80, 1.1 * 96);

    glVertex2f(1.1 * 1014 - 80, 1.1 * 96);

glEnd();



// 3

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1008 - 80, 1.1 * 100);

    glVertex2f(1.1 * 1014 - 80, 1.1 * 96);

    glVertex2f(1.1 * 1040 - 80, 1.1 * 96);

    glVertex2f(1.1 * 1046 - 80, 1.1 * 96);

    glVertex2f(1.1 * 1042 - 80, 1.1 * 142);

    glVertex2f(1.1 * 1018 - 80, 1.1 * 142);

glEnd();



// 4

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1012 - 80, 1.1 * 146);

    glVertex2f(1.1 * 1018 - 80, 1.1 * 142);

    glVertex2f(1.1 * 1042 - 80, 1.1 * 142);

    glVertex2f(1.1 * 1048 - 80, 1.1 * 144);

    glVertex2f(1.1 * 1040 - 80, 1.1 * 190);

    glVertex2f(1.1 * 1020 - 80, 1.1 * 190);

glEnd();



// 5

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1010 - 80, 1.1 * 190);

    glVertex2f(1.1 * 1020 - 80, 1.1 * 190);

    glVertex2f(1.1 * 1040 - 80, 1.1 * 190);

    glVertex2f(1.1 * 1048 - 80, 1.1 * 190);

    glVertex2f(1.1 * 1036 - 80, 1.1 * 230);

    glVertex2f(1.1 * 1014 - 80, 1.1 * 230);

glEnd();



// 6

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1008 - 80, 1.1 * 230);

    glVertex2f(1.1 * 1014 - 80, 1.1 * 230);

    glVertex2f(1.1 * 1036 - 80, 1.1 * 230);

    glVertex2f(1.1 * 1040 - 80, 1.1 * 230);

    glVertex2f(1.1 * 1030 - 80, 1.1 * 270);

    glVertex2f(1.1 * 1010 - 80, 1.1 * 270);

glEnd();



// 7

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1006 - 80, 1.1 * 270);

    glVertex2f(1.1 * 1010 - 80, 1.1 * 270);

    glVertex2f(1.1 * 1030 - 80, 1.1 * 270);

    glVertex2f(1.1 * 1026 - 80, 1.1 * 300);

    glVertex2f(1.1 * 1004 - 80, 1.1 * 304);

glEnd();



// Ground Leaf

glColor3f(0.0f, 0.5f, 0.0f);     // Classic dark green



glBegin(GL_POLYGON);

    glVertex2f(1.1 * 990 - 80, 1.1 * 1.9);

    glVertex2f(1.1 * 1010 - 80, 1.1 * 0.9);

    glVertex2f(1.1 * 1030 - 80, 1.1 * 1.5);

    glVertex2f(1.1 * 1050 - 80, 1.1 * 1.3);

    glVertex2f(1.1 * 1064 - 80, 1.1 * 3.9);

    glVertex2f(1.1 * 1060 - 80, 1.1 * 7.9);

    glVertex2f(1.1 * 1050 - 80, 1.1 * 9.9);

    glVertex2f(1.1 * 1054 - 80, 1.1 * 17.5);

    glVertex2f(1.1 * 1040 - 80, 1.1 * 16);

    glVertex2f(1.1 * 1044 - 80, 1.1 * 24);

    glVertex2f(1.1 * 1030 - 80, 1.1 * 20);

    glVertex2f(1.1 * 1036 - 80, 1.1 * 30);

    glVertex2f(1.1 * 1022 - 80, 1.1 * 24);

    glVertex2f(1.1 * 1030 - 80, 1.1 * 46);

    glVertex2f(1.1 * 1016 - 80, 1.1 * 36);

    glVertex2f(1.1 * 1010 - 80, 1.1 * 24);

    glVertex2f(1.1 * 1002 - 80, 1.1 * 42);

    glVertex2f(1.1 * 986 - 80, 1.1 * 56);

    glVertex2f(1.1 * 996 - 80, 1.1 * 24);

    glVertex2f(1.1 * 984 - 80, 1.1 * 30);

    glVertex2f(1.1 * 990 - 80, 1.1 * 18);

    glVertex2f(1.1 * 976 - 80, 1.1 * 24);

    glVertex2f(1.1 * 982 - 80, 1.1 * 15.06);

    glVertex2f(1.1 * 970 - 80, 1.1 * 16);

    glVertex2f(1.1 * 974 - 80, 1.1 * 10);

    glVertex2f(1.1 * 962 - 80, 1.1 * 4.9);

    glVertex2f(1.1 * 972 - 80, 1.1 * 2.5);

glEnd();



// Tree Leaf 1

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 972 - 80, 1.1 * 308);

    glVertex2f(1.1 * 950 - 80, 1.1 * 300);

    glVertex2f(1.1 * 934 - 80, 1.1 * 282);

    glVertex2f(1.1 * 946 - 80, 1.1 * 278);

    glVertex2f(1.1 * 930 - 80, 1.1 * 272);

    glVertex2f(1.1 * 924 - 80, 1.1 * 262);

    glVertex2f(1.1 * 916 - 80, 1.1 * 236);

    glVertex2f(1.1 * 926 - 80, 1.1 * 240);

    glVertex2f(1.1 * 918 - 80, 1.1 * 228);

    glVertex2f(1.1 * 920 - 80, 1.1 * 212);

    glVertex2f(1.1 * 930 - 80, 1.1 * 186);

    glVertex2f(1.1 * 958 - 80, 1.1 * 216);

    glVertex2f(1.1 * 950 - 80, 1.1 * 234);

    glVertex2f(1.1 * 964 - 80, 1.1 * 222);

    glVertex2f(1.1 * 986 - 80, 1.1 * 250);

    glVertex2f(1.1 * 982 - 80, 1.1 * 270);

    glVertex2f(1.1 * 990 - 80, 1.1 * 258);

    glVertex2f(1.1 * 1004 - 80, 1.1 * 304);

glEnd();



// Tree Leaf 2

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1038 - 80, 1.1 * 314);

    glVertex2f(1.1 * 1062 - 80, 1.1 * 306);

    glVertex2f(1.1 * 1078 - 80, 1.1 * 296);

    glVertex2f(1.1 * 1066 - 80, 1.1 * 290);

    glVertex2f(1.1 * 1084 - 80, 1.1 * 286);

    glVertex2f(1.1 * 1106 - 80, 1.1 * 260);

    glVertex2f(1.1 * 1090 - 80, 1.1 * 256);

    glVertex2f(1.1 * 1106 - 80, 1.1 * 250);

    glVertex2f(1.1 * 1108 - 80, 1.1 * 206);

    glVertex2f(1.1 * 1068 - 80, 1.1 * 222);

    glVertex2f(1.1 * 1068 - 80, 1.1 * 240);

    glVertex2f(1.1 * 1060 - 80, 1.1 * 226);

    glVertex2f(1.1 * 1042 - 80, 1.1 * 248);

    glVertex2f(1.1 * 1046 - 80, 1.1 * 266);

    glVertex2f(1.1 * 1034 - 80, 1.1 * 254);

    glVertex2f(1.1 * 1030 - 80, 1.1 * 270);

    glVertex2f(1.1 * 1026 - 80, 1.1 * 300);

glEnd();



// Tree Leaf 3

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 1016 - 80, 1.1 * 336);

    glVertex2f(1.1 * 1026 - 80, 1.1 * 348);

    glVertex2f(1.1 * 1042 - 80, 1.1 * 358);

    glVertex2f(1.1 * 1044 - 80, 1.1 * 348);

    glVertex2f(1.1 * 1052 - 80, 1.1 * 360);

    glVertex2f(1.1 * 1060 - 80, 1.1 * 362);

    glVertex2f(1.1 * 1100 - 80, 1.1 * 356);

    glVertex2f(1.1 * 1092 - 80, 1.1 * 346);

    glVertex2f(1.1 * 1108 - 80, 1.1 * 352);

    glVertex2f(1.1 * 1148 - 80, 1.1 * 328);

    glVertex2f(1.1 * 1104 - 80, 1.1 * 310);

    glVertex2f(1.1 * 1084 - 80, 1.1 * 320);

    glVertex2f(1.1 * 1092 - 80, 1.1 * 306);

    glVertex2f(1.1 * 1062 - 80, 1.1 * 306);

    glVertex2f(1.1 * 1038 - 80, 1.1 * 314);

glEnd();



// Tree Leaf 4

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 992 - 80, 1.1 * 332);

    glVertex2f(1.1 * 994 - 80, 1.1 * 356);

    glVertex2f(1.1 * 1010 - 80, 1.1 * 384);

    glVertex2f(1.1 * 1014 - 80, 1.1 * 374);

    glVertex2f(1.1 * 1016 - 80, 1.1 * 390);

    glVertex2f(1.1 * 1028 - 80, 1.1 * 402);

    glVertex2f(1.1 * 1048 - 80, 1.1 * 416);

    glVertex2f(1.1 * 1068 - 80, 1.1 * 422);

    glVertex2f(1.1 * 1064 - 80, 1.1 * 410);

    glVertex2f(1.1 * 1076 - 80, 1.1 * 422);

    glVertex2f(1.1 * 1098 - 80, 1.1 * 424);

    glVertex2f(1.1 * 1112 - 80, 1.1 * 420);

    glVertex2f(1.1 * 1094 - 80, 1.1 * 394);

    glVertex2f(1.1 * 1080 - 80, 1.1 * 392);

    glVertex2f(1.1 * 1088 - 80, 1.1 * 386);

    glVertex2f(1.1 * 1060 - 80, 1.1 * 362);

    glVertex2f(1.1 * 1052 - 80, 1.1 * 360);

    glVertex2f(1.1 * 1044 - 80, 1.1 * 348);

    glVertex2f(1.1 * 1042 - 80, 1.1 * 358);

    glVertex2f(1.1 * 1026 - 80, 1.1 * 348);

    glVertex2f(1.1 * 1016 - 80, 1.1 * 336);

    glVertex2f(1.1 * 1008 - 80, 1.1 * 334);

    glVertex2f(1.1 * 1002 - 80, 1.1 * 328);

glEnd();



// Tree Leaf 5

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 992 - 80, 1.1 * 332);

    glVertex2f(1.1 * 994 - 80, 1.1 * 356);

    glVertex2f(1.1 * 982 - 80, 1.1 * 374);

    glVertex2f(1.1 * 964 - 80, 1.1 * 390);

    glVertex2f(1.1 * 958 - 80, 1.1 * 378);

    glVertex2f(1.1 * 954 - 80, 1.1 * 392);

    glVertex2f(1.1 * 938 - 80, 1.1 * 402);

    glVertex2f(1.1 * 922 - 80, 1.1 * 406);

    glVertex2f(1.1 * 924 - 80, 1.1 * 394);

    glVertex2f(1.1 * 914 - 80, 1.1 * 406);

    glVertex2f(1.1 * 874 - 80, 1.1 * 404);

    glVertex2f(1.1 * 878 - 80, 1.1 * 400);

    glVertex2f(1.1 * 898 - 80, 1.1 * 378);

    glVertex2f(1.1 * 916 - 80, 1.1 * 380);

    glVertex2f(1.1 * 908 - 80, 1.1 * 372);

    glVertex2f(1.1 * 932 - 80, 1.1 * 350);

    glVertex2f(1.1 * 950 - 80, 1.1 * 354);

    glVertex2f(1.1 * 940 - 80, 1.1 * 344);

    glVertex2f(1.1 * 954 - 80, 1.1 * 336);

    glVertex2f(1.1 * 976 - 80, 1.1 * 324);

    glVertex2f(1.1 * 986 - 80, 1.1 * 330);

glEnd();



// Tree Leaf 6

glBegin(GL_POLYGON);

    glVertex2f(1.1 * 976 - 80, 1.1 * 324);

    glVertex2f(1.1 * 954 - 80, 1.1 * 336);

    glVertex2f(1.1 * 934 - 80, 1.1 * 340);

    glVertex2f(1.1 * 936 - 80, 1.1 * 326);

    glVertex2f(1.1 * 920 - 80, 1.1 * 340);

    glVertex2f(1.1 * 898 - 80, 1.1 * 334);

    glVertex2f(1.1 * 882 - 80, 1.1 * 324);

    glVertex2f(1.1 * 890 - 80, 1.1 * 316);

    glVertex2f(1.1 * 874 - 80, 1.1 * 318);

    glVertex2f(1.1 * 862 - 80, 1.1 * 302);

    glVertex2f(1.1 * 850 - 80, 1.1 * 282);

    glVertex2f(1.1 * 894 - 80, 1.1 * 282);

    glVertex2f(1.1 * 902 - 80, 1.1 * 292);

    glVertex2f(1.1 * 902 - 80, 1.1 * 282);

    glVertex2f(1.1 * 918 - 80, 1.1 * 282);

    glVertex2f(1.1 * 932 - 80, 1.1 * 286);

    glVertex2f(1.1 * 938 - 80, 1.1 * 298);

    glVertex2f(1.1 * 940 - 80, 1.1 * 288);

    glVertex2f(1.1 * 950 - 80, 1.1 * 298);

    glVertex2f(1.1 * 972 - 80, 1.1 * 308);

    glVertex2f(1.1 * 974 - 80, 1.1 * 316);

glEnd();



//coconut



glColor3f(1.0f, 0.75f, 0.0f);

  drawCircle(1007,344,21,200);

  drawCircle(1040,348,21,200);

glEnd();



//tree



//tree body



//1

glColor3f(0.36f, 0.25f, 0.20f);



glBegin(GL_POLYGON);

         glVertex2f(1126,21);//s

         glVertex2f(1130,12);//r

         glVertex2f(1133,18);//q

         glVertex2f(1140,23);//p



         glVertex2f(1136,12);//o

         glVertex2f(1143,15);//n

         glVertex2f(1143,25);//i1

         glVertex2f(1128,28);//h1



glEnd();





//2

glColor3f(0.36f, 0.25f, 0.20f);



glBegin(GL_POLYGON);

         glVertex2f(1126,28);//j1

         glVertex2f(1128,28);//h1

         glVertex2f(1143,25);//i1

         glVertex2f(1146,25);//k1

         glVertex2f(1145,48);//m1

         glVertex2f(1132,48);//l1



glEnd();



//3

glColor3f(0.36f, 0.25f, 0.20f);



glBegin(GL_POLYGON);

         glVertex2f(1129,50);//n1

         glVertex2f(1132,48);//l1

         glVertex2f(1145,48);//m1

         glVertex2f(1148,48);//o1

         glVertex2f(1146,71);//q1

         glVertex2f(1134,71);//p1

glEnd();



//4

glColor3f(0.36f, 0.25f, 0.20f);



glBegin(GL_POLYGON);

         glVertex2f(1131,73);//r1

         glVertex2f(1134,71);//p1

         glVertex2f(1146,71);//q1

         glVertex2f(1149,72);//s1

         glVertex2f(1145,95);//t1

         glVertex2f(1135,95);//u1

glEnd();



//5

glColor3f(0.36f, 0.25f, 0.20f);



glBegin(GL_POLYGON);

         glVertex2f(1130,95);//w1

         glVertex2f(1135,95);//u1

         glVertex2f(1145,95);//t1

         glVertex2f(1149,95);//v1

         glVertex2f(1143,115);//c2

         glVertex2f(1132,115);//b2

glEnd();



//6

glColor3f(0.36f, 0.25f, 0.20f);



glBegin(GL_POLYGON);

         glVertex2f(1129,115);//e2

         glVertex2f(1132,115);//b2

         glVertex2f(1143,115);//c2

         glVertex2f(1145,115);//f2

         glVertex2f(1140,135);//h2

         glVertex2f(1130,135);//g2

glEnd();



//7

glColor3f(0.36f, 0.25f, 0.20f);



glBegin(GL_POLYGON);

         glVertex2f(1128,135);//i2

         glVertex2f(1130,135);//g2

         glVertex2f(1140,135);//h2

         glVertex2f(1138,150);//j2

         glVertex2f(1127,152);//k2

glEnd();



//ground leaf

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1120,0.95);//c

         glVertex2f(1130,0.45);//d

         glVertex2f(1140,0.75);//e

         glVertex2f(1150,0.65);//f

         glVertex2f(1157,1.95);//g



         glVertex2f(1155,3.95);//h

         glVertex2f(1150,4.95);//i

         glVertex2f(1152,8.75);//j

         glVertex2f(1145,8);//k

         glVertex2f(1147,12);//l



         glVertex2f(1140,10);//m

         glVertex2f(1143,15);//n

         glVertex2f(1136,12);//o

         glVertex2f(1140,23);//p

         glVertex2f(1133,18);//q



         glVertex2f(1130,12);//r

         glVertex2f(1126,21);//s

         glVertex2f(1118,28);//t

         glVertex2f(1123,12);//u

         glVertex2f(1117,15);//v



         glVertex2f(1120,9);//w

         glVertex2f(1113,12);//z

         glVertex2f(1116,7.53);//a1

         glVertex2f(1110,8);//b1

         glVertex2f(1112,5);//c1



         glVertex2f(1106,2.45);//d1

         glVertex2f(1111,1.25);//e1

glEnd();





//tree leaf



 //1

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1111,154);//f3

         glVertex2f(1100,150);//e3

         glVertex2f(1092,141);//d3

         glVertex2f(1098,139);//c3

         glVertex2f(1090,136);//b3



         glVertex2f(1087,131);//a3

         glVertex2f(1083,118);//z2

         glVertex2f(1088,120);//w2

         glVertex2f(1084,114);//b2

         glVertex2f(1085,106);//u2



         glVertex2f(1090,93);//t2

         glVertex2f(1104,108);//s2

         glVertex2f(1100,117);//r2

         glVertex2f(1107,111);//q2

         glVertex2f(1118,125);//p2



         glVertex2f(1116,135);//02

         glVertex2f(1120,129);//n2

         glVertex2f(1127,152);//k2



glEnd();



//2

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1144,157);//w5

         glVertex2f(1156,153);//v5

         glVertex2f(1164,148);//z5

         glVertex2f(1158,145);//a6

         glVertex2f(1167,143);//b6



         glVertex2f(1178,130);//d6

         glVertex2f(1170,128);//e6

         glVertex2f(1178,125);//f6

         glVertex2f(1179,103);//g6

         glVertex2f(1159,111);//h6



         glVertex2f(1159,120);//c6

         glVertex2f(1155,113);//j6

         glVertex2f(1146,124);//k6

         glVertex2f(1148,133);//l6

         glVertex2f(1142,127);//m6



         glVertex2f(1140,135);//h2

         glVertex2f(1138,150);//j2



glEnd();



//3

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1133,168);//m5

         glVertex2f(1138,174);//l5

         glVertex2f(1146,179);//k5

         glVertex2f(1147,174);//j5

         glVertex2f(1151,180);//i5



         glVertex2f(1155,181);//h5

         glVertex2f(1175,178);//n5

         glVertex2f(1171,173);//o5

         glVertex2f(1179,176);//q5

         glVertex2f(1199,164);//r5



         glVertex2f(1177,155);//s5

         glVertex2f(1167,160);//t5

         glVertex2f(1171,153);//u5

         glVertex2f(1156,153);//v5

         glVertex2f(1144,157);//w5



glEnd();



//4



glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1121,166);//q4

         glVertex2f(1122,178);//r4

         glVertex2f(1130,192);//s4

         glVertex2f(1132,187);//t4

         glVertex2f(1133,195);//u4



         glVertex2f(1139,201);//v4

         glVertex2f(1149,208);//w4

         glVertex2f(1159,211);//z4

         glVertex2f(1157,205);//a5

         glVertex2f(1163,211);//b5



         glVertex2f(1174,212);//c5

         glVertex2f(1181,210);//d5

         glVertex2f(1172,197);//e5

         glVertex2f(1165,196);//f5

         glVertex2f(1169,193);//g5

         glVertex2f(1155,181);//h5



         glVertex2f(1151,180);//i5

         glVertex2f(1147,174);//j5

         glVertex2f(1146,179);//k5

         glVertex2f(1138,174);//l5

         glVertex2f(1133,168);//m5

         glVertex2f(1129,167);//c7

         glVertex2f(1126,164);//s6



glEnd();



//5

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1121,166);//q4

         glVertex2f(1122,178);//r4

         glVertex2f(1116,187);//p4

         glVertex2f(1107,195);//o4

         glVertex2f(1104,189);//n4



         glVertex2f(1102,196);//m4

         glVertex2f(1094,201);//l4

         glVertex2f(1086,203);//k4

         glVertex2f(1087,197);//j4

         glVertex2f(1082,203);//i4



         glVertex2f(1062,202);//h4

         glVertex2f(1064,200);//g4

         glVertex2f(1074,189);//f4

         glVertex2f(1083,190);//e4

         glVertex2f(1079,186);//d4

         glVertex2f(1091,175);//c4



         glVertex2f(1100,177);//b4

         glVertex2f(1095,172);//a4

         glVertex2f(1102,168);//w3

         glVertex2f(1113,162);//z3

         glVertex2f(1118,165);//d7



glEnd();



//6

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1113,162);//z3

         glVertex2f(1102,168);//w3

         glVertex2f(1092,170);//v3

         glVertex2f(1093,163);//u3

         glVertex2f(1085,170);//t3



         glVertex2f(1074,167);//s3

         glVertex2f(1066,162);//r3

         glVertex2f(1070,158);//q3

         glVertex2f(1062,159);//p3

         glVertex2f(1056,151);//o3



         glVertex2f(1050,141);//n3

         glVertex2f(1072,141);//m3

         glVertex2f(1076,146);//l3

         glVertex2f(1076,141);//k3

         glVertex2f(1084,141);//j3

         glVertex2f(1091,143);//i3



         glVertex2f(1094,149);//h3

         glVertex2f(1095,144);//g3

         glVertex2f(1100,149);//e3

         glVertex2f(1111,154);//f3

         glVertex2f(1112,158);//i6



glEnd();



//coconut

glColor3f(1.0f, 0.75f, 0.0f);



   drawCircle(1120,155,10,200);

   drawCircle(1136,159,10,200);



glEnd();



//tower



//lower part

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(6,42); //f (36-30=6)

         glVertex2f(232,42); //e (262-30=232)

         glVertex2f(232,58); //d (262-30=232)

         glVertex2f(6,58); //c (36-30=6)



glEnd();





glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(42,58);  //h (72-30=42)

         glVertex2f(70,58); //i (100-30=70)

         glVertex2f(70,70); //j (100-30=70)

         glVertex2f(42,70); //g (72-30=42)



glEnd();



glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(170,58);  //p (200-30=170)

         glVertex2f(196,58); //q (226-30=196)

         glVertex2f(196,70); //r (226-30=196)

         glVertex2f(170,70); //o (200-30=170)



glEnd();



//left stick

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(50,70);  //k (80-30=50)

         glVertex2f(64,70); //l (94-30=64)

         glVertex2f(86,300); //m (116-30=86)

         glVertex2f(72,300); //n (102-30=72)



glEnd();



//right stick

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(172,70);  //s (202-30=172)

         glVertex2f(190,70); //t (220-30=190)

         glVertex2f(166,300); //v (196-30=166)

         glVertex2f(152,300); //u (182-30=152)



glEnd();



//upper part



glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(56,300);  //w (86-30=56)

         glVertex2f(182,300); //z (212-30=182)

         glVertex2f(182,340); //a1 (212-30=182)

         glVertex2f(56,340); //f1 (86-30=56)



glEnd();



//upper part left stick

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(60,340);  //e1 (90-30=60)

         glVertex2f(70,340); //d1 (100-30=70)

         glVertex2f(70,392); //h1 (100-30=70)

         glVertex2f(60,392); //g1 (90-30=60)



glEnd();



//upper part right stick

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(168,340);  //c1 (198-30=168)

         glVertex2f(178,340); //b1 (208-30=178)

         glVertex2f(178,392); //j1 (208-30=178)

         glVertex2f(168,392); //i1 (198-30=168)



glEnd();



//tower top



glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(26,392);  //k1 (56-30=26)

         glVertex2f(214,392); //l1 (244-30=214)

         glVertex2f(120,460); //m1 (150-30=120)



glEnd();



//stairs left stick

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(96,58);  //o1 (126-30=96)

         glVertex2f(102,58); //q1 (132-30=102)

         glVertex2f(102,300); //p1 (132-30=102)

         glVertex2f(96,300); //n1 (126-30=96)

glEnd();



//stairs right stick

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(134,58);  //s1 (164-30=134)

         glVertex2f(140,58); //u1 (170-30=140)

         glVertex2f(140,300); //t1 (170-30=140)

         glVertex2f(134,300); //r1 (164-30=134)

glEnd();



//stairs 1

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,68);  //l6 (124-30=94)

         glVertex2f(144,68); //u6 (174-30=144)

         glVertex2f(144,74); //t6 (174-30=144)

         glVertex2f(94,74); //k6 (124-30=94)

glEnd();



//stairs 2

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,92);  //b6 (124-30=94)

         glVertex2f(144,92); //i6 (174-30=144)

         glVertex2f(144,98); //h6 (174-30=144)

         glVertex2f(94,98); //w5 (124-30=94)

glEnd();





//stairs 3

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,116);  //k5 (124-30=94)

         glVertex2f(144,116); //u5 (174-30=144)

         glVertex2f(144,122); //t5 (174-30=144)

         glVertex2f(94,122); //j5 (124-30=94)

glEnd();





//stairs 4

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,140);  //w4 (124-30=94)

         glVertex2f(144,140); //h5 (174-30=144)

         glVertex2f(144,146); //i5 (174-30=144)

         glVertex2f(94,146); //v4 (124-30=94)

glEnd();



//stairs 5

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,164);  //l4 (124-30=94)

         glVertex2f(144,164); //t4 (174-30=144)

         glVertex2f(144,170); //u4 (174-30=144)

         glVertex2f(94,170); //j4 (124-30=94)

glEnd();



//stairs 6

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,188);  //w3 (124-30=94)

         glVertex2f(144,188); //h4 (174-30=144)

         glVertex2f(144,194); //g4 (174-30=144)

         glVertex2f(94,194); //v3 (124-30=94)

glEnd();



//stairs 7

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,218);  //k3 (124-30=94)

         glVertex2f(144,218); //t3 (174-30=144)

         glVertex2f(144,224); //u3 (174-30=144)

         glVertex2f(94,224); //j3 (124-30=94)

glEnd();



//stairs 8

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,236);  //i3 (124-30=94)

         glVertex2f(144,236); //d3 (174-30=144)

         glVertex2f(144,242); //c3 (174-30=144)

         glVertex2f(94,242); //v2 (124-30=94)

glEnd();



//stairs 9

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,260);  //u2 (124-30=94)

         glVertex2f(144,260); //p2 (174-30=144)

         glVertex2f(144,266); //o2 (174-30=144)

         glVertex2f(94,266); //j2 (124-30=94)

glEnd();



//stairs 10

glColor3f(0.40f, 0.26f, 0.13f); //wood



glBegin(GL_POLYGON);

         glVertex2f(94,284);  //i2 (124-30=94)

         glVertex2f(144,284); //d2 (174-30=144)

         glVertex2f(144,290); //c2 (174-30=144)

         glVertex2f(94,290); //v1 (124-30=94)

glEnd();



//grass

//ground leaf extra 1

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1170,0.95);//c (1120+50=1170)

         glVertex2f(1180,0.45);//d (1130+50=1180)

         glVertex2f(1190,0.75);//e (1140+50=1190)

         glVertex2f(1200,0.65);//f (1150+50=1200)

         glVertex2f(1207,1.95);//g (1157+50=1207)



         glVertex2f(1205,3.95);//h (1155+50=1205)

         glVertex2f(1200,4.95);//i (1150+50=1200)

         glVertex2f(1202,8.75);//j (1152+50=1202)

         glVertex2f(1195,8);//k (1145+50=1195)

         glVertex2f(1197,12);//l (1147+50=1197)



         glVertex2f(1190,10);//m (1140+50=1190)

         glVertex2f(1193,15);//n (1143+50=1193)

         glVertex2f(1186,12);//o (1136+50=1186)

         glVertex2f(1190,23);//p (1140+50=1190)

         glVertex2f(1183,18);//q (1133+50=1183)



         glVertex2f(1180,12);//r (1130+50=1180)

         glVertex2f(1176,21);//s (1126+50=1176)

         glVertex2f(1168,28);//t (1118+50=1168)

         glVertex2f(1173,12);//u (1123+50=1173)

         glVertex2f(1167,15);//v (1117+50=1167)



         glVertex2f(1170,9);//w (1120+50=1170)

         glVertex2f(1163,12);//z (1113+50=1163)

         glVertex2f(1166,7.53);//a1 (1116+50=1166)

         glVertex2f(1160,8);//b1 (1110+50=1160)

         glVertex2f(1162,5);//c1 (1112+50=1162)



         glVertex2f(1156,2.45);//d1 (1106+50=1156)

         glVertex2f(1161,1.25);//e1 (1111+50=1161)

glEnd();





//grass 2 extra

//ground leaf

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1095,20.95);//c (1110-15=1095, 40.95-20=20.95)

         glVertex2f(1105,20.45);//d (1120-15=1105, 40.45-20=20.45)

         glVertex2f(1115,20.75);//e (1130-15=1115, 40.75-20=20.75)

         glVertex2f(1125,20.65);//f (1140-15=1125, 40.65-20=20.65)

         glVertex2f(1132,21.95);//g (1147-15=1132, 41.95-20=21.95)



         glVertex2f(1130,23.95);//h (1145-15=1130, 43.95-20=23.95)

         glVertex2f(1125,24.95);//i (1140-15=1125, 44.95-20=24.95)

         glVertex2f(1127,28.75);//j (1142-15=1127, 48.75-20=28.75)

         glVertex2f(1120,28);//k (1135-15=1120, 48-20=28)

         glVertex2f(1122,32);//l (1137-15=1122, 52-20=32)



         glVertex2f(1115,30);//m (1130-15=1115, 50-20=30)

         glVertex2f(1118,35);//n (1133-15=1118, 55-20=35)

         glVertex2f(1111,32);//o (1126-15=1111, 52-20=32)

         glVertex2f(1115,43);//p (1130-15=1115, 63-20=43)

         glVertex2f(1108,38);//q (1123-15=1108, 58-20=38)



         glVertex2f(1105,32);//r (1120-15=1105, 52-20=32)

         glVertex2f(1101,41);//s (1116-15=1101, 61-20=41)

         glVertex2f(1093,48);//t (1108-15=1093, 68-20=48)

         glVertex2f(1098,32);//u (1113-15=1098, 52-20=32)

         glVertex2f(1092,35);//v (1107-15=1092, 55-20=35)



         glVertex2f(1095,29);//w (1110-15=1095, 49-20=29)

         glVertex2f(1088,32);//z (1103-15=1088, 52-20=32)

         glVertex2f(1091,27.53);//a1 (1106-15=1091, 47.53-20=27.53)

         glVertex2f(1085,28);//b1 (1100-15=1085, 48-20=28)

         glVertex2f(1087,25);//c1 (1102-15=1087, 45-20=25)



         glVertex2f(1081,22.45);//d1 (1096-15=1081, 42.45-20=22.45)

         glVertex2f(1086,21.25);//e1 (1101-15=1086, 41.25-20=21.25)

glEnd();



//grass 3 extra

//ground leaf

glColor3f(0.16f, 0.52f, 0.13f);



glBegin(GL_POLYGON);



         glVertex2f(1095,0.95);// 20.95 - 20 = 0.95

         glVertex2f(1105,0.45);// 20.45 - 20 = 0.45

         glVertex2f(1115,0.75);// 20.75 - 20 = 0.75

         glVertex2f(1125,0.65);// 20.65 - 20 = 0.65

         glVertex2f(1132,1.95);// 21.95 - 20 = 1.95



         glVertex2f(1130,3.95);// 23.95 - 20 = 3.95

         glVertex2f(1125,4.95);// 24.95 - 20 = 4.95

         glVertex2f(1127,8.75);// 28.75 - 20 = 8.75

         glVertex2f(1120,8);// 28 - 20 = 8

         glVertex2f(1122,12);// 32 - 20 = 12



         glVertex2f(1115,10);// 30 - 20 = 10

         glVertex2f(1118,15);// 35 - 20 = 15

         glVertex2f(1111,12);// 32 - 20 = 12

         glVertex2f(1115,23);// 43 - 20 = 23

         glVertex2f(1108,18);// 38 - 20 = 18



         glVertex2f(1105,12);// 32 - 20 = 12

         glVertex2f(1101,21);// 41 - 20 = 21

         glVertex2f(1093,28);// 48 - 20 = 28

         glVertex2f(1098,12);// 32 - 20 = 12

         glVertex2f(1092,15);// 35 - 20 = 15



         glVertex2f(1095,9);// 29 - 20 = 9

         glVertex2f(1088,12);// 32 - 20 = 12

         glVertex2f(1091,7.53);// 27.53 - 20 = 7.53

         glVertex2f(1085,8);// 28 - 20 = 8

         glVertex2f(1087,5);// 25 - 20 = 5



         glVertex2f(1081,2.45);// 22.45 - 20 = 2.45

         glVertex2f(1086,1.25);// 21.25 - 20 = 1.25

glEnd();
}

void seen_three(){
    // Reset modelview

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();



    // Draw the gradient sky

    glBegin(GL_POLYGON);

        glColor3f(0.25f, 0.35f, 0.45f);

        glVertex2f(0, 163);

        glColor3f(0.55f, 0.60f, 0.65f);

        glVertex2f(1200, 163);

        glColor3f(0.70f, 0.75f, 0.78f);

        glVertex2f(1200, 686);

        glColor3f(0.30f, 0.40f, 0.50f);

        glVertex2f(0, 686);

    glEnd();



    //sun

     glColor3f(1.0f, 1.0f, 0.0f);



  drawCircle(1000,600,50,100);



glEnd();



    // Clouds (animated by cloudOffset) -- only clouds move

    drawCloudCluster(225 + cloudOffset + 800.0f, 625 - 60, 0.9f); // big one

    drawCloudCluster(900 - 90 + cloudOffset, 650 - 50, 0.6f);

    drawCloudCluster(50 + cloudOffset, 565, 1.0f);

    drawCloudCluster(250 + cloudOffset, 600, 0.6f);



    // RIVER

    glBegin(GL_POLYGON);

      glColor3ub(70, 130, 180);

        glVertex2f(0, 0);

      glColor3f(0.31f, 0.82f, 0.88f);

        glVertex2f(1200, 0);

        glVertex2f(1200,164);

      glColor3f(1.0f, 1.0f, 1.0f);

        glVertex2f(0,164);

    glEnd();



    // wave strip (animated slight by time)

    glColor3ub(70,130,180);

    glBegin(GL_TRIANGLE_STRIP);

    for (float x = 0; x <= 1200; x += 10.0f) {

        float t = glutGet(GLUT_ELAPSED_TIME) / 500.0f;

        float waveY = 160 + 8 * sinf(0.02f * x + t);

        glVertex2f(x, waveY);

        glVertex2f(x, 164);

    }

    glEnd();



    // Bridge pillars and bridge deck (kept visually similar)

    // 1st pillar

    glBegin(GL_POLYGON);

        glColor3f(0.2f, 0.2f, 0.2f);

        glVertex2f(53, 330);

        glColor3f(0.6f, 0.6f, 0.6f);

        glVertex2f(124, 330);

        glColor3f(0.8f, 0.8f, 0.8f);

        glVertex2f(152,360);

        glVertex2f(23,360);

    glEnd();

    glBegin(GL_POLYGON);

        glColor3f(0.2f, 0.2f, 0.2f);

        glVertex2f(53, 164);

        glColor3f(0.3f, 0.3f, 0.3f);

         glVertex2f(124, 164);

        glColor3f(0.6f, 0.6f, 0.6f);

        glVertex2f(124,330);

        glColor3f(0.7f, 0.7f, 0.7f);

        glVertex2f(53,330);

    glEnd();



    // 2nd pillar

    glBegin(GL_POLYGON);

        glColor3f(0.2f, 0.2f, 0.2f);

         glVertex2f(563, 164);

        glColor3f(0.3f, 0.3f, 0.3f);

         glVertex2f(640, 164);

        glColor3f(0.6f, 0.6f, 0.6f);

         glVertex2f(640,330);

        glColor3f(0.7f, 0.7f, 0.7f);

        glVertex2f(562,330);

    glEnd();

    glBegin(GL_POLYGON);

        glColor3f(0.6f, 0.6f, 0.6f);

         glVertex2f(562, 330);

        glColor3f(0.7f, 0.7f, 0.7f);

        glVertex2f(640, 330);

        glColor3f(0.85f, 0.85f, 0.85f);

         glVertex2f(663,360);

        glColor3f(0.75f, 0.75f, 0.75f);

         glVertex2f(535,360);

    glEnd();



    // 3rd pillar

    glBegin(GL_POLYGON);

        glColor3f(0.2f, 0.2f, 0.2f);

         glVertex2f(1074, 164);

        glColor3f(0.3f, 0.3f, 0.3f);

        glVertex2f(1151, 164);

        glColor3f(0.6f, 0.6f, 0.6f);

         glVertex2f(1151,330);

        glColor3f(0.7f, 0.7f, 0.7f);

         glVertex2f(1074,330);

    glEnd();

    glBegin(GL_POLYGON);

        glColor3f(0.65f, 0.65f, 0.65f);

         glVertex2f(1074, 330);

        glColor3f(0.75f, 0.75f, 0.75f);

         glVertex2f(1151, 330);

        glColor3f(0.9f, 0.9f, 0.9f);

        glVertex2f(1180,360);

        glColor3f(0.8f, 0.8f, 0.8f);

         glVertex2f(1045,360);

    glEnd();



    // main bridge deck

    glBegin(GL_POLYGON);

        glColor3f(0.2f, 0.2f, 0.2f);

        glVertex2f(0, 360);

        glVertex2f(1200, 360);

        glVertex2f(1200,450);

        glVertex2f(0,450);

    glEnd();









    // some white dividing lines on bridge (kept as lines)

    glLineWidth(3.0f);

    glColor3f(1.0f,1.0f,1.0f);

    glBegin(GL_LINES);

        // long top lines

        glVertex2f(0,470); glVertex2f(1200,470);

        glVertex2f(0,460); glVertex2f(1200,460);

        // vertical ticks spaced

        for (int x=50; x<=1150; x+=100) { glVertex2f((GLfloat)x,450); glVertex2f((GLfloat)x,470); }

        // extra lines lower

        glVertex2f(0,418); glVertex2f(1200,418);

    glEnd();







    // bus drawing with translation (busOffset moves it right->left)

    glPushMatrix();

        glTranslatef(busOffset, 0.0f, 0.0f);

        drawBus();

    glPopMatrix();



    glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);



glBegin(GL_LINES);

    glVertex2f(0, 380);      // c1

    glVertex2f(1200, 380);   // d1

glEnd();



//  line 2

 glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);



glBegin(GL_LINES);

    glVertex2f(0, 370);      // c1

    glVertex2f(1200, 370);   // d1

glEnd();





 glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(50, 360);      // c1

    glVertex2f(50, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(150, 360);      // c1

    glVertex2f(150, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(250, 360);      // c1

    glVertex2f(250, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(50, 360);      // c1

    glVertex2f(50, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(350, 360);      // c1

    glVertex2f(350, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(450, 360);      // c1

    glVertex2f(450, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(550, 360);      // c1

    glVertex2f(550, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(650, 360);      // c1

    glVertex2f(650, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(750, 360);      // c1

    glVertex2f(750, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(850, 360);      // c1

    glVertex2f(850, 380);      // d1

glEnd();



       // d1





glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(950, 360);      // c1

    glVertex2f(950, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(1050, 360);      // c1

    glVertex2f(1050, 380);      // d1

glEnd();



glLineWidth(3.0f);

glColor3f(1.0f, 1.0f, 1.0f);

glBegin(GL_LINES);

    glVertex2f(1150, 360);      // c1

    glVertex2f(1150, 380);      // d1



glEnd();



    // If raining, draw rain

    if (isRaining) drawRain();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);


    if(isseen_one&&!isseen_two){
        seen_one();
    }else if(!isseen_one&&isseen_two){
        seen_two();
    }else if(!isseen_one&&!isseen_two&&isseen_three){
        seen_three();
    }
    glFlush();
}

void update(int value)
{
    boatPosX += 4.0f;   // Move by 1 pixel each update
    if (boatPosX > 1200)
    {
        boatPosX = -200; // Reset to left side after reaching 1200
    }
    glutPostRedisplay();            // Redraw the scene
    glutTimerFunc(30, update, 0);   // Call again after 30 ms


    //extra add
    if (isRaining) {
        for (int i = 0; i < NUM_DROPS; ++i) {
            rainY[i] -= 6.0f;
            if (rainY[i] < 0.0f) {
                rainY[i] = (float)WIN_H;
                rainX[i] = (rand() / (float)RAND_MAX) * WIN_W;
            }
        }
    }

    // cloud moves left -> right
    cloudOffset += CLOUD_SPEED;
    if (cloudOffset > 1600.0f) cloudOffset = -400.0f;

    // bus moves right -> left
    busOffset -= BUS_SPEED;
    if (busOffset < -1400.0f) busOffset = 1200.0f;

    glutPostRedisplay();
    glutTimerFunc(30, updateScene, 0); //
}
void updateCloud(int value)
{
    if (moveCloud)
    {
        cloudPosX += 2.0f;   // cloud speed
        if (cloudPosX > 1200) cloudPosX = -300; // reset clouds when out of screen
    }
    glutPostRedisplay();
    glutTimerFunc(30, updateCloud, 0);
}


void initGL()
{
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1200, 0, 750);
}
void handleKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':  // move clouds right
        moveCloud = true;
        break;
    case 's':  // stop clouds
        moveCloud = false;
        break;
    case 'a':  // step clouds left
        cloudPosX -= 10;
        break;
    }

    if(key=='t'){
        isseen_one=false;
        isseen_two=true;
    }
    if(key=='h'){
        isseen_one=false;
        isseen_two=false;
        isseen_three=true;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 750);
    glutCreateWindow("Beautiful Scenic View - 1200x750 Frame");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display);
    glutTimerFunc(30, updateCloud, 0);  // start cloud update loop
    glutKeyboardFunc(handleKeys);       // enable keyboard controls

    glutTimerFunc(15, update, 0);


    initGL();
    glutMainLoop();
    return 0;
}
