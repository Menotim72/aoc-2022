use std::cmp;
use std::collections::HashMap;
use std::io;

/// returns map, start_pos, end_pos
fn get_input() -> (Vec<Vec<u32>>, (usize, usize), (usize, usize)) {
    let stdin = io::stdin();
    let mut map: Vec<Vec<u32>> = Vec::new();
    let mut line: Vec<u32>;
    let mut start = None;
    let mut end = None;
    let (mut i, mut j) = (0usize, 0usize);

    for res in stdin.lines() {
        let string = res.expect("input error");
        line = Vec::new();
        for ch in string.chars() {
            match ch {
                'S' => {
                    line.push(0);
                    start = Some((i, j));
                }
                'E' => {
                    line.push(25);
                    end = Some((i, j));
                }
                c if c.is_ascii_lowercase() => line.push(u32::from(c) - u32::from('a')),
                _ => panic!("invalid input character"),
            }
            j += 1;
        }
        map.push(line);
        j = 0;
        i += 1;
    }
    (
        map,
        start.expect("start not found"),
        end.expect("end not found"),
    )
}

/// neighbors for going down
fn neighbors(node: &(usize, usize), map: &Vec<Vec<u32>>) -> Vec<(usize, usize)> {
    let height = map[node.0][node.1];
    let mut nb = Vec::new();
    if node.0 != 0 && map[node.0 - 1][node.1] + 1 >= height {
        nb.push((node.0 - 1, node.1));
    } // above
    if node.0 + 1 != map.len() && map[node.0 + 1][node.1] + 1 >= height {
        nb.push((node.0 + 1, node.1));
    } // below
    if node.1 != 0 && map[node.0][node.1 - 1] + 1 >= height {
        nb.push((node.0, node.1 - 1));
    } // left
    if node.1 + 1 != map[node.0].len() && map[node.0][node.1 + 1] + 1 >= height {
        nb.push((node.0, node.1 + 1));
    } // right
    nb
}

/// returns key with the minimum value
fn map_min<K, V: Ord>(nodes: &HashMap<K, V>) -> Option<&K> {
    nodes
        .iter()
        .min_by(|(_, val), (_, other)| val.cmp(other))
        .map(|(key, _)| key)
}

/// finds distance downwards from start to every reachable point
fn dijkstra(map: &Vec<Vec<u32>>, start: &(usize, usize)) -> HashMap<(usize, usize), i32> {
    let mut visited = HashMap::new();
    let mut unvisited = HashMap::new();
    for i in 0..map.len() {
        for j in 0..map[i].len() {
            unvisited.insert((i, j), i32::MAX);
        }
    }
    unvisited.insert(*start, 0);

    let mut current = *start;

    while unvisited.values().any(|x| *x != i32::MAX) {
        let next_val = unvisited[&current] + 1;
        for neighbor in neighbors(&current, &map) {
            if visited.contains_key(&neighbor) {
                continue;
            }
            unvisited.insert(neighbor, cmp::min(unvisited[&neighbor], next_val));
        }
        visited.insert(current, unvisited[&current]);
        unvisited.remove(&current);
        current = *map_min(&unvisited).unwrap();
    }
    visited
}

fn main() {
    let (map, start, end) = get_input();
    let paths = dijkstra(&map, &end);
    println!("Part 1: {}", paths[&start]);
    println!(
        "Part 2: {}",
        paths
            .iter()
            .filter(|((i, j), _)| map[*i][*j] == 0)
            .map(|(_, v)| v)
            .min()
            .unwrap()
    );
}
