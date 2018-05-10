#include "Mediterranean.h"

#include "ListArrayIterator.h"

#include <sstream>

uint8 Mediterranean::computeCityGlory(uint8 player_id)
{
	/*
	uint8 city_glory = 0;
	CSC2110::ListArrayIterator<City>* cities_iter = cities->iterator();
   while (cities_iter->hasNext())
   {
      City* city = cities_iter->next();
      if (city->getPlayerID() == player_id)
	  {
		  city_glory++;
	  }
   }
   delete cities_iter;
   
   return city_glory;
   */
   
   return cities->computeCityGlory(player_id);
}

bool Mediterranean::isCityInRegion(uint8 city_id)
{
	return cities->isCityInRegion(city_id);
	//return (city_id >= first_city_id) && (city_id < (first_city_id + num_cities_in_region));
}

bool Mediterranean::canAttackCity(uint8 player_id, uint8 city_id)
{
	return cities->canAttackCity(player_id, city_id);
	/*
	if (!isCityInRegion(city_id)) return false;
	City* city = cities->get(city_id);
	return city->isOccupied() && (player_id != city->getPlayerID());
	*/
}

bool Mediterranean::canAttackInRegion(uint8 player_id)
{
	return cities->canAttackInRegion(player_id);
	/*
   CSC2110::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      bool occupied = city->isOccupied();
      uint8 other_player_id = city->getPlayerID();
      if (occupied && (other_player_id != player_id))
      {
         delete city_iter;
         return true;
      }
   }
   delete city_iter;

   return false;
   */
}

bool Mediterranean::attackCity(uint8 player_id, wxBitmap* p_img, uint8 city_id)
{
	cities->attackCity(player_id, p_img, city_id);
	/*
   CSC2110::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (city->getCityID() == city_id)
      {
         bool occupied = city->isOccupied();
         uint8 other_player_id = city->getPlayerID();

         if (!occupied || (other_player_id == player_id))
         {
            delete city_iter;
            return false;
         }

         city->occupyCity(player_id, p_img);
         delete city_iter;
         return true;
      }
   }
   delete city_iter;

   return false;
   */
}

bool Mediterranean::canDrawFromRegion(uint8 player_id)
{
	uint8 presence = getPlayerPresence(player_id);
	
	uint8 medit_card_level = medit_cards->getCardLevel();
	uint8 slavery_card_level = slavery_cards->getCardLevel();
	
	uint8 card_level = medit_card_level;
	if (slavery_card_level < card_level) card_level = slavery_card_level;
	return (presence >= card_level);
	
	/*
	uint8 card_level = 255;  //in case there are no cards left
	uint8 slavery_level = 255;

	bool any_regular_cards = !pq_cards->pqIsEmpty();
	//uint8 num_cards = cards->size();
	if (any_regular_cards)
	{
		Card* card = pq_cards->pqRemove();
		card_level = card->getCardLevel();
		pq_cards->pqInsert(card);
		card_level = card->getCardLevel();
	}

	bool any_slavery_cards = !pq_slavery->pqIsEmpty();
	//num_cards = slavery->size();
	if (any_slavery_cards)
	{
		Card* card = pq_slavery->pqRemove();
		slavery_level = card->getCardLevel();
		pq_slavery->pqInsert(card);
		slavery_level = card->getCardLevel();
	}

	if (slavery_level < card_level) card_level = slavery_level;
	return (presence >= card_level);
	*/
}

EndeavorTokenType Mediterranean::occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id)
{
	cities->occupyCity(player_id, player_img, city_id);
	/*
	City* city = cities->get(city_id);
	if (!city->isOccupied())
	{
		//return the token type that was in the city
		return city->occupyCity(player_id, player_img);  
	}
         
	return INVALID_TOKEN_TYPE;  
	*/
}

bool Mediterranean::canOccupyCity(uint8 city_id)
{
	return cities->canOccupyCity(city_id);
	/*
	if (!isCityInRegion(city_id)) return false;
	
	City* city = cities->get(city_id);
	return !city->isOccupied();
	*/
}

bool Mediterranean::canOccupyInRegion()
{
	return cities->canOccupyInRegion();
	/*
   CSC2110::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (!city->isOccupied())
      {
         delete city_iter;
         return true;
      }
   }
   delete city_iter;

   return false;
   */
}

