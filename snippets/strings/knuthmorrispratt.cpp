void compute_prefix_function(string& word, vi& pi) {
    pi = vector<int>(word.length());
    pi[0] = -1; pi[1] = 0;
    int i = 2, k = 0;

    while (i < pi.size()) {
        if (word[i - 1] == word[k]) {
            pi[i] = k + 1;
            i++; k++;
        }
        else if (k > 0) k = pi[k];
        else { pi[i] = 0; i++; }
    }
}

void knuth_morris_pratt(string& sentence, string& word) {
    int q = -1; vi pi;
    compute_prefix_function(word, pi);
    for (int i = 0; i < sentence.length(); ++i) {
        while (q >= 0 && word[q + 1] != sentence[i]) q = pi[q];
        if (word[q + 1] == sentence[i]) q++;
        if (q == word.length() - 1) {
            // Match at position (i - word.length() + 1)
            q = pi[q];
        }
    }
}