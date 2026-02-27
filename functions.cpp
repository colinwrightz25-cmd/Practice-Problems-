#include "functions.h"
#include <vector>
#include <string>
#include <limits>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cctype>

// 1) Third largest unique
int findThirdLargestUnique(const std::vector<int>& v) {
    long long first = std::numeric_limits<long long>::min();
    long long second = std::numeric_limits<long long>::min();
    long long third = std::numeric_limits<long long>::min();

    for (int x : v) {
        if (x == first || x == second || x == third) continue;

        if (x > first) {
            third = second;
            second = first;
            first = x;
        } else if (x > second) {
            third = second;
            second = x;
        } else if (x > third) {
            third = x;
        }
    }

    if (third == std::numeric_limits<long long>::min()) return -1;
    return static_cast<int>(third);
}

// 2) Kth largest unique
int kthLargestUnique(const std::vector<int>& v, int k) {
    if (k <= 0) return -1;
    std::vector<int> uniq = v;
    std::sort(uniq.begin(), uniq.end());
    uniq.erase(std::unique(uniq.begin(), uniq.end()), uniq.end());
    if (static_cast<int>(uniq.size()) < k) return -1;
    // largest is at end
    return uniq[uniq.size() - k];
}

// 3) Second smallest unique
int findSecondSmallestUnique(const std::vector<int>& v) {
    long long first = std::numeric_limits<long long>::max();
    long long second = std::numeric_limits<long long>::max();

    for (int x : v) {
        if (x == first || x == second) continue;

        if (x < first) {
            second = first;
            first = x;
        } else if (x < second) {
            second = x;
        }
    }

    if (second == std::numeric_limits<long long>::max()) return -1;
    return static_cast<int>(second);
}

// Helper: normalize rotation amount for size n (returns in [0, n-1])
static long long normK(long long k, long long n) {
    if (n == 0) return 0;
    long long r = k % n;
    if (r < 0) r += n;
    return r;
}

// 4) Rotate with huge k + empty safety
std::vector<int> rotateVectorSafe(const std::vector<int>& v, long long k) {
    const long long n = static_cast<long long>(v.size());
    if (n == 0) return {};
    long long r = normK(k, n); // right rotation by r
    if (r == 0) return v;

    std::vector<int> out(n);
    for (long long i = 0; i < n; i++) {
        out[(i + r) % n] = v[i];
    }
    return out;
}

// 5) Rotate a subrange [l, r] inclusive
std::vector<int> rotateSubrange(const std::vector<int>& v, int l, int r, int k) {
    const int n = static_cast<int>(v.size());
    if (n == 0) return v;
    if (l < 0 || r < 0 || l >= n || r >= n || l > r) return v;

    int len = r - l + 1;
    if (len <= 1) return v;

    long long rr = normK(k, len); // right rotation 
    if (rr == 0) return v;

    std::vector<int> out = v;
    for (int i = 0; i < len; i++) {
        out[l + (i + rr) % len] = v[l + i];
    }
    return out;
}

// 6) Remove consecutive duplicates, case-insensitive (preserve first char casing)
std::string removeConsecutiveDuplicatesCI(const std::string& s) {
    if (s.empty()) return "";

    std::string out;
    out.reserve(s.size());

    auto lowerc = [](unsigned char c) { return static_cast<char>(std::tolower(c)); };

    out.push_back(s[0]);
    char prev = lowerc(static_cast<unsigned char>(s[0]));

    for (size_t i = 1; i < s.size(); i++) {
        char cur = lowerc(static_cast<unsigned char>(s[i]));
        if (cur != prev) {
            out.push_back(s[i]);
            prev = cur;
        }
    }
    return out;
}