uint8 Mediterranean::getPlayerPresence(uint8 player_id)
{
	return cities->getPlayerPresence(player_id);
	/*
   uint8 player_presence = 0;

   CSC2110::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (city->getPlayerID() == player_id)
      {
         player_presence++;
      }
   }
   delete city_iter;

   return player_presence;
   */
}

uint8 Mediterranean::getPlayerIDInCity(uint8 city_id)
{
	return cities->getPlayerIDInCity(city_id);
	/*
	if (!isCityInRegion(city_id)) return 0;
   uint8 player_id = 0;

   CSC2110::ListArrayIterator<City>* city_iter = cities->iterator();
   while (city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (city->getCityID() == city_id)
      {
         player_id = city->getPlayerID();
		 break;
      }
   }
   delete city_iter;

   return player_id;
   */
}

uint8 Mediterranean::countPlayerCities(uint8 player_id)
{
   return getPlayerPresence(player_id);
}

void Mediterranean::abolishSlavery()
{
   //empty the slavery priority queue
   Card* card = slavery_cards->takeSelectedCard(0);
   while (card != NULL)
   {
	   card = slavery_cards->takeSelectedCard(0);
   }
   /*
   while(!pq_slavery->pqIsEmpty())
   {
      Card* card = pq_slavery->pqRemove();
      delete card;
	  //slavery->pop();
   }
   */
}

void Mediterranean::returnCardToRegion(Card* card)
{
	if (card->getCardID() != SLAVERY)
	{
		medit_cards->returnCardToRegion(card);
	}
	/*
   //should not be able to return slavery cards
   pq_cards->pqInsert(card);
   //cards->push(card);
   card->setPlayerID(0, card_medit_loc);
   */
}

//depends on whether the first card was a regular card or a slavery card
/*
bool Mediterranean::canDrawSecondCard(uint8 player_id, bool is_slavery)
{
   uint8 presence = getPlayerPresence(player_id);
   uint8 card_level = 255;
   uint8 num_regular_cards = cards->size();
   uint8 num_slavery_cards = slavery->size();

   if (!is_slavery)
   {
      if (num_regular_cards > 0)
      {
         card_level = cards->peek()->getCardLevel();
      }
   }
   else
   {
      if (num_slavery_cards > 0)
      {
         card_level = slavery->peek()->getCardLevel();
      }
   }
      
   return (presence >= card_level);
}
*/

bool Mediterranean::canTakeSelectedCard(uint8 player_id, bool is_slavery)
{
	uint8 presence = getPlayerPresence(player_id);
	if (!is_slavery)
	{
		uint8 card_level = medit_cards->getCardLevel();
		return (presence >= card_level);
	}
	else
	{
		uint8 card_level = slavery_cards->getCardLevel();
		return (presence >= card_level);
	}
	/*
   uint8 presence = getPlayerPresence(player_id);
   uint8 card_level = 255;
   //uint8 num_regular_cards = cards->size();
   //uint8 num_slavery_cards = slavery->size();
   
   bool any_regular_cards = !pq_cards->pqIsEmpty();
   bool any_slavery_cards = !pq_slavery->pqIsEmpty();
	//num_cards = slavery->size();

   if (!is_slavery)
   {
      if (any_regular_cards)
      {
		 Card* card = pq_cards->pqRemove();
		 card_level = card->getCardLevel();
		 pq_cards->pqInsert(card);
      }
   }
   else
   {
      if (any_slavery_cards)
      {
         Card* card = pq_slavery->pqRemove();
		 card_level = card->getCardLevel();
		 pq_slavery->pqInsert(card);
      }
   }

   return (presence >= card_level);
   */
}

Card* Mediterranean::takeSelectedCard(uint8 player_id, bool is_slavery)
{
	/*
   Card* card = NULL;
   uint8 num_regular_cards = cards->size();
   uint8 num_slavery_cards = slavery->size();

   if (!is_slavery && num_regular_cards > 0)  
   {
      card = cards->pop();
   }
   else if (num_slavery_cards > 0)
   {
      card = slavery->pop();
   }

   return card;
   */
   //uint8 num_regular_cards = cards->size();
   //uint8 num_slavery_cards = slavery->size();
   
   if (!is_slavery)
	{
		return medit_cards->takeSelectedCard(player_id);
	}
	
	else
	{
		return slavery_cards->takeSelectedCard(player_id);
	}
   
   /*
   Card* card = NULL;
   
   bool any_regular_cards = !pq_cards->pqIsEmpty();
   bool any_slavery_cards = !pq_slavery->pqIsEmpty();

   if (!is_slavery && any_regular_cards)  
   {
	   card = pq_cards->pqRemove();
	   //cards->pop();
   }
   else if (any_slavery_cards)
   {
      card = pq_slavery->pqRemove();
	  //slavery->pop();
   }
   
   return card;
   */
}

