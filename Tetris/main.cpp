#include "main.h"
#include "Tetris.h"

// 应用程序实例化
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
     // 设置随机种子
    srand(time(NULL));

     // 创建框架
    Tetris *tetris = new Tetris(wxT("Tetris"));
     // 框架剧中
    tetris->Centre();
     // 框架显示
    tetris->Show(true);

    return true;
}
