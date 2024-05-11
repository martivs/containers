#include "s21_map.h"
#include "s21_set.h"
#include "s21_list.h"
#include "s21_stack.h"
#include "s21_vector.h"
#include "s21_queue.h"
#include <stack>
#include <queue>
#include <vector>
#include <gtest/gtest.h>

// _________________>>VECTOR>>____________________________________

TEST(VectorTest, DefaultConstructor)
{
  s21::s21_vector<int> v;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor_1)
{
  size_t n = 5;
  s21::s21_vector<int> v(n);

  EXPECT_EQ(v.size(), n);
  EXPECT_GE(v.capacity(), n);
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, InitializerListConstructor)
{
  std::initializer_list<int> items = {1, 2, 3};
  s21::s21_vector<int> v(items);

  EXPECT_EQ(v.size(), 3);
  EXPECT_GE(v.capacity(), 3);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, CopyConstructor)
{
  s21::s21_vector<int> v1 = {1, 2, 3};
  s21::s21_vector<int> v2(v1);

  EXPECT_EQ(v2.size(), v1.size());
  EXPECT_EQ(v2.capacity(), v1.capacity());
  EXPECT_EQ(v2[0], v1[0]);
  EXPECT_EQ(v2[1], v1[1]);
  EXPECT_EQ(v2[2], v1[2]);
}

TEST(VectorTest, MoveConstructor)
{
  s21::s21_vector<int> v1 = {1, 2, 3};
  s21::s21_vector<int> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
  EXPECT_EQ(v1.size(), 3);
}

TEST(VectorTest, MoveAssignment)
{
  s21::s21_vector<int> v1 = {1, 2, 3};
  s21::s21_vector<int> v2;
  v2 = std::move(v1);

  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
  EXPECT_EQ(v1.size(), 3);
}

TEST(VectorTest, Destructor)
{
  {
    s21::s21_vector<int> v = {1, 2, 3};
  }
}

TEST(VectorTest, At)
{
  s21::s21_vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorTest, OperatorBracket)
{
  s21::s21_vector<int> v = {1, 2, 3};

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, Front)
{
  s21::s21_vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, Back)
{
  s21::s21_vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, Data)
{
  s21::s21_vector<int> v = {1, 2, 3};

  int *data = v.data();

  EXPECT_EQ(*data, 1);
  EXPECT_EQ(*(data + 1), 2);
  EXPECT_EQ(*(data + 2), 3);
}

TEST(VectorTest, Begin)
{
  s21::s21_vector<int> v = {1, 2, 3};

  EXPECT_EQ(*v.begin(), 1);
}

TEST(VectorTest, Empty)
{
  s21::s21_vector<int> v;

  EXPECT_TRUE(v.empty());

  v.push_back(1);

  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size)
{
  s21::s21_vector<int> v;

  EXPECT_EQ(v.size(), 0);

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.size(), 3);
}

TEST(VectorTest, MaxSize)
{
  s21::s21_vector<int> v;
  std::vector<int> a;

  EXPECT_EQ(v.max_size(),
            a.max_size());
}

TEST(VectorTest, Reserve)
{
  s21::s21_vector<int> v;

  v.reserve(10);

  EXPECT_GE(v.capacity(), 10);
}

TEST(VectorTest, Capacity)
{
  s21::s21_vector<int> v;

  EXPECT_EQ(v.capacity(), 0);

  v.reserve(10);

  EXPECT_GE(v.capacity(), 10);
}

TEST(VectorTest, ShrinkToFit)
{
  s21::s21_vector<int> v = {1, 2, 3};

  v.reserve(10);
  v.shrink_to_fit();

  EXPECT_EQ(v.capacity(), 3);
}

TEST(VectorTest, Clear)
{
  s21::s21_vector<int> v = {1, 2, 3};

  v.clear();

  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Insert)
{
  s21::s21_vector<int> v = {1, 2, 3};

  s21::s21_vector<int>::iterator it = v.insert(++v.begin(), 5);

  EXPECT_EQ(*it, 5);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 5);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
}

