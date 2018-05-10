#include "EndeavorGame.h"

#include "Permutation.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
#include "Integer.h"

#include "ImageLoader.h"
#include "PixelXML.h"
#include "PixelPoint.h"
#include "PixelDimension.h"

void EndeavorGame::disableGame()
{
	changeToGameOverState();
}

void EndeavorGame::repaint()
{
	endeavor_gui->Refresh();
}

bool EndeavorGame::isGameOver()
{
	return players->getGameRound() == 8;
}

int EndeavorGame::getPlayerID()
{
	return (int) getActivePlayer();
}

bool EndeavorGame::canOccupyInRegion(uint8 player_id, EndeavorRegionType region_type)
{
	return board->canOccupyInRegion(player_id, region_type);
}

EndeavorRegionType EndeavorGame::getRegionWithCity(uint8 city_id)
{
	return board->getRegionWithCity(city_id);
}

void EndeavorGame::useActionToken(uint8 active_player, EndeavorBuildingType building_type)
{
	players->useActionToken(active_player, building_type);
}

void EndeavorGame::discard(uint8 player_id, uint8 card_id)
{
	Card* card = players->discard(player_id, card_id);
	board->returnCardToRegion(card);
}

uint8 EndeavorGame::findSelectedCardToDiscard(uint8 player_id, uint32 x, uint32 y)
{
	return players->findSelectedCardToDiscard(player_id, x, y);
}

bool EndeavorGame::mustDiscard(uint8 player_id)
{
	return players->mustDiscard(player_id);
}

void EndeavorGame::moveGovernorCardToPlayer(uint8 player_id, EndeavorRegionType region_type)
{
	Card* governor_card = board->moveGovernorCardToPlayer(region_type);
	players->takeSelectedCard(player_id, governor_card);
}

bool EndeavorGame::canAssignGovernorCard(EndeavorRegionType region_type)
{
	return board->canAssignGovernorCard(region_type);
}

uint8 EndeavorGame::assignGovernorCard(EndeavorRegionType region_type)
{
	return board->assignGovernorCard(region_type);
}

void EndeavorGame::ship(uint8 player_id, EndeavorRegionType region_type)
{
	wxBitmap* player_img = players->getPlayerImage(player_id);
	EndeavorTokenType token_type = board->ship(player_id, region_type, player_img);
	players->ship(player_id, token_type);
}

EndeavorRegionType EndeavorGame::findSelectedShip(uint32 x, uint32 y)
{
	return board->findSelectedShip(x, y);
}

bool EndeavorGame::canShipInAnyRegion(uint8 player_id)
{
	return board->canShipInAnyRegion(player_id);
}

//methods for board (regions)
void EndeavorGame::processOccupyAttackTokens(uint8 player_id, uint8 city_id, CSC2110::ListArray<CSC2110::Integer>* tokens)
{
	CSC2110::ListArray<Connection>* possible_control = connections->getAllConnectionsContainingCityID(city_id);
	CSC2110::ListArrayIterator<Connection>* possible_control_iter = possible_control->iterator();
	while(possible_control_iter->hasNext())
	{
		Connection* conn = possible_control_iter->next();
		uint8 other_city_in_connection = 0;
		uint8 player_id_in_other_city = 0;
		if (conn->getCity1ID() == city_id)
		{
			other_city_in_connection = conn->getCity2ID();
			player_id_in_other_city = board->getPlayerIDInCity(other_city_in_connection);
		}
		else
		{
			other_city_in_connection = conn->getCity1ID();
			player_id_in_other_city = board->getPlayerIDInCity(other_city_in_connection);
		}
		
		if (player_id_in_other_city == player_id)
		{
			wxBitmap* player_circle_img = players->getPlayerImage(player_id);
			EndeavorTokenType token_type = conn->takeControlOfConnection(player_id, player_circle_img);
			if (token_type != INVALID_TOKEN_TYPE)
			{
				tokens->add(new CSC2110::Integer(token_type));
			}
		}
		
		else if (player_id_in_other_city > 0)
		{
			conn->breakControlOfConnection();
		}
	}
}

