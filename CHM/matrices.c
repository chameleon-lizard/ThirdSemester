#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

struct matrix
{
    int size;
    double **matrix_contents;
    double *results;
    double *values;
};

int detSign = 1;

void
create(struct matrix *matr, int size)
{
    matr->size = size;
    matr->values = (double *) calloc(matr->size, sizeof(*(matr->values)));
    matr->results = (double *) calloc(matr->size, sizeof(*(matr->results)));
    matr->matrix_contents = (double **) calloc(size, sizeof(*(matr->matrix_contents)));
    for (int y = 0; y < size; y++) {
        matr->matrix_contents[y] = (double *) calloc(size, sizeof(*(matr->matrix_contents[y])));
    }
}

void
copy(struct matrix *dest, struct matrix source)
{   
    dest->size = source.size;
    dest->values = (double *) calloc(dest->size, sizeof(*(dest->values)));
    dest->results = (double *) calloc(dest->size, sizeof(*(dest->results)));
    dest->matrix_contents = (double **)calloc(dest->size, sizeof(*(dest->matrix_contents)));

    for (int y = 0; y < dest->size; y++) {
        dest->values[y]  = source.values[y];
        dest->results[y] = source.results[y];
        dest->matrix_contents[y] = (double *)calloc(dest->size, sizeof(*(dest->matrix_contents)));
        for (int x = 0; x < dest->size; x++) {
            dest->matrix_contents[y][x] = source.matrix_contents[y][x];
        }
    }
}

void
del(struct matrix *matr)
{
    for (int y = 0; y < matr->size; y++) {
        free(matr->matrix_contents[y]);
        matr->matrix_contents[y] = 0;
    }

    free(matr->values);
    free(matr->results);
    free(matr->matrix_contents);
    matr->matrix_contents = 0;
}

void
print(struct matrix matr, int mode)
{
    printf("\n");
    for (int x = 0; x < matr.size; x++) {
        for (int y = 0; y < matr.size; y++) {
            printf("%-6.2lf ", matr.matrix_contents[x][y]);
        }

        if (mode == 1) {
            printf("|%-6.2lf", matr.values[x]);
        }

        printf("\n");
    }
    
    if (mode == 0) {
        printf("\nHere are the results:\n");
        for (int y = 0; y < matr.size; y++) {
            printf("x%d = %-6.2lf\n", y + 1, matr.results[y]);
        }
    }
}

struct matrix
keyboard()
{
    int size = 0;

    system("clear");
    printf("Type in amount of columns:\n");
    scanf("%d", &size);
    system("clear");

    struct matrix matr;
    create(&matr, size);

    for (int x = 0; x < matr.size; x++) {
        for (int y = 0; y < matr.size; y++) {
            printf("Type in the next number:");
            print(matr, 1);
            scanf("%lf", &matr.matrix_contents[x][y]);
            system("clear");
        }

        printf("Type in the value for this equation:");
        print(matr, 1);
        scanf("%lf", &matr.values[x]);
        system("clear");
    }

    return matr;
}

struct matrix
file(char *filename)
{
    struct matrix matr;

    FILE *file = fopen(filename, "r");

    int size = 0;
    fscanf(file, "%d", &size);

    create(&matr, size);

    for (int x = 0; x < matr.size; x++) {
        for (int y = 0; y < matr.size; y++) {
            fscanf(file, "%lf", &matr.matrix_contents[x][y]);
        }

        fscanf(file, "%lf", &matr.values[x]);
    }

    fclose(file);

    return matr;
}

void
swapLines(struct matrix *matr, int a, int b)
{
    double temp = 0;
    for (int i = 0; i < matr->size; i++) {
        temp = matr->matrix_contents[a][i];
        matr->matrix_contents[a][i] = matr->matrix_contents[b][i];
        matr->matrix_contents[b][i] = temp;
    }

    temp = matr->values[a];
    matr->values[a] = matr->values[b];
    matr->values[b] = temp;

    detSign = -detSign;
}

