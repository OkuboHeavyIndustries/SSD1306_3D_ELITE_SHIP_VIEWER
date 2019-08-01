/*
 * Code based on http://colinord.blogspot.com/2015/01/arduino-oled-module-with-3d-demo.html
 * Additional code from https://github.com/RobFis1/ST7789_3D_ELITE_TFT_eSPI
 * 3D Ship data courtesy of Ian Bell. Verticies and faces were converted from: http://www.elitehomepage.org/archive/index.htm
 * File: b7051600.zip
 * Thanks to Ian Bell and David Braben for creating Elite.
 * Okubo Heavy Industries - 1st August 2019
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
int wireframe[43][3];

int ship_vertices_cnt, ship_faces_cnt;
int ship_vertices[43][3];
int ship_faces[23][9];


int originx = 63;
int originy = 32;

int front_depth = 20;
int back_depth = -20;

float vector;

int fd = 0; //0=orthographic

float scalefactor = 0;

String ShipName = "";
String ShipType = "";
String ShipClass = "";
String ShipHyperspace = "";
String ShipSize = "";

void setup(void)
{
 pinMode(A4, OUTPUT);
 randomSeed(analogRead(A3));   
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

// this is used for rotate_ship_open (no backface culling).
void draw_wireframe_ship_open(void)
{
  int face, f_line, wf_f_1, wf_f_2;

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

void rotate_ship(void) {
  scalefactor = 0;
  for (int cnt = 0; cnt < 3; cnt ++) {
    
    for (int angle = 0; angle <= 360; angle = angle + 3) {
        u8g2.firstPage();
        do{
      for (int i = 0; i < ship_vertices_cnt; i++) {
        rot = angle * 0.0174532; //0.0174532 = one degree
        //rotateY
        rotz = ship_vertices[i][2] / scale * cos(rot) - ship_vertices[i][0] / scale * sin(rot);
        rotx = ship_vertices[i][2] / scale * sin(rot) + ship_vertices[i][0] / scale * cos(rot);
        roty = ship_vertices[i][1] / scale;
        //rotateX
        rotyy = roty * cos(rot) - rotz * sin(rot);
        rotzz = roty * sin(rot) + rotz * cos(rot);
        rotxx = rotx;
        //rotateZ
        rotxxx = rotxx * cos(rot) - rotyy * sin(rot);
        rotyyy = rotxx * sin(rot) + rotyy * cos(rot);
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
      if (scalefactor < 1) scalefactor = scalefactor + 0.01;
      delay(2);

      u8g2.setFont(u8g2_font_u8glib_4_tr);
  
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
    
    if (scalefactor >= 0.3) u8g2.drawStr(0, 43, "Class: ");
    u8g2.setCursor(20, 43);
    if (scalefactor >= 0.35) u8g2.print(ShipClass); 
    if (scalefactor >= 0.4) u8g2.drawStr(0, 49, "H-D: ");
    u8g2.setCursor(20, 49);
    if (scalefactor >= 0.45) u8g2.print(ShipHyperspace);
    if (scalefactor >= 0.5) u8g2.drawStr(0, 55, "Type: ");
    u8g2.setCursor(20, 55);
    if (scalefactor >= 0.55) u8g2.print(ShipType);
    if (scalefactor >= 0.6) u8g2.drawStr(0, 62, "ID: ");
    u8g2.setCursor(20, 62);
    if (scalefactor >= 0.8) u8g2.print(ShipName);
   
   
       
    }
   while (u8g2.nextPage()); 
  }
 
}
}

// Alternate rotation style
void rotate_ship_2(void) {
  scalefactor = 0;
  for (int cnt = 0; cnt < 3; cnt ++) {
    
    for (int angle = 0; angle <= 360; angle = angle + 3) {    
        u8g2.firstPage();
        do{
      for (int i = 0; i < ship_vertices_cnt; i++) {
        rot = angle * 0.0174532; //0.0174532 = one degree
        //rotateY
        rotx = ship_vertices[i][2] / scale * cos(rot) + ship_vertices[i][0] / scale * sin(rot);
        rotz = ship_vertices[i][2] / scale * sin(rot) - ship_vertices[i][0] / scale * cos(rot);
        roty = ship_vertices[i][1] / scale;
        //rotateX
        rotyy = roty * cos(rot) - rotz * sin(rot);
        rotzz = roty * sin(rot) + rotz * cos(rot);
        rotxx = rotx;
        //rotateZ
        rotzzz = rotxx * cos(rot) - rotyy * sin(rot);
        rotyyy = rotxx * sin(rot) + rotyy * cos(rot);
        rotxxx = rotzz;

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
    
    if (scalefactor >= 0.3) u8g2.drawStr(0, 43, "Class: ");
    u8g2.setCursor(20, 43);
    if (scalefactor >= 0.35) u8g2.print(ShipClass); 
    if (scalefactor >= 0.4) u8g2.drawStr(0, 49, "H-D: ");
    u8g2.setCursor(20, 49);
    if (scalefactor >= 0.45) u8g2.print(ShipHyperspace);
    if (scalefactor >= 0.5) u8g2.drawStr(0, 55, "Type: ");
    u8g2.setCursor(20, 55);
    if (scalefactor >= 0.55) u8g2.print(ShipType);
    if (scalefactor >= 0.6) u8g2.drawStr(0, 62, "ID: ");
    u8g2.setCursor(20, 62);
    if (scalefactor >= 0.8) u8g2.print(ShipName);   
    }
   while (u8g2.nextPage()); 
  }
 
}
}
// no backface culling
void rotate_ship_open(void) {
  scalefactor = 0;
  for (int cnt = 0; cnt < 3; cnt ++) {
    
    for (int angle = 0; angle <= 360; angle = angle + 3) {
        u8g2.firstPage();
        do{
      for (int i = 0; i < ship_vertices_cnt; i++) {
        rot = angle * 0.0174532; //0.0174532 = one degree
        //rotateY
        rotx = ship_vertices[i][2] / scale * cos(rot) + ship_vertices[i][0] / scale * sin(rot);
        rotz = ship_vertices[i][2] / scale * sin(rot) - ship_vertices[i][0] / scale * cos(rot);
        roty = ship_vertices[i][1] / scale;
        //rotateX
        rotyy = roty * cos(rot) - rotz * sin(rot);
        rotzz = roty * sin(rot) + rotz * cos(rot);
        rotxx = rotx;
        //rotateZ
        rotzzz = rotxx * cos(rot) - rotyy * sin(rot);
        rotyyy = rotxx * sin(rot) + rotyy * cos(rot);
        rotxxx = rotzz;

        //orthographic projection
        
        rotxxx = rotxxx * scalefactor + originx;
        rotyyy = rotyyy * scalefactor + originy;

        //store new vertices values for wireframe drawing
        wireframe[i][0] = rotxxx;
        wireframe[i][1] = rotyyy;
        wireframe[i][2] = rotzzz;

        //draw_vertices();
      }
      
      draw_wireframe_ship_open();
      if (scalefactor < 1) scalefactor = scalefactor + 0.02;
      delay(5);

      u8g2.setFont(u8g2_font_u8glib_4_tr);
  
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
    
    if (scalefactor >= 0.3) u8g2.drawStr(0, 43, "Class: ");
    u8g2.setCursor(20, 43);
    if (scalefactor >= 0.35) u8g2.print(ShipClass); 
    if (scalefactor >= 0.4) u8g2.drawStr(0, 49, "H-D: ");
    u8g2.setCursor(20, 49);
    if (scalefactor >= 0.45) u8g2.print(ShipHyperspace);
    if (scalefactor >= 0.5) u8g2.drawStr(0, 55, "Type: ");
    u8g2.setCursor(20, 55);
    if (scalefactor >= 0.55) u8g2.print(ShipType);
    if (scalefactor >= 0.6) u8g2.drawStr(0, 62, "ID: ");
    u8g2.setCursor(20, 62);
    if (scalefactor >= 0.8) u8g2.print(ShipName);
       
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

void ledflash(void){
  digitalWrite(A4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(30);                       // wait for a bit
  digitalWrite(A4, LOW);    // turn the LED off by making the voltage LOW
}

void boot_sequence(void)
{
    ledflash();
    clearOLED();
    u8g2.firstPage();
    //Screen flash
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.drawBox(0,0,128,64);
    u8g2.sendBuffer();
    delay(100);
    u8g2.setDrawColor(0);
    u8g2.clearBuffer();
    u8g2.drawBox(0,0,128,64);
    u8g2.sendBuffer();
    delay(500);
    //cursor flash
    for (int i = 0; i < 3; i++) {
    
    u8g2.setDrawColor(1);
    u8g2.clearBuffer();
    u8g2.drawBox(1,1,3,5);
    u8g2.sendBuffer();
    delay(300);
    
    u8g2.clearBuffer();
    u8g2.setDrawColor(0);
    u8g2.drawBox(1,1,3,5);
    u8g2.sendBuffer();
    delay(300);
    }
   
    u8g2.setDrawColor(1);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_u8glib_4_tr);
    u8g2.drawStr(15, 30, "INCOMIMG TRANSMISSION...");
    u8g2.sendBuffer();
    delay(2000);
    u8g2.setDrawColor(0);
    u8g2.drawBox(13,25,100,15);
    u8g2.sendBuffer();
    u8g2.setDrawColor(1);

    u8g2.drawStr(20, 30, "DEEP SPACE OBJECT");
    u8g2.drawStr(40, 38, "DETECTED");
    u8g2.sendBuffer();
    delay(2000);
    u8g2.setDrawColor(0);
    u8g2.drawBox(20,25,90,20);
    u8g2.sendBuffer();
    u8g2.setDrawColor(1);

    u8g2.drawStr(25, 30, "LONG RANGE SCAN");
    u8g2.drawStr(43, 38, "INITIATED");
    u8g2.sendBuffer();
    delay(2000);
    u8g2.setDrawColor(0);
    u8g2.drawBox(20,25,90,20);
    u8g2.sendBuffer();
    u8g2.setDrawColor(1);
    delay(100);
    clearOLED();
}


void cobraIII(void) {
  boot_sequence();
  ShipName = "COBRA MK.III";
  ShipType = "Combat Trader";
  ShipHyperspace = "Yes";
  ShipClass = "CF8";
  //ShipName = "Cobra Mk.III";
  memcpy(ship_vertices, cobraIII_vertices, sizeof(cobraIII_vertices));
  ship_vertices_cnt = cobraIII_vertices_cnt;
  scale = cobraIII_scale;
  memcpy(ship_faces, cobraIII_faces, sizeof(cobraIII_faces));
  ship_faces_cnt = cobraIII_faces_cnt;
  rotate_ship();
  clearOLED();
}

void adder(void) {
  boot_sequence();
  clearOLED();
  ShipName = "ADDER";
  ShipType = "Smuggler";
  ShipHyperspace = "Yes";
  ShipClass = "CF4";
  memcpy(ship_vertices, adder_vertices, sizeof(adder_vertices));
  ship_vertices_cnt = adder_vertices_cnt;
  scale = adder_scale;
  memcpy(ship_faces, adder_faces, sizeof(adder_faces));
  ship_faces_cnt = adder_faces_cnt;
  rotate_ship();
  clearOLED();
}

void asp(void) {
  boot_sequence();
  clearOLED();
  ShipName = "ASP";
  ShipType = "Pirate";
  ShipHyperspace = "Yes";
  ShipClass = "CF4";
  memcpy(ship_vertices, asp_vertices, sizeof(asp_vertices));
  ship_vertices_cnt = asp_vertices_cnt;
  scale = asp_scale;
  memcpy(ship_faces, asp_faces, sizeof(asp_faces));
  ship_faces_cnt = asp_faces_cnt;
  rotate_ship();
  clearOLED();
}

void anaconda(void) {
  boot_sequence();
  clearOLED();
  ShipName = "ANACONDA";
  ShipType = "Freighter";
  ShipHyperspace = "Yes";
  ShipClass = "CF3";
  memcpy(ship_vertices, anaconda_vertices, sizeof(anaconda_vertices));
  ship_vertices_cnt = anaconda_vertices_cnt;
  scale = anaconda_scale;
  memcpy(ship_faces, anaconda_faces, sizeof(anaconda_faces));
  ship_faces_cnt = anaconda_faces_cnt;
  rotate_ship();
  clearOLED();
}

void viper(void) {
  boot_sequence();
  clearOLED();
  ShipName = "VIPER";
  ShipType = "Police ship";
  ShipHyperspace = "No";
  ShipClass = "CF7.4";
  memcpy(ship_vertices, viper_vertices, sizeof(viper_vertices));
  ship_vertices_cnt = viper_vertices_cnt;
  scale = viper_scale;
  memcpy(ship_faces, viper_faces, sizeof(viper_faces));
  ship_faces_cnt = viper_faces_cnt;
  rotate_ship();
  clearOLED();
}

void sidewinder(void) {
  boot_sequence();
  clearOLED();
  ShipName = "SIDEWINDER";
  ShipType = "Scout ship";
  ShipHyperspace = "No";
  ShipClass = "CF9";
  memcpy(ship_vertices, sidewinder_vertices, sizeof(sidewinder_vertices));
  ship_vertices_cnt = sidewinder_vertices_cnt;
  scale = sidewinder_scale;
  memcpy(ship_faces, sidewinder_faces, sizeof(sidewinder_faces));
  ship_faces_cnt = sidewinder_faces_cnt;
  rotate_ship();
  clearOLED();
}

void coriolis(void) {
  boot_sequence();
  clearOLED();
  ShipName = "CORIOLIS STATION";
  ShipType = "Station";
  ShipHyperspace = "No";
  ShipClass = "N/A";
  memcpy(ship_vertices, coriolis_vertices, sizeof(coriolis_vertices));
  ship_vertices_cnt = coriolis_vertices_cnt;
  scale = coriolis_scale;
  memcpy(ship_faces, coriolis_faces, sizeof(coriolis_faces));
  ship_faces_cnt = coriolis_faces_cnt;
  rotate_ship();
  clearOLED();
}

void dodo(void) {
  boot_sequence();
  clearOLED();
  ShipName = "DODO STATION";
  ShipType = "Station";
  ShipHyperspace = "No";
  ShipClass = "N/A";
  memcpy(ship_vertices, dodo_vertices, sizeof(dodo_vertices));
  ship_vertices_cnt = dodo_vertices_cnt;
  scale = dodo_scale;
  memcpy(ship_faces, dodo_faces, sizeof(dodo_faces));
  ship_faces_cnt = dodo_faces_cnt;
  rotate_ship();
  clearOLED();
}

void thargoid(void) {
  boot_sequence();
  clearOLED();
  ShipName = "THARGOID";
  ShipType = "Alien";
  ShipHyperspace = "Yes";
  ShipClass = "CF6";
  memcpy(ship_vertices, thargoid_vertices, sizeof(thargoid_vertices));
  ship_vertices_cnt = thargoid_vertices_cnt;
  scale = thargoid_scale;
  memcpy(ship_faces, thargoid_faces, sizeof(thargoid_faces));
  ship_faces_cnt = thargoid_faces_cnt;
  rotate_ship();
  clearOLED();
}

void python(void) {
  boot_sequence();
  clearOLED();
  ShipName = "PYTHON";
  ShipType = "Trader";
  ShipHyperspace = "Yes";
  ShipClass = "CF3";
  memcpy(ship_vertices, python_vertices, sizeof(python_vertices));
  ship_vertices_cnt = python_vertices_cnt;
  scale = python_scale;
  memcpy(ship_faces, python_faces, sizeof(python_faces));
  ship_faces_cnt = python_faces_cnt;
  rotate_ship();
  clearOLED();
}

void cobraI(void) {
  boot_sequence();
  clearOLED();
  ShipName = "COBRA MK.I";
  ShipType = "Combat Trader";
  ShipHyperspace = "Yes";
  ShipClass = "CF3";
  memcpy(ship_vertices, cobraI_vertices, sizeof(cobraI_vertices));
  ship_vertices_cnt = cobraI_vertices_cnt;
  scale = cobraI_scale;
  memcpy(ship_faces, cobraI_faces, sizeof(cobraI_faces));
  ship_faces_cnt = cobraI_faces_cnt;
  rotate_ship();
  clearOLED();
}

void boa(void) {
  boot_sequence();
  clearOLED();
  ShipName = "BOA";
  ShipType = "Trader";
  ShipHyperspace = "Yes";
  ShipClass = "CF4";
  memcpy(ship_vertices, boa_vertices, sizeof(boa_vertices));
  ship_vertices_cnt = boa_vertices_cnt;
  scale = boa_scale;
  memcpy(ship_faces, boa_faces, sizeof(boa_faces));
  ship_faces_cnt = boa_faces_cnt;
  rotate_ship();
  clearOLED();
}

void ferdelance(void) {
  boot_sequence();
  clearOLED();
  ShipName = "FER DE LANCE";
  ShipType = "Combat Trader";
  ShipHyperspace = "Yes";
  ShipClass = "CF5";
  memcpy(ship_vertices, ferdelance_vertices, sizeof(ferdelance_vertices));
  ship_vertices_cnt = ferdelance_vertices_cnt;
  scale = ferdelance_scale;
  memcpy(ship_faces, ferdelance_faces, sizeof(ferdelance_faces));
  ship_faces_cnt = ferdelance_faces_cnt;
  rotate_ship();
  clearOLED();
}

void gecko(void) {
  boot_sequence();
  clearOLED();
  ShipName = "GECKO";
  ShipType = "Pirate";
  ShipHyperspace = "No";
  ShipClass = "CF7";
  memcpy(ship_vertices, gecko_vertices, sizeof(gecko_vertices));
  ship_vertices_cnt = gecko_vertices_cnt;
  scale = gecko_scale;
  memcpy(ship_faces, gecko_faces, sizeof(gecko_faces));
  ship_faces_cnt = gecko_faces_cnt;
  rotate_ship();
  clearOLED();
}

void krait(void) {
  boot_sequence();
  clearOLED();
  ShipName = "KRAIT";
  ShipType = "Fighter";
  ShipHyperspace = "No";
  ShipClass = "CF8";
  memcpy(ship_vertices, krait_vertices, sizeof(krait_vertices));
  ship_vertices_cnt = krait_vertices_cnt;
  scale = krait_scale;
  memcpy(ship_faces, krait_faces, sizeof(krait_faces));
  ship_faces_cnt = krait_faces_cnt;
  rotate_ship();
  clearOLED();
}

void mamba(void) {
  boot_sequence();
  clearOLED();
  ShipName = "MAMBA";
  ShipType = "Fighter";
  ShipHyperspace = "No";
  ShipClass = "CF9";
  memcpy(ship_vertices, mamba_vertices, sizeof(mamba_vertices));
  ship_vertices_cnt = mamba_vertices_cnt;
  scale = mamba_scale;
  memcpy(ship_faces, mamba_faces, sizeof(mamba_faces));
  ship_faces_cnt = mamba_faces_cnt;
  rotate_ship();
  clearOLED();
}

void moray(void) {
  boot_sequence();
  clearOLED();
  ShipName = "MORAY";
  ShipType = "Star Boat";
  ShipHyperspace = "Yes";
  ShipClass = "CF5";
  memcpy(ship_vertices, moray_vertices, sizeof(moray_vertices));
  ship_vertices_cnt = moray_vertices_cnt;
  scale = moray_scale;
  memcpy(ship_faces, moray_faces, sizeof(moray_faces));
  ship_faces_cnt = moray_faces_cnt;
  rotate_ship();
  clearOLED();
  
}

void asteroid(void) {
  boot_sequence();
  clearOLED();
  ShipName = "ASTEROID";
  ShipType = "Nav Hazard";
  ShipHyperspace = "No";
  ShipClass = "N/A";
  memcpy(ship_vertices, asteroid_vertices, sizeof(asteroid_vertices));
  ship_vertices_cnt = asteroid_vertices_cnt;
  scale = asteroid_scale;
  memcpy(ship_faces, asteroid_faces, sizeof(asteroid_faces));
  ship_faces_cnt = asteroid_faces_cnt;
  rotate_ship();
  clearOLED();
}
void boulder(void) {
  boot_sequence();
  clearOLED();
  ShipName = "BOULDER";
  ShipType = "Nav Hazard";
  ShipHyperspace = "No";
  ShipClass = "N/A";
  memcpy(ship_vertices, boulder_vertices, sizeof(boulder_vertices));
  ship_vertices_cnt = boulder_vertices_cnt;
  scale = boulder_scale;
  memcpy(ship_faces, boulder_faces, sizeof(boulder_faces));
  ship_faces_cnt = boulder_faces_cnt;
  rotate_ship();
  clearOLED();
}

void cargo(void) {
  boot_sequence();
  clearOLED();
  ShipName = "CARGO";
  ShipType = "Nav Hazard";
  ShipHyperspace = "No";
  ShipClass = "N/A";
  memcpy(ship_vertices, cargo_vertices, sizeof(cargo_vertices));
  ship_vertices_cnt = cargo_vertices_cnt;
  scale = cargo_scale;
  memcpy(ship_faces, cargo_faces, sizeof(cargo_faces));
  ship_faces_cnt = cargo_faces_cnt;
  rotate_ship();
  clearOLED();
}

void escape(void) {
  boot_sequence();
  clearOLED();
  ShipName = "ESCAPE CAPSULE";
  ShipType = "Nav Hazard";
  ShipHyperspace = "No";
  ShipClass = "N/A";
  memcpy(ship_vertices, escape_vertices, sizeof(escape_vertices));
  ship_vertices_cnt = escape_vertices_cnt;
  scale = escape_scale;
  memcpy(ship_faces, escape_faces, sizeof(escape_faces));
  ship_faces_cnt = escape_faces_cnt;
  rotate_ship();
  clearOLED();
}

void constrictor(void) {
  boot_sequence();
  clearOLED();
  ShipName = "CONSTRICTOR";
  ShipType = "Navy Vessel";
  ShipHyperspace = "Yes";
  ShipClass = "CF9";
  memcpy(ship_vertices, constrictor_vertices, sizeof(constrictor_vertices));
  ship_vertices_cnt = constrictor_vertices_cnt;
  scale = constrictor_scale;
  memcpy(ship_faces, constrictor_faces, sizeof(constrictor_faces));
  ship_faces_cnt = constrictor_faces_cnt;
  rotate_ship();
  clearOLED();
}

void thargon(void) {
  boot_sequence();
  clearOLED();
  ShipName = "THARGON";
  ShipType = "Alien";
  ShipHyperspace = "No";
  ShipClass = "CF6";
  memcpy(ship_vertices, thargon_vertices, sizeof(thargon_vertices));
  ship_vertices_cnt = thargon_vertices_cnt;
  scale = thargon_scale;
  memcpy(ship_faces, thargon_faces, sizeof(thargon_faces));
  ship_faces_cnt = thargon_faces_cnt;
  rotate_ship();
  clearOLED();
}

void worm(void) {
  boot_sequence();
  clearOLED();
  ShipName = "WORM";
  ShipType = "Landing Craft";
  ShipHyperspace = "No";
  ShipClass = "CF6";
  memcpy(ship_vertices, worm_vertices, sizeof(worm_vertices));
  ship_vertices_cnt = worm_vertices_cnt;
  scale = worm_scale;
  memcpy(ship_faces, worm_faces, sizeof(worm_faces));
  ship_faces_cnt = worm_faces_cnt;
  rotate_ship();
  clearOLED();
}

void missile(void) {
  boot_sequence();
  clearOLED();
  ShipName = "MISSILE";
  ShipType = "Ordinance";
  ShipHyperspace = "No";
  ShipClass = "CF10";
  memcpy(ship_vertices, missile_vertices, sizeof(missile_vertices));
  ship_vertices_cnt = missile_vertices_cnt;
  scale = missile_scale;
  memcpy(ship_faces, missile_faces, sizeof(missile_faces));
  ship_faces_cnt = missile_faces_cnt;
  rotate_ship();
  clearOLED();
}

void platelet(void) {
  boot_sequence();
  clearOLED();
  ShipName = "PLATELET";
  ShipType = "Nav Hazard";
  ShipHyperspace = "No";
  ShipClass = "N/A";
  memcpy(ship_vertices, platelet_vertices, sizeof(platelet_vertices));
  ship_vertices_cnt = platelet_vertices_cnt;
  scale = platelet_scale;
  memcpy(ship_faces, platelet_faces, sizeof(platelet_faces));
  ship_faces_cnt = platelet_faces_cnt;
  rotate_ship();
  clearOLED();
}

void shuttle(void) {
  boot_sequence();
  clearOLED();
  ShipName = "SHUTTLE";
  ShipType = "Cargo Shuttle";
  ShipHyperspace = "No";
  ShipClass = "CF4";
  memcpy(ship_vertices, shuttle_vertices, sizeof(shuttle_vertices));
  ship_vertices_cnt = shuttle_vertices_cnt;
  scale = worm_scale;
  memcpy(ship_faces, shuttle_faces, sizeof(shuttle_faces));
  ship_faces_cnt = shuttle_faces_cnt;
  rotate_ship_2();
  clearOLED();
}

void transport(void) {
  boot_sequence();
  clearOLED();
  ShipName = "TRANSPORTER";
  ShipType = "Cargo Shuttle";
  ShipHyperspace = "No";
  ShipClass = "CF4";
  memcpy(ship_vertices, transport_vertices, sizeof(transport_vertices));
  ship_vertices_cnt = transport_vertices_cnt;
  scale = transport_scale;
  memcpy(ship_faces, transport_faces, sizeof(transport_faces));
  ship_faces_cnt = transport_faces_cnt;
  rotate_ship();
  clearOLED();
}

void cougar(void) {
  boot_sequence();
  clearOLED();
  ShipName = "***";
  ShipType = "***";
  ShipHyperspace = "***";
  ShipClass = "***";
  memcpy(ship_vertices, cougar_vertices, sizeof(cougar_vertices));
  ship_vertices_cnt = cougar_vertices_cnt;
  scale = cougar_scale;
  memcpy(ship_faces, cougar_faces, sizeof(cougar_faces));
  ship_faces_cnt = cougar_faces_cnt;
  rotate_ship();
  clearOLED();
}

void loop(void)
{

int randompick = random(1,30); 

 switch(randompick)
  {
  case 1:
    adder();
  break;

  case 2:
    anaconda();
  break;

  case 3:
    asp();
  break;

  case 4:
    asteroid();
  break;

  case 5:
    cargo();
  break;

  case 6:
    boa();
  break;

  case 7:
    boulder();
  break;

  case 8:
    escape();
  break;

  case 9:
    cobraIII();
  break;

  case 10:
    cobraI();
  break;

  case 11:
    constrictor();
  break;

  case 12:
    coriolis();
  break;

  case 13:
    cougar();
  break;

  case 14:
    dodo();
  break;

  case 15:
    ferdelance();
  break;

  case 16:
    gecko();
  break;

  case 17:
    krait();
  break;

  case 18:
    mamba();
  break;

  case 19:
    missile();
  break;

  case 20:
    moray();
  break;

  case 21:
    platelet();
  break;

  case 22:
    python();
  break;

  case 23:
    sidewinder();
  break;

  case 24:
    shuttle();
  break;

  case 25:
    thargon();
  break;

  case 26:
    thargoid();
  break;

  case 27:
    transport();
  break;

  case 28:
    viper();
  break;

  case 29:
    worm();
  break;
  }

  int randomdelay = random(5,11); 
  delay(randomdelay*1000);
  
  /*cobraIII();
  adder();
  asp();
  anaconda();
  viper();
  sidewinder();
  coriolis();
  dodo();
  thargoid();
  python();
  cobraI();
  boa();
  ferdelance();
  gecko();
  krait();
  mamba();
  moray();
  asteroid();
  boulder();
  cargo();
  escape();
  constrictor();
  thargon();
  worm();
  missile();
  platelet();
  shuttle();
  transport();
  cougar();
*/

/*
  //this simple cube is useful for testing - Uncomment cube data in ships.h
  clearOLED();
  ShipName = "Cube";
  memcpy(ship_vertices, cube_vertices, sizeof(cube_vertices));
  ship_vertices_cnt = cube_vertices_cnt;
  scale = cube_scale;
  memcpy(ship_faces, cube_faces, sizeof(cube_faces));
  ship_faces_cnt = cube_faces_cnt;
  rotate_ship();
*/

}
