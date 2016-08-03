#include <wx/wx.h>

class my_first_app : public wxApp
{
public:
	bool OnInit()
	{
		wxFrame* window = new wxFrame(NULL, -1, "Hello World!");
		window->Center();
		window->Show();
		return true;
	}
};

IMPLEMENT_APP(my_first_app);