void EndeavorGame::occupyCity(uint8 player_id, uint8 city_id)
{
	CSC2110::ListArray<CSC2110::Integer>* all_tokens = new CSC2110::ListArray<CSC2110::Integer>();
	wxBitmap* player_img = players->getPlayerImage(player_id);

	EndeavorTokenType token_type = board->occupyCity(player_id, player_img, city_id);
	if (token_type != INVALID_TOKEN_TYPE)
	{
		all_tokens->add(new CSC2110::Integer(token_type));
	}
	
	processOccupyAttackTokens(player_id, city_id, all_tokens);
	//players deletes the ListArray and its contents
	players->occupyCity(player_id, all_tokens, 1);
}

void EndeavorGame::attackCity(uint8 player_id, uint8 city_id)
{
	CSC2110::ListArray<CSC2110::Integer>* all_tokens = new CSC2110::ListArray<CSC2110::Integer>();
	wxBitmap* player_img = players->getPlayerImage(player_id);

	board->attackCity(player_id, player_img, city_id);
	
	EndeavorTokenType token_type = INVALID_TOKEN_TYPE;
	
	processOccupyAttackTokens(player_id, city_id, all_tokens);
	
	players->occupyCity(player_id, all_tokens, 2);
}

bool EndeavorGame::canAttackInAnyRegion(uint8 player_id)
{
	return board->canAttackInAnyRegion(player_id);
}

bool EndeavorGame::canAttackCity(uint8 player_id, uint8 city_id)
{
	return board->canAttackCity(player_id, city_id);
}

bool EndeavorGame::canOccupyCity(uint8 player_id, uint8 city_id)
{
	return board->canOccupyCity(player_id, city_id);
}

bool EndeavorGame::canDrawFromAnyRegion(uint8 player_id)
{
	return board->canDrawFromAnyRegion(player_id);
}

bool EndeavorGame::canOccupyInAnyRegion(uint8 player_id)
{
	return board->canOccupyInAnyRegion(player_id);
}

void EndeavorGame::takeSelectedCard(uint8 player_id, EndeavorRegionType card_id)
{
	Card* card = board->takeSelectedCard(player_id, card_id);
	players->takeSelectedCard(player_id, card);
	if (card_id == 1 && card->getCardLevel() == 5)
	{
		board->abolishSlavery();
		players->abolishSlavery();
	}
}

bool EndeavorGame::canTakeSelectedCard(uint8 player_id, EndeavorRegionType card_id)
{
	return board->canTakeSelectedCard(player_id, card_id);
}

EndeavorRegionType EndeavorGame::findSelectedCard(uint32 x, uint32 y)
{
	return board->findSelectedCard(x, y);
}

uint8 EndeavorGame::findSelectedCity(uint32 x, uint32 y)
{
	return board->findSelectedCity(x, y);
}

//methods for players
void EndeavorGame::occupyCity(uint8 player_id, CSC2110::ListArray<CSC2110::Integer>* token_types, uint8 worker_cost)
{
	players->occupyCity(player_id, token_types, worker_cost);
}

bool EndeavorGame::canTakePaymentAction(uint8 player_id)
{
	uint8 activated_buildings = getNumActivatedBuildings(player_id);

	if (activated_buildings == 0)
	{
		return false;
	}
	
	return true;
}

bool EndeavorGame::canMakeAnyPayments(uint8 player_id)
{
	uint8 num_payments = getNumPayments(player_id);
	uint8 activated_buildings = getNumActivatedBuildings(player_id);

	if (num_payments == 0 || activated_buildings == 0)
	{
		return false;
	}
	
	return true;
}

uint8 EndeavorGame::getNumPayments(uint8 player_id)
{
	return players->getNumPayments(player_id);
}

uint8 EndeavorGame::getNumActivatedBuildings(uint8 player_id)
{
	return players->getNumActivatedBuildings(player_id);
}

void EndeavorGame::makePayment(uint8 player_id, EndeavorBuildingType building_type)
{
	players->makePayment(player_id, building_type);
}

bool EndeavorGame::canMakePaymentAction(uint8 player_id, EndeavorBuildingType building_type)
{
   return players->canMakePaymentAction(player_id, building_type);
}

