use std::cmp::Ordering;

#[derive(PartialEq, Eq, Clone, Debug)]
enum Packet {
    Int(i32),
    List(Vec<Packet>),
}

impl Ord for Packet {
    fn cmp(&self, other: &Self) -> Ordering {
        match (self, other) {
            (Packet::Int(lval), Packet::Int(rval)) => lval.cmp(rval),
            (Packet::Int(val), Packet::List(_)) => Packet::List(vec![Packet::Int(*val)]).cmp(other),
            (Packet::List(_), Packet::Int(val)) => self.cmp(&Packet::List(vec![Packet::Int(*val)])),
            (Packet::List(left), Packet::List(right)) => {
                let mut ret = None;
                for i in 0..left.len() {
                    if i == right.len() {
                        break;
                    }
                    match left[i].cmp(&right[i]) {
                        Ordering::Equal => (),
                        not_equal => {
                            ret = Some(not_equal);
                            break;
                        }
                    }
                }
                match ret {
                    Some(val) => val,
                    None => left.len().cmp(&right.len()),
                }
            }
        }
    }
}

impl PartialOrd for Packet {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn list_tokens(list: &str) -> Vec<String> {
    if !(list.starts_with('[') && list.ends_with(']')) {
        panic!("invalid list: {}", list);
    }
    let list = list.strip_prefix('[').unwrap().strip_suffix(']').unwrap();
    let mut tokens = Vec::new();
    let mut parens_level = 0;
    let mut token = String::new();
    for i in list.chars() {
        if parens_level == 0 && i == ',' {
            tokens.push(token);
            token = String::new();
        } else {
            if i == '[' {
                parens_level += 1;
            } else if i == ']' {
                parens_level -= 1;
            }
            token.push(i);
        }
    }
    if token != String::from("") {
        tokens.push(token);
    }
    tokens
}

fn parse_list(input: &str) -> Packet {
    let mut ls = Vec::new();
    for token in list_tokens(input) {
        if token.starts_with('[') {
            ls.push(parse_list(&token));
        } else {
            match token.parse::<i32>() {
                Ok(i) => ls.push(Packet::Int(i)),
                Err(_) => panic!("invalid token: {:?}", token),
            }
        }
    }
    Packet::List(ls)
}

fn get_input() -> Vec<Packet> {
    let mut signal = Vec::new();
    let stdin = std::io::stdin();
    for line in stdin.lines() {
        if let Err(_) = line {
            panic!("input error");
        }
        let ln = line.unwrap();
        if ln == String::from("") {
            continue;
        }
	signal.push(parse_list(&ln));
    }
    signal
}

#[test]
fn test_ord() {
    let l1 = parse_list("[7,7,7]");
    let l2 = parse_list("[7,7,7,7,7]");
    assert_eq!(l1 > l2, false);
    assert_eq!(l2 > l1, true);
    assert_eq!(l1 == l2, false);
}

fn main() {
    let mut input = get_input();
    println!(
        "Part 1: {}",
        input
	    .chunks(2)
            .into_iter()
	    .enumerate()
            .filter(|(_, chunk)| chunk[0] <= chunk[1])
            .map(|(i, _)| i + 1)
            .sum::<usize>()
    );
    let pack1 = Packet::List(vec![Packet::List(vec![Packet::Int(2)])]);
    let pack2 = Packet::List(vec![Packet::List(vec![Packet::Int(6)])]);
    input.push(pack1.clone());
    input.push(pack2.clone());
    input.sort_unstable();
    println!(
        "Part 2: {}",
        (input.binary_search(&pack1).unwrap() + 1) * (input.binary_search(&pack2).unwrap() + 1)
    );
}