TEST(VectorTest, Erase)
{
  s21::s21_vector<int> v = {1, 2, 3};

  auto it = ++v.begin();
  v.erase(it);

  EXPECT_EQ(*(++v.begin()), 3);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, PushBack)
{
  s21::s21_vector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBack)
{
  s21::s21_vector<int> v = {1, 2, 3};

  v.pop_back();

  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, Swap)
{
  s21::s21_vector<int> v1 = {1, 2, 3};
  s21::s21_vector<int> v2 = {4, 5};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
}

//__________________<<VECTOR<<____________________

//__________________>>SET>>_______________________

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(SetTest, DefaultConstructor)
{
  s21::Set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetTest, InitializerListConstructor)
{
  s21::Set<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(3, s.size());
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, CopyConstructor)
{
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, MoveConstructor)
{
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2(std::move(s1));
  EXPECT_EQ(3, s2.size());
  EXPECT_TRUE(s1.empty());
}

TEST(SetTest, Destructor)
{
  s21::Set<int> *s = new s21::Set<int>({1, 2, 3});
  delete s;
  EXPECT_TRUE(true);
}

TEST(SetTest, MoveAssignmentOperator)
{
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2 = {4, 5, 6};
  s2 = std::move(s1);
  EXPECT_EQ(3, s2.size());
  EXPECT_TRUE(s1.empty());
}

TEST(SetTest, Begin)
{
  s21::Set<int> s = {1, 2, 3};
  s21::Set<int>::iterator it = s.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
}

TEST(SetTest, End)
{
  s21::Set<int> s = {1, 2, 3};
  s.end();
}

TEST(SetTest, Empty)
{
  s21::Set<int> s;
  EXPECT_TRUE(s.empty());
  s.insert(1);
  EXPECT_FALSE(s.empty());
}

TEST(SetTest, Size)
{
  s21::Set<int> s = {1, 2, 3};
  EXPECT_EQ(3, s.size());
}

TEST(SetTest, MaxSize)
{
  s21::Set<int> s;
  EXPECT_GE(s.max_size(), 0);
}

TEST(SetTest, Clear)
{
  s21::Set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetTest, Insert)
{
  s21::Set<int> s;
  std::pair<s21::Set<int>::iterator, bool> result = s.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_TRUE(s.contains(1));
  EXPECT_EQ(1, *(result.first));
  result = s.insert(1);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(1, *(result.first));
}

TEST(SetTest, Insert1)
{
  s21::Set<int> s;
  s.insert(3);
  s.insert(4);
  s.insert(5);
  s.insert(1);
  s.insert(2);
}

TEST(SetTest, Insert2)
{
  s21::Set<int> s;

  s.insert(4);
  s.insert(5);
  s.insert(6);
  s.insert(8);
  s.insert(7);
}

