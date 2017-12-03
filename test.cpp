#include "deque.h"

#include <gtest/gtest.h>
#include <time.h>
#include <deque>
#include <chrono>
#include <cstdlib>

enum ActionType {
    PUSH_BACK,
    POP_BACK,
    PUSH_FRONT,
    POP_FRONT
};
const ActionType ACTIONTYPES[] = {PUSH_BACK, POP_BACK, PUSH_FRONT, POP_FRONT};

class TestDequeFixture : public ::testing::Test {
protected:

    Deque<int> dq;
    std::deque<int> std_dq;

    const int CONTAINER_SIZE = (int)1e4;

    void SetUp() {
        srand(time(NULL));
    }

    void PushBackRandomElement() {
        int val = rand();
        dq.push_back(val);
        std_dq.push_back(val);
    }

    void PushFrontRandomElement() {
        int val = rand();
        dq.push_front(val);
        std_dq.push_front(val);
    }

    void PopFrontElement() {
        dq.pop_front();
        std_dq.pop_front();
    }

    void PopBackElement() {
        dq.pop_back();
        std_dq.pop_back();
    }

    bool AreEqual() {
        for (size_t i = 0; i < std_dq.size(); ++i) {
            if (std_dq[i] != dq[i])
                return false;
        }
        return true;
    }

    void FillWithRandomElements() {
        for (int i = 0; i < CONTAINER_SIZE; ++i) {
            PushBackRandomElement();
        }
    }

    void TearDown() {
        dq.clear();
    }

};

// Container tests

TEST_F(TestDequeFixture, test_brackets) {
    FillWithRandomElements();
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        ASSERT_EQ(std_dq[i], dq[i]);
    }
}

TEST_F(TestDequeFixture, test_push_back_push_front) {
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PushBackRandomElement() :  PushFrontRandomElement();
        ASSERT_TRUE(AreEqual());
    }
}

TEST_F(TestDequeFixture, test_pop_back_pop_front) {
    FillWithRandomElements();
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PopBackElement() : PopFrontElement();
        ASSERT_TRUE(AreEqual());
    }
}

TEST_F(TestDequeFixture, test_back_front) {
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PushBackRandomElement() :  PushFrontRandomElement();
        ASSERT_EQ(std_dq.back(), dq.back());
        ASSERT_EQ(std_dq.front(), dq.front());
    }
}

TEST_F(TestDequeFixture, test_capacity) {
    ASSERT_EQ(std_dq.size(), dq.size());
    ASSERT_EQ(std_dq.empty(), dq.empty());
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PushBackRandomElement() : PushFrontRandomElement();
        ASSERT_EQ(std_dq.size(), dq.size());
        ASSERT_EQ(std_dq.empty(), dq.empty());
    }
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PopBackElement() : PopFrontElement();
        ASSERT_EQ(std_dq.size(), dq.size());
        ASSERT_EQ(std_dq.empty(), dq.empty());
    }
    ASSERT_EQ(std_dq.size(), dq.size());
    ASSERT_EQ(std_dq.empty(), dq.empty());
}

void generate_actions(std::vector<ActionType>& actions, int N) {
    actions.clear();
    int size = 0;
    for (int i = 0; i < N; ++i) {
        actions.push_back(ACTIONTYPES[rand() % 4]);
        if (actions.back() == POP_BACK || actions.back() == POP_FRONT)
            --size;
        else
            ++size;
        if (size == -1) {
            size = 0;
            actions.pop_back();
            --i;
        }
    }
}

template <class DequeType>
void run_actions(DequeType& dq, std::vector<ActionType>& actions) {
    for (size_t i = 0; i < actions.size(); ++i) {
        if (actions[i] == POP_FRONT)
            dq.pop_front();
        else if (actions[i] == POP_BACK)
            dq.pop_back();
        else if (actions[i] == PUSH_FRONT)
            dq.push_front(rand());
        else if (actions[i] == PUSH_BACK)
            dq.push_back(rand());
    }
}

