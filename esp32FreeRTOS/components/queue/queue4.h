
#ifndef QUEUE4_H
#define QUEUE4_H

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
void readTask(void *pvParm);
void writeTask(void *pvParm);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*QUEUE2_H*/
