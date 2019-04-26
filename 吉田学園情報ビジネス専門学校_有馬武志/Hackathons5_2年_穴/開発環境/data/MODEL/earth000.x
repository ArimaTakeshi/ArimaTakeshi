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
 287;
 0.00000;10.00000;0.00000;,
 0.74658;9.80785;-1.80240;,
 0.00000;9.80785;-1.95090;,
 0.00000;10.00000;0.00000;,
 1.37950;9.80785;-1.37950;,
 0.00000;10.00000;0.00000;,
 1.80240;9.80785;-0.74658;,
 0.00000;10.00000;0.00000;,
 1.95090;9.80785;0.00000;,
 0.00000;10.00000;0.00000;,
 1.80240;9.80785;0.74658;,
 0.00000;10.00000;0.00000;,
 1.37950;9.80785;1.37950;,
 0.00000;10.00000;0.00000;,
 0.74658;9.80785;1.80240;,
 0.00000;10.00000;0.00000;,
 0.00000;9.80785;1.95090;,
 0.00000;10.00000;0.00000;,
 -0.74658;9.80785;1.80240;,
 0.00000;10.00000;0.00000;,
 -1.37950;9.80785;1.37950;,
 0.00000;10.00000;0.00000;,
 -1.80240;9.80785;0.74658;,
 0.00000;10.00000;0.00000;,
 -1.95090;9.80785;-0.00000;,
 0.00000;10.00000;0.00000;,
 -1.80240;9.80785;-0.74658;,
 0.00000;10.00000;0.00000;,
 -1.37950;9.80785;-1.37950;,
 0.00000;10.00000;0.00000;,
 -0.74658;9.80785;-1.80240;,
 0.00000;10.00000;0.00000;,
 0.00000;9.80785;-1.95090;,
 1.46447;9.23880;-3.53553;,
 0.00000;9.23880;-3.82683;,
 2.70598;9.23880;-2.70598;,
 3.53553;9.23880;-1.46447;,
 3.82683;9.23880;0.00000;,
 3.53553;9.23880;1.46447;,
 2.70598;9.23880;2.70598;,
 1.46447;9.23880;3.53553;,
 0.00000;9.23880;3.82683;,
 -1.46447;9.23880;3.53553;,
 -2.70598;9.23880;2.70598;,
 -3.53553;9.23880;1.46447;,
 -3.82683;9.23880;-0.00000;,
 -3.53553;9.23880;-1.46447;,
 -2.70598;9.23880;-2.70598;,
 -1.46446;9.23880;-3.53553;,
 0.00000;9.23880;-3.82683;,
 2.12608;8.31470;-5.13280;,
 0.00000;8.31470;-5.55570;,
 3.92847;8.31470;-3.92847;,
 5.13280;8.31470;-2.12608;,
 5.55570;8.31470;0.00000;,
 5.13280;8.31470;2.12608;,
 3.92847;8.31470;3.92847;,
 2.12608;8.31470;5.13280;,
 0.00000;8.31470;5.55570;,
 -2.12607;8.31470;5.13280;,
 -3.92847;8.31470;3.92848;,
 -5.13280;8.31470;2.12608;,
 -5.55570;8.31470;-0.00000;,
 -5.13280;8.31470;-2.12608;,
 -3.92847;8.31470;-3.92848;,
 -2.12607;8.31470;-5.13280;,
 0.00000;8.31470;-5.55570;,
 2.70598;7.07107;-6.53281;,
 0.00000;7.07107;-7.07107;,
 5.00000;7.07107;-5.00000;,
 6.53281;7.07107;-2.70598;,
 7.07107;7.07107;0.00000;,
 6.53281;7.07107;2.70598;,
 5.00000;7.07107;5.00000;,
 2.70598;7.07107;6.53281;,
 0.00000;7.07107;7.07107;,
 -2.70598;7.07107;6.53282;,
 -5.00000;7.07107;5.00000;,
 -6.53281;7.07107;2.70598;,
 -7.07107;7.07107;-0.00000;,
 -6.53281;7.07107;-2.70598;,
 -5.00000;7.07107;-5.00000;,
 -2.70598;7.07107;-6.53282;,
 0.00000;7.07107;-7.07107;,
 3.18190;5.55570;-7.68178;,
 0.00000;5.55570;-8.31470;,
 5.87938;5.55570;-5.87938;,
 7.68178;5.55570;-3.18190;,
 8.31470;5.55570;0.00000;,
 7.68178;5.55570;3.18190;,
 5.87938;5.55570;5.87938;,
 3.18190;5.55570;7.68178;,
 0.00000;5.55570;8.31470;,
 -3.18189;5.55570;7.68178;,
 -5.87938;5.55570;5.87938;,
 -7.68178;5.55570;3.18190;,
 -8.31470;5.55570;-0.00000;,
 -7.68178;5.55570;-3.18190;,
 -5.87938;5.55570;-5.87938;,
 -3.18189;5.55570;-7.68178;,
 0.00000;5.55570;-8.31470;,
 3.53553;3.82683;-8.53553;,
 0.00000;3.82683;-9.23880;,
 6.53281;3.82683;-6.53281;,
 8.53553;3.82683;-3.53553;,
 9.23880;3.82683;0.00000;,
 8.53553;3.82683;3.53553;,
 6.53281;3.82683;6.53281;,
 3.53553;3.82683;8.53553;,
 0.00000;3.82683;9.23880;,
 -3.53553;3.82683;8.53553;,
 -6.53281;3.82683;6.53282;,
 -8.53553;3.82683;3.53554;,
 -9.23880;3.82683;-0.00000;,
 -8.53553;3.82683;-3.53554;,
 -6.53281;3.82683;-6.53282;,
 -3.53553;3.82683;-8.53554;,
 0.00000;3.82683;-9.23880;,
 3.75330;1.95090;-9.06127;,
 0.00000;1.95090;-9.80785;,
 6.93520;1.95090;-6.93520;,
 9.06127;1.95090;-3.75330;,
 9.80785;1.95090;0.00000;,
 9.06127;1.95090;3.75330;,
 6.93520;1.95090;6.93520;,
 3.75330;1.95090;9.06127;,
 0.00000;1.95090;9.80785;,
 -3.75330;1.95090;9.06128;,
 -6.93520;1.95090;6.93520;,
 -9.06127;1.95090;3.75330;,
 -9.80785;1.95090;-0.00000;,
 -9.06127;1.95090;-3.75330;,
 -6.93520;1.95090;-6.93520;,
 -3.75330;1.95090;-9.06128;,
 0.00000;1.95090;-9.80785;,
 3.82683;0.00000;-9.23880;,
 0.00000;0.00000;-10.00000;,
 7.07107;0.00000;-7.07107;,
 9.23880;0.00000;-3.82683;,
 10.00000;0.00000;0.00000;,
 9.23879;0.00000;3.82684;,
 7.07107;0.00000;7.07107;,
 3.82683;0.00000;9.23879;,
 0.00000;0.00000;10.00000;,
 -3.82683;0.00000;9.23880;,
 -7.07107;0.00000;7.07107;,
 -9.23879;0.00000;3.82684;,
 -10.00000;0.00000;-0.00000;,
 -9.23879;0.00000;-3.82684;,
 -7.07107;0.00000;-7.07107;,
 -3.82683;0.00000;-9.23880;,
 0.00000;0.00000;-10.00000;,
 3.75330;-1.95090;-9.06127;,
 0.00000;-1.95090;-9.80785;,
 6.93520;-1.95090;-6.93520;,
 9.06127;-1.95090;-3.75330;,
 9.80785;-1.95090;0.00000;,
 9.06127;-1.95090;3.75330;,
 6.93520;-1.95090;6.93520;,
 3.75330;-1.95090;9.06127;,
 0.00000;-1.95090;9.80785;,
 -3.75330;-1.95090;9.06128;,
 -6.93520;-1.95090;6.93520;,
 -9.06127;-1.95090;3.75330;,
 -9.80785;-1.95090;-0.00000;,
 -9.06127;-1.95090;-3.75330;,
 -6.93520;-1.95090;-6.93520;,
 -3.75330;-1.95090;-9.06128;,
 0.00000;-1.95090;-9.80785;,
 3.53553;-3.82683;-8.53553;,
 0.00000;-3.82683;-9.23880;,
 6.53282;-3.82683;-6.53282;,
 8.53553;-3.82683;-3.53553;,
 9.23880;-3.82683;0.00000;,
 8.53553;-3.82683;3.53554;,
 6.53282;-3.82683;6.53282;,
 3.53554;-3.82683;8.53553;,
 0.00000;-3.82683;9.23880;,
 -3.53553;-3.82683;8.53554;,
 -6.53281;-3.82683;6.53282;,
 -8.53553;-3.82683;3.53554;,
 -9.23880;-3.82683;-0.00000;,
 -8.53553;-3.82683;-3.53554;,
 -6.53281;-3.82683;-6.53282;,
 -3.53553;-3.82683;-8.53554;,
 0.00000;-3.82683;-9.23880;,
 3.18190;-5.55570;-7.68178;,
 0.00000;-5.55570;-8.31470;,
 5.87938;-5.55570;-5.87938;,
 7.68178;-5.55570;-3.18190;,
 8.31470;-5.55570;0.00000;,
 7.68178;-5.55570;3.18190;,
 5.87938;-5.55570;5.87938;,
 3.18190;-5.55570;7.68178;,
 0.00000;-5.55570;8.31470;,
 -3.18189;-5.55570;7.68178;,
 -5.87938;-5.55570;5.87938;,
 -7.68178;-5.55570;3.18190;,
 -8.31470;-5.55570;-0.00000;,
 -7.68178;-5.55570;-3.18190;,
 -5.87938;-5.55570;-5.87938;,
 -3.18189;-5.55570;-7.68178;,
 0.00000;-5.55570;-8.31470;,
 2.70598;-7.07107;-6.53281;,
 0.00000;-7.07107;-7.07107;,
 5.00000;-7.07107;-5.00000;,
 6.53281;-7.07107;-2.70598;,
 7.07107;-7.07107;0.00000;,
 6.53281;-7.07107;2.70598;,
 5.00000;-7.07107;5.00000;,
 2.70598;-7.07107;6.53281;,
 0.00000;-7.07107;7.07107;,
 -2.70598;-7.07107;6.53282;,
 -5.00000;-7.07107;5.00000;,
 -6.53281;-7.07107;2.70598;,
 -7.07107;-7.07107;-0.00000;,
 -6.53281;-7.07107;-2.70598;,
 -5.00000;-7.07107;-5.00000;,
 -2.70598;-7.07107;-6.53282;,
 0.00000;-7.07107;-7.07107;,
 2.12608;-8.31470;-5.13280;,
 0.00000;-8.31470;-5.55570;,
 3.92847;-8.31470;-3.92847;,
 5.13280;-8.31470;-2.12607;,
 5.55570;-8.31470;0.00000;,
 5.13280;-8.31470;2.12608;,
 3.92847;-8.31470;3.92847;,
 2.12608;-8.31470;5.13280;,
 0.00000;-8.31470;5.55570;,
 -2.12607;-8.31470;5.13280;,
 -3.92847;-8.31470;3.92848;,
 -5.13280;-8.31470;2.12608;,
 -5.55570;-8.31470;-0.00000;,
 -5.13280;-8.31470;-2.12608;,
 -3.92847;-8.31470;-3.92848;,
 -2.12607;-8.31470;-5.13280;,
 0.00000;-8.31470;-5.55570;,
 1.46447;-9.23880;-3.53553;,
 0.00000;-9.23880;-3.82683;,
 2.70598;-9.23880;-2.70598;,
 3.53553;-9.23880;-1.46447;,
 3.82683;-9.23880;0.00000;,
 3.53553;-9.23880;1.46447;,
 2.70598;-9.23880;2.70598;,
 1.46447;-9.23880;3.53553;,
 0.00000;-9.23880;3.82683;,
 -1.46446;-9.23880;3.53553;,
 -2.70598;-9.23880;2.70598;,
 -3.53553;-9.23880;1.46447;,
 -3.82683;-9.23880;-0.00000;,
 -3.53553;-9.23880;-1.46447;,
 -2.70598;-9.23880;-2.70598;,
 -1.46446;-9.23880;-3.53553;,
 0.00000;-9.23880;-3.82683;,
 0.74658;-9.80785;-1.80240;,
 0.00000;-9.80785;-1.95090;,
 1.37950;-9.80785;-1.37950;,
 1.80240;-9.80785;-0.74658;,
 1.95090;-9.80785;0.00000;,
 1.80240;-9.80785;0.74658;,
 1.37950;-9.80785;1.37950;,
 0.74658;-9.80785;1.80240;,
 0.00000;-9.80785;1.95090;,
 -0.74658;-9.80785;1.80240;,
 -1.37949;-9.80785;1.37950;,
 -1.80240;-9.80785;0.74658;,
 -1.95090;-9.80785;-0.00000;,
 -1.80240;-9.80785;-0.74658;,
 -1.37949;-9.80785;-1.37950;,
 -0.74658;-9.80785;-1.80240;,
 0.00000;-9.80785;-1.95090;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;,
 0.00000;-10.00000;-0.00000;;
 
 256;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 3;23,24,22;,
 3;25,26,24;,
 3;27,28,26;,
 3;29,30,28;,
 3;31,32,30;,
 4;2,1,33,34;,
 4;1,4,35,33;,
 4;4,6,36,35;,
 4;6,8,37,36;,
 4;8,10,38,37;,
 4;10,12,39,38;,
 4;12,14,40,39;,
 4;14,16,41,40;,
 4;16,18,42,41;,
 4;18,20,43,42;,
 4;20,22,44,43;,
 4;22,24,45,44;,
 4;24,26,46,45;,
 4;26,28,47,46;,
 4;28,30,48,47;,
 4;30,32,49,48;,
 4;34,33,50,51;,
 4;33,35,52,50;,
 4;35,36,53,52;,
 4;36,37,54,53;,
 4;37,38,55,54;,
 4;38,39,56,55;,
 4;39,40,57,56;,
 4;40,41,58,57;,
 4;41,42,59,58;,
 4;42,43,60,59;,
 4;43,44,61,60;,
 4;44,45,62,61;,
 4;45,46,63,62;,
 4;46,47,64,63;,
 4;47,48,65,64;,
 4;48,49,66,65;,
 4;51,50,67,68;,
 4;50,52,69,67;,
 4;52,53,70,69;,
 4;53,54,71,70;,
 4;54,55,72,71;,
 4;55,56,73,72;,
 4;56,57,74,73;,
 4;57,58,75,74;,
 4;58,59,76,75;,
 4;59,60,77,76;,
 4;60,61,78,77;,
 4;61,62,79,78;,
 4;62,63,80,79;,
 4;63,64,81,80;,
 4;64,65,82,81;,
 4;65,66,83,82;,
 4;68,67,84,85;,
 4;67,69,86,84;,
 4;69,70,87,86;,
 4;70,71,88,87;,
 4;71,72,89,88;,
 4;72,73,90,89;,
 4;73,74,91,90;,
 4;74,75,92,91;,
 4;75,76,93,92;,
 4;76,77,94,93;,
 4;77,78,95,94;,
 4;78,79,96,95;,
 4;79,80,97,96;,
 4;80,81,98,97;,
 4;81,82,99,98;,
 4;82,83,100,99;,
 4;85,84,101,102;,
 4;84,86,103,101;,
 4;86,87,104,103;,
 4;87,88,105,104;,
 4;88,89,106,105;,
 4;89,90,107,106;,
 4;90,91,108,107;,
 4;91,92,109,108;,
 4;92,93,110,109;,
 4;93,94,111,110;,
 4;94,95,112,111;,
 4;95,96,113,112;,
 4;96,97,114,113;,
 4;97,98,115,114;,
 4;98,99,116,115;,
 4;99,100,117,116;,
 4;102,101,118,119;,
 4;101,103,120,118;,
 4;103,104,121,120;,
 4;104,105,122,121;,
 4;105,106,123,122;,
 4;106,107,124,123;,
 4;107,108,125,124;,
 4;108,109,126,125;,
 4;109,110,127,126;,
 4;110,111,128,127;,
 4;111,112,129,128;,
 4;112,113,130,129;,
 4;113,114,131,130;,
 4;114,115,132,131;,
 4;115,116,133,132;,
 4;116,117,134,133;,
 4;119,118,135,136;,
 4;118,120,137,135;,
 4;120,121,138,137;,
 4;121,122,139,138;,
 4;122,123,140,139;,
 4;123,124,141,140;,
 4;124,125,142,141;,
 4;125,126,143,142;,
 4;126,127,144,143;,
 4;127,128,145,144;,
 4;128,129,146,145;,
 4;129,130,147,146;,
 4;130,131,148,147;,
 4;131,132,149,148;,
 4;132,133,150,149;,
 4;133,134,151,150;,
 4;136,135,152,153;,
 4;135,137,154,152;,
 4;137,138,155,154;,
 4;138,139,156,155;,
 4;139,140,157,156;,
 4;140,141,158,157;,
 4;141,142,159,158;,
 4;142,143,160,159;,
 4;143,144,161,160;,
 4;144,145,162,161;,
 4;145,146,163,162;,
 4;146,147,164,163;,
 4;147,148,165,164;,
 4;148,149,166,165;,
 4;149,150,167,166;,
 4;150,151,168,167;,
 4;153,152,169,170;,
 4;152,154,171,169;,
 4;154,155,172,171;,
 4;155,156,173,172;,
 4;156,157,174,173;,
 4;157,158,175,174;,
 4;158,159,176,175;,
 4;159,160,177,176;,
 4;160,161,178,177;,
 4;161,162,179,178;,
 4;162,163,180,179;,
 4;163,164,181,180;,
 4;164,165,182,181;,
 4;165,166,183,182;,
 4;166,167,184,183;,
 4;167,168,185,184;,
 4;170,169,186,187;,
 4;169,171,188,186;,
 4;171,172,189,188;,
 4;172,173,190,189;,
 4;173,174,191,190;,
 4;174,175,192,191;,
 4;175,176,193,192;,
 4;176,177,194,193;,
 4;177,178,195,194;,
 4;178,179,196,195;,
 4;179,180,197,196;,
 4;180,181,198,197;,
 4;181,182,199,198;,
 4;182,183,200,199;,
 4;183,184,201,200;,
 4;184,185,202,201;,
 4;187,186,203,204;,
 4;186,188,205,203;,
 4;188,189,206,205;,
 4;189,190,207,206;,
 4;190,191,208,207;,
 4;191,192,209,208;,
 4;192,193,210,209;,
 4;193,194,211,210;,
 4;194,195,212,211;,
 4;195,196,213,212;,
 4;196,197,214,213;,
 4;197,198,215,214;,
 4;198,199,216,215;,
 4;199,200,217,216;,
 4;200,201,218,217;,
 4;201,202,219,218;,
 4;204,203,220,221;,
 4;203,205,222,220;,
 4;205,206,223,222;,
 4;206,207,224,223;,
 4;207,208,225,224;,
 4;208,209,226,225;,
 4;209,210,227,226;,
 4;210,211,228,227;,
 4;211,212,229,228;,
 4;212,213,230,229;,
 4;213,214,231,230;,
 4;214,215,232,231;,
 4;215,216,233,232;,
 4;216,217,234,233;,
 4;217,218,235,234;,
 4;218,219,236,235;,
 4;221,220,237,238;,
 4;220,222,239,237;,
 4;222,223,240,239;,
 4;223,224,241,240;,
 4;224,225,242,241;,
 4;225,226,243,242;,
 4;226,227,244,243;,
 4;227,228,245,244;,
 4;228,229,246,245;,
 4;229,230,247,246;,
 4;230,231,248,247;,
 4;231,232,249,248;,
 4;232,233,250,249;,
 4;233,234,251,250;,
 4;234,235,252,251;,
 4;235,236,253,252;,
 4;238,237,254,255;,
 4;237,239,256,254;,
 4;239,240,257,256;,
 4;240,241,258,257;,
 4;241,242,259,258;,
 4;242,243,260,259;,
 4;243,244,261,260;,
 4;244,245,262,261;,
 4;245,246,263,262;,
 4;246,247,264,263;,
 4;247,248,265,264;,
 4;248,249,266,265;,
 4;249,250,267,266;,
 4;250,251,268,267;,
 4;251,252,269,268;,
 4;252,253,270,269;,
 3;255,254,271;,
 3;254,256,272;,
 3;256,257,273;,
 3;257,258,274;,
 3;258,259,275;,
 3;259,260,276;,
 3;260,261,277;,
 3;261,262,278;,
 3;262,263,279;,
 3;263,264,280;,
 3;264,265,281;,
 3;265,266,282;,
 3;266,267,283;,
 3;267,268,284;,
 3;268,269,285;,
 3;269,270,286;;
 
 MeshMaterialList {
  1;
  256;
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
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
   TextureFilename {
    "earth000.jpg";
   }
  }
 }
 MeshNormals {
  242;
  0.000000;1.000000;0.000000;,
  0.000000;0.980799;-0.195019;,
  0.074631;0.980799;-0.180174;,
  0.137899;0.980799;-0.137899;,
  0.180174;0.980799;-0.074631;,
  0.195019;0.980799;0.000000;,
  0.180174;0.980799;0.074631;,
  0.137899;0.980799;0.137899;,
  0.074631;0.980799;0.180174;,
  0.000000;0.980799;0.195019;,
  -0.074631;0.980799;0.180174;,
  -0.137899;0.980799;0.137899;,
  -0.180174;0.980799;0.074631;,
  -0.195019;0.980799;0.000000;,
  -0.180174;0.980799;-0.074631;,
  -0.137899;0.980799;-0.137899;,
  -0.074631;0.980799;-0.180174;,
  0.000000;0.923931;-0.382560;,
  0.146399;0.923931;-0.353439;,
  0.270511;0.923931;-0.270511;,
  0.353439;0.923931;-0.146399;,
  0.382560;0.923931;0.000000;,
  0.353439;0.923931;0.146399;,
  0.270511;0.923931;0.270511;,
  0.146399;0.923931;0.353439;,
  0.000000;0.923931;0.382560;,
  -0.146399;0.923931;0.353439;,
  -0.270511;0.923931;0.270511;,
  -0.353439;0.923931;0.146399;,
  -0.382560;0.923931;-0.000000;,
  -0.353439;0.923931;-0.146399;,
  -0.270511;0.923931;-0.270511;,
  -0.146399;0.923931;-0.353440;,
  0.000000;0.831566;-0.555426;,
  0.212552;0.831566;-0.513147;,
  0.392746;0.831566;-0.392746;,
  0.513147;0.831566;-0.212552;,
  0.555426;0.831566;0.000000;,
  0.513147;0.831566;0.212552;,
  0.392746;0.831566;0.392746;,
  0.212552;0.831566;0.513147;,
  0.000000;0.831566;0.555426;,
  -0.212552;0.831566;0.513147;,
  -0.392745;0.831566;0.392746;,
  -0.513147;0.831566;0.212552;,
  -0.555426;0.831566;-0.000000;,
  -0.513147;0.831566;-0.212552;,
  -0.392745;0.831566;-0.392746;,
  -0.212552;0.831566;-0.513147;,
  0.000000;0.707239;-0.706975;,
  0.270548;0.707239;-0.653160;,
  0.499907;0.707239;-0.499907;,
  0.653160;0.707239;-0.270548;,
  0.706975;0.707239;0.000000;,
  0.653160;0.707239;0.270548;,
  0.499907;0.707239;0.499907;,
  0.270548;0.707239;0.653160;,
  0.000000;0.707239;0.706975;,
  -0.270547;0.707239;0.653160;,
  -0.499907;0.707239;0.499907;,
  -0.653160;0.707239;0.270548;,
  -0.706975;0.707239;-0.000000;,
  -0.653160;0.707239;-0.270548;,
  -0.499907;0.707239;-0.499907;,
  -0.270547;0.707239;-0.653160;,
  0.000000;0.555712;-0.831375;,
  0.318153;0.555712;-0.768090;,
  0.587871;0.555712;-0.587871;,
  0.768090;0.555712;-0.318153;,
  0.831375;0.555712;0.000000;,
  0.768090;0.555712;0.318153;,
  0.587871;0.555712;0.587871;,
  0.318153;0.555712;0.768090;,
  0.000000;0.555712;0.831375;,
  -0.318153;0.555712;0.768090;,
  -0.587870;0.555712;0.587871;,
  -0.768090;0.555712;0.318153;,
  -0.831375;0.555712;-0.000000;,
  -0.768090;0.555712;-0.318153;,
  -0.587870;0.555712;-0.587871;,
  -0.318153;0.555712;-0.768090;,
  0.000000;0.382804;-0.923830;,
  0.353534;0.382804;-0.853507;,
  0.653246;0.382804;-0.653246;,
  0.853507;0.382804;-0.353534;,
  0.923830;0.382803;0.000000;,
  0.853507;0.382803;0.353534;,
  0.653246;0.382804;0.653246;,
  0.353534;0.382804;0.853507;,
  0.000000;0.382804;0.923830;,
  -0.353534;0.382804;0.853508;,
  -0.653246;0.382804;0.653246;,
  -0.853507;0.382804;0.353534;,
  -0.923830;0.382804;-0.000000;,
  -0.853507;0.382804;-0.353535;,
  -0.653246;0.382803;-0.653247;,
  -0.353534;0.382803;-0.853508;,
  0.000000;0.195159;-0.980772;,
  0.375325;0.195159;-0.906115;,
  0.693510;0.195159;-0.693510;,
  0.906115;0.195159;-0.375325;,
  0.980772;0.195159;0.000000;,
  0.906115;0.195159;0.375325;,
  0.693510;0.195159;0.693510;,
  0.375325;0.195159;0.906115;,
  0.000000;0.195159;0.980772;,
  -0.375325;0.195159;0.906115;,
  -0.693510;0.195159;0.693510;,
  -0.906115;0.195159;0.375325;,
  -0.980772;0.195159;-0.000000;,
  -0.906115;0.195159;-0.375325;,
  -0.693510;0.195159;-0.693510;,
  -0.375325;0.195159;-0.906115;,
  0.000000;0.000000;-1.000000;,
  0.382683;0.000000;-0.923880;,
  0.707107;0.000000;-0.707107;,
  0.923880;0.000000;-0.382683;,
  1.000000;0.000000;0.000000;,
  0.923880;0.000000;0.382683;,
  0.707107;0.000000;0.707107;,
  0.382683;0.000000;0.923879;,
  0.000000;0.000000;1.000000;,
  -0.382683;0.000000;0.923880;,
  -0.707107;0.000000;0.707107;,
  -0.923880;0.000000;0.382684;,
  -1.000000;0.000000;0.000000;,
  -0.923879;0.000000;-0.382684;,
  -0.707107;0.000000;-0.707107;,
  -0.382683;0.000000;-0.923880;,
  0.000000;-0.195159;-0.980772;,
  0.375325;-0.195159;-0.906115;,
  0.693510;-0.195159;-0.693510;,
  0.906115;-0.195159;-0.375325;,
  0.980772;-0.195159;0.000000;,
  0.906115;-0.195159;0.375325;,
  0.693510;-0.195159;0.693510;,
  0.375325;-0.195159;0.906115;,
  0.000000;-0.195159;0.980772;,
  -0.375325;-0.195159;0.906115;,
  -0.693510;-0.195159;0.693511;,
  -0.906115;-0.195159;0.375325;,
  -0.980772;-0.195159;0.000000;,
  -0.906115;-0.195159;-0.375325;,
  -0.693510;-0.195159;-0.693510;,
  -0.375325;-0.195159;-0.906115;,
  0.000000;-0.382803;-0.923830;,
  0.353534;-0.382803;-0.853508;,
  0.653246;-0.382803;-0.653246;,
  0.853508;-0.382803;-0.353534;,
  0.923830;-0.382803;0.000000;,
  0.853507;-0.382803;0.353534;,
  0.653246;-0.382803;0.653246;,
  0.353534;-0.382803;0.853507;,
  0.000000;-0.382803;0.923830;,
  -0.353534;-0.382803;0.853508;,
  -0.653246;-0.382803;0.653246;,
  -0.853507;-0.382803;0.353535;,
  -0.923830;-0.382803;0.000000;,
  -0.853507;-0.382803;-0.353535;,
  -0.653246;-0.382803;-0.653247;,
  -0.353534;-0.382803;-0.853508;,
  0.000000;-0.555712;-0.831375;,
  0.318153;-0.555712;-0.768090;,
  0.587871;-0.555712;-0.587871;,
  0.768090;-0.555712;-0.318153;,
  0.831375;-0.555712;0.000000;,
  0.768090;-0.555712;0.318153;,
  0.587871;-0.555712;0.587871;,
  0.318153;-0.555712;0.768090;,
  0.000000;-0.555712;0.831375;,
  -0.318153;-0.555712;0.768090;,
  -0.587870;-0.555712;0.587871;,
  -0.768090;-0.555712;0.318153;,
  -0.831375;-0.555712;-0.000000;,
  -0.768090;-0.555712;-0.318153;,
  -0.587870;-0.555712;-0.587871;,
  -0.318153;-0.555712;-0.768090;,
  0.000000;-0.707239;-0.706975;,
  0.270548;-0.707239;-0.653160;,
  0.499907;-0.707239;-0.499907;,
  0.653160;-0.707239;-0.270548;,
  0.706975;-0.707239;-0.000000;,
  0.653160;-0.707239;0.270548;,
  0.499907;-0.707239;0.499907;,
  0.270548;-0.707239;0.653160;,
  0.000000;-0.707239;0.706975;,
  -0.270547;-0.707239;0.653160;,
  -0.499907;-0.707239;0.499907;,
  -0.653160;-0.707239;0.270548;,
  -0.706975;-0.707239;-0.000000;,
  -0.653160;-0.707239;-0.270548;,
  -0.499907;-0.707239;-0.499907;,
  -0.270547;-0.707239;-0.653160;,
  0.000000;-0.831566;-0.555426;,
  0.212552;-0.831566;-0.513147;,
  0.392745;-0.831566;-0.392745;,
  0.513147;-0.831566;-0.212552;,
  0.555426;-0.831566;0.000000;,
  0.513147;-0.831566;0.212552;,
  0.392745;-0.831566;0.392745;,
  0.212552;-0.831566;0.513147;,
  0.000000;-0.831566;0.555426;,
  -0.212552;-0.831566;0.513147;,
  -0.392745;-0.831566;0.392746;,
  -0.513147;-0.831566;0.212552;,
  -0.555426;-0.831566;-0.000000;,
  -0.513147;-0.831566;-0.212552;,
  -0.392745;-0.831566;-0.392746;,
  -0.212552;-0.831566;-0.513147;,
  0.000000;-0.923931;-0.382560;,
  0.146399;-0.923931;-0.353439;,
  0.270511;-0.923931;-0.270511;,
  0.353439;-0.923931;-0.146399;,
  0.382560;-0.923931;0.000000;,
  0.353439;-0.923931;0.146399;,
  0.270511;-0.923931;0.270511;,
  0.146399;-0.923931;0.353439;,
  0.000000;-0.923931;0.382560;,
  -0.146399;-0.923931;0.353439;,
  -0.270511;-0.923931;0.270511;,
  -0.353439;-0.923931;0.146399;,
  -0.382560;-0.923931;-0.000000;,
  -0.353439;-0.923931;-0.146399;,
  -0.270511;-0.923931;-0.270511;,
  -0.146399;-0.923931;-0.353439;,
  0.000000;-0.980799;-0.195019;,
  0.074630;-0.980799;-0.180174;,
  0.137899;-0.980799;-0.137899;,
  0.180174;-0.980799;-0.074630;,
  0.195019;-0.980799;0.000000;,
  0.180174;-0.980799;0.074631;,
  0.137899;-0.980799;0.137899;,
  0.074631;-0.980799;0.180174;,
  0.000000;-0.980799;0.195019;,
  -0.074630;-0.980799;0.180174;,
  -0.137899;-0.980799;0.137899;,
  -0.180174;-0.980799;0.074631;,
  -0.195019;-0.980799;0.000000;,
  -0.180174;-0.980799;-0.074631;,
  -0.137899;-0.980799;-0.137899;,
  -0.074630;-0.980799;-0.180174;,
  0.000000;-1.000000;-0.000000;;
  256;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,1,16;,
  4;1,2,18,17;,
  4;2,3,19,18;,
  4;3,4,20,19;,
  4;4,5,21,20;,
  4;5,6,22,21;,
  4;6,7,23,22;,
  4;7,8,24,23;,
  4;8,9,25,24;,
  4;9,10,26,25;,
  4;10,11,27,26;,
  4;11,12,28,27;,
  4;12,13,29,28;,
  4;13,14,30,29;,
  4;14,15,31,30;,
  4;15,16,32,31;,
  4;16,1,17,32;,
  4;17,18,34,33;,
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,26,42,41;,
  4;26,27,43,42;,
  4;27,28,44,43;,
  4;28,29,45,44;,
  4;29,30,46,45;,
  4;30,31,47,46;,
  4;31,32,48,47;,
  4;32,17,33,48;,
  4;33,34,50,49;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,42,58,57;,
  4;42,43,59,58;,
  4;43,44,60,59;,
  4;44,45,61,60;,
  4;45,46,62,61;,
  4;46,47,63,62;,
  4;47,48,64,63;,
  4;48,33,49,64;,
  4;49,50,66,65;,
  4;50,51,67,66;,
  4;51,52,68,67;,
  4;52,53,69,68;,
  4;53,54,70,69;,
  4;54,55,71,70;,
  4;55,56,72,71;,
  4;56,57,73,72;,
  4;57,58,74,73;,
  4;58,59,75,74;,
  4;59,60,76,75;,
  4;60,61,77,76;,
  4;61,62,78,77;,
  4;62,63,79,78;,
  4;63,64,80,79;,
  4;64,49,65,80;,
  4;65,66,82,81;,
  4;66,67,83,82;,
  4;67,68,84,83;,
  4;68,69,85,84;,
  4;69,70,86,85;,
  4;70,71,87,86;,
  4;71,72,88,87;,
  4;72,73,89,88;,
  4;73,74,90,89;,
  4;74,75,91,90;,
  4;75,76,92,91;,
  4;76,77,93,92;,
  4;77,78,94,93;,
  4;78,79,95,94;,
  4;79,80,96,95;,
  4;80,65,81,96;,
  4;81,82,98,97;,
  4;82,83,99,98;,
  4;83,84,100,99;,
  4;84,85,101,100;,
  4;85,86,102,101;,
  4;86,87,103,102;,
  4;87,88,104,103;,
  4;88,89,105,104;,
  4;89,90,106,105;,
  4;90,91,107,106;,
  4;91,92,108,107;,
  4;92,93,109,108;,
  4;93,94,110,109;,
  4;94,95,111,110;,
  4;95,96,112,111;,
  4;96,81,97,112;,
  4;97,98,114,113;,
  4;98,99,115,114;,
  4;99,100,116,115;,
  4;100,101,117,116;,
  4;101,102,118,117;,
  4;102,103,119,118;,
  4;103,104,120,119;,
  4;104,105,121,120;,
  4;105,106,122,121;,
  4;106,107,123,122;,
  4;107,108,124,123;,
  4;108,109,125,124;,
  4;109,110,126,125;,
  4;110,111,127,126;,
  4;111,112,128,127;,
  4;112,97,113,128;,
  4;113,114,130,129;,
  4;114,115,131,130;,
  4;115,116,132,131;,
  4;116,117,133,132;,
  4;117,118,134,133;,
  4;118,119,135,134;,
  4;119,120,136,135;,
  4;120,121,137,136;,
  4;121,122,138,137;,
  4;122,123,139,138;,
  4;123,124,140,139;,
  4;124,125,141,140;,
  4;125,126,142,141;,
  4;126,127,143,142;,
  4;127,128,144,143;,
  4;128,113,129,144;,
  4;129,130,146,145;,
  4;130,131,147,146;,
  4;131,132,148,147;,
  4;132,133,149,148;,
  4;133,134,150,149;,
  4;134,135,151,150;,
  4;135,136,152,151;,
  4;136,137,153,152;,
  4;137,138,154,153;,
  4;138,139,155,154;,
  4;139,140,156,155;,
  4;140,141,157,156;,
  4;141,142,158,157;,
  4;142,143,159,158;,
  4;143,144,160,159;,
  4;144,129,145,160;,
  4;145,146,162,161;,
  4;146,147,163,162;,
  4;147,148,164,163;,
  4;148,149,165,164;,
  4;149,150,166,165;,
  4;150,151,167,166;,
  4;151,152,168,167;,
  4;152,153,169,168;,
  4;153,154,170,169;,
  4;154,155,171,170;,
  4;155,156,172,171;,
  4;156,157,173,172;,
  4;157,158,174,173;,
  4;158,159,175,174;,
  4;159,160,176,175;,
  4;160,145,161,176;,
  4;161,162,178,177;,
  4;162,163,179,178;,
  4;163,164,180,179;,
  4;164,165,181,180;,
  4;165,166,182,181;,
  4;166,167,183,182;,
  4;167,168,184,183;,
  4;168,169,185,184;,
  4;169,170,186,185;,
  4;170,171,187,186;,
  4;171,172,188,187;,
  4;172,173,189,188;,
  4;173,174,190,189;,
  4;174,175,191,190;,
  4;175,176,192,191;,
  4;176,161,177,192;,
  4;177,178,194,193;,
  4;178,179,195,194;,
  4;179,180,196,195;,
  4;180,181,197,196;,
  4;181,182,198,197;,
  4;182,183,199,198;,
  4;183,184,200,199;,
  4;184,185,201,200;,
  4;185,186,202,201;,
  4;186,187,203,202;,
  4;187,188,204,203;,
  4;188,189,205,204;,
  4;189,190,206,205;,
  4;190,191,207,206;,
  4;191,192,208,207;,
  4;192,177,193,208;,
  4;193,194,210,209;,
  4;194,195,211,210;,
  4;195,196,212,211;,
  4;196,197,213,212;,
  4;197,198,214,213;,
  4;198,199,215,214;,
  4;199,200,216,215;,
  4;200,201,217,216;,
  4;201,202,218,217;,
  4;202,203,219,218;,
  4;203,204,220,219;,
  4;204,205,221,220;,
  4;205,206,222,221;,
  4;206,207,223,222;,
  4;207,208,224,223;,
  4;208,193,209,224;,
  4;209,210,226,225;,
  4;210,211,227,226;,
  4;211,212,228,227;,
  4;212,213,229,228;,
  4;213,214,230,229;,
  4;214,215,231,230;,
  4;215,216,232,231;,
  4;216,217,233,232;,
  4;217,218,234,233;,
  4;218,219,235,234;,
  4;219,220,236,235;,
  4;220,221,237,236;,
  4;221,222,238,237;,
  4;222,223,239,238;,
  4;223,224,240,239;,
  4;224,209,225,240;,
  3;225,226,241;,
  3;226,227,241;,
  3;227,228,241;,
  3;228,229,241;,
  3;229,230,241;,
  3;230,231,241;,
  3;231,232,241;,
  3;232,233,241;,
  3;233,234,241;,
  3;234,235,241;,
  3;235,236,241;,
  3;236,237,241;,
  3;237,238,241;,
  3;238,239,241;,
  3;239,240,241;,
  3;240,225,241;;
 }
 MeshTextureCoords {
  287;
  0.031250;0.000000;
  0.062500;0.062500;
  0.000000;0.062500;
  0.093750;0.000000;
  0.125000;0.062500;
  0.156250;0.000000;
  0.187500;0.062500;
  0.218750;0.000000;
  0.250000;0.062500;
  0.281250;0.000000;
  0.312500;0.062500;
  0.343750;0.000000;
  0.375000;0.062500;
  0.406250;0.000000;
  0.437500;0.062500;
  0.468750;0.000000;
  0.500000;0.062500;
  0.531250;0.000000;
  0.562500;0.062500;
  0.593750;0.000000;
  0.625000;0.062500;
  0.656250;0.000000;
  0.687500;0.062500;
  0.718750;0.000000;
  0.750000;0.062500;
  0.781250;0.000000;
  0.812500;0.062500;
  0.843750;0.000000;
  0.875000;0.062500;
  0.906250;0.000000;
  0.937500;0.062500;
  0.968750;0.000000;
  1.000000;0.062500;
  0.062500;0.125000;
  0.000000;0.125000;
  0.125000;0.125000;
  0.187500;0.125000;
  0.250000;0.125000;
  0.312500;0.125000;
  0.375000;0.125000;
  0.437500;0.125000;
  0.500000;0.125000;
  0.562500;0.125000;
  0.625000;0.125000;
  0.687500;0.125000;
  0.750000;0.125000;
  0.812500;0.125000;
  0.875000;0.125000;
  0.937500;0.125000;
  1.000000;0.125000;
  0.062500;0.187500;
  0.000000;0.187500;
  0.125000;0.187500;
  0.187500;0.187500;
  0.250000;0.187500;
  0.312500;0.187500;
  0.375000;0.187500;
  0.437500;0.187500;
  0.500000;0.187500;
  0.562500;0.187500;
  0.625000;0.187500;
  0.687500;0.187500;
  0.750000;0.187500;
  0.812500;0.187500;
  0.875000;0.187500;
  0.937500;0.187500;
  1.000000;0.187500;
  0.062500;0.250000;
  0.000000;0.250000;
  0.125000;0.250000;
  0.187500;0.250000;
  0.250000;0.250000;
  0.312500;0.250000;
  0.375000;0.250000;
  0.437500;0.250000;
  0.500000;0.250000;
  0.562500;0.250000;
  0.625000;0.250000;
  0.687500;0.250000;
  0.750000;0.250000;
  0.812500;0.250000;
  0.875000;0.250000;
  0.937500;0.250000;
  1.000000;0.250000;
  0.062500;0.312500;
  0.000000;0.312500;
  0.125000;0.312500;
  0.187500;0.312500;
  0.250000;0.312500;
  0.312500;0.312500;
  0.375000;0.312500;
  0.437500;0.312500;
  0.500000;0.312500;
  0.562500;0.312500;
  0.625000;0.312500;
  0.687500;0.312500;
  0.750000;0.312500;
  0.812500;0.312500;
  0.875000;0.312500;
  0.937500;0.312500;
  1.000000;0.312500;
  0.062500;0.375000;
  0.000000;0.375000;
  0.125000;0.375000;
  0.187500;0.375000;
  0.250000;0.375000;
  0.312500;0.375000;
  0.375000;0.375000;
  0.437500;0.375000;
  0.500000;0.375000;
  0.562500;0.375000;
  0.625000;0.375000;
  0.687500;0.375000;
  0.750000;0.375000;
  0.812500;0.375000;
  0.875000;0.375000;
  0.937500;0.375000;
  1.000000;0.375000;
  0.062500;0.437500;
  0.000000;0.437500;
  0.125000;0.437500;
  0.187500;0.437500;
  0.250000;0.437500;
  0.312500;0.437500;
  0.375000;0.437500;
  0.437500;0.437500;
  0.500000;0.437500;
  0.562500;0.437500;
  0.625000;0.437500;
  0.687500;0.437500;
  0.750000;0.437500;
  0.812500;0.437500;
  0.875000;0.437500;
  0.937500;0.437500;
  1.000000;0.437500;
  0.062500;0.500000;
  0.000000;0.500000;
  0.125000;0.500000;
  0.187500;0.500000;
  0.250000;0.500000;
  0.312500;0.500000;
  0.375000;0.500000;
  0.437500;0.500000;
  0.500000;0.500000;
  0.562500;0.500000;
  0.625000;0.500000;
  0.687500;0.500000;
  0.750000;0.500000;
  0.812500;0.500000;
  0.875000;0.500000;
  0.937500;0.500000;
  1.000000;0.500000;
  0.062500;0.562500;
  0.000000;0.562500;
  0.125000;0.562500;
  0.187500;0.562500;
  0.250000;0.562500;
  0.312500;0.562500;
  0.375000;0.562500;
  0.437500;0.562500;
  0.500000;0.562500;
  0.562500;0.562500;
  0.625000;0.562500;
  0.687500;0.562500;
  0.750000;0.562500;
  0.812500;0.562500;
  0.875000;0.562500;
  0.937500;0.562500;
  1.000000;0.562500;
  0.062500;0.625000;
  0.000000;0.625000;
  0.125000;0.625000;
  0.187500;0.625000;
  0.250000;0.625000;
  0.312500;0.625000;
  0.375000;0.625000;
  0.437500;0.625000;
  0.500000;0.625000;
  0.562500;0.625000;
  0.625000;0.625000;
  0.687500;0.625000;
  0.750000;0.625000;
  0.812500;0.625000;
  0.875000;0.625000;
  0.937500;0.625000;
  1.000000;0.625000;
  0.062500;0.687500;
  0.000000;0.687500;
  0.125000;0.687500;
  0.187500;0.687500;
  0.250000;0.687500;
  0.312500;0.687500;
  0.375000;0.687500;
  0.437500;0.687500;
  0.500000;0.687500;
  0.562500;0.687500;
  0.625000;0.687500;
  0.687500;0.687500;
  0.750000;0.687500;
  0.812500;0.687500;
  0.875000;0.687500;
  0.937500;0.687500;
  1.000000;0.687500;
  0.062500;0.750000;
  0.000000;0.750000;
  0.125000;0.750000;
  0.187500;0.750000;
  0.250000;0.750000;
  0.312500;0.750000;
  0.375000;0.750000;
  0.437500;0.750000;
  0.500000;0.750000;
  0.562500;0.750000;
  0.625000;0.750000;
  0.687500;0.750000;
  0.750000;0.750000;
  0.812500;0.750000;
  0.875000;0.750000;
  0.937500;0.750000;
  1.000000;0.750000;
  0.062500;0.812500;
  0.000000;0.812500;
  0.125000;0.812500;
  0.187500;0.812500;
  0.250000;0.812500;
  0.312500;0.812500;
  0.375000;0.812500;
  0.437500;0.812500;
  0.500000;0.812500;
  0.562500;0.812500;
  0.625000;0.812500;
  0.687500;0.812500;
  0.750000;0.812500;
  0.812500;0.812500;
  0.875000;0.812500;
  0.937500;0.812500;
  1.000000;0.812500;
  0.062500;0.875000;
  0.000000;0.875000;
  0.125000;0.875000;
  0.187500;0.875000;
  0.250000;0.875000;
  0.312500;0.875000;
  0.375000;0.875000;
  0.437500;0.875000;
  0.500000;0.875000;
  0.562500;0.875000;
  0.625000;0.875000;
  0.687500;0.875000;
  0.750000;0.875000;
  0.812500;0.875000;
  0.875000;0.875000;
  0.937500;0.875000;
  1.000000;0.875000;
  0.062500;0.937500;
  0.000000;0.937500;
  0.125000;0.937500;
  0.187500;0.937500;
  0.250000;0.937500;
  0.312500;0.937500;
  0.375000;0.937500;
  0.437500;0.937500;
  0.500000;0.937500;
  0.562500;0.937500;
  0.625000;0.937500;
  0.687500;0.937500;
  0.750000;0.937500;
  0.812500;0.937500;
  0.875000;0.937500;
  0.937500;0.937500;
  1.000000;0.937500;
  0.031250;1.000000;
  0.093750;1.000000;
  0.156250;1.000000;
  0.218750;1.000000;
  0.281250;1.000000;
  0.343750;1.000000;
  0.406250;1.000000;
  0.468750;1.000000;
  0.531250;1.000000;
  0.593750;1.000000;
  0.656250;1.000000;
  0.718750;1.000000;
  0.781250;1.000000;
  0.843750;1.000000;
  0.906250;1.000000;
  0.968750;1.000000;;
 }
}
