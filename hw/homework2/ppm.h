#pragma once

#include <inttypes.h>

#include "quadtree.h"

typedef struct {
    uint32_t size;
    rgb_t** pix_mat;
} __attribute__((packed)) ppm_img_t;

ppm_img_t* ppm_create(uint32_t size);

ppm_img_t* ppm_read(char* input_file);

void ppm_print(ppm_img_t* ppm_img, char* output_file);

void __ppm_compress_rec(rgb_t** pix_mat, uint32_t size,
                        qtn_vector_t* qtn_vector, uint32_t index,
                        uint32_t threshold);

void ppm_compress(char* input_file, char* output_file, uint32_t threshold);

rgb_t** __ppm_decompress_rec(qtn_vector_t* qtn_vector, quadtree_node_t qtn);

void ppm_decompress(char* input_file, char* output_file);

void ppm_destroy(ppm_img_t** ppm_img);