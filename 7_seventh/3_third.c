#include <stdlib.h>
#include <stdio.h>

enum
{
    A_INIT = 1103515245,
    C_INIT = 12345,
    M_INIT = 2147483648
};

struct RandomGenerator;
void destroy(struct RandomGenerator *);
int next(struct RandomGenerator *);

struct RandomOperations
{
    int (*next) (struct RandomGenerator *);
    void (*destroy) (struct RandomGenerator *);
};

typedef struct RandomGenerator
{
        unsigned int a;
        unsigned int c;
        unsigned int m;
        int currentNumber;
        
        struct RandomOperations *ops;
} RandomGenerator;

struct RandomGenerator *
random_create(int seed)
{
    struct RandomGenerator *rr = calloc(1, sizeof(struct RandomGenerator));
    rr->ops = calloc(1, sizeof(struct RandomOperations));
    rr->ops->next = next;
    rr->ops->destroy = destroy;
    rr->currentNumber = seed;
    rr->a = A_INIT;
    rr->c = C_INIT;
    rr->m = M_INIT;
    return rr;
}

int 
next(struct RandomGenerator *rr) 
{
    rr->currentNumber = (rr->currentNumber * rr->a + rr->c) % rr->m;
    return rr->currentNumber;
}

void
destroy(struct RandomGenerator *rr)
{
    free(rr->ops);
    free(rr);
}

int
main(void)
{
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
        printf("%d: %d\n", j, rr->ops->next(rr));
    }
    rr->ops->destroy(rr);

    return 0;
}
