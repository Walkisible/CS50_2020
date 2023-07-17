from cs50 import get_string

# Get input from user
text = get_string("Text: ")

allcount = len(text)

# Letters counting
count_letters = 0

alphabet = [ "a", "b", "c", "d", "e", "f", "g", "h",
             "i", "j", "k", "l", "m", "n", "o", "p",
             "q", "r", "s", "t", "u", "v", "w", "x",
             "y", "z"]

for i in range(allcount):
    if text[i].lower() in alphabet:
        count_letters += 1

# Words counting
count_words = 0

for i in range(allcount):
    if text[i] == " " and not text[i + 1] == " ":
        count_words += 1

count_words += 1

# Sentences counting
count_sentences = 0

for i in range(allcount):
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        count_sentences += 1

# Coleman-Liau index
x = count_letters
y = count_words
z = count_sentences

L = float(100 * (x / y))
S = float(100 * (z / y))

index = (0.0588 * L) - (0.296 * S) - 15.8
grade = int(round(index))

# Grade classification
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print("Grade %d" % grade)
