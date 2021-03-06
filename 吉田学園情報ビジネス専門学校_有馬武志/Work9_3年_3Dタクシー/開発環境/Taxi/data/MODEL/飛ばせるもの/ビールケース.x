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
 40;
 2.50674;0.02296;-3.65023;,
 -2.47033;-0.00940;-3.62451;,
 -2.47191;3.54041;-3.62434;,
 2.49986;3.52246;-3.64135;,
 2.50674;0.02296;-3.65023;,
 -2.47033;-0.00940;-3.62451;,
 -2.50681;0.00401;3.64318;,
 2.50065;0.00273;3.64799;,
 2.49860;3.52088;3.64753;,
 -2.48955;3.53941;3.64921;,
 -2.50681;0.00401;3.64318;,
 2.50065;0.00273;3.64799;,
 2.50065;0.00273;3.64799;,
 -2.50681;0.00401;3.64318;,
 -2.47033;-0.00940;-3.62451;,
 2.50674;0.02296;-3.65023;,
 -2.47033;-0.00940;-3.62451;,
 -2.50681;0.00401;3.64318;,
 -2.48955;3.53941;3.64921;,
 -2.47191;3.54041;-3.62434;,
 2.50065;0.00273;3.64799;,
 2.50674;0.02296;-3.65023;,
 2.49986;3.52246;-3.64135;,
 2.49860;3.52088;3.64753;,
 2.48839;0.03435;3.60696;,
 -2.50681;0.00401;3.64318;,
 -2.48955;3.53941;3.64921;,
 2.49860;3.52088;3.64753;,
 2.49986;3.52246;-3.64135;,
 -2.47191;3.54041;-3.62434;,
 -2.47033;-0.00940;-3.62451;,
 2.50674;0.02296;-3.65023;,
 2.50674;0.02296;-3.65023;,
 2.50065;0.00273;3.64799;,
 2.49860;3.52088;3.64753;,
 2.49986;3.52246;-3.64135;,
 -2.50681;0.00401;3.64318;,
 -2.47033;-0.00940;-3.62451;,
 -2.47191;3.54041;-3.62434;,
 -2.48955;3.53941;3.64921;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;;
 
 MeshMaterialList {
  1;
  10;
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
    "ビールケース.png";
   }
  }
 }
 MeshNormals {
  10;
  -0.004291;0.001287;-0.999990;,
  -0.000315;-0.000789;1.000000;,
  -0.003114;0.999995;0.000462;,
  -0.003778;0.006689;-0.999971;,
  0.003114;-0.999995;-0.000462;,
  -0.999991;0.002220;-0.003721;,
  0.999999;0.001275;0.000504;,
  0.004291;-0.001287;0.999990;,
  -0.999999;-0.001275;-0.000504;,
  0.999991;-0.002220;0.003721;;
  10;
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;3,3,3,3;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  40;
  0.494868;1.000659;,
  0.005750;1.000659;,
  0.005750;0.497510;,
  0.494868;0.497510;,
  0.675579;0.989336;,
  0.748710;0.989336;,
  0.748710;0.739336;,
  0.675579;0.739336;,
  0.003735;0.506195;,
  0.500024;0.502973;,
  0.498932;1.001381;,
  0.002642;1.001381;,
  0.569162;0.985320;,
  0.819162;0.985320;,
  0.819162;0.735320;,
  0.569162;0.735320;,
  0.500169;0.501847;,
  0.002858;0.501847;,
  0.002858;-0.001400;,
  0.500169;-0.001400;,
  0.499935;0.500468;,
  0.001522;0.500468;,
  0.001522;0.000702;,
  0.499935;0.000702;,
  0.433970;1.000000;,
  0.923900;1.000000;,
  0.923900;0.502572;,
  0.433970;0.502572;,
  0.928268;0.505698;,
  0.436703;0.505698;,
  0.436703;1.001624;,
  0.928268;1.001624;,
  0.438324;0.999448;,
  0.919858;0.999448;,
  0.919858;0.502603;,
  0.438324;0.502603;,
  0.437078;1.001940;,
  0.919933;1.001940;,
  0.919933;0.503561;,
  0.437078;0.503561;;
 }
}
