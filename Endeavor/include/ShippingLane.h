#if !defined ENDEAVOR_SHIPPING_LANE
#define ENDEAVOR_SHIPPING_LANE

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListDoublyLinked.h"
#include "ListArray.h"
#include "Permutation.h"

#include "PixelPoint.h"
#include "PixelDimension.h"

#include "EndeavorHeader.h"
#include "Ship.h"
#include "Token.h"

class ShippingLane
{
	private:
		CSC2110::ListDoublyLinked<Ship>* shipping_lane;
		uint8 ship_cursor;
		uint8 num_regular_shipping_locations;
		
	public:
		ShippingLane(CSC2110::ListArray<Token>* tokens, CSC2110::Permutation& permute, CSC2110::ListArray<PixelPoint>* pixel_centers, PixelDimension& pixel_dim);
		virtual ~ShippingLane();
		
		bool isRegionOpen();
		uint8 getPlayerPresence(uint8 player_id);
		uint8 assignGovernorCard();
		bool canAssignGovernorCard();

		EndeavorTokenType ship(uint8 player_id, wxBitmap* player_img);
		
		uint8 findSelectedShip(uint32 x, uint32 y);
		void draw(wxDC&  dc);
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* ship_element, wxBitmap** player_images, wxBitmap** token_images);
};	

#endif
