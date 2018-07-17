#ifndef SHAPE_H
#define SHAPE_H

/**
* @breif 方块类型
*/
enum Tetrominoes {
	NoShape, 		///< 无图形
	ZShape,  		///< Z图形
	SShape,  		///< S图形
	LineShape, 		///< 线图形
	TShape, 		///< T图形
	SquareShape, 	///< 方形
	LShape,  		///< L形
	MirroredLShape 	///< 反L形
};

/**
* @breif 图形类
*
* @details
* 1. 管理类型
* 2. 获取图像边界
* 3. 旋转方块
*/
class Shape {
public:
     /**
    * @breif 构造函数
     */
    Shape() { SetShape(NoShape); }

     /**
     * @breif 设置图形类型
     *
     * @param shape 图形类型
     */
    void SetShape(Tetrominoes shape);

     /**
     * @breif 设置随机图形
     */
    void SetRandomShape();

     /**
     * @breif 获取图形类型
     *
     * @return 图形类型
     */
    Tetrominoes GetShape() const { return pieceShape; }

    int x(int index) const { return coords[index][0]; }
    int y(int index) const { return coords[index][1]; }

    int MinX() const;
    int MaxX() const;
    int MinY() const;
    int MaxY() const;

     /**
     * @breif 获取左旋图形
     *
     * @return 图形
     */
    Shape RotateLeft() const;

     /**
     * @breif 获取右旋图形
     *
     * @return 图形
     */
    Shape RotateRight() const;

private:
    void SetX(int index, int x) { coords[index][0] = x; }
    void SetY(int index, int y) { coords[index][1] = y; }
    Tetrominoes pieceShape;///< 方块类型
    int coords[4][2];      ///< 方块坐标
};

#endif
