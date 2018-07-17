#include <stdlib.h>
#include <algorithm>
#include "Shape.h"

using namespace std;

void Shape::SetShape(Tetrominoes shape)
{
    static const int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },		 // 无图形
      { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } }, // Z图形
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },// S图形
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },             // 线图形
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },// T图形
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },             // 方形
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },// L形
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }               // 反L形
    };

     // 设置当前的图形
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            coords[i][j] = coordsTable[shape][i][j];
    }
     // 保存当前类型
    pieceShape = shape;
}


void Shape::SetRandomShape(){
   // 设置随机图形
  int x = rand() % 7 + 1;
  SetShape(Tetrominoes(x));
}

int Shape::MinX() const{
  int m = coords[0][0];
  for (int i=0; i<4; i++) {
      m = min(m, coords[i][0]);
  }
  return m;
}

int Shape::MaxX() const {
  int m = coords[0][0];
  for (int i=0; i<4; i++) {
      m = max(m, coords[i][0]);
  }
  return m;
}

int Shape::MinY() const {
  int m = coords[0][1];
  for (int i=0; i<4; i++) {
      m = min(m, coords[i][1]);
  }
  return m;
}

int Shape::MaxY() const {
  int m = coords[0][1];
  for (int i=0; i<4; i++) {
      m = max(m, coords[i][1]);
  }
  return m;
}

Shape Shape::RotateLeft() const {
     // 方块不旋转
    if (pieceShape == SquareShape)
        return *this;

    Shape result;
    result.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        result.SetX(i, y(i));
        result.SetY(i, -x(i));
    }
    return result;
}

Shape Shape::RotateRight() const {
     // 方块不旋转
    if (pieceShape == SquareShape)
        return *this;

    Shape result;
    result.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        result.SetX(i, -y(i));
        result.SetY(i, x(i));
    }
    return result;
}