TEST(SetTest, Erase)
{
  s21::Set<int> s = {1, 2, 3};
  s21::Set<int>::iterator it = s.find(2);
  s.erase(it);
  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Erase1)
{
  s21::Set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  s21::Set<int>::iterator it1 = s.find(1);
  s.erase(it1);
  s21::Set<int>::iterator it2 = s.find(2);
  s.erase(it2);
  s21::Set<int>::iterator it3 = s.find(3);
  s.erase(it3);
  s21::Set<int>::iterator it4 = s.find(4);
  s.erase(it4);
  s21::Set<int>::iterator it5 = s.find(5);
  s.erase(it5);
  s21::Set<int>::iterator it6 = s.find(6);
  s.erase(it6);
  s21::Set<int>::iterator it7 = s.find(7);
  s.erase(it7);
  s21::Set<int>::iterator it8 = s.find(8);
  s.erase(it8);
  s21::Set<int>::iterator it9 = s.find(9);
  s.erase(it9);
  s21::Set<int>::iterator it10 = s.find(10);
  s.erase(it10);
  s21::Set<int>::iterator it11 = s.find(11);
  s.erase(it11);
  s21::Set<int>::iterator it12 = s.find(12);
  s.erase(it12);
  s21::Set<int>::iterator it13 = s.find(13);
  s.erase(it13);
  s21::Set<int>::iterator it14 = s.find(14);
  s.erase(it14);
  s21::Set<int>::iterator it15 = s.find(15);
  s.erase(it15);
  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Erase2)
{
  s21::Set<int> s = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  s21::Set<int>::iterator it15 = s.find(15);
  s.erase(it15);
  s21::Set<int>::iterator it14 = s.find(14);
  s.erase(it14);
  s21::Set<int>::iterator it13 = s.find(13);
  s.erase(it13);
  s21::Set<int>::iterator it12 = s.find(12);
  s.erase(it12);
  s21::Set<int>::iterator it11 = s.find(11);
  s.erase(it11);
  s21::Set<int>::iterator it10 = s.find(10);
  s.erase(it10);
  s21::Set<int>::iterator it9 = s.find(9);
  s.erase(it9);
  s21::Set<int>::iterator it8 = s.find(8);
  s.erase(it8);
  s21::Set<int>::iterator it7 = s.find(7);
  s.erase(it7);
  s21::Set<int>::iterator it6 = s.find(6);
  s.erase(it6);
  s21::Set<int>::iterator it5 = s.find(5);
  s.erase(it5);
  s21::Set<int>::iterator it4 = s.find(4);
  s.erase(it4);
  s21::Set<int>::iterator it3 = s.find(3);
  s.erase(it3);
  s21::Set<int>::iterator it2 = s.find(2);
  s.erase(it2);
  s21::Set<int>::iterator it1 = s.find(1);
  s.erase(it1);

  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Erase3)
{
  s21::Set<int> s = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 16, 17, 18};
  s21::Set<int>::iterator it = s.find(10);
  s.erase(it);
  s21::Set<int>::iterator it1 = s.find(15);
  s.erase(it1);
  s21::Set<int>::iterator it2 = s.find(12);
  s.erase(it2);
  s21::Set<int>::iterator it3 = s.find(14);
  s.erase(it3);
  s21::Set<int>::iterator it4 = s.find(17);
  s.erase(it4);
}

TEST(SetTest, Erase4)
{
  s21::Set<int> s = {4, 5, 6, 7, 13, 8, 9, 12, 32, 14, 3, 54, 2, 1, 23, 28};
  s21::Set<int>::iterator it = s.find(54);
  s.erase(it);
  s21::Set<int>::iterator it1 = s.find(3);
  s.erase(it1);
  s.insert(15);
  s.insert(800);
  s.insert(700);
  s21::Set<int>::iterator it2 = s.find(5);
  s.erase(it2);
  s21::Set<int>::iterator it3 = s.find(14);
  s.erase(it3);
  s.insert(222);
  s.insert(223);
  s.insert(224);
  s21::Set<int>::iterator it4 = s.find(9);
  s.erase(it4);
}
TEST(SetTest, Erase5)
{
  s21::Set<int> s = {20, 10, 200, 5, 4, 13, 8, 100, 153, 134, 173, 187, 201, 17, 15, 16, 18, 12, 11, 14};
  s21::Set<int>::iterator it = s.find(11);
  s.erase(it);
}

TEST(SetTest, Erase6)
{
  s21::Set<int> s = {10, 20, 3, 30, 40, 50, 25};
  s21::Set<int>::iterator it = s.find(3);
  s.erase(it);
}

TEST(SetTest, Erase7)
{
  s21::Set<int> s = {50, 40, 3, 30, 20, 10, 25};
  s21::Set<int>::iterator it = s.find(50);
  s.erase(it);
}

TEST(SetTest, Erase8)
{
  s21::Set<int> s = {10, 20, 3, 30, 40, 50, 18};
  s21::Set<int>::iterator it = s.find(3);
  s.erase(it);
}

TEST(SetTest, Erase9)
{
  s21::Set<int> s = {50, 40, 3, 30, 20, 10, 35};
  s21::Set<int>::iterator it = s.find(50);
  s.erase(it);
}

TEST(SetTest, Erase10)
{
  s21::Set<int> s = {10, 20, 3, 17};
  s21::Set<int>::iterator it = s.find(3);
  s.erase(it);
}

TEST(SetTest, Erase11)
{
  s21::Set<int> s = {20, 10, 7, 8};
  s21::Set<int>::iterator it = s.find(20);
  s.erase(it);
}

