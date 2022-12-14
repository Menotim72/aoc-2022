use std::collections::HashSet;
use std::cmp::{min, max};

#[derive(PartialEq, Eq, Hash, Debug, Clone, Copy)]
struct Point {
    pub x: i32,
    pub y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Self {
	Point { x, y }
    }
}

fn parse_point(point: &str) -> Point {
    let tpl = point.split_once(',').unwrap();
    Point::new(tpl.0.parse().unwrap(), tpl.1.parse().unwrap())
}

fn get_input() -> HashSet<Point> {
    let stdin = std::io::stdin();
    let mut rocks = HashSet::new();
    let (mut start, mut end);
    for line in stdin.lines() {
	let unwrapped = line.unwrap();
	let mut split = unwrapped.split(" -> ");
	start = parse_point(split.next().unwrap());
	for s in split {
	    end = parse_point(s);
	    if start.x == end.x {
		for y in min(start.y, end.y)..(max(start.y, end.y)+1) {
		    rocks.insert(Point::new(start.x, y));
		}
	    } else if start.y == end.y {
		for x in min(start.x, end.x)..(max(start.x, end.x)+1) {
		    rocks.insert(Point::new(x, start.y));
		}
	    }
	    start = end;
	}
    }
    rocks
}

fn fall_sand(mut rocks: HashSet<Point>, is_floor: bool) -> i32 {
    let min_height = rocks.iter().max_by_key(|pt| pt.y).unwrap().y;
    let mut i = 0;
    let origin = Point::new(500, 0);
    let mut sand = origin;
    loop {
	if !is_floor && sand.y >= min_height {
	    break;
	}
	if is_floor && sand.y == min_height + 1 {
	    rocks.insert(sand);
	    i += 1;
	    sand = Point::new(500, 0);
	}
	let down = Point::new(sand.x, sand.y+1);
	let left = Point::new(sand.x-1, sand.y+1);
	let right = Point::new(sand.x+1, sand.y+1);
	if !rocks.contains(&down) {
	    sand = down;
	} else if !rocks.contains(&left) {
	    sand = left;
	} else if !rocks.contains(&right) {
	    sand = right;
	} else {
	    rocks.insert(sand);
	    i += 1;
	    if is_floor && sand == origin {
		break;
	    }
	    sand = origin;
	}
    }
    i
}
   
/*
#[derive(PartialEq, Eq, Debug)]
enum Direction {
    Down,
    Right,
}

struct Line {
    start: Point,
    end: Point,
    direction: Direction,
}

impl Line {
    fn between(a: Point, b: Point) -> Self {
	if a.x == b.x {
	    Line {
		start: min_by_key(a, b, |pt| pt.y),
		end: max_by_key(a, b, |pt| pt.y),
		direction: Down,
	    }
	} else if a.y == b.y {
	    Line {
		start: min_by_key(a, b, |pt| pt.x),
		end: max_by_key(a, b, |pt| pt.x),
		direction: Right,
	    }
	} else { panic!("points not on the same line"); }
    }

    fn overlaps(&self, other: &Self) -> Option<Self> {
	if self.direction != other.direction {
	    return None;
	}
	match self.direction {
	    Right => {
		if self.y != other.y {
		    
	}
    }
}
*/
fn main() {
    let rocks = get_input();
    println!("Part 1: {}", fall_sand(rocks.clone(), false));
    println!("Part 2: {}", fall_sand(rocks, true));
}
