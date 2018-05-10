#include "Board.h"

#include "AVLTreeIterator.h"

#include "String_.h"

void Board::abolishSlavery()
{
	medit->abolishSlavery();
}

uint8 Board::computeCityGlory(uint8 player_id)
{
	uint8 city_glory_regions = 0;
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		city_glory_regions += region->computeCityGlory(player_id);
	}
	delete regions_iter;
	
	uint8 city_glory_medit = medit->computeCityGlory(player_id);
	return city_glory_regions + city_glory_medit;
}

bool Board::canOccupyInRegion(uint8 player_id, EndeavorRegionType region_type)
{
	if (region_type == MEDITERRANEAN)
	{
		return medit->canOccupyInRegion();
	}
	
	Region* region = regions->get((int) region_type - 1);
	return region->canOccupyInRegion(player_id);
}

EndeavorRegionType Board::getRegionWithCity(uint8 city_id)
{
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		EndeavorRegionType city_region = region->getRegionWithCity(city_id);
		if (city_region != INVALID_REGION_TYPE)
		{
			delete regions_iter;
			return city_region;
		}
	}
	delete regions_iter;
	return INVALID_REGION_TYPE;
}

void Board::returnCardToRegion(Card* card)
{
	EndeavorRegionType region_type = card->getCardID();
	
	//cannot return slavery cards or governor cards
	if (card->isSlavery() || card->isGovernor()) 
	{
		delete card;
		return;
	}
	
	if (region_type == MEDITERRANEAN)
	{
		medit->returnCardToRegion(card);
	}
	else
	{
		Region* region = regions->get(region_type - 1);
		region->returnCardToRegion(card);
	}
}

Card* Board::moveGovernorCardToPlayer(EndeavorRegionType region_type)
{
	Region* region = regions->get(region_type - 1);
	return region->moveGovernorCardToPlayer();
}

bool Board::canAssignGovernorCard(EndeavorRegionType region_type)
{
	Region* region = regions->get(region_type - 1);
	return region->assignGovernorCard();
}

uint8 Board::assignGovernorCard(EndeavorRegionType region_type)
{
	Region* region = regions->get(region_type - 1);
	return region->assignGovernorCard();
}

EndeavorTokenType Board::ship(uint8 player_id, EndeavorRegionType region_type, wxBitmap* player_img)
{
	Region* region = regions->get(region_type - 1);
	return region->ship(player_id, player_img);
}

EndeavorRegionType Board::findSelectedShip(uint32 x, uint32 y)
{
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		uint8 ship_id = region->findSelectedShip(x, y);
		if (ship_id > 0)
		{
			delete regions_iter;
			return region->getRegionType();
		}
	}
	delete regions_iter;
	return INVALID_REGION_TYPE;
}

//can always ship, but may not always get a token
bool Board::canShipInAnyRegion(uint8 player_id)
{
	return true;
}

void Board::attackCity(uint8 player_id, wxBitmap* player_img, uint8 city_id)
{
	if (medit->isCityInRegion(city_id))
	{
		medit->attackCity(player_id, player_img, city_id);
		return;
	}
	
	CSC2110::String temp = CSC2110::String::i_to_a(city_id);
	Region* region = regions_table->tableRetrieve(&temp);
	region->attackCity(player_id, player_img, city_id);
}

bool Board::canAttackInAnyRegion(uint8 player_id)
{
	bool can_attack = medit->canAttackInRegion(player_id);
	if (can_attack) return true;
	
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		can_attack = region->canAttackInRegion(player_id);
		if (can_attack)
		{
			delete regions_iter;
			return true;
		}
	}
	delete regions_iter;
	return false;
}

bool Board::canAttackCity(uint8 player_id, uint8 city_id)
{
	bool can_attack_city = medit->canAttackCity(player_id, city_id);
	if (can_attack_city) return true;
	
	CSC2110::String temp = CSC2110::String::i_to_a(city_id);
	Region* region = regions_table->tableRetrieve(&temp);
	if (region == NULL) return false;
	return region->canAttackCity(player_id, city_id);
}

