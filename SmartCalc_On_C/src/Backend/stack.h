#ifndef STACK_H
#define STACK_H

/** @file */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

/**
 * @brief Struct for stack with data
 * @param data Data of node
 * @param Node Pointer on next item of the stack
 */
typedef struct Node {
  Data data;
  struct Node *next;
} Node;

/**
 * @brief Push item to stack
 * @param top Pointer on top of the stack
 * @param data Data of current item
 * @return Node*
 */
Node *stack_push(Node *top, Data data);
/**
 * @brief Get item from stack
 * @param top Pointer on top of the stack
 * @return Node*
 */
Node *stack_pop(Node *top);
/**
 * @brief Removing all items and free memory
 * @param top Pointer on top of the stack
 */
void stack_free(Node *top);
/**
 * @brief Get data from top of stack
 * @param top Pointer on top of the stack
 * @return Data
 */
Data stack_peek(Node *top);
/**
 * @brief Pull characters of string to stack
 * @param top Pointer on top of the stack
 * @param str String that must be pull to stack
 * @return Node*
 */
Node *stack_push_string(Node *top, char *str);
/**
 * @brief Convert stack to array
 * @param top Pointer on top of the stack
 * @param array Result array
 * @return Data*
 */
Data *stack_to_array(Node *top, Data *array);

#endif
