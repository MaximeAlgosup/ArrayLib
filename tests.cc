#include "gtest/gtest.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <array>

#include "dArray.h"

#define BIG_SIZE 1000

/*
 * array_create
 */

TEST(ArrayCreateTest, Empty) {
  struct array a;
  array_create(&a);

  EXPECT_TRUE(array_empty(&a));
  EXPECT_TRUE(array_size(&a) == 0);

  array_destroy(&a);
}

/*
 * array_create_from
 */

TEST(ArrayCreateFromTest, OneElement) {
  static const int origin[] = { 1 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_empty(&a));
  EXPECT_EQ(array_size(&a), std::size(origin));
  EXPECT_TRUE(array_equals(&a, origin, std::size(origin)));

  array_destroy(&a);
}

TEST(ArrayCreateFromTest, ManyElements) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_empty(&a));
  EXPECT_EQ(array_size(&a), std::size(origin));
  EXPECT_TRUE(array_equals(&a, origin, std::size(origin)));

  array_destroy(&a);
}

/*
 * array_equals
 */

TEST(ArrayEqualsTest, DifferentElement) {
  static const int origin[]    = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  static const int reference[] = { 1, 2, 3, 4, 5, 6, 7, 8, 10 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_equals(&a, reference, std::size(reference)));

  array_destroy(&a);
}

TEST(ArrayEqualsTest, SizeShorter) {
  static const int origin[]    = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  static const int reference[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_equals(&a, reference, std::size(reference)));

  array_destroy(&a);
}

TEST(ArrayEqualsTest, SizeLarger) {
  static const int origin[]    = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  static const int reference[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_equals(&a, reference, std::size(reference)));

  array_destroy(&a);
}

/*
 * array_push_back
 */

TEST(ArrayPushBackTest, OneElement) {
  struct array a;
  array_create(&a);
  array_push_back(&a, 1);

  EXPECT_FALSE(array_empty(&a));
  EXPECT_TRUE(array_size(&a) == 1);
  EXPECT_EQ(array_get(&a, 0), 1);

  array_destroy(&a);
}

TEST(ArrayPushBackTest, ManyElements) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct array a;
  array_create(&a);

  for (size_t i = 0; i < std::size(origin); ++i) {
    array_push_back(&a, origin[i]);
  }

  EXPECT_FALSE(array_empty(&a));
  EXPECT_EQ(array_size(&a), std::size(origin));


  for (size_t i = 0; i < std::size(origin); ++i) {
    EXPECT_EQ(array_get(&a, i), origin[i]);
  }

  EXPECT_TRUE(array_equals(&a, origin, std::size(origin)));

  array_destroy(&a);
}

TEST(ArrayPushBackTest, Stressed) {
  struct array a;

  array_create(&a);

  for (int i = 0; i < BIG_SIZE; ++i) {
    array_push_back(&a, i + 1);
    EXPECT_EQ(array_size(&a), static_cast<std::size_t>(i + 1));
  }

  EXPECT_FALSE(array_empty(&a));

  for (int i = 0; i < BIG_SIZE; ++i) {
    EXPECT_EQ(array_get(&a, i), i + 1);
  }

  array_destroy(&a);
}

/*
 * array_pop_back
 */

TEST(ArrayPopBackTest, OneElement) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_EQ(array_size(&a), std::size(origin));

  array_pop_back(&a);

  EXPECT_EQ(array_size(&a), std::size(origin) - 1);

  for (std::size_t i = 0; i < std::size(origin) - 1; ++i) {
    EXPECT_EQ(array_get(&a, i), origin[i]);
  }

  array_destroy(&a);
}

TEST(ArrayPopBackTest, ManyElements) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_EQ(array_size(&a), std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    array_pop_back(&a);
  }

  EXPECT_TRUE(array_empty(&a));
  EXPECT_EQ(array_size(&a), 0u);

  array_destroy(&a);
}

/*
 * array_insert
 */

TEST(ArrayInsertTest, Beginning) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 42, 9, 3, 7, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  array_insert(&a, 42, 0); // insert at the beginning

  EXPECT_EQ(array_size(&a), std::size(expected));
  EXPECT_TRUE(array_equals(&a, expected, std::size(expected)));

  array_destroy(&a);
}

TEST(ArrayInsertTest, Middle) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 42, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  array_insert(&a, 42, 3); // insert in the middle

  EXPECT_EQ(array_size(&a), std::size(expected));
  EXPECT_TRUE(array_equals(&a, expected, std::size(expected)));

  array_destroy(&a);
}

TEST(ArrayInsertTest, End) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 2, 4, 0, 8, 42 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  array_insert(&a, 42, std::size(origin)); // insert at the end

  EXPECT_EQ(array_size(&a), std::size(expected));
  EXPECT_TRUE(array_equals(&a, expected, std::size(expected)));

  array_destroy(&a);
}

TEST(ArrayInsertTest, Stressed) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  for (int i = 0; i < BIG_SIZE; ++i) {
    array_insert(&a, i + 1, 4);
    EXPECT_EQ(array_size(&a), std::size(origin) + i + 1);
  }

  array_destroy(&a);
}


