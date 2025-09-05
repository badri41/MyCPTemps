const int K = 26;

struct Node { // All ops in O(|s|)
    int next[K];
    bool is_leaf; 

    Node() {
        fill(begin(next), end(next), -1);
        is_leaf = false;
    }
};

struct Trie {
    vector<Node> t;

    Trie() {
        t.emplace_back();
    }

    void add_string(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back();
            }
            v = t[v].next[c];
        }
        t[v].is_leaf = true; 
    }

    bool contains(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) return false;
            v = t[v].next[c];
        }
        return t[v].is_leaf;
    }

    bool starts_with(const string &prefix) {
        int v = 0;
        for (char ch : prefix) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) return false;
            v = t[v].next[c];
        }
        return true;
    }
};
Trie T = Trie();

