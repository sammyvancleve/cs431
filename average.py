lines = open("nums", 'r').read()
data = lines.splitlines()
data_int = [int(x) for x in data]
total = sum(data_int) 
print(total/10)
