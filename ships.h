int cobra_vertices_cnt = 28;
int cobra_scale = 2;
int cobra_vertices[28][3] = {
 { 32 , 0 , 76 },   //  0
 { -32 , 0 , 76 },  //  1
 { 0 , 26 , 24 },   //  2
 { -120 , -3 , -8 },  //  3
 { 120 , -3 , -8 },   //  4
 { -88 , 16 , -40 },  //  5
 { 88 , 16 , -40 },   //  6
 { 128 , -8 , -40 },  //  7
 { -128 , -8 , -40 },   //  8
 { 0 , 26 , -40 },  //  9
 { -32 , -24 , -40 },   //  10
 { 32 , -24 , -40 },  //  11
 { -36 , 8 , -40 },   //  12
 { -8 , 12 , -40 },   //  13
 { 8 , 12 , -40 },  //  14
 { 36 , 8 , -40 },  //  15
 { 36 , -12 , -40 },  //  16
 { 8 , -16 , -40 },   //  17
 { -8 , -16 , -40 },  //  18
 { -36 , -12 , -40 },   //  19
 { 0 , 0 , 76 },  //  20
 { 0 , 0 , 90 },  //  21
 { -80 , -6 , -40 },  //  22
 { -80 , 6 , -40 },   //  23
 { -88 , 0 , -40 },   //  24
 { 80 , 6 , -40 },  //  25
 { 88 , 0 , -40 },  //  26
 { 80 , -6 , -40 }  //  27
};

int cobra_faces_cnt = 17;
int cobra_faces[17][9] = {
  { 3, 0, 1, 2, 0, 0, 0, 0, 0 },     //0
  { 3, 2, 1, 5, 0, 0, 0, 0, 0 },     //1
  { 3, 0, 2, 6, 0, 0, 0, 0, 0 },     //2
  { 3, 5, 1, 3, 0, 0, 0, 0, 0 },     //3
  { 3, 0, 6, 4, 0, 0, 0, 0, 0 },     //4
  { 3, 9, 2, 5, 0, 0, 0, 0, 0 },     //5
  { 3, 9, 6, 2, 0, 0, 0, 0, 0 },     //6
  { 3, 8, 5, 3, 0, 0, 0, 0, 0 },     //7
  { 3, 4, 6, 7, 0, 0, 0, 0, 0 },     //8
  { 7, 6, 9, 5, 8, 10, 11, 7, 0 },   //9
  { 4, 10, 8, 3, 1, 0, 0, 0, 0 },    //10
  { 4, 10, 1, 0, 11, 0, 0, 0, 0 },   //11
  { 4, 11, 0, 4, 7, 0, 0, 0, 0 },    //12
  { 4, 17, 16, 15, 14, 0, 0, 0, 0 }, //13
  { 4, 19, 18, 13, 12, 0, 0, 0, 0 }, //14
  { 3, 22, 23, 24, 0, 0, 0, 0, 0 },  //15
  { 3, 26, 25, 27, 0, 0, 0, 0, 0 }   //16
};

int adder_vertices_cnt = 18;
int adder_scale = 1;
int adder_vertices[18][3] = {
 { -18 , 0 , 40 },   //  0
 { 18 , 0 , 40 },   //  1
 { 30 , 0 , -24 },  //  2
 { 30 , 0 , -40 },  //  3
 { 18 , -7 , -40 },   //  4
 { -18 , -7 , -40 },  //  5
 { -30 , 0 , -40 },   //  6
 { -30 , 0 , -24 },   //  7
 { -18 , 7 , -40 },   //  8
 { 18 , 7 , -40 },  //  9
 { -18 , 7 , 13 },  //  10
 { 18 , 7 , 13 },   //  11
 { -18 , -7 , 13 },   //  12
 { 18 , -7 , 13 },  //  13
 { -11 , 3 , 29 },  //  14
 { 11 , 3 , 29 },   //  15
 { 11 , 4 , 24 },   //  16
 { -11 , 4 , 24 }  //  17
};

int adder_faces_cnt = 14;
int adder_faces[14][9] = {
  { 4, 11, 1, 0, 10, 0, 0, 0, 0 }, //  0
  { 4, 13, 12, 0, 1, 0, 0, 0, 0 }, //  1
  { 3, 2, 1, 11, 0, 0, 0, 0, 0 }, //  2
  { 3, 13, 1, 2, 0, 0, 0, 0, 0 }, //  3
  { 4, 2, 11, 9, 3, 0, 0, 0, 0 }, //  4
  { 4, 4, 13, 2, 3, 0, 0, 0, 0 }, //  5
  { 6, 9, 8, 6, 5, 4, 3, 0, 0 }, // 6
  { 4, 10, 7, 6, 8, 0, 0, 0, 0 }, //  7
  { 4, 12, 5, 6, 7, 0, 0, 0, 0 }, //  8
  { 3, 10, 0, 7, 0, 0, 0, 0, 0 }, //  9
  { 3, 12, 7, 0, 0, 0, 0, 0, 0 }, //  10
  { 4, 10, 8, 9, 11, 0, 0, 0, 0 }, //  11
  { 4, 12, 13, 4, 5, 0, 0, 0, 0 }, //  12
  { 4, 17, 16, 15, 14, 0, 0, 0, 0 } //  13
};

