#include "GameServer.h"

#include "wx/wx.h"
#include "wx/sizer.h"

#include "EndeavorGame.h"

class EndeavorServerApp : public wxApp
{
	public:
		bool OnInit();
};

IMPLEMENT_APP(EndeavorServerApp)


bool EndeavorServerApp::OnInit()
{	
	int screen_width = wxSystemSettings::GetMetric (wxSYS_SCREEN_X);
	int screen_height = wxSystemSettings::GetMetric (wxSYS_SCREEN_Y);

	std::string ip = "127.0.0.1";
	int port= 6789;
	int num_play = 5;
	
	EndeavorGame* endeavor_game = new EndeavorGame(screen_width, screen_height);
		
	CSC2110::String title_str("EndeavorServer");
	std::string title_std_str(title_str.get_std_str());
	endeavor_game->setTitle(title_std_str);
	endeavor_game->showGUI();
	
	
	if(wxApp::argc == 3)
	{	
		ip = wxApp::argv[0].ToStdString();
		
		std::string port_num_std_str = wxApp::argv[1].ToStdString();
		CSC2110::String port_num_str(port_num_std_str.c_str());
		port= port_num_str.a_to_i();
		
		std::string num_players_std_str = wxApp::argv[2].ToStdString();
		CSC2110::String num_players_str(num_players_std_str.c_str());
		num_play = num_players_str.a_to_i();
	}
	
	GameServer* game_server = new GameServer(ip, port, num_play, endeavor_game);

    return true;
} 
