#include "wx/wx.h"
#include "wx/sizer.h"

#include "ReadFile.h"
#include "String_.h"

#include "EndeavorGame.h"

class EndeavorApp : public wxApp
{
	public:
		bool OnInit();
};

IMPLEMENT_APP(EndeavorApp)

bool EndeavorApp::OnInit()
{
	/*
	int num_players = 1;
	
	if (wxApp::argc >= 2)
	{
		char* num_players_str = (char*) wxApp::argv[1].ToStdString().c_str();
		int n_p = Utils::chartoi(num_players_str);
		num_players = n_p;
	}
	*/
	//make sure auto display scaling is disabled!
	int screen_width = wxSystemSettings::GetMetric (wxSYS_SCREEN_X);
	int screen_height = wxSystemSettings::GetMetric (wxSYS_SCREEN_Y);

	EndeavorGame* endeavor_game = new EndeavorGame(screen_width, screen_height);
	
	CSC2110::String title_str("Endeavor");
	std::string title_std_str(title_str.get_std_str());
	endeavor_game->setTitle(title_std_str);
	endeavor_game->showGUI();
	
	/*
	CSC2110::ReadFile* rf = new CSC2110::ReadFile("resources/endeavor_clicks.txt");
	String* x_str = rf->readLine();
	String* y_str = NULL;
	
	while(!rf->eof())
	{
		String* y_str = rf->readLine();
		int x = x_str->a_to_i();
		int y = y_str->a_to_i();
		endeavor_game->mouseClicked(x, y);
	
		delete x_str;
		delete y_str;
		x_str = rf->readLine();
	}
	delete rf;
*/
    return true;
} 
