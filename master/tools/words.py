import random

print("Generate 2000 pronounceable non-words")

def v():
  vowels = "aeiouy"
  return random.choice(vowels)

def c():
  consonants = "bcdfghjklmnpqrstvwxyz"
  return random.choice(consonants)

with open("words.txt", 'w') as wf:
  vowels = "aeiouy"
  for i in range(2000): #gen 2000 words
    word = ""
    wasCons = False
    twoVowel = False
    for j in range(random.choice(range(5,11))): #letters in word
      if not(twoVowel) and (wasCons or random.getrandbits(1)):
        if word == "" or word[-1] in vowels:
          twoVowel = True
        word = word + v()
        wasCons = False
      else:
        word = word + c()
        wasCons = True
        twoVowel = False
    wf.write(word.title() + "\n")

print("Generation Complete")