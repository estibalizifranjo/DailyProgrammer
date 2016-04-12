#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

static std::vector<std::string> dictionary;
static std::string dictionaryFile("enable1.txt");
static std::string letters;

void readDictionary() {
  std::ifstream dictionaryStream(dictionaryFile);
  std::string word;
  while (dictionaryStream) {
    dictionaryStream >> word;
    dictionary.push_back(word);
  }
}

std::vector<std::string> getWords(std::string uniqueLetters, size_t tam) {
  std::vector<std::string> candidates;
  for (const std::string &s : dictionary) {
    if (s.size() == tam) {
      for (char c : s) {
        if (uniqueLetters.find(c) == std::string::npos) {
          goto out;
        }
      }
      candidates.push_back(s);
      out:;
    }
  }

  return candidates;
}

bool findCandidates(const std::vector<std::string> &candidates,
                    std::vector<std::string> &result, size_t tam) {

  if (result.size() == tam) {
    std::string flat;
    for (const std::string &word : result) {
      flat.append(word);
    }
    std::sort(flat.begin(), flat.end());
    return flat == letters;
  }

  std::string start;

  for (const std::string &s : result) {
    start.push_back(s[result.size()]);
  }

  auto first = std::lower_bound(candidates.begin(), candidates.end(), start);
  while (first->compare(0, start.size(), start) == 0) {
    result.push_back(*first);
    if (findCandidates(candidates, result, tam)) {
      return true;
    }
    result.pop_back();
    ++first;
  }

  return false;
}

std::vector<std::string>
findWordSquare(const std::vector<std::string> &candidates, size_t tam) {
  std::vector<std::string> wordSquare;

  for (std::string word : candidates) {
    wordSquare.push_back(word);
    if (findCandidates(candidates, wordSquare, tam)) {
      return wordSquare;
    } else {
      wordSquare.pop_back();
    }
  }
  return wordSquare;
}

int main(int argc, char *argv[]) {
  readDictionary();
  size_t tam;
  std::ifstream fileStream(argv[1]);
  if (!fileStream) {
    std::cerr << "ERROR";
    exit(-1);
  }

  while (fileStream >> tam >> letters) {
    std::sort(letters.begin(), letters.end());
    char previous = letters[0];
    static std::string uniqueLetters;
    uniqueLetters.push_back(previous);

    for (char c : letters) {
      if (c != previous) {
        uniqueLetters.push_back(c);
        previous = c;
      }
    }

    std::vector<std::string> candidates = getWords(uniqueLetters, tam);
    std::vector<std::string> wordSquare = findWordSquare(candidates, tam);

    for (std::string s : wordSquare) {
      std::cout << s << std::endl;
    }

    std::cout << std::endl;
  }

  return 0;
}
