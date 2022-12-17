use std::ops::Range;
use itertools::Itertools;

#[derive(Debug, PartialEq, Eq)]
struct Point {
    pub x: i32,
    pub y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Self {
        Point { x, y }
    }

    // Manhattan distance
    fn distance(&self, other: &Self) -> i32 {
        i32::abs(self.x - other.x) + i32::abs(self.y - other.y)
    }
}

#[derive(Debug)]
struct Sensor {
    pub position: Point,
    pub beacon: Point,
}

impl Sensor {
    fn new(sensor_x: i32, sensor_y: i32, beacon_x: i32, beacon_y: i32) -> Self {
        Sensor {
            position: Point::new(sensor_x, sensor_y),
            beacon: Point::new(beacon_x, beacon_y),
        }
    }

    // Range of detection in that row
    fn window(&self, row: i32) -> Option<Range<i32>> {
        let distance = self.position.distance(&self.beacon);
        let offset = distance - i32::abs(self.position.y - row);
        if offset < 0 {
            None
        } else {
            Some(Range {
                start: self.position.x - offset,
                end: self.position.x + offset + 1,
            })
        }
    }

    // All positions excluded by its reach
    fn excluded(&self) -> Vec<(usize, usize)> {
        let mut exc = Vec::new();
        let distance = self.position.distance(&self.beacon);
        for i in (-distance)..(distance + 1) {
            let row = self.position.y + i;
            if row < 0 || row > 4000000 {
                continue;
            }
            for col in self.window(row).unwrap() {
                if col < 0 || col > 4000000 {
                    continue;
                }
                exc.push((row as usize, col as usize));
            }
        }
        exc
    }
}

fn get_input() -> Vec<Sensor> {
    let mut sensors = Vec::new();
    for res in std::io::stdin().lines() {
        let line = res.unwrap();
        let mut spl = line.split(' ');
        sensors.push(Sensor::new(
            spl.nth(2)
                .unwrap()
                .strip_prefix("x=")
                .unwrap()
                .strip_suffix(",")
                .unwrap()
                .parse()
                .unwrap(),
            spl.next()
                .unwrap()
                .strip_prefix("y=")
                .unwrap()
                .strip_suffix(":")
                .unwrap()
                .parse()
                .unwrap(),
            spl.nth(4)
                .unwrap()
                .strip_prefix("x=")
                .unwrap()
                .strip_suffix(",")
                .unwrap()
                .parse()
                .unwrap(),
            spl.next()
                .unwrap()
                .strip_prefix("y=")
                .unwrap()
                .parse()
                .unwrap(),
        ));
    }
    sensors
}

// Reduce ranges into non-overlapping ranges
fn reduce(ranges: Vec<Range<i32>>) -> Vec<Range<i32>> {
    let mut reduced = Vec::new();
    for mut range in ranges {
        let partition = reduced.partition_point(|part: &Range<i32>| part.start < range.start);

        // Checks ranges after partition
        while partition < reduced.len() && reduced[partition].start < range.end {
            let part = reduced.remove(partition);
            if part.end >= range.end {
                range.end = part.end;
                break; // Guaranteed not to continue after this anyways
            }
        }

        // Checks range before partition
        if partition > 0 && range.start < reduced[partition - 1].end {
            reduced[partition - 1].end = reduced[partition-1].end.max(range.end);
        } else {
            reduced.insert(partition, range);
        }
    }
    reduced
}

fn combined_window(sensors: &Vec<Sensor>, row: i32) -> Vec<Range<i32>> {
    reduce(sensors.iter().filter_map(|sensor| sensor.window(row)).collect())
}

// Number of positions covered by ranges
// ranges are assumed to be non-overlapping, if not use reduce first
fn positions(ranges: Vec<Range<i32>>) -> i32 {
    let mut total = 0;
    for range in ranges {
	total += range.end - range.start;
    }
    total
}

fn part_1(sensors: &Vec<Sensor>, row: i32) -> i32 {
    let ranges = combined_window(sensors, row);
    let beacons: i32 = sensors.iter()
	.filter(|sensor| sensor.beacon.y == row)
	.unique_by(|sensor| sensor.beacon.x)
	.count().try_into().unwrap();
    positions(ranges) - beacons
}

fn covers(ranges: Vec<Range<i32>>, range: Range<i32>) -> bool {
    let partition = ranges.partition_point(|part| part.contains(&range.start));
    partition > 0 && ranges[partition-1].contains(&range.end)
}

fn part_2(sensors: &Vec<Sensor>) -> Option<(i32, i32)> {
    for row in 0..4000001 {
        if row % 100000 == 0 {
	    // progress meter because this takes a bit
            println!("row={}", row);
        }
	if !covers(combined_window(sensors, row), 0..4000001) {
	    let cw = combined_window(sensors, row);
	    return Some((row,  cw[0].end));
	}
    }
    None
}

fn main() {
    let input = get_input();
    println!("Part 1: {}", part_1(&input, 2000000));
    let (row, col) = part_2(&input).unwrap();
    println!("Part 2: {}, {} -> {}", row, col, (row as i64) + (col as i64)*4000000);
}
