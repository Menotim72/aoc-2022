from sys import stdin

stacks = [list(s) for s in
          ([],
          "GDVZJSB",
          "ZSMGVP",
          "CLBSWTQF",
          "HJGWMRVQ",
          "CLSNFMD",
          "RGCD",
          "HGTRJDSQ",
          "PFV",
          "DRSTJ")]

def move_9000(amount, fro, to):
    for i in range(amount):
        to.append(fro.pop())

def move_9001(amount, fro, to):
    to.extend(fro[-amount:])
    del fro[-amount:]

def get_input_and_move(stacks, move):
    while stdin.readline() != '\n':
        pass
    while (line := stdin.readline()) != '':
        ls = line.split(' ')
        move(int(ls[1]), stacks[int(ls[3])], stacks[int(ls[5])])

def part_1():
    get_input_and_move(stacks, move_9000)
    print(''.join(s[-1] for s in stacks[1:]))

def part_2():
    get_input_and_move(stacks, move_9001)
    print(''.join(s[-1] for s in stacks[1:]))

if __name__ == '__main__':
    part_2()