EndeavorRegionType Mediterranean::findSelectedCard(uint32 x, uint32 y)
{
	EndeavorRegionType region_type_1 = medit_cards->findSelectedCard(x, y);
	EndeavorRegionType region_type_2 = slavery_cards->findSelectedCard(x, y);

	if (region_type_1 == MEDITERRANEAN)
	{
		return region_type_1;
	}
	else if (region_type_2 == SLAVERY)
	{
		return region_type_2;
	}
	
	return INVALID_REGION_TYPE;
	/*
   //uint8 num_regular_cards = cards->size();
   //uint8 num_slavery_cards = slavery->size();
   Card* card = NULL;
   
   bool any_regular_cards = !pq_cards->pqIsEmpty();
   bool any_slavery_cards = !pq_slavery->pqIsEmpty();

   if (any_regular_cards)
   {
		//card = cards->peek();
	  
		card = pq_cards->pqRemove();
		//card_level = card->getCardLevel();
		pq_cards->pqInsert(card);
		 
      if (card->isSelectedCard(x, y))
      {
         return card->getCardID(); 
      }
   }

   if (any_slavery_cards)
   {
	   card = pq_slavery->pqRemove();
		//card_level = card->getCardLevel();
		pq_slavery->pqInsert(card);
		
      //card = slavery->peek();
      if (card->isSelectedCard(x, y))
      {
         return card->getCardID();  
      }
   }
   
   return INVALID_REGION_TYPE;  
   */
}

uint8 Mediterranean::findSelectedCity(uint32 x, uint32 y)
{
	return cities->findSelectedCity(x, y);
	/*
   CSC2110::ListArrayIterator<City>* iter = cities->iterator();
   while(iter->hasNext())
   {
      City* city = iter->next();
      if (city->isSelectedCity(x, y))
      {
         delete iter;
         return city->getCityID();
      }
   }
   delete iter;

   return 0;  
   */
}

void Mediterranean::draw(wxDC&  dc)
{
	cities->draw(dc);
	/*
   CSC2110::ListArrayIterator<City>* iter = cities->iterator();
   while(iter->hasNext())
   {
      City* city = iter->next();
      city->draw(dc);
   }
   delete iter;
   */
/*
   if (cards->size() > 0)
   {
      Card* card = cards->peek();
      card->draw(dc);
   }

   if (slavery->size() > 0)
   {
      Card* card = slavery->peek();
      card->draw(dc);
   }
   */
   
   medit_cards->draw(dc);
   slavery_cards->draw(dc);
   /*
   bool any_regular_cards = !pq_cards->pqIsEmpty();
   bool any_slavery_cards = !pq_slavery->pqIsEmpty();
   
   if (any_regular_cards)
	{
		Card* card = pq_cards->pqRemove();
		card->draw(dc);
		pq_cards->pqInsert(card);
	}
	
	if (any_slavery_cards)
   {
      Card* card = pq_slavery->pqRemove();
		card->draw(dc);
		pq_slavery->pqInsert(card);
   }
   */
}