// 7) Remove punctuation but keep apostrophes inside words (between letters)
void removePunctuationSmart(std::string& s) {
    std::string out;
    out.reserve(s.size());

    auto isLetter = [](unsigned char c) { return std::isalpha(c) != 0; };
    auto isPunct  = [](unsigned char c) { return std::ispunct(c) != 0; };

    for (size_t i = 0; i < s.size(); i++) {
        unsigned char c = static_cast<unsigned char>(s[i]);

        if (s[i] == '\'') {
            bool left = (i > 0) && isLetter(static_cast<unsigned char>(s[i - 1]));
            bool right = (i + 1 < s.size()) && isLetter(static_cast<unsigned char>(s[i + 1]));
            if (left && right) out.push_back('\''); // keep
            // else drop
        } else if (isPunct(c)) {
            // drop punctuation
        } else {
            out.push_back(s[i]);
        }
    }

    s = out;
}

// 8) Collapse whitespace: any whitespace-run -> single space, trim ends
void normalizeSpaces(std::string& s) {
    std::string out;
    out.reserve(s.size());

    bool inSpace = false;
    for (unsigned char c : s) {
        if (std::isspace(c)) {
            if (!out.empty()) inSpace = true; // mark that we saw space after some content
        } else {
            if (inSpace) {
                out.push_back(' ');
                inSpace = false;
            }
            out.push_back(static_cast<char>(c));
        }
    }
    // no trailing space because we only push space before a non-space char
    s = out;
}

// 9) Longest run of increasing (strictly increasing contiguous)
int longestIncreasingRun(const std::vector<int>& v) {
    if (v.empty()) return 0;
    int best = 1;
    int cur = 1;
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] > v[i - 1]) {
            cur++;
        } else {
            cur = 1;
        }
        best = std::max(best, cur);
    }
    return best;
}

// 10) Longest run of equal values
int longestEqualRun(const std::vector<int>& v) {
    if (v.empty()) return 0;
    int best = 1;
    int cur = 1;
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] == v[i - 1]) cur++;
        else cur = 1;
        best = std::max(best, cur);
    }
    return best;
}

// 11) Remove all duplicates but keep first occurrence order
std::vector<int> uniquePreserveOrder(const std::vector<int>& v) {
    std::unordered_set<int> seen;
    std::vector<int> out;
    out.reserve(v.size());

    for (int x : v) {
        if (seen.insert(x).second) {
            out.push_back(x);
        }
    }
    return out;
}

// 12) Second most frequent with tie-breaking
int secondMostFrequent(const std::vector<int>& v) {
    if (v.empty()) return -1;

    std::unordered_map<int, int> freq;
    freq.reserve(v.size() * 2);
    for (int x : v) freq[x]++;

    if (freq.size() < 2) return -1;

    // Track top and second by frequency; tie-breaker smallest value.
    int bestVal = 0, bestF = -1;
    int secondVal = 0, secondF = -1;

    auto better = [](int f1, int v1, int f2, int v2) {
        if (f1 != f2) return f1 > f2;
        return v1 < v2;
    };

    for (const auto& kv : freq) {
        int val = kv.first;
        int f = kv.second;

        if (bestF == -1 || better(f, val, bestF, bestVal)) {
            // demote best to second
            if (!(bestF == -1)) {
                if (secondF == -1 || better(bestF, bestVal, secondF, secondVal)) {
                    secondF = bestF;
                    secondVal = bestVal;
                }
            }
            bestF = f;
            bestVal = val;
        } else {
            if (secondF == -1 || better(f, val, secondF, secondVal)) {
                secondF = f;
                secondVal = val;
            }
        }
    }

    // Need distinct best and second, guaranteed by freq.size()>=2
    return secondVal;
}

// 13) Majority element (> n/2), else -1
int majorityElement(const std::vector<int>& v) {
    if (v.empty()) return -1;

    // Boyer-Moore
    int candidate = 0;
    int count = 0;
    for (int x : v) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            count++;
        } else {
            count--;
        }
    }

    // Verify
    int occ = 0;
    for (int x : v) if (x == candidate) occ++;
    if (occ > static_cast<int>(v.size()) / 2) return candidate;
    return -1;
}

