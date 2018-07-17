#include "Tetris.h"
#include "Board.h"

Tetris::Tetris(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(180, 380)){
   // 创建记分状态栏
  wxStatusBar *sb = CreateStatusBar();

   // 设置初始分值为0
  sb->SetStatusText(wxT("0"));

   // 创建面板
  Board *board = new Board(this);

   // 设置焦点
  board->SetFocus();

   // 启动
  board->Start();
}
