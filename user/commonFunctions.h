#pragma once

#include <stdbool.h>

#ifdef __cplusplus
 extern "C" {
#endif

   /**
    * @brief Returns true if called from an ISR
    * @return true if called from ISR, false if called from Task contect (from Simmulation allways false)
   */
   bool inHandlerModePublic();

#ifdef __cplusplus
 }
#endif