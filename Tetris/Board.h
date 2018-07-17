#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include <wx/wx.h>

/**
* @breif 面板类
*/
class Board : public wxPanel {

public:
     /**
    * @breif 构造函数
     *
     * @param parent 框架类
     */
    Board(wxFrame *parent);

     /**
    * @breif 启动
     */
    void Start();

     /**
    * @breif 暂停
     */
    void Pause();

     /**
    * @breif 暂停
     */
    void linesRemovedChanged(int numLines);

protected:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxCommandEvent& event);

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    Tetrominoes & ShapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }

    int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
    int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }

     /**
    * @breif 清空面板
     */
    void ClearBoard();

     /**
    * @breif 下落
     */
    void DropDown();

     /**
    * @breif 下落一行
     */
    void OneLineDown();

    void PieceDropped();

    void RemoveFullLines();

     /**
    * @breif 创建新的方块
     */
    void NewPiece();

     /**
    * @breif 尝试移动
     */
    bool TryMove(const Shape& newPiece, int newX, int newY);

     /**
     * @brief 绘制方块
     */
    void DrawSquare(wxPaintDC &dc, int x, int y, Tetrominoes shape);

    wxTimer *timer;					///< 计时器
    bool isStarted;					///< 开始状态
    bool isPaused;					///< 暂停状态
    bool isFallingFinished;				///< 下落完成

    Shape curPiece;					///< 当前方块
    int curX;						///< 当前方块X坐标
    int curY;						///< 当前方块Y坐标

    int numLinesRemoved;					///< 移除行数
    Tetrominoes board[BoardWidth * BoardHeight];	///< 方块面板
    wxStatusBar *m_stsbar; 				///< 分值状态栏
};

#endif
