#if !defined ENDEAVOR_MEDITERRANEAN
#define ENDEAVOR_MEDITERRANEAN

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListArray.h"
#include "StackLinked.h"
#include "PQHeap.h"
#include "Permutation.h"

#include "PixelXML.h"
#include "PixelDimension.h"
#include "PixelPoint.h"
#include "ImageLoader.h"

#include "Cities.h"
#include "Cards.h"
#include "Card.h"
#include "City.h"
#include "Token.h"

class Mediterranean
{
	private:
		//CSC2110::StackLinked<Card>* cards;
		//CSC2110::StackLinked<Card>* slavery;
		
		//CSC2110::PQHeap<Card>* pq_cards;
		//CSC2110::PQHeap<Card>* pq_slavery;
		
		Cards* medit_cards;
		Cards* slavery_cards;
		
		Cities* cities;
		
		//CSC2110::ListArray<City>* cities;
		
		//wxBitmap** card_images;
		//wxBitmap** slavery_images;
	  
		//PixelPoint* card_medit_loc;
		//PixelPoint* card_slavery_loc;
		
		uint8 region_id;
		//uint8 first_city_id;
		//uint8 num_cities_in_region;
		
	public:
		Mediterranean(uint8 region_id, PixelXML& pixel_xml, ImageLoader* image_loader, CSC2110::ListArray<Token>* tokens, CSC2110::Permutation& permute, uint8 city_counter);
		virtual ~Mediterranean();
		
		uint8 computeCityGlory(uint8 player_id);
		
		bool isCityInRegion(uint8 city_id);
		bool canAttackCity(uint8 player_id, uint8 city_id);
		bool canAttackInRegion(uint8 player_id);
		bool attackCity(uint8 player_id, wxBitmap* p_img, uint8 city_id);

		bool canOccupyInRegion();
		bool canOccupyCity(uint8 city_id);
		EndeavorTokenType occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id);

		uint8 getPlayerPresence(uint8 player_id);
		uint8 countPlayerCities(uint8 player_id);

		uint8 getPlayerIDInCity(uint8 city_id);
		uint8 findSelectedCity(uint32 x, uint32 y);

		EndeavorRegionType findSelectedCard(uint32 x, uint32 y);
		//need to know from which stack to take the card
		Card* takeSelectedCard(uint8 player_id, bool is_slavery);
		bool canTakeSelectedCard(uint8 player_id, bool is_slavery);
		bool canDrawFromRegion(uint8 player_id);
		//bool canDrawSecondCard(uint8 player_id, bool is_slavery);
		void returnCardToRegion(Card* card);
		void abolishSlavery();

		void draw(wxDC&  dc);
		
		//void getPossibleCitiesToOccupy(CSC2110::ListArray<City>* cities_to_occupy);
		//void getPossibleCitiesToAttack(CSC2110::ListArray<City>* cities_to_attack, uint8 player_id);
		//void getPossibleCardToDraw(CSC2110::ListArray<Card>* cards_to_draw, uint8 player_id);
		
		Card* getCard(uint8 card_level, bool is_slavery);
		TiXmlElement* writeXML();
		void readXML(TiXmlElement* medit_element, wxBitmap** player_images, wxBitmap** token_images);
};

#endif
