/**
 * @file kingdom_connectivity.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  3月 02 15:51:52 CST
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

struct road {
    int from;
    int to;
    int times;
};

int city_num, road_num;

/**
 * @brief get road list from stdin
 * @param road_num : the number of road
 * @return on error returns NULL, otherwise returns struct #road *
 */
struct road *get_road_list(int road_num)
{
    int i;
    int size;
    struct road *road_list;

    size = sizeof(struct road) * (road_num + 1); 
    road_list = (struct road *)malloc(size);
    if (road_list == NULL) {
        printf("malloc failed\n");
        return NULL;
    }
    memset(road_list, 0, size);

    for (i = 0; i < road_num; i++) {
        scanf("%d %d", &road_list[i].from, &road_list[i].to);
    }
    
    return road_list;
}

/**
 * @brief get the list of city which can go to city
 * @param city : should go to city
 * @param road_list : all road in it
 * @return on error returns NULL, otherwise returns city_from_list
 */
int *get_city_from_list(int city, struct road *road_list)
{
    int count, *city_from_list, *tmp_list;
    int size;
    struct road *road;

    /* get from city list number to malloc */
    count = 0;
    road = road_list;
    while (road->to != 0) {
        if (road->to == city) {
            count++;
        }
        road++;
    }
    
    size = sizeof(int) * (count + 1);
    city_from_list = (int *)malloc(size);
    if (city_from_list == NULL) {
        printf("malloc city_from failed\n");
        return NULL;
    }
    memset(city_from_list, 0, size);

    /* set city_from_list */
    road = road_list;
    tmp_list = city_from_list;
    while (road->to != 0) {
        if (road->to == city) {
            *tmp_list++ = road->from;
            road->times++;
            DBG("\n%d --> %d: times: %d\n", road->from, road->to, road->times);
        }
        road++;
    }

    return city_from_list;
}

/**
 * @brief get the number of path from city_from to city_to
 * @param city_start : start point of city
 * @param city_to : 
 * @param road_list : 
 * @param road_num : the number of road
 * @return on infinite returns -1, otherwise returns the number of path
 */
int get_path_number(int city_start, int city_to, struct road *road_list, int road_num)
{
    int num, *city_from_list, tmp_num;
    int *pcity;
    struct road *road;
    static int target_from;            /*
                                        * if target city call
                                        * get_city_from_list, target_from set 1,
                                        * and don't call again
                                        */

    DBG("->%d", city_to);

    num = 0;

    if (city_to == city_num) {
        if (target_from == 0) {
            target_from = 1;
        } else {
            return 0;
        }
    }

    city_from_list = get_city_from_list(city_to, road_list);
    if (city_from_list == NULL) {
        return 0;
    }

    /* check infinite*/
    road = road_list;
    while (road->to != 0) {
        if (road->times >= road_num) {
            DBG("%d --> %d: times: %d\n", road->from, road->to, road->times);
            return -1;
        }
        road++;
    }

    pcity = city_from_list;
    while (*pcity != 0) {
        if (*pcity == city_start) {
            DBG("->%d", *pcity);
            num++;
        } else {
            tmp_num = get_path_number(city_start, *pcity, road_list, road_num);
            if (tmp_num < 0) {
                return -1;
            }
            num += tmp_num;
        }
        pcity++;
    }

    return num;
}

int main(int argc, char *argv[])
{
    int i, path_num;
    struct road *road_list;
    
    scanf("%d %d", &city_num, &road_num);
    DBG("city_num = %d, road_num = %d\n", city_num, road_num);

    road_list = get_road_list(road_num);

    for (i = 0; i < road_num; i++) {
        DBG("road[%d]: %3d   --> %3d\n", i + 1, road_list[i].from, road_list[i].to);
    } 

    path_num = get_path_number(1, city_num, road_list, road_num);
    if (path_num < 0) {
        printf("INFINITE PATHS");
    }else {
        printf("%d", path_num);
    }

    free(road_list);
    return 0;
}
