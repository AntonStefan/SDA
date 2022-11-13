#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "quadtree.h"

// function that creates a new qtn vector
qtn_vector_t* qtn_vector_create(uint32_t node_count)
{   
    // allocate memory for a new qtn vector
    qtn_vector_t* qtn_vector = calloc(1, sizeof(*qtn_vector));
    assert(qtn_vector);

    qtn_vector->v = calloc(node_count, sizeof(*qtn_vector->v));
    assert(qtn_vector->v);

    qtn_vector->node_count = node_count;

    return qtn_vector;
}

void qtn_vector_resize(qtn_vector_t* qtn_vector, uint32_t node_count)
{
    if (!qtn_vector)
        return;

    quadtree_node_t* ret = realloc(qtn_vector->v,
                                   node_count * sizeof(quadtree_node_t));
    assert(ret);

    qtn_vector->v = ret;
    qtn_vector->node_count = node_count;
}

// function that checks if a quadtree node
bool is_leaf(quadtree_node_t qtn)
{
    if (qtn.top_left == -1 && qtn.top_right == -1 &&
        qtn.bottom_left == -1 && qtn.bottom_right == -1)
        return 1;

    return 0;
}

qtn_vector_t* qtn_vector_read(char* input_file)
{
    if (!input_file)
        return NULL;

    // open input file
    FILE* in_fp = fopen(input_file, "rb");
    assert(in_fp);

    // read qtn vector from input file
    uint32_t leaf_count;
    uint32_t node_count;

    fread(&leaf_count, sizeof(uint32_t), 1, in_fp);
    fread(&node_count, sizeof(uint32_t), 1, in_fp);

    qtn_vector_t* qtn_vector = qtn_vector_create(node_count);
    
    fread(qtn_vector->v, sizeof(quadtree_node_t), node_count, in_fp);

    // close input file
    fclose(in_fp);

    return qtn_vector;
}

void qtn_vector_print(qtn_vector_t* qtn_vector, char* output_file)
{
    if (!output_file)
        return;

    // open output file
    FILE* out_fp = fopen(output_file, "wb");
    assert(out_fp);

    // write qtn vector to output file
    fwrite(&qtn_vector->leaf_count, sizeof(uint32_t), 1, out_fp);
    fwrite(&qtn_vector->node_count, sizeof(uint32_t), 1, out_fp);
    fwrite(qtn_vector->v, sizeof(quadtree_node_t), qtn_vector->node_count, out_fp);

    // close output file
    fclose(out_fp);
}

void qtn_vector_destroy(qtn_vector_t** qtn_vector)
{
    if (!qtn_vector || !*qtn_vector)
        return;

    free((*qtn_vector)->v);
    (*qtn_vector)->v = NULL;

    free(*qtn_vector);
    *qtn_vector = NULL;
}

