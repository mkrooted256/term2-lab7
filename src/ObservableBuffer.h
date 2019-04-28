#ifndef LAB7_OBSERVABLE_H
#define LAB7_OBSERVABLE_H

#include <vector>

template <typename T, typename Ts>
class ObservableBuffer {
public:
    class Listener {
    public:
        virtual void handle(const T& last_input, const Ts& buffer) = 0;
    };
private:
    std::vector<Listener *> listeners;
protected:
    Ts buffer;
    void notify_listeners(const T& last_input);
    void clear_listeners();
public:
    void attach_listener(Listener * l);
};

template<typename T, typename Ts>
void ObservableBuffer<T, Ts>::notify_listeners(const T& last_input) {
    for (Listener * l: listeners) {
        l -> handle(last_input, buffer);
    }
}

template<typename T, typename Ts>
void ObservableBuffer<T, Ts>::clear_listeners() {
    listeners.clear();
}

template<typename T, typename Ts>
void ObservableBuffer<T, Ts>::attach_listener(ObservableBuffer::Listener *l) {
    listeners.push_back(l);
}

#endif //LAB7_OBSERVABLE_H
