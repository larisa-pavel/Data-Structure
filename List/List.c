#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef double Item;
typedef struct List
{
    int timestamp;
    double value;
    struct List *next;
    struct List *prev;
} List;
void create_dll(List **head, int tmp, double val)
{
    List *nou1 = (List *)malloc(sizeof(List));
    List *last1 = *head;
    nou1->timestamp = tmp;
    nou1->value = val;
    nou1->next = NULL;
    if (*head == NULL)
    {
        nou1->prev = NULL;
        *head = nou1;
        return;
    }
    while (last1->next != NULL)
    {
        last1 = last1->next;
    }
    last1->next = nou1;
    nou1->prev = last1;
    return;
}
void read_dll(List **head, List **new_head, double val, int tmp)
{
    List *nou1 = (List *)malloc(sizeof(List));
    List *nou2 = (List *)malloc(sizeof(List));
    List *last1 = *head;
    List *last2 = *new_head;
    nou1->timestamp = tmp;
    nou1->value = val;
    nou1->next = NULL;
    nou2->timestamp = tmp;
    nou2->value = val;
    nou2->next = NULL;
    if (*head == NULL && *new_head == NULL)
    {
        nou1->prev = NULL;
        nou2->prev = NULL;
        *new_head = nou2;
        *head = nou1;
        return;
    }
    while (last1->next != NULL)
    {
        last1 = last1->next;
    }
    last1->next = nou1;
    nou1->prev = last1;
    while (last2->next != NULL)
    {
        last2 = last2->next;
    }
    last2->next = nou2;
    nou2->prev = last2;
    return;
}
void eliminare_nod(List **head, List **del)
{
    List *current = (*head);
    if ((*head) == NULL)
    {
        return;
    }
    while (current->next != NULL && (*del)->value != current->value)
    {
        current = current->next;
    }
    List *ok1;
    List *ok2;
    ok1 = current->prev;
    ok2 = current->next;
    ok1->next = ok2;
    ok2->prev = ok1;
    free(current);
}
int e1(List **last)
{
    double e1, e2, e3, e4, e5, med, dev, cont;
    e1 = (*last)->prev->prev->value;
    e2 = (*last)->prev->value;
    e3 = (*last)->value;
    e4 = (*last)->next->value;
    e5 = (*last)->next->next->value;
    med = (e1 + e2 + e3 + e4 + e5) / 5;
    cont = 0;
    cont = cont + ((e1 - med) * (e1 - med));
    cont = cont + ((e2 - med) * (e2 - med));
    cont = cont + ((e3 - med) * (e3 - med));
    cont = cont + ((e4 - med) * (e4 - med));
    cont = cont + ((e5 - med) * (e5 - med));
    dev = sqrt(cont / 5);
    double interval1, interval2;
    interval1 = med - dev;
    interval2 = med + dev;
    if (e3 >= interval1 && e3 <= interval2)
    {
        return 0;
    }
    return 1;
}
void free_chain(List **chain)
{
    (*chain) = (*chain)->next;
    List *lastt;
    while ((*chain) != NULL)
    {
        List *next = (*chain)->next;
        free((*chain)->prev);
        lastt = (*chain);
        (*chain) = next;
    }
    free(lastt);
}