EndeavorTokenType Board::occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id)
{
	if (medit->isCityInRegion(city_id))
	{
		return medit->occupyCity(player_id, player_img, city_id);
	}
	
	CSC2110::String temp = CSC2110::String::i_to_a(city_id);
	Region* region = regions_table->tableRetrieve(&temp);
	return region->occupyCity(player_id, player_img, city_id);
}

bool Board::canOccupyInAnyRegion(uint8 player_id)
{
	bool can_occupy = medit->canOccupyInRegion();
	if (can_occupy) return true;
	
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		can_occupy = region->canOccupyInRegion(player_id);
		if (can_occupy)
		{
			delete regions_iter;
			return true;
		}
	}
	delete regions_iter;
	return false;
}

bool Board::canOccupyCity(uint8 player_id, uint8 city_id)
{
	bool can_occupy_city = medit->canOccupyCity(city_id);
	if (can_occupy_city) return true;
	
	CSC2110::String temp = CSC2110::String::i_to_a(city_id);
	Region* region = regions_table->tableRetrieve(&temp);
	if (region == NULL) return false;
	return region->canOccupyCity(player_id, city_id);
}

uint8 Board::getPlayerIDInCity(uint8 city_id)
{
	if (medit->isCityInRegion(city_id))
	{
		return medit->getPlayerIDInCity(city_id);
	}
	
	CSC2110::String temp = CSC2110::String::i_to_a(city_id);
	Region* region = regions_table->tableRetrieve(&temp);
	if (region == NULL) return 0;
	return region->getPlayerIDInCity(city_id);
}

bool Board::canDrawFromAnyRegion(uint8 player_id)
{
	bool can_draw = medit->canDrawFromRegion(player_id);
	if (can_draw) return true;
	
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		can_draw = region->canDrawFromRegion(player_id);
		if (can_draw)
		{
			delete regions_iter;
			return true;
		}
	}
	delete regions_iter;
	return false;
}

Card* Board::takeSelectedCard(uint8 player_id, EndeavorRegionType card_id)
{
	if (card_id == MEDITERRANEAN)
	{
		return medit->takeSelectedCard(player_id, false);
	}
	else if (card_id == SLAVERY)  //slavery card selected
	{
		return medit->takeSelectedCard(player_id, true);
	}
	
	else
	{
		return regions->get(card_id - 1)->takeSelectedCard(player_id);
	}
}

bool Board::canTakeSelectedCard(uint8 player_id, EndeavorRegionType card_id)
{
	if (card_id == MEDITERRANEAN)
	{
		return medit->canTakeSelectedCard(player_id, false);
	}
	else if (card_id == SLAVERY)  //slavery card selected
	{
		return medit->canTakeSelectedCard(player_id, true);
	}
	
	else
	{
		return regions->get(card_id - 1)->canDrawFromRegion(player_id);
	}
}

EndeavorRegionType Board::findSelectedCard(uint32 x, uint32 y)
{
	EndeavorRegionType card_id = medit->findSelectedCard(x, y);
	if (card_id != INVALID_REGION_TYPE) return card_id;
	
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		card_id = region->findSelectedCard(x, y);
		if (card_id != INVALID_REGION_TYPE)
		{
			delete regions_iter;
			return region->getRegionType();
		}
	}
	delete regions_iter;
	
	return INVALID_REGION_TYPE;
}

uint8 Board::findSelectedCity(uint32 x, uint32 y)
{
	uint8 city_id = medit->findSelectedCity(x, y);
	if (city_id > 0) return city_id;
	
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		city_id = region->findSelectedCity(x, y);
		if (city_id > 0)
		{
			delete regions_iter;
			return city_id;
		}
	}
	delete regions_iter;

	return 0;
}

