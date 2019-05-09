sample_words = []
white_space_letters = [' ', '\n']

with open('sample_words.txt', 'r') as f:
	for line in f:
		sample_words.append(line.strip())

import random

random.seed(201120848)

with open('fake-data.txt', 'w') as f:
	l = len(sample_words)
	idx = 0

	for _ in range(1000000000):
		idx = (idx + int(random.random() * l)) % l if random.random() > 0.5 else (idx - int(random.random() * l)) % l 
		f.write(sample_words[idx] + white_space_letters[0 if random.random() < 0.9 else 1])
