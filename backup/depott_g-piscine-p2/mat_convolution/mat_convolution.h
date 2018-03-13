#ifndef MAT_CONVOLUTION_H
# define MAT_CONVOLUTION_H

# define M_SIZE 5
# define K_SIZE 3

void mat_convolution(const int mat[M_SIZE][M_SIZE],
                     const int ker[K_SIZE][K_SIZE],
                     int res[M_SIZE][M_SIZE]);

#endif
