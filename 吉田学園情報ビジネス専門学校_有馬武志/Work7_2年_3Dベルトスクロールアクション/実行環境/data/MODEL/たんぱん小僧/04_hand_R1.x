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
 24;
 -1.06373;-0.90717;2.67004;,
 -1.03816;1.02239;2.70434;,
 -12.16475;0.96214;2.26066;,
 -12.18506;-0.57183;2.23338;,
 0.88657;0.99630;1.18280;,
 0.86100;-0.93328;1.14850;,
 -12.12335;2.46894;1.09236;,
 -0.98611;2.91782;1.23476;,
 -14.06836;-0.74767;1.29182;,
 -14.04281;1.18190;1.32612;,
 -1.06196;-2.80760;1.13296;,
 -12.18365;-2.08270;1.01143;,
 -0.94440;2.91392;-1.09538;,
 -12.09021;2.46589;-0.76009;,
 0.92828;0.99240;-1.14735;,
 -12.08878;0.95508;-1.98204;,
 -0.94263;1.01351;-2.63246;,
 -14.00110;1.17804;-1.00402;,
 -0.96819;-0.91606;-2.66677;,
 -12.10910;-0.57893;-2.00931;,
 0.90271;-0.93711;-1.18166;,
 -12.15049;-2.08581;-0.84102;,
 -1.02024;-2.81149;-1.19718;,
 -14.02667;-0.75153;-1.03832;;
 
 26;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;6,2,1,7;,
 4;8,3,2,9;,
 4;10,0,3,11;,
 3;10,5,0;,
 3;4,7,1;,
 3;6,9,2;,
 3;8,11,3;,
 4;7,12,13,6;,
 4;14,12,7,4;,
 4;15,13,12,16;,
 4;9,6,13,17;,
 3;14,16,12;,
 3;15,17,13;,
 4;16,18,19,15;,
 4;20,18,16,14;,
 4;21,19,18,22;,
 4;17,15,19,23;,
 3;20,22,18;,
 3;21,23,19;,
 4;22,10,11,21;,
 4;5,10,22,20;,
 4;23,21,11,8;,
 4;20,14,4,5;,
 4;8,9,17,23;;
 
 MeshMaterialList {
  8;
  26;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.109600;0.313600;0.536800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.743200;0.712000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.109600;0.109600;0.109600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.514400;0.329600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.536800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.332800;0.332800;0.332800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   0.500000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "heimin.jpg";
   }
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   0.500000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "heimin.jpg";
   }
  }
 }
 MeshNormals {
  26;
  0.291488;-0.334785;0.896077;,
  0.302094;0.301093;0.904479;,
  -0.221684;0.315779;0.922573;,
  -0.227621;-0.335899;0.913981;,
  0.348088;0.830915;0.434069;,
  0.340443;0.841316;-0.419865;,
  -0.269252;0.861114;-0.431261;,
  -0.266102;0.861155;0.433130;,
  0.291322;0.330900;-0.897573;,
  0.285822;-0.312624;-0.905854;,
  -0.242900;-0.306715;-0.920285;,
  -0.232543;0.338997;-0.911595;,
  0.322775;-0.844877;-0.426613;,
  0.323172;-0.844540;0.426981;,
  -0.284550;-0.858924;0.425771;,
  -0.294005;-0.849103;-0.438846;,
  0.832216;-0.367467;-0.415192;,
  0.837706;0.357516;-0.412832;,
  0.835397;0.339700;0.432106;,
  0.822149;-0.373763;0.429386;,
  -0.399700;-0.319540;0.859148;,
  -0.395385;0.305178;0.866336;,
  -0.723512;0.456455;-0.517861;,
  -0.411418;-0.290071;-0.864057;,
  -0.879233;0.476105;-0.016523;,
  -0.891490;-0.452785;-0.015199;;
  26;
  4;0,1,2,3;,
  4;18,1,0,19;,
  4;7,2,1,4;,
  4;20,3,2,21;,
  4;13,0,3,14;,
  3;13,19,0;,
  3;18,4,1;,
  3;7,21,2;,
  3;20,14,3;,
  4;4,5,6,7;,
  4;17,5,4,18;,
  4;11,6,5,8;,
  4;24,7,6,22;,
  3;17,8,5;,
  3;11,22,6;,
  4;8,9,10,11;,
  4;16,9,8,17;,
  4;15,10,9,12;,
  4;22,11,10,23;,
  3;16,12,9;,
  3;15,23,10;,
  4;12,13,14,15;,
  4;19,13,12,16;,
  4;25,15,14,25;,
  4;16,17,18,19;,
  4;25,24,22,25;;
 }
 MeshTextureCoords {
  24;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