int asp_vertices_cnt = 17;
int asp_scale = 1;
int asp_vertices[17][3] = {
  { 0, -18, 0 }, //  0
  { 0, -9, -45 }, //  1
  { 43, 0, -45 }, //  2
  { 69, -3, 0 }, //  3
  { 43, -14, 28 }, //  4
  { -43, 0, -45 }, //  5
  { -69, -3, 0 }, //  6
  { -43, -14, 28 }, //  7
  { 26, -7, 73 }, //  8
  { -26, -7, 73 }, //  9
  { 43, 14, 28 }, //  10
  { -43, 14, 28 }, //  11
  { 0, 9, -45 }, //  12
  { -17, 0, -45 }, //  13
  { 17, 0, -45 }, //  14
  { 0, -4, -45 }, //  15
  { 0, 4, -45 }, //  16
};

int asp_faces_cnt = 13;
int asp_faces[13][9] = {
  { 5, 4, 0, 7, 9, 8, 0, 0, 0 }, //  0
  { 5, 2, 1, 0, 4, 3, 0, 0, 0 }, //  1
  { 5, 5, 6, 7, 0, 1, 0, 0, 0 }, //  2
  { 3, 12, 10, 11, 0, 0, 0, 0, 0 }, //  3
  { 4, 11, 10, 8, 9, 0, 0, 0, 0 }, //  4
  { 4, 6, 5, 12, 11, 0, 0, 0, 0 }, //  5
  { 4, 3, 10, 12, 2, 0, 0, 0, 0 }, //  6
  { 3, 3, 4, 8, 0, 0, 0, 0, 0 }, //  7
  { 3, 9, 7, 6, 0, 0, 0, 0, 0 }, //  8
  { 3, 8, 10, 3, 0, 0, 0, 0, 0 }, //  9
  { 3, 6, 11, 9, 0, 0, 0, 0, 0 }, //  10
  { 4, 12, 5, 1, 2, 0, 0, 0, 0 }, //  11
  { 4, 16, 13, 15, 14, 0, 0, 0, 0 }  //  12
};

int anaconda_vertices_cnt = 15;
int anaconda_scale = 2;
int anaconda_vertices[15][3] = {
 { 0 , 4 , -29 },   //  0
 { -22 , -7 , -19 },   //  1
 { -13 , -24 , -2 },   //  2
 { 13 , -24 , -2 },   //  3
 { 22 , -7 , -19 },   //  4
 { 0 , 24 , -25 },   //  5
 { -35 , 8 , -8 },   //  6
 { -22 , -20 , 20 },   //  7
 { 22 , -20 , 20 },   //  8
 { 35 , 8 , -8 },   //  9
 { -22 , 27 , -12 },   //  10
 { -35 , -1 , 16 },   //  11
 { 0 , 0 , 127 },   //  12
 { 35 , -1 , 16 },   //  13
 { 22 , 27 , -12 }   //  14
};

int anaconda_faces_cnt = 12;
int anaconda_faces[12][9] = {
{ 5, 4, 0, 1, 2, 3, 0, 0, 0 },  //  0
//{ 5, 6, 10, 5, 0, 1, 0, 0, 0 },  //  1
{ 5, 1, 0, 5, 10, 6, 0, 0, 0 },  //  1
{ 5, 2, 1, 6, 11, 7, 0, 0, 0 },  //  2
{ 5, 3, 2, 7, 12, 8, 0, 0, 0 },  //  3
{ 5, 4, 3, 8, 13, 9, 0, 0, 0 },  //  4
{ 5, 14, 5, 0, 4, 9, 0, 0, 0 },  //  5
{ 3, 5, 14, 10, 0, 0, 0, 0, 0 },  //  6
{ 4, 12, 11, 6, 10, 0, 0, 0, 0 },  //  7
{ 3, 11, 12, 7, 0, 0, 0, 0, 0 },  //  8
{ 3, 12, 13, 8, 0, 0, 0, 0, 0 },  //  9
{ 4, 12, 14, 9, 13, 0, 0, 0, 0 },  //  10
{ 3, 14, 12, 10, 0, 0, 0, 0, 0 }  //  11
};

