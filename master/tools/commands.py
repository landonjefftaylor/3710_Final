import random

words = []
with open("words.txt") as wordtxt:
  for line in wordtxt:
    words.append(line.rstrip())

verbs = []
with open("verbs.txt") as verbtxt:
  for line in verbtxt:
    verbs.append(line.rstrip())

with open("commands.txt", 'w') as commands:

  commands.write("static uint8_t* player1[10][5] = {\n")
  for i in range(0,10):
    commands.write("\t{")
    rwords = random.sample(words,5)
    for i in range(0,5):
      rstr = random.choice(verbs) + " the " + rwords[i] + "!" 
      commands.write('"' + rstr + '"')
      if i < 4:
        commands.write(', ')
    commands.write("}\n")
  commands.write("}\n")

  commands.write("static uint8_t* player2[10][16] = {\n")
  for i in range(0,10):
    commands.write("\t{")
    rwords = random.sample(words,16)
    for i in range(0,16):
      rstr = random.choice(verbs) + " the " + rwords[i] + "!" 
      commands.write('"' + rstr + '"')
      if i < 15:
        commands.write(', ')
    commands.write("}\n")
  commands.write("}\n")