TEST(SetTest, Swap)
{
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge)
{
  s21::Set<int> s1 = {1, 2, 3};
  s21::Set<int> s2 = {4, 5, 6};
  s1.merge(s2);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, Find)
{
  s21::Set<int> s = {1, 2, 3};
  s21::Set<int>::iterator it = s.find(2);
  EXPECT_EQ(2, *it);
}

TEST(SetTest, Contains)
{
  s21::Set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(1));
  EXPECT_FALSE(s.contains(4));
}

//_________________<<SET<<__________________

//_________________>>MAP>>__________________

TEST(MapTest, DefaultConstructor)
{
  s21::Map<int, int> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InitializerListConstructor)
{
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m[1], 10);
  EXPECT_EQ(m[2], 20);
  EXPECT_EQ(m[3], 30);
  EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapTest, CopyConstructor)
{
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1[1], m2[1]);
  EXPECT_EQ(m1[2], m2[2]);
  EXPECT_EQ(m1[3], m2[3]);
}

TEST(MapTest, MoveConstructor)
{
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> m2(std::move(m1));
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
  EXPECT_EQ(m2[3], 30);
  EXPECT_TRUE(m1.empty());
  EXPECT_EQ(m1.size(), 0);
}

TEST(MapTest, Destructor)
{
  s21::Map<int, int> *m = new s21::Map<int, int>{{1, 10}, {2, 20}, {3, 30}};
  delete m;
}

TEST(MapTest, AssignmentOperatorMove)
{
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
  EXPECT_EQ(m2[3], 30);
  EXPECT_TRUE(m1.empty());
  EXPECT_EQ(m1.size(), 0);
}

TEST(MapTest, At)
{
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m.at(1), 10);
  EXPECT_EQ(m.at(2), 20);
  EXPECT_EQ(m.at(3), 30);
  EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapTest, IndexOperator)
{
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m[1], 10);
  EXPECT_EQ(m[2], 20);
  EXPECT_EQ(m[3], 30);
  m[1] = 100;
  m[4] = 40;
  EXPECT_EQ(m[1], 100);
  EXPECT_EQ(m[4], 40);
}

TEST(MapTest, Iterator)
{
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int>::iterator it = m.begin();
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, 10);
  ++it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, 20);
  ++it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, 30);
  ++it;
  EXPECT_EQ(it, m.end());
}

TEST(MapTest, Empty)
{
  s21::Map<int, int> m;
  EXPECT_TRUE(m.empty());
  m.insert({1, 10});
  EXPECT_FALSE(m.empty());
  m.erase(m.begin());
  EXPECT_TRUE(m.empty());
}

TEST(MapTest, Size)
{
  s21::Map<int, int> m;
  EXPECT_EQ(m.size(), 0);
  m.insert({1, 10});
  m.insert({2, 20});
  m.insert({3, 30});
  EXPECT_EQ(m.size(), 3);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 2);
  m.clear();
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, MaxSize)
{
  s21::Map<int, int> m;
  EXPECT_GT(m.max_size(), 0);
}

TEST(MapTest, Clear)
{
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 3);
  m.clear();
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InsertValue)
{
  s21::Map<int, int> m;
  auto res = m.insert({1, 10});
  EXPECT_TRUE(res.second);
  EXPECT_EQ((*res.first).first, 1);
  EXPECT_EQ((*res.first).second, 10);
  res = m.insert({1, 20});
  EXPECT_FALSE(res.second);
  EXPECT_EQ((*res.first).first, 1);
  EXPECT_EQ((*res.first).second, 10);
}

TEST(MapTest, InsertKeyValue)
{
  s21::Map<int, int> m;
  auto res = m.insert(1, 10);
  EXPECT_TRUE(res.second);
  EXPECT_EQ((*res.first).first, 1);
  EXPECT_EQ((*res.first).second, 10);
  res = m.insert({1, 20});
  EXPECT_FALSE(res.second);
  EXPECT_EQ((*res.first).first, 1);
  EXPECT_EQ((*res.first).second, 10);
}

TEST(MapTest, InsertOrAssign)
{
  s21::Map<int, int> m;
  auto res = m.insert_or_assign(1, 10);
  EXPECT_TRUE(res.second);
  EXPECT_EQ((*res.first).first, 1);
  EXPECT_EQ((*res.first).second, 10);
  res = m.insert_or_assign(1, 20);
  EXPECT_FALSE(res.second);
  EXPECT_EQ((*res.first).first, 1);
  EXPECT_EQ((*res.first).second, 20);
}