Mediterranean::Mediterranean(uint8 r_id, PixelXML& pixel_xml, ImageLoader* image_loader, CSC2110::ListArray<Token>* tokens, CSC2110::Permutation& permute, uint8 city_counter)
{
	//cities = new CSC2110::ListArray<City>();
	
	//cards = new CSC2110::StackLinked<Card>();
	//slavery = new CSC2110::StackLinked<Card>();
	
	//pq_cards = new CSC2110::PQHeap<Card>(&Card::compareCardsByLevelAsc);
	//pq_slavery = new CSC2110::PQHeap<Card>(&Card::compareCardsByLevelAsc);

	PixelDimension pixel_card_dim = pixel_xml.getPixelDimension("mediterranean_cards");
	PixelDimension pixel_city_dim = pixel_xml.getPixelDimension("mediterranean_cities");
 
	CSC2110::ListArray<PixelPoint>* mediterranean_card_centers = pixel_xml.getPixelCentersList("mediterranean_cards");
	CSC2110::ListArray<PixelPoint>* mediterranean_city_centers = pixel_xml.getPixelCentersList("mediterranean_cities");
	
	region_id = r_id;
	//first_city_id = city_counter;
	//num_cities_in_region = mediterranean_city_centers->size();
	
	CSC2110::ListArrayIterator<PixelPoint>* mediterranean_cards_iter = mediterranean_card_centers->iterator();
	PixelPoint* card_medit_loc = mediterranean_cards_iter->next();
	PixelPoint* card_slavery_loc = mediterranean_cards_iter->next();
	delete mediterranean_cards_iter;
	delete mediterranean_card_centers;
	
	medit_cards = new Cards(MEDITERRANEAN, image_loader, *card_medit_loc, pixel_card_dim, pixel_card_dim);
	slavery_cards = new Cards(SLAVERY, image_loader, *card_slavery_loc, pixel_card_dim, pixel_card_dim);
	
	delete card_medit_loc;
	delete card_slavery_loc;
	/*
	CSC2110::ListArrayIterator<PixelPoint>* mediterranean_cities_iter = mediterranean_city_centers->iterator();

	while(mediterranean_cities_iter->hasNext())
	{
		PixelPoint* pixel_city_center = mediterranean_cities_iter->next();
		   
		uint8 token_index = permute.next();
		Token* token = tokens->get(token_index);
		EndeavorTokenType token_type = token->getTokenType();
		wxBitmap* token_img = token->getTokenImage();
			   
		City* city = new City(city_counter, token_type, token_img, pixel_city_center, pixel_city_dim);
		cities->add(city);

		city_counter++;
		delete pixel_city_center;
	}
	delete mediterranean_cities_iter;
	delete mediterranean_city_centers;
	*/
	cities = new Cities(tokens, permute, mediterranean_city_centers, pixel_city_dim, 1);
	/*
	card_images = new wxBitmap*[12];  //contains both non-rotated and rotated images
	slavery_images = new wxBitmap*[12];

	int card_counter = 0;
	for (int i = 5; i >= 0; i--)
	{
		//complicated since the file name needs the current value of i
		std::ostringstream s_card_str;
		s_card_str << "mediterranean_" << i;
		std::string card_str(s_card_str.str());

		wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());

		//account for both the standard card image and the rotated one
		//the mediterranean does not have any rotated images
		//thus, use the standard image for both
		card_images[card_counter++] = card_img;
		card_images[card_counter++] = card_img;

		Card* card;
			
		switch(i)
		{
			case 0: card = new Card(MEDITERRANEAN, i, card_img, card_img, card_medit_loc, pixel_card_dim, pixel_card_dim, 0, 1, 1, 0, 0, false, false); break;
			case 1: card = new Card(MEDITERRANEAN, i, card_img, card_img, card_medit_loc, pixel_card_dim, pixel_card_dim, 0, 2, 0, 1, 0, false, false); break;
			case 2: card = new Card(MEDITERRANEAN, i, card_img, card_img, card_medit_loc, pixel_card_dim, pixel_card_dim, 0, 0, 0, 3, 0, false, false); break;
			case 3: card = new Card(MEDITERRANEAN, i, card_img, card_img, card_medit_loc, pixel_card_dim, pixel_card_dim, 1, 1, 1, 1, 0, false, false); break;
			case 4: card = new Card(MEDITERRANEAN, i, card_img, card_img, card_medit_loc, pixel_card_dim, pixel_card_dim, 0, 0, 0, 0, 5, false, false); break;
			case 5: card = new Card(MEDITERRANEAN, i, card_img, card_img, card_medit_loc, pixel_card_dim, pixel_card_dim, 0, 3, 0, 0, 3, false, false); break;
		}
		//cards->push(card);
		pq_cards->pqInsert(card);
	}
	 
	card_counter = 0;
	for (int i = 5; i >= 0; i--)
	{
		std::ostringstream s_card_str;
		s_card_str << "slavery_" << i;
		std::string card_str(s_card_str.str());

		wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
		slavery_images[card_counter++] = card_img;
		slavery_images[card_counter++] = card_img;

		Card* card;
		switch(i)
		{
			case 0: card = new Card(SLAVERY, i, card_img, card_img, card_slavery_loc, pixel_card_dim, pixel_card_dim, 2, 0, 0, 0, 0, true, false); break;
			case 1: card = new Card(SLAVERY, i, card_img, card_img, card_slavery_loc, pixel_card_dim, pixel_card_dim, 0, 0, 2, 0, 0, true, false); break;
			case 2: card = new Card(SLAVERY, i, card_img, card_img, card_slavery_loc, pixel_card_dim, pixel_card_dim, 1, 0, 2, 0, 0, true, false); break;
			case 3: card = new Card(SLAVERY, i, card_img, card_img, card_slavery_loc, pixel_card_dim, pixel_card_dim, 3, 0, 0, 0, 0, true, false); break;
			case 4: card = new Card(SLAVERY, i, card_img, card_img, card_slavery_loc, pixel_card_dim, pixel_card_dim, 2, 0, 2, 0, 0, true, false); break;
			case 5: card = new Card(SLAVERY, i, card_img, card_img, card_slavery_loc, pixel_card_dim, pixel_card_dim, 3, 0, 2, 0, 0, true, false); break;
		}

		//slavery->push(card);
		pq_slavery->pqInsert(card);
	}
	*/
}