// Gauss
struct matrix
gauss(struct matrix matr)
{
    // Going forwards:
    for (int i = 0; i < matr.size - 1; i++) {
        for (int j = i + 1; j < matr.size; j++) {

            // If the first element equals 0:
            if (matr.matrix_contents[i][i] == 0) {
                int currentLine = i;

                // Finding the first non-zero element:
                for (int k = i + 1; k < matr.size; k++) {
                    if (matr.matrix_contents[k][i] != 0) {
                        currentLine = k;
                        break;
                    }
                }

                // Swapping the i and the initial line that has a zero element:
                swapLines(&matr, i, currentLine);
            }

            // Calculating the factor:
            double factor = matr.matrix_contents[j][i] / matr.matrix_contents[i][i];

            // Substraction of the j line from i line multiplied on the factor:
            for (int k = i; k < matr.size; k++) {
                matr.matrix_contents[j][k] -= factor * matr.matrix_contents[i][k];
            }

            matr.values[j] -= matr.values[i] * factor;
        }
    }

    // Going backwards:
    if (!matr.matrix_contents[matr.size - 1][matr.size - 1]) {
        matr.results[matr.size - 1] = 0;
    } else {
        matr.results[matr.size - 1] = matr.values[matr.size - 1] / matr.matrix_contents[matr.size - 1][matr.size - 1];
    }

    for (int i = matr.size - 2; i >= 0; i--) {
        for (int j = matr.size - 1; j > i; j--) {
            matr.values[i] -= matr.matrix_contents[i][j] * matr.results[j];
        }

        if (!matr.values[i]) {
            matr.results[i] = 0;
        } else {
            matr.results[i] = matr.values[i] / matr.matrix_contents[i][i];
        }
    }  

    return matr;
}

// Improved Gauss:
struct matrix
gauss2(struct matrix matr)
{
    double *res = (double *) calloc(matr.size, sizeof(double));
    int *res_num = (int *) calloc(matr.size, sizeof(double));
    for (int i = 0; i < matr.size; i++) {
        res_num[i] = i;
    }

    // Forward:
    for (int i = 0; i < matr.size - 1; i++) {
        // Finding the maximum:
        double max = abs(matr.matrix_contents[i][i]);
        int index = i;
        for (int k = i + 1; k < matr.size; k++) {
            if (abs(matr.matrix_contents[i][k]) > max) {
                index = k;
                max = abs(matr.matrix_contents[i][k]);
            }
        }

        // Swapping i and index:
        if (i != index) {
            for (int k = 0; k < matr.size; k++) {
                swapLines(&matr, i, index);
            }
        }
        int buf = res_num[i];
        res_num[i] = res_num[index];
        res_num[index] = buf;

        double factor;
        for (int j = i + 1; j < matr.size; j++) {
            // Finding factor:
            factor = matr.matrix_contents[j][i]/matr.matrix_contents[i][i];

            // Substracting from line j line i multiplied by factor:
            for (int k = i; k < matr.size; k++) {
                matr.matrix_contents[j][k] -= factor * matr.matrix_contents[i][k];
            }
            matr.values[j] -= factor * matr.values[i];
        }
    }

    // Backward:
    if (!matr.matrix_contents[matr.size - 1][matr.size - 1]) {
        res[matr.size - 1] = 0;
    } else {
        res[matr.size - 1] = matr.values[matr.size - 1] / matr.matrix_contents[matr.size - 1][matr.size - 1];
    }

    for (int i = matr.size - 2; i >= 0; i--) {
        double factor = matr.values[i];
        for (int j = matr.size - 1; j > i; j--) {
            factor -= matr.matrix_contents[i][j]*res[j];
        }

        if (!factor) {
            res[i] = 0;
        } else {
            res[i] = factor / matr.matrix_contents[i][i];
        }
    }

    // Setting back the order:
    for (int i = 0; i < matr.size; i++) {
        if (res_num[i] != i) {
            double temp = res[i];
            res[i] = res[res_num[i]];
            res[res_num[i]] = temp;
            
            int buf = res_num[i];
            res_num[i] = res_num[buf];
            res_num[buf] = buf;
        }
    }

    // Copying the results:
    for (int i = 0; i < matr.size; i++) {
        matr.results[i] = res[i];
    }

    free(res);

    return matr;
}

