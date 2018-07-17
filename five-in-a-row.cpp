#include <wx/wx.h>
#include <cstdlib>
#include <cmath>

using namespace std;

// 面板类
class TestPanel:public wxPanel{
public:
	TestPanel(wxFrame* parent):wxPanel(parent),cell(20),broad(18*cell),black(true),timer(this,wxID_ANY){
		// 绑定绘制事件
		Bind(wxEVT_PAINT,&TestPanel::OnPaint,this);
		// 绑定鼠标单机事件
		Bind(wxEVT_LEFT_DOWN,&TestPanel::OnLeftDown,this);
		Bind(wxEVT_MOTION,&TestPanel::OnMove,this);
		Bind(wxEVT_KEY_DOWN,&TestPanel::OnKeyDown,this);
		Bind(wxEVT_TIMER,&TestPanel::OnTimer,this);
		memset(record,0,19*19*sizeof(char));
		timer.Start(500);
		curX = 9;
		curY = -1;
    coords[0] = wxPoint(0,0);
	coords[1] = wxPoint(1,0);
	coords[2] = wxPoint(0,-1);
	coords[3] = wxPoint(0,-2);
	}
	void OnTimer(wxTimerEvent& event){
		if(curY<17)curY++;
		Refresh();
	}
	void OnKeyDown(wxKeyEvent & event){
		switch(event.GetKeyCode()){
			case WXK_LEFT:
			if(0<curX&&curY!=17)curX--;
			break;
			case WXK_RIGHT:
			if(curX<17&&curY!=17)curX++;
			break;
			case WXK_DOWN:
			if(curY<17)curY++;
			break;
			case WXK_UP:
			//for(int i=0;i<4;i++){
			//	swap(coords[i].x,coords[i].y);
			//	coords[i].y *=-1;
			//}		
			//break;
			//case WXK_SPACE:
			for(int i=0;i<4;i++){
				swap(coords[i].x,coords[i].y);
				coords[i].x *=-1;
			}		
			break;
		}
		Refresh();
	}
	wxPoint GetBroadPos(wxPoint const& pos){
		wxPoint temp = pos - vec;
		float fx = 1.0*temp.x/cell;
		float fy = 1.0*temp.y/cell;
	    // 规则二：必须下在交点
		return wxPoint(round(fx),round(fy));

	}
	void OnMove(wxMouseEvent& event){
		pos = event.GetPosition();
		Refresh();	
	}
	void OnLeftDown(wxMouseEvent &event){
		wxPoint pos = GetBroadPos(event.GetPosition());
		// 规则一：必须下在棋盘上
		if(pos.x >= 0 && pos.x <=18 && pos.y >= 0 && pos.y <= 18){
			// 规则三：必须下在没有棋子的地方
			if(record[pos.x][pos.y] == 0){
		       record[pos.x][pos.y] = black?1:2;
			   // 规则四：黑白子交替下
			   black = !black;
			   Refresh();// 刷新
			}
		}
		if(Success(pos.x,pos.y)){
			wxMessageBox(wxT("You Win"));
		}
	}
	bool Success(int x,int y){
		// 横向检测
		int count = 1;
		// 左向
		for(int i=1;i<5;i++){
			if(x-i<0)break;
			if(record[x][y] != record[x-i][y])break;
			count++;
		}
		if(5 == count)return true;
		for(int i=1;i<5;i++){
			if(x+i>18)break;
			if(record[x][y] != record[x+i][y])break;
			count++;
		}
		if(5 <= count)return true;
		

		// 纵向检测
		// 左斜向
		//
		return false;
	}
	void DrawTetris(wxPaintDC& dc,int x,int y){
		for(int i=0;i<4;i++){
			dc.SetPen(*wxWHITE_PEN);
			DrawRect(dc,x+coords[i].x,y+coords[i].y);
		}
		
		dc.DrawText(wxString::Format(wxT("(%d,%d)"),x,y),wxPoint(10,10));
	}
	void DrawRect(wxPaintDC& dc,int x,int y){
		wxPoint pos = vec+wxPoint(x*cell,y*cell);
		dc.DrawRectangle(pos,wxSize(cell,cell));
	}
    // 事件处理函数
	void OnPaint(wxPaintEvent &event){
		// 绘制设备上下文
		wxPaintDC dc(this);

		wxSize size = GetClientSize();
		
		int left = (size.x - broad)/2;
		int top = (size.y - broad)/2;
		vec = wxPoint(left,top);
		// 行
		for(int i=0;i<19;i++){
			//dc.DrawLine(wxPoint(0,i*cell)+vec,wxPoint(18*cell,i*cell)+vec);
			dc.DrawLine(wxPoint(left,top+i*cell),wxPoint(left+18*cell,top+i*cell));
		}
		for(int i=0;i<19;i++){
			dc.DrawLine(wxPoint(i*cell,0)+vec,wxPoint(i*cell,18*cell)+vec);
		}
		
		for(int i=0;i<19;i++){
			for(int j=0;j<19;j++){
				if(record[i][j] != 0){
					DownChess(dc,i,j,record[i][j] == 2?true:false);
				}		
			}
		}
		if(!black){
			dc.SetBrush(*wxWHITE_BRUSH);
		}else{
		    dc.SetBrush(*wxBLACK_BRUSH);
		}
		dc.DrawCircle(pos,cell/2);
		DrawTetris(dc,curX,curY);
	}

	void DownChess(wxPaintDC& dc,int x,int y,bool white){
		if(white){
			dc.SetBrush(*wxWHITE_BRUSH);
		}else{
		    dc.SetBrush(*wxBLACK_BRUSH);
		}
		dc.DrawCircle(wxPoint(x*cell,y*cell)+vec,cell/2);
	}
private:
    wxPoint coords[4];
	wxPoint pos;
	const int cell;
	const int broad;
	wxPoint vec;
	char record[19][19];
	bool black;
	wxTimer timer;
	int curX;
	int curY;
};

// 框架类
class TestFrame:public wxFrame{
public:
	TestFrame(wxString const&title):wxFrame(NULL,wxID_ANY,title){
		// 创建面板对象
		wxPanel* pPanel = new TestPanel(this);
	}
};

// 应用程序类
class FrameApp:public wxApp{
	// 重写初始化函数
	bool OnInit(){
		// 创建框架
		wxFrame* pFrame = new TestFrame(wxT("MyFrame"));
		// 显示框架
		pFrame->Show(true);
		return true;
	}
};

IMPLEMENT_APP(FrameApp);//应用程序实例化
