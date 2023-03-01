
#ifndef SEMPHR2_H
#define SEMPHR2_H

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
void task1(void *pvParm);
void task2(void *pvParm);
void task3(void *pvParm);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*QUEUE2_H*/
