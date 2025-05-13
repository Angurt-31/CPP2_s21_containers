#include "gtest/gtest.h"
#include "../s21_conteiner/Stack/s21_stack.h"

TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, CopyConstructor) {
    Stack<int> stack1;
    stack1.push_back(1);
    stack1.push_back(2);
    stack1.push_back(3);

    Stack<int> stack2(stack1);
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);
    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack1.top(), 3);
}

TEST(StackTest, MoveConstructor) {
    Stack<int> stack1;
    stack1.push_back(1);
    stack1.push_back(2);
    stack1.push_back(3);

    Stack<int> stack2(std::move(stack1));
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);
    EXPECT_TRUE(stack1.empty());
}

TEST(StackTest, InitializerListConstructor) {
    Stack<int> stack({1, 2, 3, 4, 5});
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);
}

TEST(StackTest, PushAndPop) {
    Stack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 3);

    stack.pop_back();
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);
}

TEST(StackTest, Top) {
    Stack<int> stack;
    EXPECT_THROW(stack.top(), std::out_of_range);

    stack.push_back(1);
    EXPECT_EQ(stack.top(), 1);
}

TEST(StackTest, Insert) {
    Stack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    stack.insert(1, 4);
    EXPECT_EQ(stack.at(1), 4);
    EXPECT_EQ(stack.size(), 4);

    EXPECT_THROW(stack.insert(5, 5), std::out_of_range);
}

TEST(StackTest, Erase) {
    Stack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    stack.erase(1);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.at(0), 1);
    EXPECT_EQ(stack.at(1), 3);

    EXPECT_THROW(stack.erase(3), std::out_of_range);
}

TEST(StackTest, At) {
    Stack<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);

    EXPECT_EQ(stack.at(0), 1);
    EXPECT_EQ(stack.at(1), 2);
    EXPECT_EQ(stack.at(2), 3);

    EXPECT_THROW(stack.at(3), std::out_of_range);
}
