with open("text3.txt", 'r') as f:
    lines = f.readlines()

    line_n = 1
    for line in lines:
        if "keshav" in line:
            print(f"keshav found in line {line_n}")
        line_n += 1
