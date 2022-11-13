#pragma once

#include <inttypes.h>
#include <stdbool.h>

typedef struct {
    unsigned char red, green, blue;
} rgb_t;

typedef struct {
    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} __attribute__((packed)) quadtree_node_t;

typedef struct {
    quadtree_node_t* v;
    uint32_t leaf_count;
    uint32_t node_count;
} __attribute__((packed)) qtn_vector_t;

qtn_vector_t* qtn_vector_create(uint32_t node_count);

void qtn_vector_resize(qtn_vector_t* qtn_vector, uint32_t node_count);

bool is_leaf(quadtree_node_t qtn);

qtn_vector_t* qtn_vector_read(char* input_file);

void qtn_vector_print(qtn_vector_t* qtn_vector, char* output_file);

void qtn_vector_destroy(qtn_vector_t** qtn_vector);