Mediterranean::~Mediterranean()
{   
//std::cout << "Mediterranean Destructor Called." << std::endl;

	delete cities;
/*
   CSC2110::ListArrayIterator<City>* city_iter = cities->iterator();
   while(city_iter->hasNext())
   {
      City* city = city_iter->next();
      delete city;
   }
   delete city_iter;
   delete cities;
   */
   /*
   while(!pq_cards->pqIsEmpty())
   {
      Card* card = pq_cards->pqRemove();
      delete card;
   }
   delete pq_cards;
   
   while(!pq_slavery->pqIsEmpty())
   {
      Card* card = pq_slavery->pqRemove();
      delete card;
   }
   delete pq_slavery;
   */
//the medit image arrays have duplicate images in them
/*
   for (int i = 0; i <= 11; i += 2)
   {
	   delete card_images[i];
	   delete slavery_images[i];
   }
   delete[] card_images;
   delete[] slavery_images;
   */
   delete medit_cards;
   delete slavery_cards;

   //delete card_medit_loc;
   //delete card_slavery_loc;
}

Card* Mediterranean::getCard(uint8 card_level, bool is_slavery)
{
	if (!is_slavery)
	{
		return medit_cards->getCard(card_level);
	}
	else
	{
		return slavery_cards->getCard(card_level);
	}
}

TiXmlElement* Mediterranean::writeXML()
{
   TiXmlElement* region_element = new TiXmlElement("Region");
   
   TiXmlElement* cities_element = cities->writeXML();
   region_element->LinkEndChild(cities_element);
   
   TiXmlElement* medit_cards_element = medit_cards->writeXML();
   region_element->LinkEndChild(medit_cards_element);
   
   TiXmlElement* slavery_cards_element = slavery_cards->writeXML();
   region_element->LinkEndChild(slavery_cards_element);
   
   return region_element;
}

void Mediterranean::readXML(TiXmlElement* region_element, wxBitmap** player_images, wxBitmap** token_images)
{
	TiXmlElement* cities_element = region_element->FirstChildElement();
	cities->readXML(cities_element, player_images, token_images);
   
	TiXmlElement* medit_cards_element = cities_element->NextSiblingElement();
	medit_cards->readXML(medit_cards_element);
	
	TiXmlElement* slavery_cards_element = medit_cards_element->NextSiblingElement();
	slavery_cards->readXML(slavery_cards_element);
}

/*
void Mediterranean::getPossibleCitiesToOccupy(ListArray<City>* cities_to_occupy)
{
   CSC2110::ListArrayIterator<City>* city_iter = cities->iterator();
   while(city_iter->hasNext())
   {
      City* city = city_iter->next();
      if (!city->isOccupied())
      {
         cities_to_occupy->add(city);
      }
   }
   delete city_iter;
}

void Mediterranean::getPossibleCardToDraw(ListArray<Card>* cards_to_draw, uint8 player_id)
{
	bool can_draw = canDrawFromRegion(player_id);
	if (!can_draw) return;
	uint8 card_level = 0;
	uint8 slavery_level = 0;

	uint8 presence = getPlayerPresence(player_id);

	uint8 num_cards = cards->size();
	if (num_cards > 0)
	{
		card_level = cards->peek()->getCardLevel();
		if (presence >= card_level)
		{
			cards_to_draw->add(cards->peek());
		}
	}

	uint8 num_slavery = slavery->size();
	if (num_slavery > 0)
	{
		slavery_level = slavery->peek()->getCardLevel();
		if (presence >= slavery_level)
		{
			cards_to_draw->add(slavery->peek());
		}
	}
}
*/
