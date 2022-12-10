use std::io;
use std::collections::HashMap;

enum InputCommand {
    Cd(String),
    Ls,
    Dir(String),
    File(u32),
    EOF,
    InputError,
}

/// Parses input line (from stdin)
fn parse_input_line() -> InputCommand {
    let stdin = io::stdin();
    let mut line = String::new();
    match stdin.read_line(&mut line) {
	Err(_) => return InputCommand::InputError,
	Ok(0) => return InputCommand::EOF,
	_ => (),
    }
    if line.starts_with ("$ ls") {
	InputCommand::Ls
    } else if line.starts_with("$ cd ") {
	InputCommand::Cd(line.strip_prefix("$ cd ").unwrap()
	                 .strip_suffix('\n').unwrap()
			 .to_owned())
    } else if line.starts_with("dir ") {
	InputCommand::Dir(line.strip_prefix("dir ").unwrap()
	                  .strip_suffix('\n').unwrap()
			  .to_owned())
    } else if let Some(num) = line.split(' ').next() {
	if let Ok(size) = num.parse() {
	    InputCommand::File(size)
	} else { InputCommand::InputError }
    } else { InputCommand::InputError }
}

fn child(path: &Vec<String>, name: String) -> Vec<String> {
    let mut ch = path.clone();
    ch.push(name);
    ch
}


/// Run inputted commands, returning the directory tree
fn run_commands() -> HashMap<Vec<String>, u32> {
    parse_input_line(); // ignore first line
    let mut tree: HashMap<Vec<String>, u32> = HashMap::new();
    let mut cd = vec![String::from("/")];
    tree.insert(cd.clone(), 0);

    loop { match parse_input_line() {
	InputCommand::EOF => break,
	InputCommand::Ls => (),
	InputCommand::Dir(dir) => { tree.insert(child(&cd, dir), 0); },
	InputCommand::File(size) =>
	    *tree.get_mut(&cd).expect("in non-existing directory") += size,
	InputCommand::Cd(dir) => if dir == ".." {
	    cd.pop();
	} else {
	    cd.push(dir.to_owned());
	}
	InputCommand::InputError => panic!("Invalid command")
    }}
    tree
}

fn get_size(path: &Vec<String>, tree: &HashMap<Vec<String>, u32>) -> u32 {
    let mut total = 0;
    for (p, size) in tree {
	if p.starts_with(&path) {
	    total += size;
	}
    }
    total
}

fn part_1() {
    let tree = run_commands();
    let mut total = 0;
    for (path, _) in &tree {
	let size = get_size(path, &tree);
	if size <= 100000 { total += size; }
    }
    println!("{}", total);
}

fn part_2() {
    let tree = run_commands();
    let available = 70000000 - get_size(&vec![String::from("/")], &tree);
    let needed = 30000000 - available;
    let mut min_enough = 70000000;
    for (path, _) in &tree {
	let size = get_size(path, &tree);
	if needed <= size && size < min_enough { min_enough = size; }
    }
    println!("{}", min_enough);
}

fn main() {
    //part_1();
    part_2();
}
