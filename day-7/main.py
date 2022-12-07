class Dir:
    def __init__(self, name, parent):
        self.name = name
        self.size = 0
        self.parent = parent
        self.children = {} 

    def get_child(self, name):
        if name == '..':
            return self.parent
        return self.children[name]

    def add_child(self, name):
        self.children[name] = Dir(name, self)

    def get_size(self):
        return self.size + sum(self.children[n].get_size()
                               for n in self.children)

    def walk_children(self):
        yield self
        for child in self.children.values():
            for s in child.walk_children():
                yield s

def parse_input():
    file = open('input.txt', 'r')
    file.readline() # Skip first line

    root = Dir("/", None)
    cd = root
    for line in file:
        if line.startswith('$ cd'):
            cd = cd.get_child(line.strip().split(' ')[-1])
        elif line.startswith('dir '):
            cd.add_child(line.strip().split(' ')[-1])
        elif line.startswith('$ ls'):
            pass
        else:
            cd.size += int(line.split(' ')[0])
    return root

def part_1():
    root = parse_input()
    total = 0
    for child in root.walk_children():
        size = child.get_size()
        if size <= 100000:
            total += size
    print(total)

def part_2():
    root = parse_input()
    smallest = root.get_size()
    needed = 30000000 - (70000000 - smallest)
    for child in root.walk_children():
        size = child.get_size()
        if needed <= size < smallest:
            smallest = size
    print(smallest)

if __name__ == '__main__':
    part_2()
