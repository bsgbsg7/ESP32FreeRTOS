
#ifndef QUEUE2_H
#define QUEUE2_H

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
void receTask(void *pvParm);
void sendTask2(void *pvParm);
void sendTask1(void *pvParm);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*QUEUE2_H*/
