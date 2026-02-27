#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>

int findThirdLargestUnique(const std::vector<int>& v);

int kthLargestUnique(const std::vector<int>& v, int k);

int findSecondSmallestUnique(const std::vector<int>& v);

std::vector<int> rotateVectorSafe(const std::vector<int>& v, long long k);

std::vector<int> rotateSubrange(const std::vector<int>& v, int l, int r, int k);

std::string removeConsecutiveDuplicatesCI(const std::string& s);

void removePunctuationSmart(std::string& s);

void normalizeSpaces(std::string& s);

int longestIncreasingRun(const std::vector<int>& v);

int longestEqualRun(const std::vector<int>& v);

std::vector<int> uniquePreserveOrder(const std::vector<int>& v);

int secondMostFrequent(const std::vector<int>& v);

int majorityElement(const std::vector<int>& v);

bool canBeSortedByOneSwap(const std::vector<int>& v);

std::string removePatternRepeat(std::string s, const std::string& pat);

bool isBalancedParens(const std::string& s);

std::string smallestWindowAllChars(const std::string& s, const std::string& required);

std::string runLengthEncode(const std::string& s);

int findMissing1ToN(const std::vector<int>& v, int n);

double evalPoly(const std::vector<double>& coeffs, double x);

#endif