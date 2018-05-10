#if !defined ENDEAVOR_BOARD
#define ENDEAVOR_BOARD

#include "wx/wx.h"
#include "tinyxml.h"

#include "PixelXML.h"
#include "ImageLoader.h"

#include "ListArray.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "TableAVL.h"
#include "Permutation.h"

#include "EndeavorHeader.h"
#include "Mediterranean.h"
#include "Region.h"

//#include "QuadTree.h"

class Board
{
   private:
      wxBitmap* board_img;
	  
	  Mediterranean* medit;
	  CSC2110::ListArray<Region>* regions;
	  //CSC2110::BinarySearchTree<Region>* regions_tree;
	  //CSC2110::AVLTree<Region>* regions_tree;
	  CSC2110::TableAVL<Region>* regions_table;
	  
	  //QuadTree<Region>* quad_tree;

   public:
      Board(PixelXML& pixel_xml, ImageLoader* image_loader, CSC2110::ListArray<Token>* tokens, CSC2110::Permutation& permute);
      virtual ~Board();
	  
	  uint8 computeCityGlory(uint8 player_id);
	  void abolishSlavery();
	  
	  EndeavorRegionType getRegionWithCity(uint8 city_id);
	  bool canOccupyInRegion(uint8 player_id, EndeavorRegionType region_type);
	  
	  //ship
	  Card* moveGovernorCardToPlayer(EndeavorRegionType region_type);
	  bool canAssignGovernorCard(EndeavorRegionType region_type);
	  uint8 assignGovernorCard(EndeavorRegionType region_type);
	  EndeavorTokenType ship(uint8 player_id, EndeavorRegionType region_type, wxBitmap* player_img);
	  EndeavorRegionType findSelectedShip(uint32 x, uint32 y);
	  bool canShipInAnyRegion(uint8 player_id);
	  
	  //attack
	  void attackCity(uint8 player_id, wxBitmap* player_img, uint8 city_id);
	  bool canAttackInAnyRegion(uint8 player_id);
	  bool canAttackCity(uint8 player_id, uint8 city_id);
	  
	  //draw
	  void returnCardToRegion(Card* card);
	  bool canDrawFromAnyRegion(uint8 player_id);
	  bool canTakeSelectedCard(uint8 player_id, EndeavorRegionType card_id);
	  Card* takeSelectedCard(uint8 player_id, EndeavorRegionType card_id);
	  EndeavorRegionType findSelectedCard(uint32 x, uint32 y);
	  
	  //occupy
	  bool canOccupyCity(uint8 player_id, uint8 city_id);
	  uint8 getPlayerIDInCity(uint8 city_id);
	  bool canOccupyInAnyRegion(uint8 player_id);
	  EndeavorTokenType occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id);
	  uint8 findSelectedCity(uint32 x, uint32 y);
	  
	  void draw(wxDC&  dc);
	  
	  Card* getCard(EndeavorRegionType card_region_type, uint8 card_level);
	  TiXmlElement* writeXML();
      void readXML(TiXmlElement* board_element, wxBitmap** player_images, wxBitmap** token_images);
	  
};

#endif