int viper_vertices_cnt = 15;
int viper_scale = 1;
int viper_vertices[15][3] = {
 { 0 , 0 , 72 },   //  0
 { 0 , 16 , 24 },   //  1
 { 0 , -16 , 24 },  //  2
 { 48 , 0 , -24 },  //  3
 { -48 , 0 , -24 },   //  4
 { 24 , -16 , -24 },  //  5
 { -24 , -16 , -24 },   //  6
 { 24 , 16 , -24 },   //  7
 { -24 , 16 , -24 },  //  8
 { -32 , 0 , -24 },   //  9
 { 32 , 0 , -24 },  //  10
 { 8 , 8 , -24 },   //  11
 { -8 , 8 , -24 },  //  12
 { -8 , -8 , -24 },   //  13
 { 8 , -8 , -24 }  //  14
};

int viper_faces_cnt = 9;
int viper_faces[9][9] = {
  { 3, 7, 1, 8, 0, 0, 0, 0, 0 },
  { 4, 0, 4, 8, 1, 0, 0, 0, 0 },
  { 4, 1, 7, 3, 0, 0, 0, 0, 0 },
  { 4, 6, 4, 0, 2, 0, 0, 0, 0 },
  { 4, 3, 5, 2, 0, 0, 0, 0, 0 },
  { 3, 5, 6, 2, 0, 0, 0, 0, 0 },
  { 6, 6, 5, 3, 7, 8, 4, 0, 0 },
  { 3, 13, 12, 9, 0, 0, 0, 0, 0 },
  { 3, 11, 14, 10, 0, 0, 0, 0, 0 }
};

int sidewinder_vertices_cnt = 10;
int sidewinder_scale = 1;
int sidewinder_vertices[10][3] = {
 { -32 , 0 , 36 },   //  0
 { 32 , 0 , 36 },   //  1
 { 64 , 0 , -28 },  //  2
 { -64 , 0 , -28 },   //  3
 { 0 , 16 , -28 },  //  4
 { 0 , -16 , -28 },   //  5
 { -12 , 6 , -28 },   //  6
 { 12 , 6 , -28 },  //  7
 { 12 , -6 , -28 },   //  8
 { -12 , -6 , -28 }  //  9
};

int sidewinder_faces_cnt = 8;
int sidewinder_faces[8][9] = {
  { 3, 1, 0, 4, 0, 0, 0, 0, 0 }, //  0
  { 3, 0, 3, 4, 0, 0, 0, 0, 0 }, //  1
  { 3, 1, 4, 2, 0, 0, 0, 0, 0 }, //  2
  { 4, 2, 4, 3, 5, 0, 0, 0, 0 }, //  3
  { 3, 3, 0, 5, 0, 0, 0, 0, 0 }, //  4
  { 3, 5, 0, 1, 0, 0, 0, 0, 0 }, //  5
  { 3, 5, 1, 2, 0, 0, 0, 0, 0 }, //  6
  { 4, 8, 7, 6, 9, 0, 0, 0, 0 }  //  7
};

int dodo_vertices_cnt = 24;
int dodo_scale = 4;
int dodo_vertices[24][3] = {
 { 0 , 150 , 196 },   //  0
 { 143 , 46 , 196 },  //  1
 { 88 , -121 , 196 },   //  2
 { -88 , -121 , 196 },  //  3
 { -143 , 46 , 196 },   //  4
 { 0 , 243 , 46 },  //  5
 { 231 , 75 , 46 },   //  6
 { 143 , -196 , 46 },   //  7
 { -143 , -196 , 46 },  //  8
 { -231 , 75 , 46 },  //  9
 { 143 , 196 , -46 },   //  10
 { 231 , -75 , -46 },   //  11
 { 0 , -243 , -46 },  //  12
 { -231 , -75 , -46 },  //  13
 { -143 , 196 , -46 },  //  14
 { 88 , 121 , -196 },   //  15
 { 143 , -46 , -196 },  //  16
 { 0 , -150 , -196 },   //  17
 { -143 , -46 , -196 },   //  18
 { -88 , 121 , -196 },  //  19
 { -16 , 32 , 196 },  //  20
 { -16 , -32 , 196 },   //  21
 { 16 , 32 , 196 },   //  22
 { 16 , -32 , 196 }  //  23
};

int dodo_faces_cnt = 13;
int dodo_faces[13][9] = {
  { 5, 3, 2, 1, 0, 4, 0, 0, 0 },  //  0
  { 5, 6, 10, 5, 0, 1, 0, 0, 0 },  //  1
  { 5, 7, 11, 6, 1, 2, 0, 0, 0 },  //  2
  { 5, 8, 12, 7, 2, 3, 0, 0, 0 },  //  3
  { 5, 9, 13, 8, 3, 4, 0, 0, 0 },  //  4
  { 5, 5, 14, 9, 4, 0, 0, 0, 0 },  //  5
  { 5, 15, 19, 14, 5, 10, 0, 0, 0 }, //  6
  { 5, 16, 15, 10, 6, 11, 0, 0, 0 }, //  7
  { 5, 17, 16, 11, 7, 12, 0, 0, 0 }, //  8
  { 5, 18, 17, 12, 8, 13, 0, 0, 0 }, //  9
  { 5, 19, 18, 13, 9, 14, 0, 0, 0 }, //  10
  { 5, 19, 15, 16, 17, 18, 0, 0, 0 },  //  11
  { 4, 21, 23, 22, 20, 0, 0, 0, 0 }   //  12
};

