/*
 * Based on an idea of https://www.reddit.com/r/EliteDangerous/comments/bjdg54/old_school_elite_ship_viewer/
 * 
 * Code base on http://colinord.blogspot.com/2015/01/arduino-oled-module-with-3d-demo.html
 */


#include <U8g2lib.h>


#include "ships.h"

//The following line will need changing depending on your board type!
// U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


//float tx, nx, p;
//float ty, ny, py;
float rot, rotx, roty, rotz, rotxx, rotyy, rotzz, rotxxx, rotyyy, rotzzz;
int i; //0 to 360
int fl, scale; //focal length
int wireframe[32][3];

int ship_vertices_cnt, ship_faces_cnt;
int ship_vertices[32][3];
int ship_faces[32][9];


int originx = 63;
int originy = 32;

int front_depth = 20;
int back_depth = -20;

float vector;

int fd = 0; //0=orthographic

float scalefactor = 0;

String ShipName = "";

void setup(void)
{
  pinMode(A4, OUTPUT);
    
 u8g2.begin();

//Clear Screen
 u8g2.firstPage();
 do {
// empty screen

 } while ( u8g2.nextPage() );



}


void draw_wireframe_ship(void)
{
  int face, f_line, wf_f_1, wf_f_2;

//  img.setColorDepth(8);         // Set colour depth first
//  img.createSprite(135, 135);                  // then create the sprite
//  img.fillSprite(TFT_BLACK);

  for ( face = 0; face < ship_faces_cnt; face++) {
    vector = 0;
    for ( f_line = 1; f_line < ship_faces[face][0]; f_line++) {
      wf_f_1 = ship_faces[face][f_line];
      wf_f_2 = ship_faces[face][f_line + 1];
      vector += wireframe[wf_f_1][0] * wireframe[wf_f_2][1] - wireframe[wf_f_1][1] * wireframe[wf_f_2][0];
    };
    wf_f_1 = ship_faces[face][f_line];
    wf_f_2 = ship_faces[face][1];
    vector += wireframe[wf_f_1][0] * wireframe[wf_f_2][1] - wireframe[wf_f_1][1] * wireframe[wf_f_2][0];

    //Serial.printf("Face %02i ", face);
    //Serial.println(vector);
    if ( vector >= 0 ) {
      for ( f_line = 1; f_line < ship_faces[face][0]; f_line++) {
        wf_f_1 = ship_faces[face][f_line];
        wf_f_2 = ship_faces[face][f_line + 1];
        u8g2.drawLine(wireframe[wf_f_1][0], wireframe[wf_f_1][1], wireframe[wf_f_2][0], wireframe[wf_f_2][1]);
      }
      wf_f_1 = ship_faces[face][f_line];
      wf_f_2 = ship_faces[face][1];
      u8g2.drawLine(wireframe[wf_f_1][0], wireframe[wf_f_1][1], wireframe[wf_f_2][0], wireframe[wf_f_2][1]);
    }
  }
 
}

void rotate_ship(void) {
  scalefactor = 0;
  for (int cnt = 0; cnt < 3; cnt ++) {
    
    for (int angle = 0; angle <= 360; angle = angle + 3) {
        u8g2.firstPage();
        do{
      for (int i = 0; i < ship_vertices_cnt; i++) {
        rot = angle * 0.0174532; //0.0174532 = one degree
        //rotateY
        rotz = ship_vertices[i][2] / scale * sin(rot) + ship_vertices[i][0] / scale * cos(rot);
        rotx = ship_vertices[i][2] / scale * cos(rot) - ship_vertices[i][0] / scale * sin(rot);
        roty = ship_vertices[i][1] / scale;
        //rotateX
        rotyy = roty * sin(rot) - rotz * cos(rot);
        rotzz = roty * cos(rot) + rotz * sin(rot);
        rotxx = rotx;
        //rotateZ
        rotxxx = rotxx * sin(rot) - rotyy * cos(rot);
        rotyyy = rotxx * cos(rot) + rotyy * sin(rot);
        rotzzz = rotzz;

        //orthographic projection
        
        rotxxx = rotxxx * scalefactor + originx;
        rotyyy = rotyyy * scalefactor + originy;

        //store new vertices values for wireframe drawing
        wireframe[i][0] = rotxxx;
        wireframe[i][1] = rotyyy;
        wireframe[i][2] = rotzzz;

        //draw_vertices();
      }
      
      draw_wireframe_ship();
      if (scalefactor < 1) scalefactor = scalefactor + 0.02;
      delay(5);

      u8g2.setFont(u8g2_font_u8glib_4_tr);
    //u8g2.setFont(u8g2_tinytim_t);
    
  
    u8g2.setCursor(99, 10);
    u8g2.print(wireframe[0][0]);
    u8g2.setCursor(109, 10);
    u8g2.print(wireframe[0][1]);
    u8g2.setCursor(119, 10);
    u8g2.print(wireframe[0][2]);

    u8g2.setCursor(99, 16);
    u8g2.print(wireframe[1][0]);
    u8g2.setCursor(109, 16);
    u8g2.print(wireframe[1][1]);
    u8g2.setCursor(119, 16);
    u8g2.print(wireframe[1][2]);

    u8g2.setCursor(99, 22);
    u8g2.print(wireframe[2][0]);
    u8g2.setCursor(109, 22);
    u8g2.print(wireframe[2][1]);
    u8g2.setCursor(119, 22);
    u8g2.print(wireframe[2][2]);

    u8g2.setCursor(99, 28);
    u8g2.print(wireframe[3][0]);
    u8g2.setCursor(109, 28);
    u8g2.print(wireframe[3][1]);
    u8g2.setCursor(119, 28);
    u8g2.print(wireframe[3][2]);

    u8g2.setCursor(99, 34);
    u8g2.print(wireframe[7][0]);
    u8g2.setCursor(109, 34);
    u8g2.print(wireframe[7][1]);
    u8g2.setCursor(119, 34);
    u8g2.print(wireframe[7][2]);


    
    u8g2.setCursor(101, 50);
    u8g2.print(rotxxx);
    
    u8g2.setCursor(101, 56);
    u8g2.print(rotyyy);
    
    u8g2.setCursor(101, 62);
    u8g2.print(rotzzz);
    
    u8g2.drawStr(0, 5, "OKUBO HEAVY");
    u8g2.drawStr(3, 11, "INDUSTRIES");
    
    u8g2.setCursor(0, 62);
    if (scalefactor >= 0.24) u8g2.print(ShipName);

       
    }
   while (u8g2.nextPage()); 
  }
 
}
}