TEST(MapTest, Erase)
{
  s21::Map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  m.insert({3, 30});
  EXPECT_EQ(m.size(), 3);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 2);
}

TEST(MapTest, Swap)
{
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::Map<int, int> m2 = {{3, 30}, {4, 40}};
  m1.swap(m2);
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m1[3], 30);
  EXPECT_EQ(m1[4], 40);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
}

TEST(MapTest, Merge)
{
  s21::Map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::Map<int, int> m2 = {{2, 30}, {3, 40}};
  m1.merge(m2);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1[1], 10);
  EXPECT_EQ(m1[2], 20);
  EXPECT_EQ(m1[3], 40);
  EXPECT_EQ(m2.size(), 0);
}

TEST(MapTest, Contains)
{
  s21::Map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
  EXPECT_FALSE(m.contains(4));
}

//__________________>>List>>___________________
TEST(ListTest, DefaultConstructor)
{
  s21::list<int> list;
  EXPECT_EQ(list.size(), 0U);
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, MoveAssignmentOperator)
{
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  s21::list<int> list2;
  list2 = std::move(list1);
  EXPECT_TRUE(list1.empty());

  ASSERT_EQ(list2.size(), 3U);
  int expected_values2[] = {1, 2, 3};
  auto i = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++i)
  {
    EXPECT_EQ(*it, expected_values2[i]);
  }
}

TEST(ListTest, CopyAssignmentOperator)
{
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  s21::list<int> list2;
  list2 = list1;

  ASSERT_EQ(list1.size(), 3U);
  int expected_values1[] = {1, 2, 3};
  int i = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++i)
  {
    EXPECT_EQ(*it, expected_values1[i]);
  }

  ASSERT_EQ(list2.size(), 3U);
  int expected_values2[] = {1, 2, 3};
  i = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++i)
  {
    EXPECT_EQ(*it, expected_values2[i]);
  }
}

TEST(ListTest, PushFrontAndBack)
{
  s21::list<int> list;

  list.push_front(1);
  EXPECT_EQ(list.size(), 1U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 1);

  list.push_back(2);
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, PopFrontAndBack)
{
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_front();
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 2);

  list.pop_back();
  EXPECT_EQ(list.size(), 1U);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, ClearList)
{
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.clear();
  EXPECT_EQ(list.size(), 0U);
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, ReverseList)
{
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.reverse();
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, UniqueList)
{
  s21::list<int> list;
  list.push_back(1);
  list.push_back(1);
  list.push_back(2);
  list.push_back(2);
  list.push_back(3);
  list.push_back(3);
  list.unique();
  EXPECT_EQ(list.size(), 3U);
}

TEST(ListTest, SortList)
{
  s21::list<int> list;
  list.push_back(3);
  list.push_back(1);
  list.push_back(2);
  list.sort();
  s21::list<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, InsertAtBeginning)
{
  s21::list<int> list = {1, 2, 3};
  s21::list<int>::iterator it = list.insert(list.begin(), 42);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.front(), 42);
}

TEST(ListTest, EraseFirstElement)
{
  s21::list<int> list = {1, 2, 3};
  list.erase(list.begin());
  s21::list<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Sort)
{
  s21::list<int> list = {8, 3, 2, 10, 7, 4, 6, 1, 9, 5};

  list.sort();

  s21::list<int> expected_list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto it1 = list.begin();
  auto it2 = expected_list.begin();
  while (it1 != list.end() && it2 != expected_list.end())
  {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(it1, list.end());
  EXPECT_EQ(it2, expected_list.end());
}

TEST(ListMergeTest, MergeTwoEmptyLists)
{
  s21::list<int> list1;
  s21::list<int> list2;

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 0U);
  EXPECT_EQ(list2.size(), 0U);
}