int
determinant(struct matrix matr) 
{
    struct matrix result;
    copy(&result, gauss(matr));
    int det = 1;
    for (int i = 0; i < result.size; i++) {
        det *= result.matrix_contents[i][i];
    }

    del(&result);
    return det * detSign;
}

struct matrix
transpose(struct matrix matr)
{
    struct matrix transposed;
    create(&transposed, matr.size);

    for (int i = 0; i < matr.size; i++) {
        for (int j = 0; j < matr.size; j++) {
            transposed.matrix_contents[j][i] = matr.matrix_contents[i][j];
        }
    }

    return transposed;
}

struct matrix
invert(struct matrix matr)
{
    struct matrix inverted;
    create(&inverted, matr.size);
    for (int i = 0; i < matr.size; i++) {
        inverted.matrix_contents[i][i] = 1;
    }

    for (int j = 0; j < matr.size; j++) {  // Forward
        int t = j; // Finding first non zero line
        while (t < matr.size && !matr.matrix_contents[t][j]) {
            t++;
        }

        if (t != j) {
            double *buffer = matr.matrix_contents[j];
            matr.matrix_contents[j] = matr.matrix_contents[t];
            matr.matrix_contents[t] = buffer;
            buffer = inverted.matrix_contents[j];
            inverted.matrix_contents[j] = inverted.matrix_contents[t];
            inverted.matrix_contents[t] = buffer;
        }

        double factor = matr.matrix_contents[j][j];
        for (int k = 0; k < matr.size; k++) {
            matr.matrix_contents[j][k] /= factor;
            inverted.matrix_contents[j][k] /= factor;
        }

        for (int i = t + 1; i < matr.size; i++) {
            if (matr.matrix_contents[i][j]) {
                double factor = matr.matrix_contents[i][j];
                for (int k = 0; k < matr.size; k++) {
                    matr.matrix_contents[i][k] -= matr.matrix_contents[j][k] * factor;
                    inverted.matrix_contents[i][k] -= inverted.matrix_contents[j][k] * factor;
                }
            }
        }
    }

    // Backward
    for (int j = matr.size - 1; j > 0; j--) {
        for (int i = j - 1; i >= 0; i--) {
            for (int k = 0; k < matr.size; k++) {
                inverted.matrix_contents[i][k] -= matr.matrix_contents[i][j] * inverted.matrix_contents[j][k];
            }
        }
    }

    return inverted;
}
    
double
norm(struct matrix matr)
{
    double result = 0;
    for (int i = 0; i < matr.size; i++) {
        double sum = 0;
        for (int j = 0; j < matr.size; j++) {
            sum += abs(matr.matrix_contents[i][j]);
        }

        if (sum > result) {
            result = sum;
        }
    }

    return result;
}

double
condition(struct matrix matr)
{
    return norm(matr) * norm(invert(matr));
}

void 
next(struct matrix matr, double *current, double *previous, double omega) 
{
    for (int i = 0; i < matr.size; i++) {
        double first = 0;
        double second = 0;
        for (int j = 0; j < i; j++) {
            first += matr.matrix_contents[i][j] * current[j];
        }
        for (int j = i; j < matr.size; j++) {
            second += matr.matrix_contents[i][j] * previous[j];
        }
        current[i] = previous[i] + 
            (omega / matr.matrix_contents[i][i]) * 
            (matr.values[i] - first - second);
    }
}


double 
norm_relax(double *current, double *previous, int size)
{
    double res = 0;
    for (int i = 0; i < size; i++) {
        res += pow((current[i] - previous[i]), 2);
    }

    return sqrt(res);
}

