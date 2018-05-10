#if !defined ENDEAVOR_STATE
#define ENDEAVOR_STATE

#include "EndeavorHeader.h"
#include "String_.h"

class EndeavorState
{
   private:
		CSC2110::String* state_key;

   public:
      EndeavorState(CSC2110::String* key);
      virtual ~EndeavorState();
	  
	  CSC2110::String* getKey();

      virtual void mouseClicked(uint32 x, uint32 y) = 0;
	  
	  static int computeHashFunctionState(EndeavorState* state);
      static int computeHashFunctionKey(CSC2110::String* key);
	  
	  static int compareStates(EndeavorState* state_1, EndeavorState* state_2);
	  static int compareStatesByKeyAndState(CSC2110::String* key, EndeavorState* state);
	  
};

#endif