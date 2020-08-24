// ------------------------------------------------------------------------
// File:    dpi_commin.c
//
// Summary: 
//
//
// Note:     
// ------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>


#include "dpi_common.h"

#include "_macros_print.h"

//#include "platform_drivers.h"

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// <dpiCommonWaitForTrue>
// Poll routine looking for TRUE return for success.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL dpiCommonWaitForTrue(BOOL (*f)(void), uint32_t iLoops) {
  BOOL bLoop= true;
  BOOL bReturn= false;
  BOOL bStat;
 
  while(bLoop) {
    //
    if(iLoops == 0) {
      return(false);
    }
    else {
      iLoops--;
    }
    // If True return by function, set return to true, exit while loop.
    bStat= (BOOL)(*f)();
    //
    if(bStat) {
      bLoop= false;
      bReturn= true;
      return(true);
    }
  }
  
  return(bReturn);
}



BOOL dpiCommonWaitForFalse(BOOL (*f)(void), uint32_t iLoops) {
  BOOL bLoop= true;
  BOOL bReturn= false;
 
  while(bLoop) {
    //
    if(iLoops == 0) {
      return(false);
    }
    else {
      iLoops--;
    }
    // 
    if((*f)() == false) {
      bLoop= false;
      bReturn= true;
      return(true);
    }
  }
  
  return(bReturn);
}



BOOL dpiCommonWaitForTrueWithSleep(BOOL (*f)(void), uint32_t iLoops, uint32_t iMilliSecSleep) {
  BOOL bLoop= true;
  BOOL bReturn= false;
  BOOL bStat;

  while(bLoop) {
    //
    if(iLoops == 0) {
      return(false);
    }
    else {
      iLoops--;
    }
    // If True return by function, set return to true, exit while loop.
    bStat= (BOOL)(*f)();
    //
    if(bStat) {
      bLoop= false;
      bReturn= true;
      return(true);
    }
    //
    //if(iMilliSecSleep > 0)
    //  mdelay(iMilliSecSleep);
  }
  
  return(bReturn);
}



BOOL dpiCommonWaitForFalseWithSleep(BOOL (*f)(void), uint32_t iLoops, uint32_t iMilliSecSleep) {
  BOOL bLoop= true;
  BOOL bReturn= false;

  while(bLoop) {
    //
    if(iLoops == 0) {
      return(false);
    }
    else {
      iLoops--;
    }
    // 
    if((*f)() == false) {
      bLoop= false;
      bReturn= true;
      return(true);
    }
   //
  //  if(iMilliSecSleep > 0)
    //  mdelay(iMilliSecSleep);
  }
  
  return(bReturn);
}





// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// <dpiCommonWaitForTrue_uint32_t>
// Poll routine looking for TRUE return for success.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL dpiCommonWaitForTrue_uint32_t(BOOL (*f)(uint32_t), uint32_t a, uint32_t iLoops) {
  BOOL bLoop= true;
  BOOL bReturn= false;
  BOOL bStat;
 
  while(bLoop) {
    //
    if(iLoops == 0) {
      return(false);
    }
    else {
      iLoops--;
    }
    // 
    bStat= (BOOL)(*f)(a);
    //
    if(bStat) {
      bLoop= false;
      bReturn= true;
      return(true);
    }
  }
  
  return(bReturn);
}



BOOL dpiCommonWaitForFalse_uint32_t(BOOL (*f)(uint32_t), uint32_t a, uint32_t iLoops) {
  BOOL bLoop= true;
  BOOL bReturn= false;
 
  while(bLoop) {
    //
    if(iLoops == 0) {
      return(false);
    }
    else {
      iLoops--;
    }
    // 
    if((*f)(a) == false) {
      bLoop= false;
      bReturn= true;
      return(true);
    }
  }
  
  return(bReturn);
}



// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// <dpiCommonWaitForTrue_uint32_t_UINT8>
// Poll routine looking for TRUE return for success.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
 BOOL dpiCommonWaitForTrue_uint32_t_UINT8(BOOL (*f)(uint32_t, UINT8), uint32_t a, UINT8 b, uint32_t iLoops) {
   BOOL bLoop= true;
   BOOL bReturn= false;
   BOOL bStat;
   
   while(bLoop) {
    //
     if(iLoops == 0) {
       return(false);
     }
     else {
       iLoops--;
     }
     //
     bStat= (BOOL)(*f)(a, b);
     //
     if(bStat) {
       bLoop= false;
       bReturn= true;
       return(true);
     }
   }
   
   return(bReturn);
 }
 
 

 BOOL dpiCommonWaitForFalse_uint32_t_UINT8(BOOL (*f)(uint32_t, UINT8), uint32_t a, UINT8 b, uint32_t iLoops) {
   BOOL bLoop= true;
   BOOL bReturn= false;
   
   while(bLoop) {
     //
     if(iLoops == 0) {
       return(false);
     }
     else {
       iLoops--;
     }
     // 
     if((*f)(a, b) == false) {
       bLoop= false;
       bReturn= true;
       return(true);
     }
   }
   
   return(bReturn);
 }
 



// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// <dpiCommonWaitForTrue_uint32_t_uint32_t>
// Poll routine looking for TRUE return for success.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
 BOOL dpiCommonWaitForTrue_uint32_t_uint32_t(BOOL (*f)(uint32_t, uint32_t), uint32_t a, uint32_t b, uint32_t iLoops) {
   BOOL bLoop= true;
   BOOL bReturn= false;
   BOOL bStat;
   
   while(bLoop) {
    //
     if(iLoops == 0) {
       return(false);
     }
     else {
       iLoops--;
     }
     //
     bStat= (BOOL)(*f)(a, b);
     //
     if(bStat) {
       bLoop= false;
       bReturn= true;
       return(true);
     }
   }
   
   return(bReturn);
 }
 
 

 BOOL dpiCommonWaitForFalse_uint32_t_uint32_t(BOOL (*f)(uint32_t, uint32_t), uint32_t a, uint32_t b, uint32_t iLoops) {
   BOOL bLoop= true;
   BOOL bReturn= false;
   
   while(bLoop) {
     //
     if(iLoops == 0) {
       return(false);
     }
     else {
       iLoops--;
     }
     // 
     if((*f)(a, b) == false) {
       bLoop= false;
       bReturn= true;
       return(true);
     }
   }
   
   return(bReturn);
 }
 



 // ---------------------------------------------------------------------------
 // ---------------------------------------------------------------------------
 // ---------------------------------------------------------------------------
 // <dpiCommonWaitForTrue_uint32_t_uint32_t_UINT8>
 // Poll routine looking for TRUE return for success.
 // ---------------------------------------------------------------------------
 // ---------------------------------------------------------------------------
 // ---------------------------------------------------------------------------
  BOOL dpiCommonWaitForTrue_uint32_t_uint32_t_UINT8(BOOL (*f)(uint32_t, uint32_t, UINT8), uint32_t a, uint32_t b, UINT8 c, uint32_t iLoops) {
    BOOL bLoop= true;
    BOOL bReturn= false;
    BOOL bStat;

    while(bLoop) {
     //
      if(iLoops == 0) {
        return(false);
      }
      else {
        iLoops--;
      }
      //
      bStat= (BOOL)(*f)(a, b, c);
      //
      if(bStat) {
        bLoop= false;
        bReturn= true;
        return(true);
      }
    }

    return(bReturn);
  }



  BOOL dpiCommonWaitForFalse_uint32_t_uint32_t_UINT8(BOOL (*f)(uint32_t, uint32_t, UINT8), uint32_t a, uint32_t b, UINT8 c, uint32_t iLoops) {
    BOOL bLoop= true;
    BOOL bReturn= false;

    while(bLoop) {
      //
      if(iLoops == 0) {
        return(false);
      }
      else {
        iLoops--;
      }
      //
      if((*f)(a, b, c) == false) {
        bLoop= false;
        bReturn= true;
        return(true);
      }
    }

    return(bReturn);
  }




