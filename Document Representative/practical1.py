import nltk
import string
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import PorterStemmer
from collections import Counter

# Download required NLTK data
nltk.download('punkt')
nltk.download('stopwords')

# Read file
with open("sample.txt", "r", encoding="utf-8") as file:
    text = file.read()

# Convert to lowercase
text = text.lower()

# Remove punctuation
text = text.translate(str.maketrans('', '', string.punctuation))

# Tokenization
tokens = word_tokenize(text)

# Remove stop words
stop_words = set(stopwords.words('english'))
filtered = []

for word in tokens:
    if word not in stop_words:
        filtered.append(word)

# Apply Porter Stemmer
ps = PorterStemmer()
stemmed = []

for word in filtered:
    stemmed.append(ps.stem(word))

# Count frequency
frequency = Counter(stemmed)

# Display representative words
print("\nRepresentative Words\n")

for word, count in frequency.most_common(10):
    print(word, ":", count)
    