int coriolis_vertices_cnt = 16;
int coriolis_scale = 4;
int coriolis_vertices[16][3] = {
 { 160 , 0 , 160 },   //  0
 { 0 , 160 , 160 },   //  1
 { -160 , 0 , 160 },  //  2
 { 0 , -160 , 160 },  //  3
 { 160 , -160 , 0 },  //  4
 { 160 , 160 , 0 },   //  5
 { -160 , 160 , 0 },  //  6
 { -160 , -160 , 0 },   //  7
 { 160 , 0 , -160 },  //  8
 { 0 , 160 , -160 },  //  9
 { -160 , 0 , -160 },   //  10
 { 0 , -160 , -160 },   //  11
 { 10 , -30 , 160 },  //  12
 { 10 , 30 , 160 },   //  13
 { -10 , 30 , 160 },  //  14
 { -10 , -30 , 160 }   //  15
};

int coriolis_faces_cnt = 15;
int coriolis_faces[15][9] = {
  { 4, 1, 2, 3, 0, 0, 0, 0, 0 },  //  0
  { 3, 4, 0, 3, 0, 0, 0, 0, 0 }, //  1
  { 3, 5, 1, 0, 0, 0, 0, 0, 0 }, //  2
  { 3, 1, 6, 2, 0, 0, 0, 0, 0 }, //  3
  { 3, 2, 7, 3, 0, 0, 0, 0, 0 }, //  4
  { 4, 11, 4, 3, 7, 0, 0, 0, 0 },  //  5
  { 4, 8, 5, 0, 4, 0, 0, 0, 0 }, //  6
  { 4, 10, 7, 2, 6, 0, 0, 0, 0 },  //  7
  { 4, 6, 1, 5, 9, 0, 0, 0, 0 }, //  8
  { 3, 11, 7, 10, 8, 5, 9, 6, 0 }, //  9
  { 3, 8, 4, 11, 8, 0, 0, 0, 0 },  //  10
  { 3, 9, 5, 8, 1, 0, 0, 0, 0 }, //  11
  { 3, 10, 6, 9, 7, 0, 0, 0, 0 },  //  12
  { 4, 11, 10, 9, 8, 0, 0, 0, 0 }, //  13
  { 4, 15, 12, 13, 14, 0, 0, 0, 0 } //  14
};

int thargoid_vertices_cnt = 20;
int thargoid_scale = 3;
int thargoid_vertices[20][3] = {
 { 32 , -48 , 48 },   //  0
 { 32 , -68 , 0 },  //  1
 { 32 , -48 , -48 },  //  2
 { 32 , 0 , -68 },  //  3
 { 32 , 48 , -48 },   //  4
 { 32 , 68 , 0 },   //  5
 { 32 , 48 , 48 },  //  6
 { 32 , 0 , 68 },   //  7
 { -24 , -116 , 116 },  //  8
 { -24 , -164 , 0 },  //  9
 { -24 , -116 , -116 },   //  10
 { -24 , 0 , -164 },  //  11
 { -24 , 116 , -116 },  //  12
 { -24 , 164 , 0 },   //  13
 { -24 , 116 , 116 },   //  14
 { -24 , 0 , 164 },   //  15
 { -24 , 64 , 80 },   //  16
 { -24 , 64 , -80 },  //  17
 { -24 , -64 , -80 },   //  18
 { -24 , -64 , 80 }  //  19
};

int thargoid_faces_cnt = 10;
int thargoid_faces[10][9] = {
{ 4, 9, 8, 0, 1, 0, 0, 0, 0 },  //  0
{ 4, 10, 9, 1, 2, 0, 0, 0, 0 },  //  1
{ 4, 11, 10, 2, 3, 0, 0, 0, 0 },  //  2
{ 4, 12, 11, 3, 4, 0, 0, 0, 0 },  //  3
{ 8, 7, 6, 5, 4, 3, 2, 1, 0 },  //  4
{ 4, 13, 12, 4, 5, 0, 0, 0, 0 },  //  5
{ 4, 14, 13, 5, 6, 0, 0, 0, 0 },  //  6
{ 4, 15, 14, 6, 7, 0, 0, 0, 0 },  //  7
{ 4, 15, 7, 0, 8, 0, 0, 0, 0 },  //  8
{ 8, 8, 9, 10, 11, 12, 13, 14, 15 }  //  9
};
