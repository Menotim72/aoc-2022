#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

#define max(a,b) (a)>(b) ? (a) : (b)

int get_input(Sensor sensors[]);
int offset(Sensor sensor, int row);
int distance(Point a, Point b);

#define MAXSENSORS 32
#define MAXROW 10000000
#define ROW 10

int row[MAXROW];

int main() {
  Sensor sensors[MAXSENSORS];
  int amount = get_input(sensors);

  int max_seen = -1;
  int min_seen = MAXROW;
  int ofs, start, end;
  for (int s = 0; s < amount; s++) {
    // Calculates offset
    ofs = offset(sensors[s], ROW);
    if (ofs == -1) continue;

    // Calculates range sensed by sensor
    start = sensors[s].position.x - ofs;
    end = sensors[s].position.x + ofs;

    // Marks range in array as sure not to have beacons
    for (int i = start; i <= end; i++)
      if (i < 0) row[MAXROW-i] = 1;
      else row[i] = 1;

    // min_seen and max_seen are used to iterate through row
    if (end > max_seen) max_seen = end;
    if (start < min_seen) min_seen = start;
    printf("%d\n", row[max_seen]);
  }
  
  // Marks position of beacons as having beacons
  for (int s = 0; s < amount; s++) {
    if (sensors[s].beacon.y == ROW)
      row[sensors[s].beacon.x] = 0;
  }
 
  // Counts places sure not to have beacons in row
  int total = 0;
  for (int i = min_seen; i <= max_seen; i++) {
    if (i > 0) printf(row[MAXROW-i] ? "#" : ".");
    else printf(row[i] ? "#" : ".");
  }
  printf("\n");
    
  return 0;
}