void clearOLED(){
    u8g2.firstPage();  
    do {
    } while( u8g2.nextPage() );

}
void loop(void)
{
// int i, j;

  clearOLED();
  ShipName = "Cobra Mk.III";
  memcpy(ship_vertices, cobra_vertices, sizeof(cobra_vertices));
  ship_vertices_cnt = cobra_vertices_cnt;
  scale = cobra_scale;
  memcpy(ship_faces, cobra_faces, sizeof(cobra_faces));
  ship_faces_cnt = cobra_faces_cnt;
  rotate_ship();

clearOLED();
  ShipName = "Adder";
  memcpy(ship_vertices, adder_vertices, sizeof(adder_vertices));
  ship_vertices_cnt = adder_vertices_cnt;
  scale = adder_scale;
  memcpy(ship_faces, adder_faces, sizeof(adder_faces));
  ship_faces_cnt = adder_faces_cnt;
  rotate_ship();

  clearOLED();
  ShipName = "Asp";
  memcpy(ship_vertices, asp_vertices, sizeof(asp_vertices));
  ship_vertices_cnt = asp_vertices_cnt;
  scale = asp_scale;
  memcpy(ship_faces, asp_faces, sizeof(asp_faces));
  ship_faces_cnt = asp_faces_cnt;
  rotate_ship();

 clearOLED();
  ShipName = "Anaconda";
  memcpy(ship_vertices, anaconda_vertices, sizeof(anaconda_vertices));
  ship_vertices_cnt = anaconda_vertices_cnt;
  scale = anaconda_scale;
  memcpy(ship_faces, anaconda_faces, sizeof(anaconda_faces));
  ship_faces_cnt = anaconda_faces_cnt;
  rotate_ship();

 clearOLED();
  ShipName = "Viper";
  memcpy(ship_vertices, viper_vertices, sizeof(viper_vertices));
  ship_vertices_cnt = viper_vertices_cnt;
  scale = viper_scale;
  memcpy(ship_faces, viper_faces, sizeof(viper_faces));
  ship_faces_cnt = viper_faces_cnt;
  rotate_ship();

 clearOLED();
  ShipName = "Sidewinder";
  memcpy(ship_vertices, sidewinder_vertices, sizeof(sidewinder_vertices));
  ship_vertices_cnt = sidewinder_vertices_cnt;
  scale = sidewinder_scale;
  memcpy(ship_faces, sidewinder_faces, sizeof(sidewinder_faces));
  ship_faces_cnt = sidewinder_faces_cnt;
  rotate_ship();

 clearOLED();
  ShipName = "Coriolis Station";
  memcpy(ship_vertices, coriolis_vertices, sizeof(coriolis_vertices));
  ship_vertices_cnt = coriolis_vertices_cnt;
  scale = coriolis_scale;
  memcpy(ship_faces, coriolis_faces, sizeof(coriolis_faces));
  ship_faces_cnt = coriolis_faces_cnt;
  rotate_ship();

 clearOLED();
  ShipName = "Dodo Station";
  memcpy(ship_vertices, dodo_vertices, sizeof(dodo_vertices));
  ship_vertices_cnt = dodo_vertices_cnt;
  scale = dodo_scale;
  memcpy(ship_faces, dodo_faces, sizeof(dodo_faces));
  ship_faces_cnt = dodo_faces_cnt;
  rotate_ship();

 clearOLED();
 ShipName = "Thargoid";
  memcpy(ship_vertices, thargoid_vertices, sizeof(thargoid_vertices));
  ship_vertices_cnt = thargoid_vertices_cnt;
  scale = thargoid_scale;
  memcpy(ship_faces, thargoid_faces, sizeof(thargoid_faces));
  ship_faces_cnt = thargoid_faces_cnt;
  rotate_ship();

}