// 14) Can be sorted nondecreasing by at most one swap
bool canBeSortedByOneSwap(const std::vector<int>& v) {
    if (v.size() <= 2) return true;

    std::vector<int> sorted = v;
    std::sort(sorted.begin(), sorted.end());

    std::vector<size_t> diff;
    diff.reserve(3);

    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] != sorted[i]) diff.push_back(i);
        if (diff.size() > 2) return false;
    }

    // Already sorted
    if (diff.empty()) return true;

    // Exactly two mismatches -> one swap can fix
    if (diff.size() == 2) return true;

    // Exactly one mismatch can't happen with a permutation unless duplicates allow,
    // but still not fixable with one swap in general. Return false.
    return false;
}

// 15) Remove a pattern repeatedly until none remain
std::string removePatternRepeat(std::string s, const std::string& pat) {
    if (pat.empty()) return s; // avoid infinite loop

    size_t pos = s.find(pat);
    while (pos != std::string::npos) {
        s.erase(pos, pat.size());
        pos = s.find(pat);
    }
    return s;
}

// 16) Balanced parentheses (ignore other chars)
bool isBalancedParens(const std::string& s) {
    int bal = 0;
    for (char c : s) {
        if (c == '(') bal++;
        else if (c == ')') {
            bal--;
            if (bal < 0) return false;
        }
    }
    return bal == 0;
}

// 17) Smallest window containing all chars (with multiplicity)
std::string smallestWindowAllChars(const std::string& s, const std::string& required) {
    if (required.empty()) return "";
    if (s.empty()) return "";

    std::vector<int> need(256, 0);
    int requiredCount = 0;
    for (unsigned char c : required) {
        if (need[c] == 0) {}
        need[c]++;
        requiredCount++;
    }

    std::vector<int> have(256, 0);
    int formed = 0; // number of required chars satisfied (counting multiplicity)

    int bestLen = std::numeric_limits<int>::max();
    int bestL = -1;

    int l = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        unsigned char cr = static_cast<unsigned char>(s[r]);
        have[cr]++;
        if (need[cr] > 0 && have[cr] <= need[cr]) {
            formed++;
        }

        while (formed == requiredCount && l <= r) {
            int len = r - l + 1;
            if (len < bestLen) {
                bestLen = len;
                bestL = l;
            }

            unsigned char cl = static_cast<unsigned char>(s[l]);
            have[cl]--;
            if (need[cl] > 0 && have[cl] < need[cl]) {
                formed--;
            }
            l++;
        }
    }

    if (bestL == -1) return "";
    return s.substr(bestL, bestLen);
}

// 18) Run-length encoding: "aaabb" -> "a3b2"
std::string runLengthEncode(const std::string& s) {
    if (s.empty()) return "";
    std::string out;
    out.reserve(s.size());

    char cur = s[0];
    int count = 1;

    for (size_t i = 1; i < s.size(); i++) {
        if (s[i] == cur) {
            count++;
        } else {
            out.push_back(cur);
            out += std::to_string(count);
            cur = s[i];
            count = 1;
        }
    }
    out.push_back(cur);
    out += std::to_string(count);
    return out;
}

// 19) Missing number in 1..n (exactly one missing), else -1 if invalid
int findMissing1ToN(const std::vector<int>& v, int n) {
    if (n <= 0) return -1;
    if ((int)v.size() != n - 1) return -1;

    std::vector<bool> seen(n + 1, false);
    for (int x : v) {
        if (x < 1 || x > n) return -1;
        if (seen[x]) return -1; // duplicate no good
        seen[x] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (!seen[i]) return i;
    }
    return -1;
}

// 20) Polynomial evaluation (Horner), coef high power first
double evalPoly(const std::vector<double>& coeffs, double x) {
    double result = 0.0;
    for (double c : coeffs) {
        result = result * x + c;
    }
    return result;
}