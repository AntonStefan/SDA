#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "quadtree.h"
#include "ppm.h"

#define MAX_BUFFER_SIZE 4
#define MAX_NODE_COUNT 5

ppm_img_t* ppm_create(uint32_t size)
{
    // allocate memory for a new ppm image
    ppm_img_t* ppm_img = calloc(1, sizeof(*ppm_img));
    assert(ppm_img);

    // allocate memory for pixel matrix
    ppm_img->pix_mat = calloc(size, sizeof(rgb_t*));
    assert(ppm_img->pix_mat);

    for (uint32_t i = 0; i < size; i++) {
        ppm_img->pix_mat[i] = calloc(size, sizeof(rgb_t));
        assert(ppm_img->pix_mat[i]);
    }

    ppm_img->size = size;

    return ppm_img;
}

// function that reads a ppm image from file
ppm_img_t* ppm_read(char* input_file)
{
    if (!input_file)
        return NULL;

    // open input file
    FILE* in_fp = fopen(input_file, "rb");
    assert(in_fp);

    // read size
    char buffer[MAX_BUFFER_SIZE];
    uint32_t size;

    fscanf(in_fp, "%s", buffer);
    fscanf(in_fp, "%"SCNd32"", &size);
    fscanf(in_fp, "%"SCNd32"", &size);
    fscanf(in_fp, "%s", buffer);

    // create new ppm image
    ppm_img_t* ppm_img = ppm_create(size);

    // move file pointer so fread reads correctly
    fseek(in_fp, 1, SEEK_CUR);
    
    // read pixel matrix
    for (uint32_t i = 0; i < ppm_img->size; i++)
        fread(ppm_img->pix_mat[i], sizeof(rgb_t), ppm_img->size, in_fp);

    // close input file
    fclose(in_fp);

    return ppm_img;
}

void ppm_print(ppm_img_t* ppm_img, char* output_file)
{
    if (!ppm_img || !output_file)
        return;

    // open output file
    FILE* out_fp = fopen(output_file, "w");
    assert(out_fp);

    // write ppm image to output file
    fprintf(out_fp, "P6\n%"PRId32"% "PRId32"\n255\n",
            ppm_img->size, ppm_img->size);

    fclose(out_fp);
    out_fp = fopen(output_file, "ab");

    for (uint32_t i = 0; i < ppm_img->size; i++)
        fwrite(ppm_img->pix_mat[i], sizeof(rgb_t), ppm_img->size, out_fp);

    // close output file
    fclose(out_fp);
}

void __ppm_compress_rec(rgb_t** pix_mat, uint32_t size,
                        qtn_vector_t* qtn_vector, uint32_t index,
                        uint32_t threshold)
{
    qtn_vector->v[index].area = pow(size, 2);
    qtn_vector->v[index].top_left = -1;
    qtn_vector->v[index].top_right = -1;
    qtn_vector->v[index].bottom_left = -1;
    qtn_vector->v[index].bottom_right = -1;

    if (qtn_vector->v[index].area == 1) {
        qtn_vector->v[index].red = pix_mat[0][0].red;
        qtn_vector->v[index].green = pix_mat[0][0].green;
        qtn_vector->v[index].blue = pix_mat[0][0].blue;
        qtn_vector->leaf_count++;

        return;
    }

    // calculate average color
    double red_avg = 0;
    double green_avg = 0;
    double blue_avg = 0;

    for (uint32_t i = 0; i < size; i++) {
        for (uint32_t j = 0; j < size; j++) {
            red_avg += pix_mat[i][j].red;
            green_avg += pix_mat[i][j].green;
            blue_avg += pix_mat[i][j].blue;
        }
    }

    red_avg /= pow(size, 2);
    green_avg /= pow(size, 2);
    blue_avg /= pow(size, 2);

    qtn_vector->v[index].red = red_avg;
    qtn_vector->v[index].green = green_avg;
    qtn_vector->v[index].blue = blue_avg;

    // calculate similarity score
    double score = 0;

    for (uint32_t i = 0; i < size; i++) {
        for (uint32_t j = 0; j < size; j++) {
            score += pow(red_avg - pix_mat[i][j].red, 2);
            score += pow(green_avg - pix_mat[i][j].green, 2);
            score += pow(blue_avg - pix_mat[i][j].blue, 2);
        }
    }

    score /= 3 * pow(size, 2);

    if (score <= threshold) {
        qtn_vector->leaf_count++;
        return;
    }

    qtn_vector->v[index].top_left = qtn_vector->node_count;
    qtn_vector->v[index].top_right = qtn_vector->node_count + 1;
    qtn_vector->v[index].bottom_right = qtn_vector->node_count + 2;
    qtn_vector->v[index].bottom_left = qtn_vector->node_count + 3;

    qtn_vector_resize(qtn_vector, qtn_vector->node_count + 4);

    // divide current pixel matrix into four
    rgb_t** div_pix_mat[4];

    for (uint32_t i = 0; i < 4; i++) {
        div_pix_mat[i] = calloc(size / 2, sizeof(rgb_t*));
        assert(div_pix_mat[i]);

        for (uint32_t j = 0; j < size / 2; j++) {
            div_pix_mat[i][j] = calloc(size / 2, sizeof(rgb_t));
            assert(div_pix_mat[i][j]);

            for (uint32_t k = 0; k < size / 2; k++) {
                switch (i)
                {
                case 0:
                    div_pix_mat[i][j][k] = pix_mat[j][k];
                    break;
                
                case 1:
                    div_pix_mat[i][j][k] = pix_mat[j][k + size / 2];
                    break;

                case 2:
                    div_pix_mat[i][j][k] = pix_mat[j + size / 2][k + size / 2];
                    break;

                case 3:
                    div_pix_mat[i][j][k] = pix_mat[j + size / 2][k];
                    break;
                }
            }
        }
    }

    __ppm_compress_rec(div_pix_mat[0], size / 2, qtn_vector,
                       qtn_vector->v[index].top_left, threshold);
    __ppm_compress_rec(div_pix_mat[1], size / 2, qtn_vector,
                       qtn_vector->v[index].top_right, threshold);
    __ppm_compress_rec(div_pix_mat[2], size / 2, qtn_vector,
                       qtn_vector->v[index].bottom_right, threshold);
    __ppm_compress_rec(div_pix_mat[3], size / 2, qtn_vector,
                       qtn_vector->v[index].bottom_left, threshold);

    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < size / 2; j++)
            free(div_pix_mat[i][j]);

        free(div_pix_mat[i]);
    }
}