/*
 * array_remove
 */

TEST(ArrayRemoveTest, Beginning) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 3, 7, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  array_remove(&a, 0); // remove at the beginning

  EXPECT_EQ(array_size(&a), std::size(expected));
  EXPECT_TRUE(array_equals(&a, expected, std::size(expected)));

  array_destroy(&a);
}

TEST(ArrayRemoveTest, Middle) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  array_remove(&a, 3); // remove in the middle

  EXPECT_EQ(array_size(&a), std::size(expected));
  EXPECT_TRUE(array_equals(&a, expected, std::size(expected)));

  array_destroy(&a);
}

TEST(ArrayRemoveTest, End) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 2, 4, 0 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  array_remove(&a, std::size(origin) - 1); // remove at the end

  EXPECT_EQ(array_size(&a), std::size(expected));
  EXPECT_TRUE(array_equals(&a, expected, std::size(expected)));

  array_destroy(&a);
}

/*
 * array_get
 */

TEST(ArrayGetTest, ValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    EXPECT_EQ(array_get(&a, i), origin[i]);
  }

  array_destroy(&a);
}

TEST(ArrayGetTest, NotValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_EQ(array_get(&a, std::size(origin)), 0);
  EXPECT_EQ(array_get(&a, -1), 0);

  array_destroy(&a);
}

/*
 * array_set
 */

TEST(ArraySetTest, ValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    array_set(&a, i, origin[i] - 1);
    EXPECT_EQ(array_get(&a, i), origin[i] - 1);
  }

  EXPECT_EQ(array_size(&a), std::size(origin));

  array_destroy(&a);
}

TEST(ArraySetTest, NotValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  array_set(&a, std::size(origin), 42);
  array_set(&a, -1, 42);

  EXPECT_EQ(array_size(&a), std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    EXPECT_EQ(array_get(&a, i), origin[i]);
  }

  array_destroy(&a);
}

/*
 * array_search
 */

TEST(ArraySearchTest, Present) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  for (size_t i = 0; i < std::size(origin); ++i) {
    size_t index = array_search(&a, origin[i]);
    EXPECT_EQ(index, i);
  }

  array_destroy(&a);
}

TEST(ArraySearchTest, NotPresent) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  size_t index = array_search(&a, -1);
  EXPECT_EQ(index, std::size(origin));

  array_destroy(&a);
}

/*
 * array_search_sorted
 */