TEST(ListMergeTest, MergeNonEmptyAndEmptyLists)
{
  s21::list<int> list1;
  s21::list<int> list2;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i)
  {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListMergeTest, MergeEmptyAndNonEmptyLists)
{
  s21::list<int> list1;
  s21::list<int> list2;

  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i)
  {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListMergeTest, MergeTwoNonEmptyLists)
{
  s21::list<int> list1;
  s21::list<int> list2;

  list1.push_back(1);
  list1.push_back(3);
  list1.push_back(5);

  list2.push_back(2);
  list2.push_back(4);
  list2.push_back(6);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i)
  {
    EXPECT_EQ(*it, expected[i]);
  }
}
// //_______________<<List<<____________________

//_________________>>Stack>>_________________

TEST(StackTest, DefaultConstructor)
{
  s21::s21_stack<int> my_stack;
  std::stack<int> stl_stack;
  EXPECT_EQ(my_stack.size(), stl_stack.size());
  EXPECT_EQ(my_stack.empty(), stl_stack.empty());
}

TEST(StackTest, InitializerListConstructor)
{
  s21::s21_stack<unsigned int> s1{1, 2, 3};
  ASSERT_EQ(s1.size(), 3u);
  ASSERT_EQ(s1.top(), 3u);

  s21::s21_stack<std::string> s2{"hello", "world"};
  ASSERT_EQ(s2.size(), 2u);
  ASSERT_EQ(s2.top(), "world");
}

TEST(StackTest, InitializerListConstructorPair)
{
  s21::s21_stack<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::stack<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty())
  {
    EXPECT_EQ(q1.top(), q2.top());
    q1.pop();
    q2.pop();
  }
}

TEST(StackTest, EmptyInitializerListConstructor)
{
  s21::s21_stack<int> s{};
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0u);
}

