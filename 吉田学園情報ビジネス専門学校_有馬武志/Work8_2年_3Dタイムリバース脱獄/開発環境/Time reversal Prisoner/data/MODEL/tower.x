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
 172;
 -57.28593;369.73010;-47.44318;,
 44.20927;369.73010;-47.44318;,
 57.61514;-1.48148;-60.84906;,
 -70.69185;-1.48148;-60.84906;,
 44.20927;369.73010;-47.44318;,
 44.20927;369.73010;54.05243;,
 57.61514;-1.48148;67.45831;,
 57.61514;-1.48148;-60.84906;,
 44.20927;369.73010;54.05243;,
 -57.28593;369.73010;54.05243;,
 -70.69185;-1.48148;67.45831;,
 57.61514;-1.48148;67.45831;,
 -57.28593;369.73010;54.05243;,
 -57.28593;369.73010;-47.44318;,
 -70.69185;-1.48148;-60.84906;,
 -70.69185;-1.48148;67.45831;,
 44.20927;369.73010;-47.44318;,
 -57.28593;369.73010;-47.44318;,
 -70.69185;-1.48148;-60.84906;,
 57.61514;-1.48148;-60.84906;,
 -82.16944;408.19040;-72.32697;,
 69.09276;408.19040;-72.32697;,
 57.61514;366.15384;-60.84906;,
 -70.69185;366.15384;-60.84906;,
 69.09276;408.19040;-72.32697;,
 69.09276;408.19040;78.93622;,
 57.61514;366.15384;67.45831;,
 57.61514;366.15384;-60.84906;,
 69.09276;408.19040;78.93622;,
 -82.16944;408.19040;78.93622;,
 -70.69185;366.15384;67.45831;,
 57.61514;366.15384;67.45831;,
 -82.16944;408.19040;78.93622;,
 -82.16944;408.19040;-72.32697;,
 -70.69185;366.15384;-60.84906;,
 -70.69185;366.15384;67.45831;,
 69.09276;408.19040;-72.32697;,
 -82.16944;408.19040;-72.32697;,
 -70.69185;366.15384;-60.84906;,
 57.61514;366.15384;-60.84906;,
 -82.16944;408.19040;78.93622;,
 69.09276;408.19040;78.93622;,
 69.09276;408.19040;-72.32697;,
 -82.16944;408.19040;-72.32697;,
 -65.77126;443.40927;62.53778;,
 52.69460;443.40927;62.53778;,
 52.69460;443.40927;-55.92853;,
 -65.77126;443.40927;-55.92853;,
 -72.97118;461.17093;-63.12848;,
 59.89445;461.17093;-63.12848;,
 68.34200;439.23495;-71.57599;,
 -81.41868;439.23495;-71.57599;,
 59.89445;461.17093;-63.12848;,
 59.89445;461.17093;69.73773;,
 68.34200;439.23495;78.18512;,
 68.34200;439.23495;-71.57599;,
 59.89445;461.17093;69.73773;,
 -72.97118;461.17093;69.73773;,
 -81.41868;439.23495;78.18512;,
 68.34200;439.23495;78.18512;,
 -72.97118;461.17093;69.73773;,
 -72.97118;461.17093;-63.12848;,
 -81.41868;439.23495;-71.57599;,
 -81.41868;439.23495;78.18512;,
 59.89445;461.17093;-63.12848;,
 -72.97118;461.17093;-63.12848;,
 -81.41868;439.23495;-71.57599;,
 68.34200;439.23495;-71.57599;,
 -72.97118;461.17093;69.73773;,
 59.89445;461.17093;69.73773;,
 59.89445;461.17093;-63.12848;,
 -72.97118;461.17093;-63.12848;,
 -50.67165;476.12662;-40.82794;,
 37.59491;476.12662;-40.82794;,
 37.59491;459.68930;-40.82794;,
 -50.67165;459.68930;-40.82794;,
 37.59491;476.12662;-40.82794;,
 37.59491;476.12662;47.43768;,
 37.59491;459.68930;47.43768;,
 37.59491;459.68930;-40.82794;,
 37.59491;476.12662;47.43768;,
 -50.67165;476.12662;47.43768;,
 -50.67165;459.68930;47.43768;,
 37.59491;459.68930;47.43768;,
 -50.67165;476.12662;47.43768;,
 -50.67165;476.12662;-40.82794;,
 -50.67165;459.68930;-40.82794;,
 -50.67165;459.68930;47.43768;,
 37.59491;476.12662;-40.82794;,
 -50.67165;476.12662;-40.82794;,
 -50.67165;459.68930;-40.82794;,
 37.59491;459.68930;-40.82794;,
 55.67638;440.50684;66.18658;,
 65.36433;440.50684;66.18658;,
 65.36433;407.79504;66.18658;,
 55.67638;407.79504;66.18658;,
 65.36433;440.50684;66.18658;,
 65.36433;440.50684;75.87408;,
 65.36433;407.79504;75.87408;,
 65.36433;407.79504;66.18658;,
 65.36433;440.50684;75.87408;,
 55.67638;440.50684;75.87408;,
 55.67638;407.79504;75.87408;,
 65.36433;407.79504;75.87408;,
 55.67638;440.50684;75.87408;,
 55.67638;440.50684;66.18658;,
 55.67638;407.79504;66.18658;,
 55.67638;407.79504;75.87408;,
 65.36433;440.50684;66.18658;,
 55.67638;440.50684;66.18658;,
 55.67638;407.79504;66.18658;,
 65.36433;407.79504;66.18658;,
 -75.73819;440.50684;66.18658;,
 -66.05024;440.50684;66.18658;,
 -66.05024;407.79504;66.18658;,
 -75.73819;407.79504;66.18658;,
 -66.05024;440.50684;66.18658;,
 -66.05024;440.50684;75.87408;,
 -66.05024;407.79504;75.87408;,
 -66.05024;407.79504;66.18658;,
 -66.05024;440.50684;75.87408;,
 -75.73819;440.50684;75.87408;,
 -75.73819;407.79504;75.87408;,
 -66.05024;407.79504;75.87408;,
 -75.73819;440.50684;75.87408;,
 -75.73819;440.50684;66.18658;,
 -75.73819;407.79504;66.18658;,
 -75.73819;407.79504;75.87408;,
 -66.05024;440.50684;66.18658;,
 -75.73819;440.50684;66.18658;,
 -75.73819;407.79504;66.18658;,
 -66.05024;407.79504;66.18658;,
 -75.73819;440.50684;-69.78973;,
 -66.05024;440.50684;-69.78973;,
 -66.05024;407.79504;-69.78973;,
 -75.73819;407.79504;-69.78973;,
 -66.05024;440.50684;-69.78973;,
 -66.05024;440.50684;-60.10223;,
 -66.05024;407.79504;-60.10223;,
 -66.05024;407.79504;-69.78973;,
 -66.05024;440.50684;-60.10223;,
 -75.73819;440.50684;-60.10223;,
 -75.73819;407.79504;-60.10223;,
 -66.05024;407.79504;-60.10223;,
 -75.73819;440.50684;-60.10223;,
 -75.73819;440.50684;-69.78973;,
 -75.73819;407.79504;-69.78973;,
 -75.73819;407.79504;-60.10223;,
 -66.05024;440.50684;-69.78973;,
 -75.73819;440.50684;-69.78973;,
 -75.73819;407.79504;-69.78973;,
 -66.05024;407.79504;-69.78973;,
 56.23228;440.50684;-68.49689;,
 65.92024;440.50684;-68.49689;,
 65.92024;407.79504;-68.49689;,
 56.23228;407.79504;-68.49689;,
 65.92024;440.50684;-68.49689;,
 65.92024;440.50684;-58.80939;,
 65.92024;407.79504;-58.80939;,
 65.92024;407.79504;-68.49689;,
 65.92024;440.50684;-58.80939;,
 56.23228;440.50684;-58.80939;,
 56.23228;407.79504;-58.80939;,
 65.92024;407.79504;-58.80939;,
 56.23228;440.50684;-58.80939;,
 56.23228;440.50684;-68.49689;,
 56.23228;407.79504;-68.49689;,
 56.23228;407.79504;-58.80939;,
 65.92024;440.50684;-68.49689;,
 56.23228;440.50684;-68.49689;,
 56.23228;407.79504;-68.49689;,
 65.92024;407.79504;-68.49689;;
 
 51;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;60,53,64,65;,
 4;66,67,54,63;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;84,77,88,89;,
 4;90,91,78,87;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;104,97,108,109;,
 4;110,111,98,107;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;124,117,128,129;,
 4;130,131,118,127;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;144,137,148,149;,
 4;150,151,138,147;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;164,157,168,169;,
 4;170,171,158,167;;
 
 MeshMaterialList {
  1;
  51;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game103\\Desktop\\マップエディタ\\ver.1.8.1\\マップエディタ\\data\\TEXTURE\\cona.jpg";
   }
  }
 }
 MeshNormals {
  18;
  0.000000;0.036090;-0.999349;,
  0.999349;0.036090;0.000000;,
  0.000000;0.036090;0.999349;,
  0.000000;-0.263403;-0.964686;,
  0.964687;-0.263397;-0.000000;,
  0.000000;-0.263403;0.964686;,
  0.000000;1.000000;0.000000;,
  0.000000;0.359372;-0.933194;,
  0.933194;0.359373;0.000000;,
  0.000000;0.359367;0.933196;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.999349;0.036090;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.964688;-0.263397;0.000000;,
  -0.933195;0.359371;0.000000;,
  -1.000000;0.000000;0.000000;;
  51;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;13,13,13,13;,
  4;6,6,6,6;,
  4;14,14,14,14;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;15,15,15,15;,
  4;6,6,6,6;,
  4;14,14,14,14;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;16,16,16,16;,
  4;6,6,6,6;,
  4;14,14,14,14;,
  4;6,6,6,6;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;17,17,17,17;,
  4;6,6,6,6;,
  4;14,14,14,14;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;17,17,17,17;,
  4;6,6,6,6;,
  4;14,14,14,14;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;17,17,17,17;,
  4;6,6,6,6;,
  4;14,14,14,14;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;17,17,17,17;,
  4;6,6,6,6;,
  4;14,14,14,14;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;17,17,17,17;,
  4;6,6,6,6;,
  4;14,14,14,14;;
 }
 MeshTextureCoords {
  172;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