TEST_F(TestDequeFixture, test_amortized_complexity) {
    const int COEFFICIENTS[] = {2, 3, 5, 10};
    const int MIN_SIZE = 10000;
    const int MAX_SIZE = 100000000;
    std::chrono::time_point<std::chrono::system_clock> time1, time2;
    double time_current, time_previous = 0;
    std::vector<ActionType> actions;
    for (int c = 0; c < 4; ++c) {
        std::cout << "Coefficient: " << COEFFICIENTS[c] << '\n';
        for (int size = MIN_SIZE; size <= MAX_SIZE; size *= COEFFICIENTS[c]) {
            dq.clear();
            generate_actions(actions, size);

            time1 = std::chrono::system_clock::now();
            run_actions(dq, actions);
            time2 = std::chrono::system_clock::now();

            time_current = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();

            if (size != MIN_SIZE && time_previous > 0) {
                std::cout << time_current / time_previous << '\n';
                EXPECT_LE(time_current / time_previous, COEFFICIENTS[c] * 2);
            }
            time_previous = time_current;
        }
    }
}

// Iterator tests

TEST_F(TestDequeFixture, test_begin_end) {
    FillWithRandomElements();
    auto std_it = std_dq.begin();
    Deque<int>::iterator it = dq.begin();
    for (; it < dq.end(); ++it) {
        ASSERT_EQ(*std_it, *it);
        ++std_it;
    }
    ASSERT_TRUE(it == dq.end());
}

TEST_F(TestDequeFixture, test_begin_end_pluseq) {
    FillWithRandomElements();
    for (int d = 1; d < 20; ++d) {
        std::deque<int>::iterator std_it = std_dq.begin();
        Deque<int>::iterator it = dq.begin();
        for (; it < dq.end(); it += d) {
            ASSERT_EQ(*std_it, *it);
           std_it += d;
        }
    }
}

TEST_F(TestDequeFixture, test_rbegin_rend) {
    FillWithRandomElements();
    std::deque<int>::reverse_iterator std_it = std_dq.rbegin();
    Deque<int>::reverse_iterator it = dq.rbegin();
    for (; it < dq.rend(); ++it) {
        ASSERT_EQ(*std_it, *it);
        ++std_it;
    }
    ASSERT_TRUE(it == dq.rend());
}

TEST_F(TestDequeFixture, test_rbegin_rend_pluseq) {
    FillWithRandomElements();
    for (int d = 1; d < 20; ++d) {
        std::deque<int>::reverse_iterator std_it = std_dq.rbegin();
        Deque<int>::reverse_iterator it = dq.rbegin();
        for (; it < dq.rend(); it += d) {
            ASSERT_EQ(*std_it, *it);
            std_it += d;
        }
    }
}

TEST_F(TestDequeFixture, test_iterator_plus) {
    FillWithRandomElements();
    std::deque<int>::iterator std_it = std_dq.begin();
    Deque<int>::iterator it = dq.begin();
    for (int d = 0; d < CONTAINER_SIZE; ++d) {
        ASSERT_EQ(*(std_it + d), * (it + d));
        ASSERT_EQ(*(d + it), *(d + std_it));
    }
}

TEST_F(TestDequeFixture, test_riterator_plus) {
    FillWithRandomElements();
    std::deque<int>::reverse_iterator std_it = std_dq.rbegin();
    Deque<int>::reverse_iterator it = dq.rbegin();
    for (int d = 0; d < CONTAINER_SIZE; ++d) {
        ASSERT_EQ(*(std_it + d), *(it + d));
        ASSERT_EQ(*(d + std_it), *(d + it));
    }
}

TEST_F(TestDequeFixture, test_iterator_brackets) {
    FillWithRandomElements();
    std::deque<int>::iterator std_it = std_dq.begin();
    Deque<int>::iterator it = dq.begin();
    for (int d = 0; d < CONTAINER_SIZE; ++d) {
        ASSERT_EQ(std_it[d], it[d]);
    }
}

TEST_F(TestDequeFixture, test_riterator_brackets) {
    FillWithRandomElements();
    std::deque<int>::reverse_iterator std_it = std_dq.rbegin();
    Deque<int>::reverse_iterator it = dq.rbegin();
    for (int d = 0; d < CONTAINER_SIZE; ++d) {
        ASSERT_EQ(std_it[d], it[d]);
    }
}