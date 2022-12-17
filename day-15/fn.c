#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

/* manhattan distance between points */
int distance(Point a, Point b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

#define MAXLINE 1024

/* gets input into sensors and returns amount of sensors */
int get_input(Sensor sensors[]) {
  int i = 0;
  Point sensor, beacon;
  char line[MAXLINE];
  while (fgets(line, MAXLINE, stdin)) {
    sscanf(line, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d",
	   &sensor.x, &sensor.y, &beacon.x, &beacon.y);
    sensors[i].position = sensor;
    sensors[i].beacon = beacon;
    i++;
  }
  return i;
}

/* offset: sensor can access its x +- offset at row y
   returns -1 on out of range */
int offset(Sensor sensor, int row) {
  int dist = distance(sensor.position, sensor.beacon);
  if (sensor.position.y + dist < row || sensor.position.y - dist > row)
    return -1;
  return dist - abs(sensor.position.y - row);
}

/* test for get_input 
int main() {
  Sensor sensors[32];
  int n = get_input(sensors);
  for (int i = 0; i < n; i++) {
    printf("x=%d, y=%d -> x=%d, y=%d \n", sensors[i].position.x,
	   sensors[i].position.y, sensors[i].beacon.x, sensors[i].beacon.y);
  }
  return 0;
}
*/