Board::Board(PixelXML& pixel_xml, ImageLoader* image_loader, CSC2110::ListArray<Token>* tokens, CSC2110::Permutation& permute)
{
	board_img = image_loader->loadImageRGBA("board");
	medit = new Mediterranean(1, pixel_xml, image_loader, tokens, permute, 1);
	
	regions = new CSC2110::ListArray<Region>();
	regions_table = new CSC2110::TableAVL<Region>(&Region::compareRegions, &Region::compareRegionsByKeyAndRegion);
	//regions_tree = new CSC2110::AVLTree<Region>(&Region::compareRegions, &Region::compareRegionsByKeyAndRegion);
	
	Region* south_america = new Region(SOUTH_AMERICA, pixel_xml, image_loader, tokens, permute, 13);
	regions_table->tableInsert(south_america);
	regions->add(1, south_america);
	
	Region* far_east = new Region(FAR_EAST, pixel_xml, image_loader, tokens, permute, 25);
	regions_table->tableInsert(far_east);
	regions->add(2, far_east);
	
	Region* india = new Region(INDIA, pixel_xml, image_loader, tokens, permute, 22);
	regions_table->tableInsert(india);
	regions->add(2, india);
	
	Region* africa = new Region(AFRICA, pixel_xml, image_loader, tokens, permute, 11);
	regions_table->tableInsert(africa);
	regions->add(1, africa);
	
	Region* north_america = new Region(NORTH_AMERICA, pixel_xml, image_loader, tokens, permute, 19);
	regions_table->tableInsert(north_america);
	regions->add(3, north_america);
	
	Region* caribbean = new Region(CARIBBEAN, pixel_xml, image_loader, tokens, permute, 16);
	regions_table->tableInsert(caribbean);
	regions->add(3, caribbean);

}

Board::~Board()
{

	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		delete region;
	}
	delete regions_iter;
	delete regions_table;
	//delete regions_tree;
	delete regions;
	
	delete medit;
	
	delete board_img;
}

void Board::draw(wxDC&  dc)
{
	dc.DrawBitmap(*board_img, 0, 0);
	medit->draw(dc);
	
	CSC2110::ListArrayIterator<Region>* regions_iter = regions->iterator();
	while(regions_iter->hasNext())
	{
		Region* region = regions_iter->next();
		region->draw(dc);
	}
	delete regions_iter;
}

Card* Board::getCard(EndeavorRegionType card_region_type, uint8 card_level)
{
	Card* card = NULL;
	if (card_region_type == MEDITERRANEAN)
	{
		card = medit->getCard(card_level, false);
	}
	else if (card_region_type == SLAVERY)
	{
		card = medit->getCard(card_level, true);
	}
	else
	{
		Region* region = regions->get(card_region_type - 1);
		card = region->getCard(card_level);
	}
	return card;
}

TiXmlElement* Board::writeXML()
{
   TiXmlElement* board_element = new TiXmlElement("Board");
   
   TiXmlElement* medit_element = medit->writeXML();
   board_element->LinkEndChild(medit_element);
   
   CSC2110::AVLTreeIterator<Region>* region_iter = regions_table->iterator();
   while(region_iter->hasNext())
   {
	   Region* region = region_iter->next();
	   TiXmlElement* region_element = region->writeXML();
	   board_element->LinkEndChild(region_element);
   }
   delete region_iter;

   return board_element;
}

void Board::readXML(TiXmlElement* board_element, wxBitmap** player_images, wxBitmap** token_images)
{
	TiXmlElement* medit_element = board_element->FirstChildElement();
	medit->readXML(medit_element, player_images, token_images);
	
	TiXmlElement* region_element = medit_element->NextSiblingElement();
   CSC2110::AVLTreeIterator<Region>* region_iter = regions_table->iterator();
   while(region_iter->hasNext())
   {
	   Region* region = region_iter->next();
	   region->readXML(region_element, player_images, token_images);
	   region_element = region_element->NextSiblingElement();
   }
   delete region_iter;
}
