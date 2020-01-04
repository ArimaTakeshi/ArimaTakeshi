xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 153;
 0.13017;2.18264;1.38618;,
 1.12342;2.44912;-0.22886;,
 -0.02853;2.65497;-0.27807;,
 1.23655;2.02743;1.39437;,
 0.43512;0.71841;2.27480;,
 1.45761;0.65131;2.17335;,
 0.62176;-1.01150;1.62578;,
 1.58787;-1.04064;1.58933;,
 0.61375;-1.67628;-0.32786;,
 1.64463;-1.77288;-0.34526;,
 -0.06003;1.87922;-1.80510;,
 1.12813;1.68210;-1.76034;,
 0.07624;0.50453;-2.60528;,
 1.25972;0.34902;-2.55321;,
 0.33140;-1.04764;-2.14188;,
 1.64463;-1.77288;-0.34526;,
 0.61375;-1.67628;-0.32786;,
 1.64463;-1.77288;-0.34526;,
 1.46524;-1.15105;-2.12454;,
 2.84997;1.68627;-1.64964;,
 4.51103;0.42880;-2.26250;,
 2.95454;0.39006;-2.43813;,
 4.42726;1.75922;-1.54216;,
 2.87842;2.35174;-0.17010;,
 4.49031;2.37619;-0.12513;,
 3.12229;-1.06313;-2.05315;,
 4.61979;-0.97420;-1.86003;,
 3.25157;-1.64622;-0.32616;,
 4.72703;-1.57199;-0.27271;,
 1.64463;-1.77288;-0.34526;,
 1.64463;-1.77288;-0.34526;,
 3.23606;-0.81435;1.47117;,
 4.72703;-1.57199;-0.27271;,
 4.76242;-0.74010;1.42503;,
 4.72703;-1.57199;-0.27271;,
 3.25157;-1.64622;-0.32616;,
 3.25157;-1.64622;-0.32616;,
 3.25157;-1.64622;-0.32616;,
 3.15196;0.76783;2.05468;,
 4.72123;0.75830;2.01713;,
 2.99253;2.01178;1.34360;,
 4.59653;1.96268;1.37020;,
 5.97987;1.94608;1.39586;,
 5.87587;2.48797;-0.20317;,
 7.15020;1.99311;1.32886;,
 7.33468;2.53536;-0.31138;,
 6.07889;0.77082;2.10954;,
 7.08541;0.77707;2.11829;,
 6.06460;-0.64822;1.42960;,
 7.09358;-0.71542;1.41994;,
 5.95329;-1.56139;-0.25096;,
 4.72703;-1.57199;-0.27271;,
 7.24691;-1.63638;-0.27828;,
 5.87018;-0.93432;-1.72200;,
 5.95329;-1.56139;-0.25096;,
 7.45092;-0.99698;-1.81807;,
 5.95329;-1.56139;-0.25096;,
 5.95329;-1.56139;-0.25096;,
 7.24691;-1.63638;-0.27828;,
 5.84108;0.44713;-2.10546;,
 7.54175;0.43849;-2.16754;,
 5.79268;1.84159;-1.64047;,
 7.48210;1.86119;-1.75449;,
 8.93649;-1.04403;-1.90758;,
 8.99269;0.40103;-2.26750;,
 8.71806;-1.63736;-0.25616;,
 7.24691;-1.63638;-0.27828;,
 10.58507;-0.97122;-1.78426;,
 10.60400;0.33937;-2.19084;,
 10.44668;-1.44329;-0.18085;,
 8.95889;1.80948;-1.75225;,
 10.53180;2.40510;-0.54524;,
 10.56408;1.65269;-1.71910;,
 8.89118;2.55736;-0.41632;,
 8.59561;-0.77973;1.44387;,
 10.33832;0.90643;1.90274;,
 8.65769;0.82476;2.00375;,
 10.32231;-0.59787;1.45459;,
 8.71806;-1.63736;-0.25616;,
 8.71806;-1.63736;-0.25616;,
 10.44668;-1.44329;-0.18085;,
 8.71806;-1.63736;-0.25616;,
 8.77376;2.11117;1.14007;,
 10.45145;2.09785;0.93690;,
 12.27999;1.46113;-1.57014;,
 12.23318;2.15642;-0.60190;,
 12.32488;0.30668;-2.00387;,
 13.83692;1.27789;-1.47602;,
 13.80211;1.86362;-0.62926;,
 13.88770;0.28009;-1.87163;,
 12.15623;1.93626;0.78618;,
 13.75322;1.71159;0.60225;,
 12.15315;0.90827;1.75715;,
 13.80513;0.84774;1.56089;,
 12.19166;-0.49242;1.33883;,
 13.85681;-0.43503;1.18259;,
 12.28912;-1.22140;-0.16024;,
 10.44668;-1.44329;-0.18085;,
 13.90729;-1.03394;-0.18059;,
 12.35124;-0.81448;-1.56791;,
 12.28912;-1.22140;-0.16024;,
 13.92414;-0.66827;-1.42765;,
 12.28912;-1.22140;-0.16024;,
 12.28912;-1.22140;-0.16024;,
 13.90729;-1.03394;-0.18059;,
 15.31379;-0.60110;-1.38574;,
 13.90729;-1.03394;-0.18059;,
 13.90729;-1.03394;-0.18059;,
 15.32750;-0.91825;-0.18263;,
 16.56627;-0.58045;-1.32776;,
 16.65213;-0.80841;-0.18197;,
 15.25710;0.21480;-1.80622;,
 16.54497;0.14204;-1.85614;,
 15.24184;1.12111;-1.47948;,
 15.26967;1.66796;-0.69399;,
 16.55085;0.99950;-1.54549;,
 16.63529;1.54302;-0.82984;,
 15.34437;-0.40091;1.07817;,
 15.32442;0.80247;1.37885;,
 16.75903;-0.35956;1.07928;,
 16.79599;0.79828;1.24585;,
 15.32750;-0.91825;-0.18263;,
 15.32750;-0.91825;-0.18263;,
 16.65213;-0.80841;-0.18197;,
 15.32750;-0.91825;-0.18263;,
 16.65213;-0.80841;-0.18197;,
 15.27002;1.59103;0.44742;,
 16.70706;1.49318;0.27121;,
 17.55942;-0.62587;-1.26485;,
 17.55942;-0.62587;-1.26485;,
 17.69882;-0.77639;-0.12289;,
 17.53529;0.06153;-1.80841;,
 17.53529;0.06153;-1.80841;,
 17.55942;-0.62587;-1.26485;,
 17.89720;0.74113;1.28146;,
 17.89720;0.74113;1.28146;,
 17.83823;1.40501;0.20573;,
 17.69882;-0.77639;-0.12289;,
 16.65213;-0.80841;-0.18197;,
 17.69882;-0.77639;-0.12289;,
 17.80573;-0.34464;1.04089;,
 17.83823;1.40501;0.20573;,
 17.83823;1.40501;0.20573;,
 17.77058;1.43718;-0.97028;,
 17.80573;-0.34464;1.04089;,
 17.80573;-0.34464;1.04089;,
 17.89720;0.74113;1.28146;,
 17.65040;0.91015;-1.64938;,
 17.65040;0.91015;-1.64938;,
 17.53529;0.06153;-1.80841;,
 17.77058;1.43718;-0.97028;,
 17.77058;1.43718;-0.97028;,
 17.65040;0.91015;-1.64938;;
 
 192;
 3;0,1,2;,
 3;1,0,3;,
 3;4,3,0;,
 3;3,4,5;,
 3;6,5,4;,
 3;5,6,7;,
 3;8,7,6;,
 3;7,8,9;,
 3;10,1,11;,
 3;1,10,2;,
 3;12,11,13;,
 3;11,12,10;,
 3;14,15,16;,
 3;17,14,18;,
 3;12,18,14;,
 3;18,12,13;,
 3;19,20,21;,
 3;20,19,22;,
 3;23,22,19;,
 3;22,23,24;,
 3;11,21,13;,
 3;21,11,19;,
 3;1,19,11;,
 3;19,1,23;,
 3;25,20,26;,
 3;20,25,21;,
 3;18,21,25;,
 3;21,18,13;,
 3;27,26,28;,
 3;26,27,25;,
 3;29,25,27;,
 3;25,30,18;,
 3;31,32,33;,
 3;34,31,35;,
 3;7,36,31;,
 3;37,7,9;,
 3;38,33,39;,
 3;33,38,31;,
 3;5,31,38;,
 3;31,5,7;,
 3;40,39,41;,
 3;39,40,38;,
 3;3,38,40;,
 3;38,3,5;,
 3;23,41,24;,
 3;41,23,40;,
 3;1,40,23;,
 3;40,1,3;,
 3;42,24,41;,
 3;24,42,43;,
 3;44,43,42;,
 3;43,44,45;,
 3;46,41,39;,
 3;41,46,42;,
 3;47,42,46;,
 3;42,47,44;,
 3;48,39,33;,
 3;39,48,46;,
 3;49,46,48;,
 3;46,49,47;,
 3;50,33,51;,
 3;33,50,48;,
 3;52,48,50;,
 3;48,52,49;,
 3;53,28,26;,
 3;28,53,54;,
 3;55,56,53;,
 3;57,55,58;,
 3;59,26,20;,
 3;26,59,53;,
 3;60,53,59;,
 3;53,60,55;,
 3;61,20,22;,
 3;20,61,59;,
 3;62,59,61;,
 3;59,62,60;,
 3;43,22,24;,
 3;22,43,61;,
 3;45,61,43;,
 3;61,45,62;,
 3;63,60,64;,
 3;60,63,55;,
 3;65,55,63;,
 3;55,65,66;,
 3;67,64,68;,
 3;64,67,63;,
 3;69,63,67;,
 3;63,69,65;,
 3;70,71,72;,
 3;71,70,73;,
 3;62,73,70;,
 3;73,62,45;,
 3;64,72,68;,
 3;72,64,70;,
 3;60,70,64;,
 3;70,60,62;,
 3;74,75,76;,
 3;75,74,77;,
 3;78,77,74;,
 3;77,79,80;,
 3;49,76,47;,
 3;76,49,74;,
 3;52,74,49;,
 3;74,52,81;,
 3;82,75,83;,
 3;75,82,76;,
 3;44,76,82;,
 3;76,44,47;,
 3;73,83,71;,
 3;83,73,82;,
 3;45,82,73;,
 3;82,45,44;,
 3;84,71,85;,
 3;71,84,72;,
 3;86,72,84;,
 3;72,86,68;,
 3;87,85,88;,
 3;85,87,84;,
 3;89,84,87;,
 3;84,89,86;,
 3;90,71,83;,
 3;71,90,85;,
 3;91,85,90;,
 3;85,91,88;,
 3;92,83,75;,
 3;83,92,90;,
 3;93,90,92;,
 3;90,93,91;,
 3;94,75,77;,
 3;75,94,92;,
 3;95,92,94;,
 3;92,95,93;,
 3;96,77,97;,
 3;77,96,94;,
 3;98,94,96;,
 3;94,98,95;,
 3;99,69,67;,
 3;69,99,100;,
 3;101,102,99;,
 3;103,101,104;,
 3;86,67,68;,
 3;67,86,99;,
 3;89,99,86;,
 3;99,89,101;,
 3;105,106,101;,
 3;107,105,108;,
 3;109,108,105;,
 3;108,109,110;,
 3;111,101,89;,
 3;101,111,105;,
 3;112,105,111;,
 3;105,112,109;,
 3;113,88,114;,
 3;88,113,87;,
 3;111,87,113;,
 3;87,111,89;,
 3;115,114,116;,
 3;114,115,113;,
 3;112,113,115;,
 3;113,112,111;,
 3;117,93,95;,
 3;93,117,118;,
 3;119,118,117;,
 3;118,119,120;,
 3;121,95,98;,
 3;95,122,117;,
 3;123,117,124;,
 3;117,125,119;,
 3;126,88,91;,
 3;88,126,114;,
 3;127,114,126;,
 3;114,127,116;,
 3;118,91,93;,
 3;91,118,126;,
 3;120,126,118;,
 3;126,120,127;,
 3;128,110,109;,
 3;110,129,130;,
 3;131,109,112;,
 3;109,132,133;,
 3;134,127,120;,
 3;127,135,136;,
 3;137,119,138;,
 3;119,139,140;,
 3;141,116,127;,
 3;116,142,143;,
 3;144,120,119;,
 3;120,145,146;,
 3;147,112,115;,
 3;112,148,149;,
 3;150,115,116;,
 3;115,151,152;;
 
 MeshMaterialList {
  1;
  192;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.721569;0.570980;0.360784;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  140;
  0.104617;0.988976;-0.104797;,
  0.179249;0.978359;-0.103366;,
  0.128218;0.869149;0.477640;,
  0.069960;0.707860;0.702880;,
  0.093502;0.251047;0.963448;,
  0.079996;-0.059163;0.995038;,
  0.029210;-0.590705;0.806359;,
  0.047617;-0.792949;0.607424;,
  -0.048979;-0.940351;0.336661;,
  -0.006133;-0.935290;0.353829;,
  0.088235;0.663136;-0.743280;,
  0.157208;0.782805;-0.602081;,
  0.062379;0.133793;-0.989044;,
  0.059143;0.126406;-0.990214;,
  -0.069026;-0.805172;-0.589011;,
  0.019386;-0.549080;-0.835545;,
  0.077575;0.155997;-0.984707;,
  0.076634;0.145235;-0.986425;,
  0.043729;0.739879;-0.671317;,
  -0.043975;0.806524;-0.589563;,
  0.017308;0.995666;-0.091376;,
  -0.036572;0.999236;0.013801;,
  0.111561;-0.673287;-0.730916;,
  0.103542;-0.675341;-0.730201;,
  0.047924;-0.928547;-0.368108;,
  0.078596;-0.938975;-0.334887;,
  0.036604;-0.670114;0.741355;,
  0.087625;-0.668322;0.738693;,
  -0.010260;0.050749;0.998659;,
  0.043114;0.081434;0.995746;,
  -0.011482;0.791339;0.611270;,
  0.025887;0.799337;0.600325;,
  -0.011554;0.788282;0.615206;,
  -0.058109;0.997340;-0.043994;,
  0.011851;0.792143;0.610221;,
  -0.031485;0.997434;-0.064304;,
  -0.031451;0.040930;0.998667;,
  0.030292;0.171896;0.984649;,
  -0.015473;-0.680818;0.732289;,
  -0.012931;-0.590450;0.806971;,
  0.006536;-0.885445;0.464698;,
  -0.036586;-0.882578;0.468740;,
  0.006216;-0.659541;-0.751643;,
  -0.055573;-0.769240;-0.636538;,
  0.034886;0.019494;-0.999201;,
  -0.047725;-0.010679;-0.998803;,
  -0.042447;0.690260;-0.722315;,
  -0.025322;0.644717;-0.764002;,
  0.017350;0.043126;-0.998919;,
  0.014607;-0.678098;-0.734826;,
  0.024808;-0.936275;-0.350391;,
  0.078425;0.022497;-0.996666;,
  0.100710;-0.578893;-0.809160;,
  0.104705;-0.952704;-0.285291;,
  0.113606;0.964456;-0.238577;,
  0.099822;0.533197;-0.840081;,
  0.031270;0.632455;-0.773966;,
  0.033219;0.992886;-0.114343;,
  0.069337;0.098708;0.992698;,
  0.046228;0.106950;0.993189;,
  0.019036;-0.649379;0.760227;,
  0.080286;-0.738359;0.669611;,
  0.096102;0.847933;0.521319;,
  0.033844;0.811749;0.583026;,
  0.154295;0.961933;-0.225563;,
  0.117354;0.616047;-0.778918;,
  0.111427;0.005995;-0.993754;,
  0.129212;0.961021;-0.244424;,
  0.097600;0.615015;-0.782451;,
  0.083246;-0.019016;-0.996348;,
  0.145272;0.876366;0.459215;,
  0.145502;0.899556;0.411860;,
  0.110635;0.218206;0.969611;,
  0.138780;0.533451;0.834368;,
  0.092507;-0.647211;0.756677;,
  0.086172;-0.660434;0.745923;,
  0.095806;-0.888946;0.447880;,
  0.084345;-0.905485;0.415913;,
  0.126870;-0.740187;-0.660323;,
  0.085081;-0.760378;-0.643884;,
  0.035402;-0.792741;-0.608530;,
  0.062357;-0.969519;-0.236947;,
  0.024097;-0.840062;-0.541956;,
  0.028820;-0.983912;-0.176312;,
  0.016689;-0.052709;-0.998470;,
  -0.008680;-0.070309;-0.997488;,
  0.079441;0.957025;-0.278912;,
  0.039145;0.608383;-0.792677;,
  0.059809;0.970098;-0.235230;,
  -0.001972;0.672255;-0.740317;,
  0.063566;-0.664193;0.744854;,
  0.067957;-0.209161;0.975517;,
  0.037867;-0.645966;0.762426;,
  0.057367;0.369877;0.927308;,
  0.106682;0.924153;0.366823;,
  0.085798;0.945656;0.313645;,
  -0.093845;-0.945130;-0.312927;,
  -0.081126;-0.943417;-0.321533;,
  0.078166;-0.942767;-0.324161;,
  0.064308;-0.940018;-0.335008;,
  0.056883;-0.897006;0.438344;,
  0.030415;-0.906990;0.420052;,
  0.152900;-0.896335;0.416178;,
  0.069270;-0.932327;0.354920;,
  -0.000041;-0.897991;0.440013;,
  0.014912;-0.919500;-0.392806;,
  -0.060066;-0.919465;-0.388555;,
  -0.061498;-0.918881;-0.389713;,
  0.005142;-0.923770;-0.382914;,
  0.090553;-0.886515;0.453752;,
  0.078999;-0.883090;0.462506;,
  -0.007363;-0.893010;0.449976;,
  0.100878;-0.880648;0.462907;,
  0.118082;-0.955324;-0.270947;,
  0.113047;-0.955829;-0.271315;,
  0.107069;-0.954469;-0.278434;,
  0.054774;-0.958354;-0.280280;,
  0.078146;-0.963790;-0.254955;,
  0.074868;-0.911940;0.403436;,
  0.047776;-0.924314;0.378632;,
  0.076332;-0.922805;0.377630;,
  0.027288;-0.942497;0.333100;,
  -0.032652;-0.980720;-0.192670;,
  0.037917;-0.990103;-0.135126;,
  -0.009111;-0.590458;-0.807017;,
  0.021357;-0.619653;-0.784586;,
  0.023579;0.815024;0.578946;,
  0.096253;0.849390;0.518914;,
  0.009950;-0.942339;0.334513;,
  0.026046;-0.938021;0.345599;,
  0.079947;0.996001;0.039868;,
  0.095464;0.995196;0.021736;,
  0.038316;-0.143489;0.988910;,
  -0.042602;-0.212697;0.976189;,
  -0.061002;0.340364;-0.938313;,
  0.061642;0.175756;-0.982502;,
  -0.000572;0.796392;-0.604781;,
  0.006153;0.789463;-0.613768;,
  0.088468;-0.278478;0.956360;,
  0.095804;0.755728;0.647840;;
  192;
  3;2,0,1;,
  3;0,2,3;,
  3;4,3,2;,
  3;3,4,5;,
  3;6,5,4;,
  3;5,6,7;,
  3;8,7,6;,
  3;7,8,9;,
  3;11,0,10;,
  3;0,11,1;,
  3;13,10,12;,
  3;10,13,11;,
  3;14,96,96;,
  3;97,14,15;,
  3;13,15,14;,
  3;15,13,12;,
  3;18,16,17;,
  3;16,18,19;,
  3;20,19,18;,
  3;19,20,21;,
  3;10,17,12;,
  3;17,10,18;,
  3;0,18,10;,
  3;18,0,20;,
  3;23,16,22;,
  3;16,23,17;,
  3;15,17,23;,
  3;17,15,12;,
  3;25,22,24;,
  3;22,25,23;,
  3;98,23,25;,
  3;23,99,15;,
  3;27,100,26;,
  3;101,27,101;,
  3;7,102,27;,
  3;103,7,9;,
  3;29,26,28;,
  3;26,29,27;,
  3;5,27,29;,
  3;27,5,7;,
  3;31,28,30;,
  3;28,31,29;,
  3;3,29,31;,
  3;29,3,5;,
  3;20,30,21;,
  3;30,20,31;,
  3;0,31,20;,
  3;31,0,3;,
  3;32,21,30;,
  3;21,32,33;,
  3;34,33,32;,
  3;33,34,35;,
  3;36,30,28;,
  3;30,36,32;,
  3;37,32,36;,
  3;32,37,34;,
  3;38,28,26;,
  3;28,38,36;,
  3;39,36,38;,
  3;36,39,37;,
  3;40,26,104;,
  3;26,40,38;,
  3;41,38,40;,
  3;38,41,39;,
  3;42,24,22;,
  3;24,42,105;,
  3;43,106,42;,
  3;107,43,107;,
  3;44,22,16;,
  3;22,44,42;,
  3;45,42,44;,
  3;42,45,43;,
  3;46,16,19;,
  3;16,46,44;,
  3;47,44,46;,
  3;44,47,45;,
  3;33,19,21;,
  3;19,33,46;,
  3;35,46,33;,
  3;46,35,47;,
  3;49,45,48;,
  3;45,49,43;,
  3;50,43,49;,
  3;43,50,108;,
  3;52,48,51;,
  3;48,52,49;,
  3;53,49,52;,
  3;49,53,50;,
  3;56,54,55;,
  3;54,56,57;,
  3;47,57,56;,
  3;57,47,35;,
  3;48,55,51;,
  3;55,48,56;,
  3;45,56,48;,
  3;56,45,47;,
  3;60,58,59;,
  3;58,60,61;,
  3;109,61,60;,
  3;61,110,110;,
  3;39,59,37;,
  3;59,39,60;,
  3;41,60,39;,
  3;60,41,111;,
  3;63,58,62;,
  3;58,63,59;,
  3;34,59,63;,
  3;59,34,37;,
  3;57,62,54;,
  3;62,57,63;,
  3;35,63,57;,
  3;63,35,34;,
  3;65,54,64;,
  3;54,65,55;,
  3;66,55,65;,
  3;55,66,51;,
  3;68,64,67;,
  3;64,68,65;,
  3;69,65,68;,
  3;65,69,66;,
  3;70,54,62;,
  3;54,70,64;,
  3;71,64,70;,
  3;64,71,67;,
  3;72,62,58;,
  3;62,72,70;,
  3;73,70,72;,
  3;70,73,71;,
  3;74,58,61;,
  3;58,74,72;,
  3;75,72,74;,
  3;72,75,138;,
  3;76,61,112;,
  3;61,76,74;,
  3;77,74,76;,
  3;74,77,75;,
  3;78,53,52;,
  3;53,78,113;,
  3;79,114,78;,
  3;115,79,115;,
  3;66,52,51;,
  3;52,66,78;,
  3;69,78,66;,
  3;78,69,79;,
  3;80,116,79;,
  3;117,80,81;,
  3;82,81,80;,
  3;81,82,83;,
  3;84,79,69;,
  3;79,84,80;,
  3;85,80,84;,
  3;80,85,82;,
  3;87,67,86;,
  3;67,87,68;,
  3;84,68,87;,
  3;68,84,69;,
  3;89,86,88;,
  3;86,89,87;,
  3;85,87,89;,
  3;87,85,84;,
  3;90,138,75;,
  3;73,90,91;,
  3;92,91,90;,
  3;91,92,93;,
  3;118,75,77;,
  3;75,119,90;,
  3;120,90,120;,
  3;90,121,92;,
  3;94,67,71;,
  3;67,94,86;,
  3;95,86,94;,
  3;86,95,88;,
  3;139,71,73;,
  3;71,139,94;,
  3;93,94,139;,
  3;94,93,95;,
  3;122,83,82;,
  3;83,123,123;,
  3;124,82,85;,
  3;82,125,125;,
  3;126,95,93;,
  3;95,127,127;,
  3;128,92,128;,
  3;92,129,129;,
  3;130,88,95;,
  3;88,131,131;,
  3;132,93,92;,
  3;93,133,133;,
  3;134,85,89;,
  3;85,135,135;,
  3;136,89,88;,
  3;89,137,137;;
 }
 MeshTextureCoords {
  153;
  0.200300;0.545110;,
  0.182630;0.564720;,
  0.181250;0.543330;,
  0.201310;0.567430;,
  0.219250;0.551370;,
  0.218020;0.572240;,
  0.239870;0.558010;,
  0.237590;0.576150;,
  0.261520;0.570320;,
  0.260050;0.586100;,
  0.160180;0.543820;,
  0.162620;0.566250;,
  0.143060;0.549830;,
  0.145680;0.570470;,
  0.123680;0.557090;,
  0.103290;0.585070;,
  0.100880;0.569010;,
  0.103290;0.585070;,
  0.126540;0.576270;,
  0.165620;0.587980;,
  0.149080;0.611210;,
  0.147720;0.590490;,
  0.168630;0.609250;,
  0.184350;0.588530;,
  0.186480;0.611200;,
  0.129530;0.595670;,
  0.130360;0.614430;,
  0.106040;0.604400;,
  0.108140;0.621330;,
  0.103290;0.585070;,
  0.103290;0.585070;,
  0.236070;0.598040;,
  0.258510;0.622870;,
  0.236850;0.617340;,
  0.258510;0.622870;,
  0.258750;0.605390;,
  0.258750;0.605390;,
  0.258750;0.605390;,
  0.217290;0.594570;,
  0.218760;0.614680;,
  0.201400;0.590980;,
  0.204160;0.611470;,
  0.207030;0.627330;,
  0.187570;0.626870;,
  0.206690;0.642510;,
  0.187260;0.642460;,
  0.219510;0.629900;,
  0.220050;0.644260;,
  0.235010;0.631920;,
  0.236680;0.645450;,
  0.258720;0.636420;,
  0.258510;0.622870;,
  0.258800;0.648890;,
  0.131190;0.630670;,
  0.109960;0.634120;,
  0.133040;0.644160;,
  0.109960;0.634120;,
  0.109960;0.634120;,
  0.112010;0.645820;,
  0.149920;0.628930;,
  0.150950;0.644650;,
  0.168720;0.627680;,
  0.168240;0.642550;,
  0.136390;0.662580;,
  0.152700;0.661380;,
  0.114530;0.658870;,
  0.112010;0.645820;,
  0.138980;0.680170;,
  0.154010;0.679210;,
  0.119470;0.681810;,
  0.169420;0.659810;,
  0.184850;0.677680;,
  0.169280;0.677680;,
  0.186190;0.660010;,
  0.238640;0.661420;,
  0.219020;0.678020;,
  0.219770;0.660600;,
  0.236280;0.680520;,
  0.258830;0.662830;,
  0.258830;0.662830;,
  0.258340;0.687230;,
  0.258830;0.662830;,
  0.203120;0.660220;,
  0.201470;0.678260;,
  0.171400;0.698310;,
  0.184600;0.697450;,
  0.156030;0.699810;,
  0.173190;0.717430;,
  0.185370;0.716540;,
  0.158360;0.718700;,
  0.201920;0.696910;,
  0.201980;0.716070;,
  0.218880;0.698850;,
  0.218810;0.717970;,
  0.236670;0.702690;,
  0.236850;0.721880;,
  0.257390;0.709770;,
  0.258340;0.687230;,
  0.256380;0.727750;,
  0.141740;0.701340;,
  0.124430;0.703530;,
  0.144550;0.719770;,
  0.124430;0.703530;,
  0.124430;0.703530;,
  0.127830;0.721110;,
  0.147700;0.736850;,
  0.127830;0.721110;,
  0.127830;0.721110;,
  0.129810;0.735650;,
  0.150840;0.753620;,
  0.131310;0.753610;,
  0.159850;0.735300;,
  0.162200;0.753450;,
  0.174070;0.734490;,
  0.186870;0.735330;,
  0.173980;0.752710;,
  0.186950;0.753150;,
  0.237030;0.738850;,
  0.219190;0.735960;,
  0.236280;0.755350;,
  0.218230;0.755250;,
  0.255380;0.742430;,
  0.255380;0.742430;,
  0.255530;0.755290;,
  0.255380;0.742430;,
  0.255530;0.755290;,
  0.202460;0.734890;,
  0.202050;0.753170;,
  0.151040;0.765800;,
  0.151040;0.765800;,
  0.132330;0.765750;,
  0.165610;0.765530;,
  0.165610;0.765530;,
  0.151040;0.765800;,
  0.219070;0.765520;,
  0.219070;0.765520;,
  0.204520;0.765750;,
  0.254990;0.765940;,
  0.255530;0.755290;,
  0.254990;0.765940;,
  0.235940;0.765750;,
  0.204520;0.765750;,
  0.204520;0.765750;,
  0.185690;0.765450;,
  0.235940;0.765750;,
  0.235940;0.765750;,
  0.219070;0.765520;,
  0.175420;0.765410;,
  0.175420;0.765410;,
  0.165610;0.765530;,
  0.185690;0.765450;,
  0.185690;0.765450;,
  0.175420;0.765410;;
 }
}