bool EndeavorGame::canMakePayment(uint8 player_id, EndeavorBuildingType building_type)
{
	return players->canMakePayment(player_id, building_type);
}

void EndeavorGame::activateBuilding(uint8 player_id, EndeavorBuildingType building_type)
{
	players->activateBuilding(player_id, building_type);
}

bool EndeavorGame::canActivateBuilding(uint8 player_id, EndeavorBuildingType building_type)
{
	return players->canActivateBuilding(player_id, building_type);
}

EndeavorBuildingType EndeavorGame::findSelectedBuildingPlayerBoard(uint8 player_id, uint32 x, uint32 y)
{
	return players->findSelectedBuilding(player_id, x, y);
}

uint8 EndeavorGame::getNumWorkers(uint8 player_id)
{
	return players->getNumWorkers(player_id);
}

void EndeavorGame::populationGrowth(uint8 player_id)
{
	players->populationGrowth(player_id);
}

void EndeavorGame::nextPlayer()
{
	players->nextPlayer();
}

void EndeavorGame::nextPlayerAfterPass()
{
	bool change_state = false;
	if (current_state == action_state)
	{
		change_state = players->nextPlayerAfterPassCheckForNewRound();
		if (change_state && players->getGameRound() == 8)
		{
			changeToGameOverState();
		}
	}
	else
	{
		change_state = players->nextPlayerAfterPass();
	}
	
	if (change_state)
	{
		state_queue->enqueue(state_queue->dequeue());
		current_state = state_queue->peek();
	}
	
	//payments can be a pain!
	while(current_state == payment_state && !canMakeAnyPayments(players->getActivePlayer()))
	{
		change_state = players->nextPlayerAfterPass();
		if (change_state)
		{
			state_queue->enqueue(state_queue->dequeue());
			current_state = state_queue->peek();
		}
	}
}

bool EndeavorGame::doesPlayerPass(uint32 x, uint32 y)
{
	return players->doesPlayerPass(x, y);
}

uint8 EndeavorGame::getActivePlayer()
{
	uint8 active_player = players->getActivePlayer();
	computeTotalGlory(active_player);
	return active_player;
}

bool EndeavorGame::canTakeBuilding(uint8 active_player_id, EndeavorBuildingType building_type, uint8 lowest_level_available)
{
	return players->canTakeBuilding(active_player_id, building_type, lowest_level_available);
}

void EndeavorGame::takeBuilding(uint8 active_player_id, Building* selected_building)
{
	players->takeBuilding(active_player_id, selected_building);
}

//methods for buildings
uint8 EndeavorGame::getLowestLevelAvailable()
{
	return buildings->getLowestLevelAvailable();
}

EndeavorBuildingType EndeavorGame::findSelectedBuilding(uint32 x, uint32 y)
{
	return buildings->findSelectedBuilding(x, y);
}

Building* EndeavorGame::removeBuilding(EndeavorBuildingType building_type)
{
	return buildings->removeBuilding(building_type);
}

