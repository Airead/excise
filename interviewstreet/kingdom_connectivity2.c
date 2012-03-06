/**
 * @file kingdom_connectivity.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  3月 05 15:35:53 CST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG_

#ifdef _DEBUG_
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

struct point {
    int indeg;
    int outdeg;
    int status;
    struct edge *edge;
};

struct edge {
    int begin;
    int end;
    struct edge *next;
};

/**
 * @brief insert edge to point_list
 * @param point_list
 * @param begin
 * @param end
 * @return on success returns 0, otherwise returns -1
 */
int point_list_insert_edge(struct point *point_list, int begin, int end)
{
    struct edge *tmpedge;

    if ((tmpedge = malloc(sizeof(struct edge))) == NULL) {
        return -1;
    }

    tmpedge->begin = begin;
    tmpedge->end = end;
    tmpedge->next = point_list[begin - 1].edge;
    point_list[begin - 1].edge = tmpedge;

    point_list[begin - 1].outdeg++;
    point_list[end - 1].indeg++;
    
    return 0;
}

/**
 * @brief get point list from stdin
 * @param city_num
 * @return on error returns NULL, otherwise returns point_list
 */
struct point *get_point_list(int city_num)
{
    struct point *point_list;
    int size;

    point_list = NULL;
        
    size = sizeof(struct point) * city_num;
    if ((point_list = malloc(size)) == NULL) {
        fprintf(stderr, "create point failed\n");
        return NULL;
    }
    memset(point_list, 0, size);

    return point_list;
}

/**
 * @brief get edge list from stdin
 * @param edge_num
 * @return on error returns NULL, otherwise returns edge_list
 */
struct edge *get_edge_list(int edge_num)
{
    struct edge *edge_list;
    int begin, end;
    int i, size;

    edge_list = NULL;
        
    size = sizeof(struct edge) * edge_num;
    if ((edge_list = malloc(size)) == NULL) {
        fprintf(stderr, "create edge failed\n");
        return NULL;
    }
    memset(edge_list, 0, size);

    for (i = 0; i < edge_num; i++) {
        scanf("%d %d", &begin, &end);
        edge_list[i].begin = begin;
        edge_list[i].end = end;
    }

    return edge_list;
}

/**
 * @brief find the point whose indeg is indeg
 * @param indeg
 * @param point_list
 * @param city
 * @return not found returns NULL, otherwise returns struct *point
 */
struct point *find_point_from_indeg(int indeg, struct point *point_list, int city_num)
{
    int i;
    struct point *p;

    for (i = 0; i < city_num; i++) {
        if (point_list[i].indeg == indeg && point_list[i].status == 0) {
            p = &point_list[i];
            break;
        }
    }
    
    if (i == city_num) {
        p = NULL;
    }
    
    return p;
}

/**
 * @brief check cyclic 
 * @param point_list
 * @param city_num
 * @return not cyclic returns 0, otherwise returns 1;
 */
int is_cyclic(struct point *point_list, int city_num)
{
    int i;
    struct point *p;

    for (i = 0; i < city_num; i++) {
        point_list[i].status = 0;
    }

    i = 0;
    while ((p = find_point_from_indeg(0, point_list, city_num)) != NULL) {
        p->status = 1;
        while (p->edge != NULL) {
            point_list[p->edge->end - 1].indeg--;
            p->edge = p->edge->next;
        }
        i++;
    }

    if (i < city_num) {
        return 1;
    }

    return 0;
}

/**
 * @brief target is destination, path_num++
 * @param point_list
 * @param city_num
 * @param path_num
 * @return on success returns 0, otherwise returns -1
 *
 * check the second parameter point 
 */
int check_target(struct point *point_list, int city, int city_num, int *path_num)
{
    struct edge *tmpedge;

    DBG("%d->", city);

    if (city == city_num) {
        DBG("++");
        (*path_num)++;
        return 0;
    }

    tmpedge = point_list[city - 1].edge;
    while (tmpedge != NULL) {
        check_target(point_list, tmpedge->end, city_num, path_num);
        tmpedge = tmpedge->next;
    }

    return 0;
}

/**
 * @brief get the number of different paths
 * @param point_list
 * @param city_num
 * @param edge_num
 * @return on error returns -1, otherwise returns number;
 */
int get_path_number(struct point *point_list, int city_num, int edge_num)
{
    int path_num;

    path_num = 0;
    check_target(point_list, 1, city_num, &path_num);
    
    return path_num;
}

int debug_point_list(struct point *point_list, int city_num)
{
    int i;
    struct edge *edge;

    fprintf(stderr, "point | indeg | outdeg | target \n");

    for (i = 0; i < city_num; i++) {
        fprintf(stdout, "%3d   | %3d   | %4d   | ", i + 1, point_list[i].indeg, point_list[i].outdeg);
        edge = point_list[i].edge;
        while (edge != NULL) {
            fprintf(stdout, "%d, ", edge->end);
            edge = edge->next;
        }
        fprintf(stdout, "\n");
    }

    return 0;
}

/**
 * @brief reset point list with edge list
 * @param point_list
 * @param edge_list
 * @param edge_num
 * @return on success returns 0, otherwise returns -1
 */
int point_list_reset(struct point *point_list, struct edge *edge_list, int edge_num)
{
    int i;

    for (i = 0; i < edge_num; i++) {
        if (point_list_insert_edge(point_list, edge_list[i].begin, edge_list[i].end) < 0) {
            fprintf(stderr, "inset edge failed\n");
            return -1;
        }
    }
    
    return 0;
}

int main(int argc, char *argv[])
{
    int city_num, edge_num;
    struct point *point_list;
    struct edge *edge_list;
    int path_num;

    scanf("%d %d", &city_num, &edge_num);
    DBG("city num: %d, edge num: %d\n", city_num, edge_num);

    if ((point_list = get_point_list(city_num)) == NULL) {
        fprintf(stderr, "get point_list failed\n");
        exit(1);
    }

    if ((edge_list = get_edge_list(edge_num)) == NULL) {
        fprintf(stderr, "get edge_list failed\n");
        exit(1);
    }

    if (point_list_reset(point_list, edge_list, edge_num) < 0) {
        fprintf(stderr, "point list reset failed\n");
        exit(1);
    }

//    debug_point_list(point_list, city_num);
 
    if (is_cyclic(point_list, city_num) != 0) {
        fprintf(stdout, "INFINITE PATHS");
        return 0;
    }

    if (point_list_reset(point_list, edge_list, edge_num) < 0) {
        fprintf(stderr, "point list reset failed\n");
        exit(1);
    }

    path_num = get_path_number(point_list, city_num, edge_num);

    fprintf(stdout, "%d", path_num);
    
    return 0;
}