void ppm_compress(char* input_file, char* output_file, uint32_t threshold)
{
    if (!input_file || !output_file)
        return;

    // read ppm image from file
    ppm_img_t* ppm_img = ppm_read(input_file);

    // create qtn vector
    qtn_vector_t* qtn_vector = qtn_vector_create(1);

    // recursively fill qtn vector
    __ppm_compress_rec(ppm_img->pix_mat, ppm_img->size,
                       qtn_vector, 0, threshold);

    // print qtn vector to output file
    qtn_vector_print(qtn_vector, output_file);

    // free memory
    ppm_destroy(&ppm_img);
    qtn_vector_destroy(&qtn_vector);
}

rgb_t** __ppm_decompress_rec(qtn_vector_t* qtn_vector, quadtree_node_t qtn)
{
    if (!qtn_vector)
        return NULL;

    // get pixel matrix size from qtn
    uint32_t size = sqrt(qtn.area);

    // allocate memory for pixel matrix
    rgb_t** pix_mat = calloc(size, sizeof(rgb_t*));
    assert(pix_mat);

    for (uint32_t i = 0; i < size; i++) {
        pix_mat[i] = calloc(size, sizeof(rgb_t));
        assert(pix_mat[i]);

        // fill pixel matrix with qtn.color
        for (uint32_t j = 0; j < size; j++) {
            pix_mat[i][j].red = qtn.red;
            pix_mat[i][j].green = qtn.green;
            pix_mat[i][j].blue = qtn.blue;
        }
    }

    if (is_leaf(qtn)) {
        // fill pixel matrix with qtn.color
        for (uint32_t i = 0; i < size; i++)
            for (uint32_t j = 0; j < size; j++) {
                pix_mat[i][j].red = qtn.red;
                pix_mat[i][j].green = qtn.green;
                pix_mat[i][j].blue = qtn.blue;
            }

        return pix_mat;
    }

    // allocate memory for 4 matrices of size = size / 2
    rgb_t** div_pix_matrix[4];

    div_pix_matrix[0] = __ppm_decompress_rec(qtn_vector,
                                             qtn_vector->v[qtn.top_left]);
    div_pix_matrix[1] = __ppm_decompress_rec(qtn_vector,
                                             qtn_vector->v[qtn.top_right]);
    div_pix_matrix[2] = __ppm_decompress_rec(qtn_vector,
                                             qtn_vector->v[qtn.bottom_right]);
    div_pix_matrix[3] = __ppm_decompress_rec(qtn_vector,
                                             qtn_vector->v[qtn.bottom_left]);

    for (uint32_t i = 0; i < size; i++) {
        for (uint32_t j = 0; j < size; j++) {
            if (i < size / 2 && j < size / 2)
                pix_mat[i][j] = div_pix_matrix[0][i][j];
            else if (i < size / 2 && j >= size / 2)
                pix_mat[i][j] = div_pix_matrix[1][i][j - size / 2];
            else if (i >= size / 2 && j >= size / 2)
                pix_mat[i][j] = div_pix_matrix[2][i - size / 2][j - size / 2];
            else
                pix_mat[i][j] = div_pix_matrix[3][i - size / 2][j];
        }
    }

    // free memory for the 4 smaller matrices
    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < size / 2; j++)
            free(div_pix_matrix[i][j]);

        free(div_pix_matrix[i]);
    }

    return pix_mat;
}

void ppm_decompress(char* input_file, char* output_file)
{
    if (!input_file || !output_file)
        return;

    // read qtn vector from input file
    qtn_vector_t* qtn_vector = qtn_vector_read(input_file);

    // allocate memory for a new ppm image
    ppm_img_t* ppm_img = calloc(1, sizeof(*ppm_img));
    assert(ppm_img);

    // get image size
    ppm_img->size = sqrt(qtn_vector->v[0].area);

    // recursively reconstruct pixel matrix from qtn vector
    ppm_img->pix_mat = __ppm_decompress_rec(qtn_vector, qtn_vector->v[0]);

    // write ppm img to output file
    ppm_print(ppm_img, output_file);

    // free memory
    ppm_destroy(&ppm_img);
    qtn_vector_destroy(&qtn_vector);
}

void ppm_destroy(ppm_img_t** ppm_img)
{
    if (!ppm_img || !*ppm_img)
        return;

    for (uint32_t i = 0; i < (*ppm_img)->size; i++) {
        free((*ppm_img)->pix_mat[i]);
        (*ppm_img)->pix_mat[i] = NULL;
    }

    free((*ppm_img)->pix_mat);
    (*ppm_img)->pix_mat = NULL;

    free(*ppm_img);
    *ppm_img = NULL;
}