void caut_mediana(List *last, double *val, int *tmp)
{
    double e1, e2, e3, e4, e5;
    *val = 0;
    *tmp = 0;
    e1 = last->prev->prev->value;
    e2 = last->prev->value;
    e3 = last->value;
    e4 = last->next->value;
    e5 = last->next->next->value;
    double temp;
    if (e1 > e2)
    {
        temp = e1;
        e1 = e2;
        e2 = temp;
    }
    if (e1 > e3)
    {
        temp = e1;
        e1 = e3;
        e3 = temp;
    }
    if (e1 > e4)
    {
        temp = e1;
        e1 = e4;
        e4 = temp;
    }
    if (e1 > e5)
    {
        temp = e1;
        e1 = e5;
        e5 = temp;
    }
    if (e2 > e3)
    {
        temp = e2;
        e2 = e3;
        e3 = temp;
    }
    if (e2 > e4)
    {
        temp = e2;
        e2 = e4;
        e4 = temp;
    }
    if (e2 > e5)
    {
        temp = e2;
        e2 = e5;
        e5 = temp;
    }
    if (e3 > e4)
    {
        temp = e3;
        e3 = e4;
        e4 = temp;
    }
    if (e3 > e5)
    {
        temp = e3;
        e3 = e5;
        e5 = temp;
    }
    if (e4 > e5)
    {
        temp = e4;
        e4 = e5;
        e5 = temp;
    }
    *val = e3;
    *tmp = last->timestamp;
}
void print_dll(List *head)
{
    if (head == NULL)
    {
        printf("e gol frate\n");
        return;
    }
    while (head != NULL)
    {
        printf("%d %.2lf\n", head->timestamp, head->value);
        head = head->next;
    }
}
int main(int argc, char *argv[])
{
    int n, i, j;
    double val;
    int tmp;
    List *head = NULL;
    List *new_head = NULL;
    List *task1 = NULL;
    List *task2 = NULL;
    List *task3 = NULL;
    List *task5 = NULL;
    List *last = NULL;
    List *last2 = NULL;
    List *last3 = NULL;
    List *last5 = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        scanf("%lf", &val);
        read_dll(&head, &new_head, val, tmp);
    }
    int new_n = n;
    for (j = 1; j < argc; j++)
    {
        if (strstr(argv[j], "--st"))
        {
            int interval, max, k, min;
            interval = atoi(argv[j] + 4);
            List *sort = NULL;
            List *index = NULL;
            double temp;
            for (sort = head; sort->next != NULL; sort = sort->next)
            {
                for (index = sort->next; index != NULL; index = index->next)
                {
                    if (sort->value > index->value)
                    {
                        temp = sort->value;
                        sort->value = index->value;
                        index->value = temp;
                    }
                }
            }
            min = ((int)(head->value / interval) - 1) * interval;
            max = ((int)(sort->value / interval) + 1) * interval;
            for (i = min; i < max; i = i + interval)
            {
                k = 0;
                while (head->value < i + interval && head->value > i)
                {
                    k++;
                    if (head->next != NULL)
                    {
                        head = head->next;
                    }
                    else
                    {
                        printf("[%d, %d] %d\n", i, i + interval, k);
                        while (head->prev != NULL)
                        {
                            head = head->prev;
                        }
                        free_chain(&head);
                        free_chain(&new_head);
                        return 0;
                    }
                }
                if (k != 0)
                {
                    printf("[%d, %d] %d\n", i, i + interval, k);
                }
            }
        }
        if (strcmp(argv[j], "--c") == 0)
        {
            last5 = new_head;
            create_dll(&task5, last5->timestamp, last5->value);
            create_dll(&task5, last5->next->timestamp, last5->next->value);
            last5 = last5->next->next;
            n = new_n;
            for (i = 0; i < new_n - 5; i++)
            {
                if (last5->next->timestamp - last5->timestamp >= 1000)
                {
                    create_dll(&task5, last5->timestamp, last5->value);
                    double w1, w2, w3, c, value_left1, value_left2, value_left3
                                    , value_right1, value_right2, value_right3;
                    int timestamp_left1, timestamp_right1;
                    while (task5->timestamp != last5->timestamp)
                    {
                        task5 = task5->next;
                    }
                    value_left1 = task5->value;
                    timestamp_left1 = task5->timestamp;

                    value_left2 = task5->prev->value;

                    value_left3 = task5->prev->prev->value;

                    value_right1 = last5->next->value;
                    timestamp_right1 = last5->next->timestamp;

                    value_right2 = last5->next->next->value;

                    value_right3 = last5->next->next->next->value;
                    w1 = 0.07017543;
                    w2 = 0.22807017;
                    w3 = 0.70175438;
                    tmp = last5->timestamp + 200;
                    while (task5->prev != NULL)
                    {
                        task5 = task5->prev;
                    }
                    while (tmp < last5->next->timestamp)
                    {
                        c = (double)(tmp - timestamp_left1) / (timestamp_right1 
                                                            - timestamp_left1);
                        val = (1 - c) * (value_left3 * w1 + value_left2 * w2 +
                                         value_left1 * w3) +
                              c * (value_right3 * w1 +
                                   value_right2 * w2 + value_right1 * w3);
                        create_dll(&task5, tmp, val);
                        n++;
                        tmp = tmp + 200;
                    }
                    last5 = last5->next;
                }
                else
                {
                    create_dll(&task5, last5->timestamp, last5->value);
                    last5 = last5->next;
                }
            }
            create_dll(&task5, last5->timestamp, last5->value);
            create_dll(&task5, last5->next->timestamp, last5->next->value);
            create_dll(&task5, last5->next->next->timestamp,
                       last5->next->next->value);
            if (j == argc - 1)
            {
                printf("%d\n", n);
                print_dll(task5);
            }
            new_n = n;
            free_chain(&new_head);
            new_head = task5;
        }
        if (strcmp(argv[j], "--u") == 0)
        {
            last = new_head;
            last = last->next;
            for (i = 0; i < new_n - 1; i++)
            {
                if (last->timestamp - last->prev->timestamp <= 1000 &&
                    last->timestamp - last->prev->timestamp >= 100)
                {
                    last->timestamp = (last->timestamp +
                                       last->prev->timestamp) /
                                      2;
                    last->value = (last->value + last->prev->value) / 2;
                }
                if (last->next != NULL)
                {
                    last = last->next;
                }
            }

            if (j == argc - 1)
            {
                printf("%d\n", new_n);
                print_dll(new_head);
            }
        }
        if (strcmp(argv[j], "--e1") == 0)
        {
            last = new_head;
            for (i = 0; i < new_n; i++)
            {
                create_dll(&task1, last->timestamp, last->value);
                last = last->next;
            }
            last = new_head;
            last = last->next->next;
            int nr = new_n;
            for (i = 0; i < new_n - 4; i++)
            {
                if (e1(&last) == 1)
                {
                    eliminare_nod(&task1, &last);
                    nr--;
                }
                last = last->next;
            }
            new_n = nr;
            if (j == argc - 1)
            {
                printf("%d\n", new_n);
                print_dll(task1);
            }
            free_chain(&new_head);
            new_head = task1;
        }
        if (strcmp(argv[j], "--e2") == 0)
        {
            last2 = new_head;
            last2 = last2->next->next;
            for (i = 0; i < new_n - 4; i++)
            {
                caut_mediana(last2, &val, &tmp);
                create_dll(&task2, tmp, val);
                last2 = last2->next;
            }
            if (j == argc - 1)
            {
                printf("%d\n", new_n - 4);
                print_dll(task2);
            }
            new_n = new_n - 4;
            free_chain(&new_head);
            new_head = task2;
        }
        if (strcmp(argv[j], "--e3") == 0)
        {
            last3 = new_head;
            last3 = last3->next->next;
            double media = 0;
            for (i = 0; i < new_n - 4; i++)
            {
                media = last3->prev->prev->value + last3->prev->value +
                last3->value + last3->next->value + last3->next->next->value;
                media = media / 5;
                create_dll(&task3, last3->timestamp, media);
                last3 = last3->next;
            }
            if (j == argc - 1)
            {
                printf("%d\n", new_n - 4);
                print_dll(task3);
            }
            new_n = new_n - 4;
            free_chain(&new_head);
            new_head = task3;
        }
    }
    free_chain(&head);
    free_chain(&new_head);
    return 0;
}