double *
relax(struct matrix matr)
{
    double epsilon = 0;
    printf("Please, specify the accuracy. %lf\n", epsilon);
    scanf("%lf", &epsilon);

    long long max = 0;
    printf("Please, specify the max iterations number.\n");
    scanf("%lld", &max);

    double omega = 0;
    printf("Please, specify the first omega value.\n");
    scanf("%lf", &omega);

    double increment;
    printf("Please, specify the omega increment.\n");
    scanf("%lf", &increment);

    int min = max;
    double best_w;
    double *buffer   = (double *) calloc(matr.size, sizeof(*buffer));
    double *current  = (double *) calloc(matr.size, sizeof(*current));
    double *previous = (double *) calloc(matr.size, sizeof(*previous));

    for (double w = omega; w < 2; w += increment) {
        for (int i = 0; i < matr.size; i++) {
            previous[i] = 0;
        }

        long long counter = 0;
        for (int i = 0; 1; i++) {
            counter++;
            next(matr, current, previous, w);
            for (int k = 0; k < matr.size; k++) {
                buffer[k] = 0;
                for (int l = 0; l < matr.size; l++) {
                    buffer[k] += matr.matrix_contents[k][l] * current[l];
                }
            }

            if (norm_relax(buffer, matr.values, matr.size) < epsilon) {
                if (counter <= min) {
                    min = counter;
                    best_w = w;
                }

                printf("w = %lf  %lld iterations\n", w, counter);
                break;
            }

            if (counter >= max) {
                printf("More than %lld iterations\n", max);
                break;
            }

            for (int k = 0; k < matr.size; k++) {
                previous[k] = current[k];
            }
        }
    }

    free(buffer);
    free(previous);

    if (current) {
        printf("Best result with w = %lf. Number of iterations = %d\n", best_w, min);
    } else {
        printf("Wrong input\n");
        _exit(1);
    }

    return current;
}

struct matrix
special(int size, int x)
{
    struct matrix matr;
    create(&matr, size);

    for (int i = 1; i <= matr.size; i++) {
        for (int j = 1; j <= matr.size; j++) {
            if (i == j) {
                matr.matrix_contents[i - 1][j - 1] = pow((1.001 - 2 * 3 * pow(10, -3) - 1), i + j);
            } else {
                matr.matrix_contents[i - 1][j - 1] = pow(1.001 - 2 * 3 * pow(10, -3), i + j) + 0.1 * (j - i);
            }
        }

        matr.values[i - 1] = x * exp(x / i) * cos(x / i);
    }

    return matr;
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage:\nFirst argument: \n\tIf 1, the matrix is specified from keyboard by user, else is taken from file.\nSecond argument:\n\tIf the first argument is 1, it contains the mode, else it is the name of the file.\nThird argument (or second if the first equals one):\n\tIt contains the mode specificator. Modes availible:\n\t\t0 - Gauss\n\t\t1 - Gauss with selection\n\t\t2 - Determinant\n\t\t3 - Find condition number\n\t\t4 - Invert matrix\n\t\t5 - Successive over-relaxation method\n");
        return 0;
    }

    struct matrix matr;
    int argument = 1;
    if (atoi(argv[argument]) == 1) {
        copy(&matr, keyboard());
        argument++;
    } else {
        argument++;
        copy(&matr, file(argv[argument]));
        argument++;
    }

    int operation = atoi(argv[argument]);

    switch(operation)
    {
        case 0:
            printf("This is Gauss's method:\n");
            print(gauss(matr), 0);
            break;
        case 1:
            printf("This is Gauss's method with selection:\n");
            print(gauss2(matr), 0);
            break;
        case 2:
            printf("\nDeterminant of this matrix is:\n%d\n", determinant(matr));
            break;
        case 3:
            printf("\nThis is the condition number:\n%lf\n", condition(matr));
            break;
        case 4:
            printf("\nThis is inverted matrix:");
            print(invert(matr), 2);
            break;
        case 5:
            printf("\nThis is successive over-relaxation method:\n");
            double *result = relax(matr);
            for (int i = 0; i < matr.size; i++) {
                printf("%lf\n", result[i]);
            }

            free(result);
            break;
    }

        printf("Usage:\nFirst argument: \n\tIf 1, the matrix is specified from keyboard by user, else is taken from file.\nSecond argument:\n\tIf the first argument is 1, it contains the mode, else it is the name of the file.\nThird argument (or second if the first equals one):\n\tIt contains the mode specificator. Modes availible:\n\t\t0 - Gauss\n\t\t1 - Gauss with selection\n\t\t2 - Determinant\n\t\t3 - Find condition number\n\t\t4 - Invert matrix\n\t\t5 - Successive over-relaxation method\n");

    del(&matr);
    return 0;
}
