#ifndef QUEUE1_H
#define QUEUE1_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/
void receTask(void * pvParm);
void sendTask(void * pvParm);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*QUEUE1_H*/
