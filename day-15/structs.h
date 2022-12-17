/* a coordinate point */
typedef struct Point {
  int x;
  int y;
} Point;


/* a sensor */
typedef struct Sensor {
  struct Point position;
  struct Point beacon;
} Sensor;
