with open("cards1.txt", "w") as cards:
  with open("com1.txt") as com:
    i = 0
    for line in com:
      words = line.split('"')
      cards.write("\nGame mode " + str(i) + "\n")
      for word in words:
        if "!" in word:
          cards.write(word.rstrip("!").split()[-1] + "\n")
      i = i + 1

with open("cards2.txt", "w") as cards:
  with open("com2.txt") as com:
    i = 0
    for line in com:
      words = line.split('"')
      cards.write("\nGame mode " + str(i) + "\n")
      for word in words:
        if "!" in word:
          cards.write(word.rstrip("!").split()[-1] + "\n")
      i = i + 1