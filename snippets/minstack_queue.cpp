//region minqueue
struct minstack {
    stack<int> s, mins;
    int top() { return s.top(); }
    int findMin() { return mins.top(); }
    void push(int v) { s.push(v), mins.push(min(mins.empty() ? v : findMin(), v)); }
    void pop() { s.pop(), mins.pop(); }
    bool empty() { return s.empty(); }
};

struct minqueue {
    minstack inbox, outbox;
    int findMin() { if (inbox.empty() || outbox.empty()) return inbox.empty() ? outbox.findMin() : inbox.findMin(); return min(inbox.findMin(), outbox.findMin()); }
    void push(int el, int val) { inbox.push(el); }
    void pop() { if (outbox.empty()) while (!inbox.empty()) { outbox.push(inbox.top()); inbox.pop(); } outbox.pop(); }
    bool empty() { return inbox.empty() && outbox.empty(); }
};
//not tested
//endregion
