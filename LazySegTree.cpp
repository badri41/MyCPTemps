template<typename T>
struct SegmentTree {
    T neutral = 0; // change according to operation
    int n;
    vector<T> tree, lazy;

    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.assign(2 * n, neutral);
        lazy.assign(2 * n, neutral);
    }

    SegmentTree(vector<T> vec) {
        int sz = (int)vec.size();
        n = 1;
        while (n < sz) n <<= 1;
        tree.assign(2 * n, neutral);
        lazy.assign(2 * n, neutral);
        for (int i = 0; i < sz; i++) tree[n + i] = vec[i];
        for (int i = sz; i < n; i++) tree[n + i] = neutral;
        for (int i = n - 1; i >= 1; i--)
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    T merge(T a, T b) { 
        return a + b;
    }

    // apply lazy value to node
    void apply(int node, int node_low, int node_high, T val) {
        tree[node] += (node_high - node_low + 1) * val; // for sum segtree
        lazy[node] += val;
    }

    // push lazy value down
    void push(int node, int node_low, int node_high) {
        if (lazy[node] != neutral) {
            int mid = (node_low + node_high) >> 1;
            apply(node << 1, node_low, mid, lazy[node]);
            apply(node << 1 | 1, mid + 1, node_high, lazy[node]);
            lazy[node] = neutral;
        }
    }

    // range update [l, r] with val
    void update(int node, int node_low, int node_high, int l, int r, T val) {
        if (r < node_low || l > node_high) return; // disjoint
        if (l <= node_low && node_high <= r) { // fully inside
            apply(node, node_low, node_high, val);
            return;
        }
        push(node, node_low, node_high);
        int mid = (node_low + node_high) >> 1;
        update(node << 1, node_low, mid, l, r, val);
        update(node << 1 | 1, mid + 1, node_high, l, r, val);
        tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
    }

    // range query [l, r]
    T query(int node, int node_low, int node_high, int l, int r) {
        if (r < node_low || l > node_high) return neutral;
        if (l <= node_low && node_high <= r) return tree[node];
        push(node, node_low, node_high);
        int mid = (node_low + node_high) >> 1;
        return merge(
            query(node << 1, node_low, mid, l, r),
            query(node << 1 | 1, mid + 1, node_high, l, r)
        );
    }

    void update(int l, int r, T val) { update(1, 0, n - 1, l, r, val); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

