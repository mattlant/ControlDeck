// 
// 
// 

#include "InputDebouncer.h"

bool InputDebouncer::isDebounced( byte value, byte debounceCount)
{
  if ( _keepValue != value ) 
  {
      _bounce = debounceCount;  
      _keepValue = value;
  }
  else if ( _bounce > 0 ) _bounce-- ;
  
  return _bounce == 0;
}

