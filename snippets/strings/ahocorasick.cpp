template <int ALPHABET_SIZE, int (*mp)(char)>
class AC_FSM {
    struct Node {
        int child[ALPHABET_SIZE], failure = 0;
        vector<int> match;
        Node() {
            for (int i = 0; i < ALPHABET_SIZE; ++i) child[i] = -1;
        }
    };
    vector <Node> a;
    int words = 0;
    vector<int> word_lengths;
public:
    AC_FSM() { a.push_back(Node()); }
    void insert_word(string& word, int id) {
        int n = 0;
        words++;
        word_lengths.push_back(word.length());
        for (int w = 0; w < word.size(); ++w) {
            if (a[n].child[mp(word[w])] == -1) {
                a[n].child[mp(word[w])] = a.size();
                a.push_back(Node());
            }
            n = a[n].child[mp(word[w])];
            if (w == word.length() - 1)
                a[n].match.push_back(id);
        }
    }
    void construct_automaton() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (a[0].child[i] == -1)
                a[0].child[i] = 0;
        }

        queue<int> q;
        for (int k = 0; k < ALPHABET_SIZE; ++k) {
            if (a[0].child[k] != 0) {
                a[a[0].child[k]].failure = 0;
                q.push(a[0].child[k]);
            }
        }
        while (!q.empty()) {
            int r = q.front(); q.pop();
            for (int k = 0; k < ALPHABET_SIZE; ++k) {
                if (a[r].child[k] != -1) {
                    q.push(a[r].child[k]);
                    int v = a[r].failure;
                    while (a[v].child[k] == -1) v = a[v].failure;
                    a[a[r].child[k]].failure = a[v].child[k];
                    for (int w : a[a[v].child[k]].match)
                        a[a[r].child[k]].match.push_back(w);
                }
            }
        }
    }
    void aho_corasick(string& sentence, vector< vector<int> >& matches) {
        matches.assign(words, vector<int>());
        int state = 0;
        for (int i = 0; i < sentence.length(); ++i) {
            while (a[state].child[mp(sentence[i])] == -1)
                state = a[state].failure;
            state = a[state].child[mp(sentence[i])];
            if (!a[state].match.empty()) {
                for (int w : a[state].match)
                    matches[w].push_back(i - word_lengths[w] + 1);
            }
        }
    }
};