TEST(StackTest, Empty)
{
  s21::s21_stack<std::pair<std::string, int>> s;
  std::stack<std::pair<std::string, int>> s_stl;

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());

  s.push({"one", 1});
  s_stl.push({"one", 1});

  EXPECT_FALSE(s.empty());
  EXPECT_FALSE(s_stl.empty());

  s.pop();
  s_stl.pop();

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, Size)
{
  s21::s21_stack<std::pair<std::string, unsigned int>> s;
  std::stack<std::pair<std::string, unsigned int>> s_stl;

  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s_stl.size(), 0u);

  s.push({"one", 1u});
  s_stl.push({"one", 1u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.push({"two", 2u});
  s_stl.push({"two", 2u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.push({"three", 3u});
  s_stl.push({"three", 3u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());
}

TEST(StackTest, PushPopTop)
{
  std::stack<int> std_stack;
  s21::s21_stack<int> s21_stack;
  for (int i = 1; i <= 10; ++i)
  {
    std_stack.push(i);
    s21_stack.push(i);
  }
  while (!std_stack.empty())
  {
    EXPECT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST(StackTest, PushAndPopString)
{
  s21::s21_stack<std::string> s;
  std::stack<std::string> s_stl;

  s.push("one");
  s_stl.push("one");
  EXPECT_EQ(s.top(), s_stl.top());

  s.push("two");
  s_stl.push("two");
  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, TopPair)
{
  s21::s21_stack<std::pair<std::string, int>> s;
  std::stack<std::pair<std::string, int>> s_stl;

  s.push({"one", 1});
  s_stl.push({"one", 1});

  EXPECT_EQ(s.top(), s_stl.top());

  s.push({"two", 2});
  s_stl.push({"two", 2});

  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();

  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, CopyConstructor)
{
  std::stack<int> std_stack;
  s21::s21_stack<int> s21_stack;
  for (int i = 1; i <= 10; ++i)
  {
    std_stack.push(i);
    s21_stack.push(i);
  }
  std::stack<int> std_copy(std_stack);
  s21::s21_stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty())
  {
    EXPECT_EQ(std_copy.top(), s21_copy.top());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, CopyConstructorString)
{
  s21::s21_stack<std::string> s1;
  std::stack<std::string> s1_stl;

  s1.push("one");
  s1_stl.push("one");
  s1.push("two");
  s1_stl.push("two");

  s21::s21_stack<std::string> s2(s1);
  std::stack<std::string> s2_stl(s1_stl);

  while (!s1.empty() && !s2.empty())
  {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(StackTest, CopyConstructorPair)
{
  s21::s21_stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});

  s21::s21_stack<std::pair<std::string, int>> s2(s1);
  std::stack<std::pair<std::string, int>> s2_stl(s1_stl);

  while (!s1.empty() && !s2.empty())
  {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(StackTest, CopyConstructorEmpty)
{
  std::stack<int> std_stack;
  s21::s21_stack<int> s21_stack;
  std::stack<int> std_copy(std_stack);
  s21::s21_stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, MoveConstructorPair)
{
  s21::s21_stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});

  s21::s21_stack<std::pair<std::string, int>> s2(std::move(s1));
  std::stack<std::pair<std::string, int>> s2_stl(std::move(s1_stl));

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
}

TEST(StackTest, MoveConstructorString)
{
  s21::s21_stack<std::string> s1;
  std::stack<std::string> s1_stl;

  s1.push("one");
  s1_stl.push("one");
  s1.push("two");
  s1_stl.push("two");

  s21::s21_stack<std::string> s2(std::move(s1));
  std::stack<std::string> s2_stl(std::move(s1_stl));

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);
  EXPECT_TRUE(s2.top() == "two");

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
  EXPECT_TRUE(s2_stl.top() == "two");
}

TEST(StackTest, CopyAssignmentOperator)
{
  s21::s21_stack<int> my_stack;
  std::stack<int> stl_stack;

  for (int i = 0; i < 10; ++i)
  {
    my_stack.push(i);
    stl_stack.push(i);
  }

  s21::s21_stack<int> my_copy_stack;
  std::stack<int> stl_copy_stack;

  my_copy_stack = my_stack;
  stl_copy_stack = stl_stack;

  EXPECT_EQ(my_copy_stack.size(), stl_copy_stack.size());

  while (!my_copy_stack.empty())
  {
    EXPECT_EQ(my_copy_stack.top(), stl_copy_stack.top());
    my_copy_stack.pop();
    stl_copy_stack.pop();
  }

  EXPECT_TRUE(my_copy_stack.empty());
  EXPECT_TRUE(stl_copy_stack.empty());
}

TEST(StackTest, MoveAssignmentOperator)
{
  s21::s21_stack<int> my_stack;
  std::stack<int> stl_stack;

  for (int i = 0; i < 10; ++i)
  {
    my_stack.push(i);
    stl_stack.push(i);
  }

  s21::s21_stack<int> my_move_stack;
  std::stack<int> stl_move_stack;

  my_move_stack = std::move(my_stack);
  stl_move_stack = std::move(stl_stack);

  EXPECT_EQ(my_move_stack.size(), stl_move_stack.size());
  EXPECT_EQ(my_stack.size(), stl_stack.size());

  while (!my_move_stack.empty())
  {
    EXPECT_EQ(my_move_stack.top(), stl_move_stack.top());
    my_move_stack.pop();
    stl_move_stack.pop();
  }

  EXPECT_TRUE(my_stack.empty());
  EXPECT_TRUE(stl_stack.empty());
}

TEST(StackTest, AssignmentOperatorEmpty)
{
  std::stack<int> std_stack;
  s21::s21_stack<int> s21_stack;
  std::stack<int> std_copy;
  s21::s21_stack<int> s21_copy;
  std_copy = std_stack;
  s21_copy = s21_stack;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

// //_________________>>Queue>>_________________

TEST(QueueTest, DefaultConstructor)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  EXPECT_EQ(std_queue.empty(), s21_queue.empty());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, InitializerListConstructor)
{
  s21::s21_queue<unsigned int> q1{1, 2, 3};
  ASSERT_EQ(q1.size(), 3u);
  ASSERT_EQ(q1.front(), 1u);
  ASSERT_EQ(q1.back(), 3u);

  s21::s21_queue<std::string> q2{"hello", "world"};
  ASSERT_EQ(q2.size(), 2u);
  ASSERT_EQ(q2.front(), "hello");
  ASSERT_EQ(q2.back(), "world");
}

TEST(QueueTest, InitializerListConstructorPair)
{
  s21::s21_queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty())
  {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, EmptyInitializerListConstructor)
{
  s21::s21_queue<unsigned int> q{};
  ASSERT_TRUE(q.empty());
}

TEST(QueueTest, CopyInitializerListConstructor)
{
  s21::s21_queue<unsigned int> q1{1, 2, 3};
  s21::s21_queue<unsigned int> q2{q1};
  ASSERT_EQ(q1.size(), q2.size());
  ASSERT_EQ(q1.front(), q2.front());
  ASSERT_EQ(q1.back(), q2.back());
}

TEST(QueueTest, MoveInitializerListConstructor)
{
  s21::s21_queue<unsigned int> q1{1, 2, 3};
  s21::s21_queue<unsigned int> q2{std::move(q1)};
  ASSERT_EQ(q1.size(), 0u);
  ASSERT_EQ(q2.size(), 3u);
  ASSERT_EQ(q2.front(), 1u);
  ASSERT_EQ(q2.back(), 3u);
}

TEST(QueueTest, PushPopFrontBack)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i)
  {
    std_queue.push(i);
    s21_queue.push(i);
  }
  while (!std_queue.empty())
  {
    EXPECT_EQ(std_queue.front(), s21_queue.front());
    EXPECT_EQ(std_queue.back(), s21_queue.back());
    std_queue.pop();
    s21_queue.pop();
  }
}

TEST(QueueTest, FrontBackPair)
{
  s21::s21_queue<std::pair<std::string, int>> q{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q.front().first, q2.front().first);
  EXPECT_EQ(q.front().second, q2.front().second);
  EXPECT_EQ(q.back().first, q2.back().first);
  EXPECT_EQ(q.back().second, q2.back().second);
}

TEST(QueueTest, PushPopPair)
{
  s21::s21_queue<std::pair<std::string, int>> q;
  std::queue<std::pair<std::string, int>> q2;
  q.push({"one", 1});
  q2.push({"one", 1});
  q.push({"two", 2});
  q2.push({"two", 2});
  q.push({"three", 3});
  q2.push({"three", 3});
  EXPECT_EQ(q.empty(), q2.empty());
  EXPECT_EQ(q.size(), q2.size());
  while (!q.empty())
  {
    EXPECT_EQ(q.front().first, q2.front().first);
    EXPECT_EQ(q.front().second, q2.front().second);
    q.pop();
    q2.pop();
  }
}

TEST(QueueTest, CopyConstructor)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i)
  {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::s21_queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty())
  {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyConstructorPair)
{
  s21::s21_queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::s21_queue<std::pair<std::string, int>> q2(q1);
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty())
  {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, CopyConstructorEmpty)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  std::queue<int> std_copy(std_queue);
  s21::s21_queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyConstructorSize)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i)
  {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::s21_queue<int> s21_copy(s21_queue);
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyAssignmentOperator)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i)
  {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::s21_queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  while (!std_copy.empty())
  {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
}

TEST(QueueTest, CopyAssignmentPair)
{
  s21::s21_queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::s21_queue<std::pair<std::string, int>> q2;
  std::queue<std::pair<std::string, int>> q3;
  q2 = q1;
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty())
  {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, AssignmentOperator)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i)
  {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::s21_queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty())
  {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, AssignmentOperatorEmpty)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  std::queue<int> std_copy;
  s21::s21_queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, AssignmentOperatorSize)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i)
  {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::s21_queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, MoveAssignmentOperator)
{
  std::queue<int> std_queue;
  s21::s21_queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i)
  {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_move;
  s21::s21_queue<int> s21_move;
  std_move = std::move(std_queue);
  s21_move = std::move(s21_queue);
  while (!std_move.empty())
  {
    EXPECT_EQ(std_move.front(), s21_move.front());
    std_move.pop();
    s21_move.pop();
  }
}

TEST(QueueTest, MoveAssignmentPair)
{
  s21::s21_queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::s21_queue<std::pair<std::string, int>> q2;
  std::queue<std::pair<std::string, int>> q3;
  q2 = std::move(q1);
  q3.push({"one", 1});
  q3.push({"two", 2});
  q3.push({"three", 3});
  EXPECT_EQ(q1.empty(), true);
  EXPECT_EQ(q2.size(), q3.size());
  while (!q2.empty())
  {
    EXPECT_EQ(q2.front().first, q3.front().first);
    EXPECT_EQ(q2.front().second, q3.front().second);
    q2.pop();
    q3.pop();
  }
}
