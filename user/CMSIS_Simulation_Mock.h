#pragma once


#ifdef __cplusplus
 extern "C" {
#endif


/*!
 *  Returns allways 0 due to simmulation
 */
int __get_IPSR();


void xPortSysTickHandler(void);



#ifdef __cplusplus
 }
#endif