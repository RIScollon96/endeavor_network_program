#include "GameClient.h"

#include "wx/wx.h"
#include "wx/sizer.h"

#include "EndeavorGame.h"

class EndeavorClientApp : public wxApp
{
	public:
		bool OnInit();
};

IMPLEMENT_APP(EndeavorClientApp)

bool EndeavorClientApp::OnInit()
{
	
	int screen_width = wxSystemSettings::GetMetric (wxSYS_SCREEN_X);
	int screen_height = wxSystemSettings::GetMetric (wxSYS_SCREEN_Y);

	EndeavorGame* endeavor_game = new EndeavorGame(screen_width, screen_height);
	
	CSC2110::String title_str("Endeavor");
	std::string title_std_str(title_str.get_std_str());
	endeavor_game->setTitle(title_std_str);
	endeavor_game->showGUI();
	
	std::string ip_address = "127.0.0.1";
	int port_num = 6789;
	
	if(wxApp::argc == 2)
	{	
		ip_address = wxApp::argv[0].ToStdString();
		
		std::string port_num_std_str = wxApp::argv[1].ToStdString();
		CSC2110::String port_num_str(port_num_std_str.c_str());
		port_num = port_num_str.a_to_i();
	}
	
	GameClient* game_client = new GameClient(ip_address, port_num, endeavor_game);
	
    return true;
}