EndeavorGame::EndeavorGame(int screen_width, int screen_height)
{	 
	PixelXML pixel_xml("resources/endeavor_pixels.xml");	
	ImageLoader* image_loader = ImageLoader::getImageLoader();

	PixelDimension pixel_dim = pixel_xml.getPixelDimension("gui");
	int gui_width = pixel_dim.getWidth();
	int gui_height = pixel_dim.getHeight();

	int x_loc = (screen_width - gui_width)/2;
	int y_loc = (screen_height - gui_height)/2;

	endeavor_gui = new BasicGUI(x_loc, y_loc, gui_width, gui_height, this);
	
	token_images = new wxBitmap*[8];
	
	wxBitmap* industry_img = image_loader->loadImageRGBA("industry");
	token_images[0] = industry_img;
	
	wxBitmap* culture_img = image_loader->loadImageRGBA("culture");
	token_images[1] = culture_img;
	
	wxBitmap* finance_img = image_loader->loadImageRGBA("finance");
	token_images[2] = finance_img;
	
	wxBitmap* politics_img = image_loader->loadImageRGBA("politics");
	token_images[3] = politics_img;
	
	wxBitmap* ship_or_draw_img = image_loader->loadImageRGBA("ship_or_draw");
	token_images[4] = ship_or_draw_img;
	
	wxBitmap* occupy_or_draw_img = image_loader->loadImageRGBA("occupy_or_draw");
	token_images[5] = occupy_or_draw_img;
	
	wxBitmap* payment_img = image_loader->loadImageRGBA("payment");
	token_images[6] = payment_img;
	
	wxBitmap* attack_img = image_loader->loadImageRGBA("attack");
	token_images[7] = attack_img;

	CSC2110::ListArray<Token>* tokens = new CSC2110::ListArray<Token>();
	
	int token_count = 0;

	EndeavorTokenType current_type = INDUSTRY;
	for (int i = 0; i < 17; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	current_type = CULTURE;
	for (int i = 0; i < 20; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	current_type = FINANCE;
	for (int i = 0; i < 17; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	current_type = POLITICS;
	for (int i = 0; i < 25; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	current_type = SHIP_DRAW;
	for (int i = 0; i < 6; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	current_type = OCCUPY_DRAW;
	for (int i = 0; i < 6; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	current_type = PAYMENT;
	for (int i = 0; i < 2; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	current_type = ATTACK;
	for (int i = 0; i < 2; i++)
	{
		Token* token = new Token(current_type, token_images[current_type - 1]);
		tokens->add(token);
		token_count++;
	}
	
	CSC2110::Permutation permute(95, 95);
	String file_name("resources/endeavor_permutation.txt");
	permute.writeFile(file_name);
	permute.readFile(file_name);
	
	board = new Board(pixel_xml, image_loader, tokens, permute);
	connections = new Connections(pixel_xml, permute, tokens);
	buildings = new Buildings(pixel_xml, image_loader);
	players = new Players(pixel_xml, image_loader, buildings);
	
	CSC2110::ListArrayIterator<Token>* token_iter = tokens->iterator();
	while(token_iter->hasNext())
	{
		Token* token = token_iter->next();
		if (token)
		{
			delete token;
		}
	}
	delete token_iter;
	delete tokens;
	
	endeavor_state_hash_table = new CSC2110::HashTableAVL<EndeavorState>(3, &EndeavorState::computeHashFunctionState, &EndeavorState::computeHashFunctionKey, &EndeavorState::compareStates, &EndeavorState::compareStatesByKeyAndState);
    
	CSC2110::String* build_key = new CSC2110::String("build");
	build_state = new BuildState(this, build_key);
	
	CSC2110::String* payment_key = new CSC2110::String("payment");
	payment_state = new PaymentState(this, payment_key);
	
	CSC2110::String* action_key = new CSC2110::String("action");
	action_state = new ActionState(this, action_key);
	//endeavor_state_hash_table->tableInsert(action_state);
	
	CSC2110::String* discard_key = new CSC2110::String("discard");
	discard_state = new DiscardState(this, discard_key);
	//endeavor_state_hash_table->tableInsert(discard_state);
	
	CSC2110::String* game_over_key = new CSC2110::String("game_over");
	game_over_state = new GameOverState(this, game_over_key);
	
	CSC2110::String* occupy_key = new CSC2110::String("occupy");
	occupy_state = new OccupyState(this, occupy_key);
	endeavor_state_hash_table->tableInsert(occupy_state);
	
	CSC2110::String* ship_key = new CSC2110::String("ship");
	ship_state = new ShipState(this, ship_key);
	endeavor_state_hash_table->tableInsert(ship_state);
	
	CSC2110::String* attack_key = new CSC2110::String("attack");
	attack_state = new AttackState(this, attack_key);
	endeavor_state_hash_table->tableInsert(attack_state);
	
	CSC2110::String* draw_key = new CSC2110::String("draw");
	draw_card_state = new DrawCardState(this, draw_key);
	endeavor_state_hash_table->tableInsert(draw_card_state);
	
	CSC2110::String* ship_or_draw_key = new CSC2110::String("ship_or_draw");
	ship_or_draw_state = new ShipOrDrawState(this, ship_or_draw_key);
	endeavor_state_hash_table->tableInsert(ship_or_draw_state);
	
	CSC2110::String* occupy_or_draw_key = new CSC2110::String("occupy_or_draw");
	occupy_or_draw_state = new OccupyOrDrawState(this, occupy_or_draw_key);
	endeavor_state_hash_table->tableInsert(occupy_or_draw_state);
	
	CSC2110::String* occupy_or_attack_key = new CSC2110::String("occupy_or_attack");
	occupy_or_attack_state = new OccupyOrAttackState(this, occupy_or_attack_key);
	endeavor_state_hash_table->tableInsert(occupy_or_attack_state);
	
	CSC2110::String* ship_and_occupy_key = new CSC2110::String("ship_and_occupy");
	ship_and_occupy_state = new ShipAndOccupyState(this, ship_and_occupy_key);
	endeavor_state_hash_table->tableInsert(ship_and_occupy_state);
	
	CSC2110::String* ship_and_ship_key = new CSC2110::String("ship_and_ship");
	ship_and_ship_state = new ShipAndShipState(this, ship_and_ship_key);
	endeavor_state_hash_table->tableInsert(ship_and_ship_state);
	
	CSC2110::String* draw_and_draw_key = new CSC2110::String("draw_and_draw");
	draw_and_draw_state = new DrawAndDrawState(this, draw_and_draw_key);
	endeavor_state_hash_table->tableInsert(draw_and_draw_state);
	
	CSC2110::String* payment_action_key = new CSC2110::String("payment_action");
	payment_action_state = new PaymentActionState(this, payment_action_key);
	endeavor_state_hash_table->tableInsert(payment_action_state);
	
	state_queue = new CSC2110::QueueArray<EndeavorState>();
	state_queue->enqueue(build_state);
	state_queue->enqueue(payment_state);
	state_queue->enqueue(action_state);
	
	current_state = state_queue->peek();
}

EndeavorGame::~EndeavorGame()
{
//std::cout << "Endeavor Destructor Called." << std::endl;

	delete endeavor_state_hash_table;  //currently, hash table does not have an iterator
	delete state_queue;
	
	delete action_state;
	delete payment_state;
	delete build_state;
	delete discard_state;
	delete game_over_state;
	
	delete occupy_state;
	delete ship_state;
	delete attack_state;
	delete draw_card_state;
	delete ship_or_draw_state;
	delete occupy_or_draw_state;
	delete occupy_or_attack_state;
	delete ship_and_occupy_state;
	delete ship_and_ship_state;
	delete draw_and_draw_state;
	delete payment_action_state;
	
	delete buildings;
	delete players;
	delete connections;
	delete board;

	for (int i = 0; i < 8; i++)
	{
		if (token_images[i])
		{
			delete token_images[i];
		}
	}
	delete[] token_images;
}

void EndeavorGame::draw(wxDC&  dc, int width, int height)
{
	board->draw(dc);
	connections->draw(dc);
	buildings->draw(dc);
	players->draw(dc);
}

void EndeavorGame::computeTotalGlory(uint8 player_id)
{
	uint8 connection_glory = connections->computeConnectionsGlory(player_id);
	uint8 city_glory = board->computeCityGlory(player_id);
	players->computeTotalGlory(player_id, connection_glory + city_glory);
}

void EndeavorGame::mouseClicked(int x, int y)
{
	uint8 player_id = players->findSelectedPlayer(x, y);
	if (player_id > 0)
	{
		players->selectPlayer(player_id);
		computeTotalGlory(player_id);
		return;
	}
	
	current_state->mouseClicked(x, y);
	
	//std::cout << x << std::endl;
	//std::cout << y << std::endl;
}

void EndeavorGame::changeToState(const char* key)
{
	CSC2110::String state_key(key);
	current_state = endeavor_state_hash_table->tableRetrieve(&state_key);
}

void EndeavorGame::changeToActionState()
{
	current_state = action_state;
}

void EndeavorGame::changeToDiscardState()
{
	current_state = discard_state;
}

void EndeavorGame::changeToGameOverState()
{
	current_state = game_over_state;
}

/*
void EndeavorGame::changeToShipState()
{
	current_state = ship_state;
}

void EndeavorGame::changeToOccupyState()
{
	current_state = occupy_state;
}

void EndeavorGame::changeToAttackState()
{
	current_state = attack_state;
}

void EndeavorGame::changeToDrawCardState()
{
	current_state = draw_card_state;
}

void EndeavorGame::changeToShipOrDrawState()
{
	current_state = ship_or_draw_state;
}

void EndeavorGame::changeToOccupyOrDrawState()
{
	current_state = occupy_or_draw_state;
}

void EndeavorGame::changeToOccupyOrAttackState()
{
	current_state = occupy_or_attack_state;
}

void EndeavorGame::changeToShipAndOccupyState()
{
	current_state = ship_and_occupy_state;
}

void EndeavorGame::changeToShipAndShipState()
{
	current_state = ship_and_ship_state;
}

void EndeavorGame::changeToDrawAndDrawState()
{
	current_state = draw_and_draw_state;
}

void EndeavorGame::changeToPaymentActionState()
{
	current_state = payment_action_state;
}
*/

void EndeavorGame::setTitle(std::string title_str)
{
	endeavor_gui->setTitle(title_str);
}

void EndeavorGame::showGUI()
{
	endeavor_gui->show();
}

void EndeavorGame::keyPressed(int key_code)
{
	if (key_code == 76)  //'l'
	{
		loadGame();
	}
	else if (key_code == 83)  //'s'
	{
		saveGame();
	}
}

void EndeavorGame::saveGame()
{
	TiXmlElement* game_element = writeXML();
	if (game_element == NULL) return;
	TiXmlDocument doc("resources/endeavor_save.xml");
	doc.LinkEndChild(game_element);
	doc.SaveFile();
	
/*
   TiXmlElement* round_element = Utils::xmlElementFromInteger("round", round);
   endeavor_element->LinkEndChild(round_element);

   int state = 1;  //build state by default
   if (current_state == payment_state) state = 2;
   else if (current_state == action_state) state = 3;
   else if (current_state == draw_state) state = 4;
   else if (current_state == ship_state) state = 5;
   else if (current_state == occupy_state) state = 6;
   else if (current_state == attack_state) state = 7;
   else if (current_state == game_over_state) state = 16;

   TiXmlElement* state_element = Utils::xmlElementFromInteger("state", state);
   endeavor_element->LinkEndChild(state_element);

   TiXmlElement* game_element = elements->writeXML();
   endeavor_element->LinkEndChild(game_element);
 */
   
   //doc->SaveFile();
   //delete doc;
}

void EndeavorGame::loadGame()
{
	TiXmlDocument doc;
	doc.LoadFile("resources/endeavor_save.xml");
	TiXmlElement* game_element = doc.RootElement();
	readXML(game_element);

   /*
   TiXmlElement* round_element = endeavor_element->FirstChildElement();
   round = Utils::integerFromXMLElement(round_element);

   TiXmlElement* state_element = round_element->NextSiblingElement();
   int state = Utils::integerFromXMLElement(state_element);

   if (state == 1) current_state = build_state;
   else if (state == 2) current_state = payment_state;
   else if (state == 3) current_state = action_state;
   else if (state == 4) current_state = draw_state;
   else if (state == 5) current_state = ship_state;
   else if (state == 6) current_state = occupy_state;
   else if (state == 7) current_state = attack_state;
   else if (state == 16) current_state = game_over_state;
*/
   //TiXmlElement* game_element = endeavor_element->FirstChildElement();
   

   //selectPlayer(getActivePlayer());
}

Card* EndeavorGame::getCard(EndeavorRegionType card_region_type, uint8 card_level)
{
	return board->getCard(card_region_type, card_level);
}

Building* EndeavorGame::getSpecificBuilding(uint8 unique_building_id)
{
	return buildings->getSpecificBuilding(unique_building_id);
}

CSC2110::String EndeavorGame::getGameState()
{
	TiXmlElement* game_element = writeXML();
	TiXmlDocument* doc = new TiXmlDocument();
    doc->LinkEndChild(game_element);
	TiXmlPrinter printer;

	// attach it to the document you want to convert in to a std::string 
	doc->Accept(&printer);

	// Create a std::string and copy your document data in to the string    
	std::string xml_std_str = printer.CStr();
	CSC2110::String xml_str(xml_std_str.c_str());
	//std::cout << xml_std_str.c_str() << std::endl;
	delete doc;
	return xml_str;
}

void EndeavorGame::setGameState(CSC2110::String& xml_str)
{
	//std::cout << xml_str.get_c_str() << std::endl;
	TiXmlDocument* doc = new TiXmlDocument();
	doc->Parse(xml_str.get_c_str());
	TiXmlElement* game_element = doc->RootElement();
	readXML(game_element);
	delete doc;
}

TiXmlElement* EndeavorGame::writeXML()
{
	int state = 0; 
	EndeavorState* save_state = state_queue->peek();
	if (save_state == build_state)
	{
		state = 1;
	}
	else if (save_state == payment_state)
	{
		state = 2;
	}
	else if (save_state == action_state)
	{
		state = 3;
	}
	else if (save_state == game_over_state)
	{
		state = 4;
	}

	if (state < 1) return NULL;
   
   TiXmlElement* game_element = new TiXmlElement("Endeavor");
   
   TiXmlElement* state_element = EndeavorGame::xmlElementFromInteger("game_state", state);
	game_element->LinkEndChild(state_element);
	
   TiXmlElement* players_element = players->writeXML();
   TiXmlElement* board_element = board->writeXML();
   TiXmlElement* buildings_element = buildings->writeXML();
   TiXmlElement* connections_element = connections->writeXML();

   game_element->LinkEndChild(players_element);
   game_element->LinkEndChild(board_element);
   game_element->LinkEndChild(buildings_element);
   game_element->LinkEndChild(connections_element);
   
   return game_element;
}

void EndeavorGame::readXML(TiXmlElement* game_element)
{
	TiXmlElement* state_element = game_element->FirstChildElement("game_state");
	int state = EndeavorGame::integerFromXMLElement(state_element);

	EndeavorState* rotate_state = state_queue->peek();
	if (state == 1)
	{
		while (rotate_state != build_state)
		{
			rotate_state = state_queue->dequeue();
			state_queue->enqueue(rotate_state);
			rotate_state = state_queue->peek();
		}
		current_state = rotate_state;
	}
	
	else if (state == 2)
	{
		while (rotate_state != payment_state)
		{
			rotate_state = state_queue->dequeue();
			state_queue->enqueue(rotate_state);
			rotate_state = state_queue->peek();
		}
		current_state = rotate_state;
	}
	
	else if (state == 3)
	{
		while (rotate_state != action_state)
		{
			rotate_state = state_queue->dequeue();
			state_queue->enqueue(rotate_state);
			rotate_state = state_queue->peek();
		}
		current_state = rotate_state;
	}
	
	else
	{
		current_state = game_over_state;
	}
	
	TiXmlElement* players_element = game_element->FirstChildElement("Players");
   players->readXML(players_element, this);

   TiXmlElement* board_element = players_element->NextSiblingElement();
   wxBitmap** player_images = players->getPlayerCircleImages();
   board->readXML(board_element, player_images, token_images);

	TiXmlElement* buildings_element = board_element->NextSiblingElement();
   buildings->readXML(buildings_element);

	TiXmlElement* connections_element = buildings_element->NextSiblingElement();
   connections->readXML(connections_element, player_images, token_images);

}

int EndeavorGame::integerFromXMLElement(TiXmlElement* integer_element)
{
	const char* element_c_str = integer_element->GetText();
	CSC2110::String element_str(element_c_str);
	int element_integer = element_str.a_to_i();
	return element_integer;
}

TiXmlElement* EndeavorGame::xmlElementFromInteger(const char* element_tag, int integer_to_insert)
{
   TiXmlElement* integer_element = new TiXmlElement(element_tag);
   CSC2110::String integer_str = CSC2110::String::i_to_a(integer_to_insert);
   char* integer_c_str = integer_str.get_c_str();
   TiXmlText* integer_text = new TiXmlText(integer_c_str);
   integer_element->LinkEndChild(integer_text);
   delete[] integer_c_str;  //added!
   return integer_element;
}