TEST(ArraySearchSortedTest, Present) {
  static const int origin[] = { 1, 2, 3, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  for (size_t i = 0; i < std::size(origin); ++i) {
    size_t index = array_search_sorted(&a, origin[i]);
    EXPECT_EQ(index, i);
  }

  array_destroy(&a);
}


TEST(ArraySearchSortedTest, NotPresentBefore) {
  static const int origin[] = { 1, 2, 3, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  size_t index = array_search_sorted(&a, -1); // before everything
  EXPECT_EQ(index, std::size(origin));

  array_destroy(&a);
}

TEST(ArraySearchSortedTest, NotPresentAfter) {
  static const int origin[] = { 1, 2, 3, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  size_t index = array_search_sorted(&a, 15); // after everything
  EXPECT_EQ(index, std::size(origin));

  array_destroy(&a);
}

TEST(ArraySearchSortedTest, NotPresentMiddle) {
  static const int origin[] = { 1, 2, 3, 5, 6, 7, 8, 9 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  size_t index = array_search_sorted(&a, 4); // in the middle of other elements
  EXPECT_EQ(index, std::size(origin));

  array_destroy(&a);
}

/*
 * array_is_sorted
 */

TEST(ArrayIsSortedTest, Empty) {
  struct array a;
  array_create(&a);

  EXPECT_TRUE(array_is_sorted(&a));

  array_destroy(&a);
}

TEST(ArrayIsSortedTest, Sorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_TRUE(array_is_sorted(&a));

  array_destroy(&a);
}

TEST(ArrayIsSortedTest, NotSorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 10, 9, 8, 7, 6 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_sorted(&a));

  array_destroy(&a);
}

TEST(ArrayIsSortedTest, NotSortedAtTheEnd) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_sorted(&a));

  array_destroy(&a);
}

/*
 * array_partition
 */

TEST(ArrayPartitionTest, WholeSorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  ptrdiff_t p = array_partition(&a, 0, std::size(origin) - 1);
  int pivot = array_get(&a, p);

  for (ptrdiff_t i = 0; i < p; ++i) {
    EXPECT_LT(array_get(&a, i), pivot);
  }

  for (ptrdiff_t i = p + 1; i < static_cast<ptrdiff_t>(std::size(origin)); ++i) {
    EXPECT_GT(array_get(&a, i), pivot);
  }

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

TEST(ArrayPartitionTest, WholeNotSorted) {
  static const int origin[] = { 5, 4, 1, 6, 10, 3, 0, 9, 8, 2, 7 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  ptrdiff_t p = array_partition(&a, 0, std::size(origin) - 1);
  int pivot = array_get(&a, p);

  for (ptrdiff_t i = 0; i < p; ++i) {
    EXPECT_LT(array_get(&a, i), pivot);
  }

  for (ptrdiff_t i = p + 1; i < static_cast<ptrdiff_t>(std::size(origin)); ++i) {
    EXPECT_GT(array_get(&a, i), pivot);
  }

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

TEST(ArrayPartitionTest, PartNotSorted) {
  static const int origin[] = { 5, 4, 1, 6, 10, 3, 0, 9, 8, 2, 7 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  ptrdiff_t p = array_partition(&a, 3, 8);
  int pivot = array_get(&a, p);

  for (ptrdiff_t i = 3; i < p; ++i) {
    EXPECT_LT(array_get(&a, i), pivot);
  }

  for (ptrdiff_t i = p + 1; i < 8; ++i) {
    EXPECT_GT(array_get(&a, i), pivot);
  }

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

TEST(ArrayPartitionTest, Single) {
  static const int origin[] = { 5, 4, 1, 6, 10, 3, 0, 9, 8, 2, 7 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  ptrdiff_t p = array_partition(&a, 5, 5);

  EXPECT_EQ(p, 5);

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

/*
 * array_quick_sort
 */

TEST(ArrayQuickSortTest, NotSorted) {
  static const int origin[] = { 8, 4, 1, 6, 10, 3, 0, 9, 5, 2, 7 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_sorted(&a));

  array_quick_sort(&a);

  EXPECT_TRUE(array_is_sorted(&a));

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

TEST(ArrayQuickSortTest, SortedBackward) {
  static const int origin[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_sorted(&a));

  array_quick_sort(&a);

  EXPECT_TRUE(array_is_sorted(&a));

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

TEST(ArrayQuickSortTest, Sorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_TRUE(array_is_sorted(&a));

  array_quick_sort(&a);

  EXPECT_TRUE(array_is_sorted(&a));

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

/*
 * array_heap_sort
 */

TEST(ArrayHeapSortTest, NotSorted) {
  static const int origin[] = { 8, 4, 1, 6, 10, 3, 0, 9, 5, 2, 7 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_sorted(&a));

  array_heap_sort(&a);

  EXPECT_TRUE(array_is_sorted(&a));

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

TEST(ArrayHeapSortTest, SortedBackward) {
  static const int origin[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_sorted(&a));

  array_heap_sort(&a);

  EXPECT_TRUE(array_is_sorted(&a));

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

TEST(ArrayHeapSortTest, Sorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_TRUE(array_is_sorted(&a));

  array_heap_sort(&a);

  EXPECT_TRUE(array_is_sorted(&a));

  for (int val : origin) {
    EXPECT_NE(array_search(&a, val), std::size(origin));
  }

  array_destroy(&a);
}

/*
 * array_is_heap
 */

TEST(ArrayIsHeapTest, Empty) {
  struct array a;
  array_create(&a);

  EXPECT_TRUE(array_is_heap(&a));

  array_destroy(&a);
}

TEST(ArrayIsHeapTest, SimpleHeap1) {
  static const int origin[] = { 13, 6, 8, 5, 3 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_TRUE(array_is_heap(&a));

  array_destroy(&a);
}

TEST(ArrayIsHeapTest, SimpleHeap2) {
  static const int origin[] = { 81, 45, 24, 21, 6, 17, 19, 14 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_TRUE(array_is_heap(&a));

  array_destroy(&a);
}

TEST(ArrayIsHeapTest, NotHeap1) {
  static const int origin[] = { 6, 5, 4, 3, 1, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_heap(&a));

  array_destroy(&a);
}

TEST(ArrayIsHeapTest, NotHeap2) {
  static const int origin[] = { 6, 5, 4, 3, 1, 0, 8 };

  struct array a;
  array_create_from(&a, origin, std::size(origin));

  EXPECT_FALSE(array_is_heap(&a));

  array_destroy(&a);
}

/*
 * array_heap_add
 */

TEST(ArrayHeapAddTest, Stressed) {
  struct array a;

  array_create(&a);

  for (int i = 0; i < BIG_SIZE; ++i) {
    array_heap_add(&a, i);
    EXPECT_EQ(i, array_heap_top(&a));
    EXPECT_TRUE(array_is_heap(&a));
  }

  array_destroy(&a);
}

/*
 * array_heap_remove_top
 */

TEST(ArrayHeapRemoveTopTest, Stressed) {
  struct array a;

  array_create(&a);

  for (int i = 0; i < BIG_SIZE; ++i) {
    array_heap_add(&a, i);
  }

  EXPECT_TRUE(array_is_heap(&a));

  for (int i = 0; i < BIG_SIZE; ++i) {
    EXPECT_EQ(BIG_SIZE - i - 1, array_heap_top(&a));
    array_heap_remove_top(&a);
  }

  EXPECT_TRUE(array_empty(&a));

  array_destroy(&a);
}