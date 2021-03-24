//
//  deques.cpp
//  CF.STL_Containers_Deque
//
//  Created by Alan Sampson on 3/23/21.
//
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/container

#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <compare>
#include <memory>
#include <type_traits>
#include <span>
#include <new>
#include <compare>
#include <deque>
#include <cassert>

using namespace std::literals::string_literals;

//  MARK: - Definitions

//  MARK: - Local Constants.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  MARK: namespace konst
namespace konst {

auto delimiter(char const dc = '-', size_t sl = 80) -> std::string const {
  auto const dlm = std::string(sl, dc);
  return dlm;
}

static
auto const dlm = delimiter();

static
auto const dot = delimiter('.');

} /* namespace konst */

#if (__cplusplus > 201707L)
#endif  /* (__cplusplus > 201707L) */

//  MARK: - Function Prototype.
auto C_deque(int argc, const char * argv[]) -> decltype(argc);

//  MARK: - Implementation.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  std::cout << "CF.STL_Containers_Deque\n";
  std::cout << "C++ Version: "s << __cplusplus << std::endl;

  std::cout << '\n' << konst::dlm << std::endl;
  C_deque(argc, argv);

  return 0;
}

//  MARK: - C_deque
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  MARK: namespace cdque
namespace cdque {

template<typename T>
std::ostream& operator<<(std::ostream & os, const std::deque<T> & v_que) {
  os.put('[');
  char comma[3] = {'\0', ' ', '\0'};
  for (const auto & elmt : v_que) {
    os << comma << elmt;
    comma[0] = ',';
  }
  return os << ']';
}

} /* namespace cdque */

//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  MARK: namespace cdqstf
namespace cdqstf {

// minimal C++11 allocator with debug output
template <class Tp>
struct NAlloc {
  typedef Tp value_type;

  NAlloc() = default;

  template <class T> NAlloc(NAlloc<T> const &) {}

  Tp * allocate(std::size_t nr) {
    nr *= sizeof(Tp);
    std::cout << "allocating "s << nr << " bytes\n"s;
    return static_cast<Tp *>(::operator new(nr));
  }

  void deallocate(Tp * ptr, std::size_t nr) {
    std::cout << "deallocating "s << nr * sizeof * ptr << " bytes\n"s;
    ::operator delete(ptr);
  }
};

template <class T, class U>
bool operator==(const NAlloc<T> &, const NAlloc<U> &) {
  return true;
}

template <class T, class U>
bool operator!=(const NAlloc<T>&, const NAlloc<U> &) {
  return false;
}

} /* namespace cdqstf */

//  MARK: namespace cdqswp
namespace cdqswp {

template<class Os, class Co> Os & operator<<(Os & os, const Co & co) {
  os << "{"s;
  for (auto const & ix : co) {
    os << ' ' << ix;
  }
  return os << " } "s;
}

} /* namespace cdqswp */

//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_deque()
 */
auto C_deque(int argc, const char * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque"s << '\n';
  {
    // Create a deque containing integers
    std::deque<int> dq = { 7, 5, 16, 8, };

    // Add an integer to the beginning and end of the deque
    dq.push_front(13);
    dq.push_back(25);

    // Iterate and print values of deque
    for (int nr : dq) {
      std::cout << std::setw(4) << nr << '\n';
    }

    std::cout << '\n';
  };

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - constructor"s << '\n';
  {
    using namespace cdque;

    // c++11 initializer list syntax:
    std::deque<std::string> words1 {"the"s, "frogurt"s, "is"s, "also"s, "cursed"s, };
    std::cout << "words1: "s << words1 << '\n';

    // words2 == words1
    std::deque<std::string> words2(words1.begin(), words1.end());
    std::cout << "words2: "s << words2 << '\n';

    // words3 == words1
    std::deque<std::string> words3(words1);
    std::cout << "words3: "s << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    std::deque<std::string> words4(5, "Mo"s);
    std::cout << "words4: "s << words4 << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - operator="s << '\n';
  {
    auto display_sizes = [](std::deque<int> const & nums1,
                            std::deque<int> const & nums2,
                            std::deque<int> const & nums3) {
      std::cout << "nums1: "s << nums1.size()
                << " nums2: "s << nums2.size()
                << " nums3: "s << nums3.size() << '\n';
    };

    std::deque<int> nums1 { 3, 1, 4, 6, 5, 9, };
    std::deque<int> nums2;
    std::deque<int> nums3;

    std::cout << "Initially:\n"s;
    display_sizes(nums1, nums2, nums3);

    // copy assignment copies data from nums1 to nums2
    nums2 = nums1;

    std::cout << "After assigment:\n"s;
    display_sizes(nums1, nums2, nums3);

    // move assignment moves data from nums1 to nums3,
    // modifying both nums1 and nums3
    nums3 = std::move(nums1);

    std::cout << "After move assigment:\n"s;
    display_sizes(nums1, nums2, nums3);

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - assign"s << '\n';
  {
    std::deque<char> characters;

    auto print_deque = [&](){
      for (char ch : characters)
        std::cout << ch << ' ';
      std::cout << '\n';
    };

    characters.assign(5, 'a');
    print_deque();

    const std::string extra(6, 'b');
    characters.assign(extra.begin(), extra.end());
    print_deque();

    characters.assign({ 'C', '+', '+', '1', '1', });
    print_deque();

    std::cout << '\n';
  };

  /// Element access
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - at"s << '\n';
  {
    std::deque<int> data = { 1, 2, 4, 5, 5, 6, };

    // Set element 1
    data.at(1) = 88;

    // Read element 2
    std::cout << "Element at index 2 has value "s << data.at(2) << '\n';

    std::cout << "data size = "s << data.size() << '\n';

    try {
    // Set element 6
      data.at(6) = 666;
    }
    catch (std::out_of_range const & exc) {
      std::cout << exc.what() << '\n';
    }

    // Print final values
    std::cout << "data:"s;
    for (int elem : data) {
      std::cout << " " << elem;
    }
    std::cout << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - operator[]"s << '\n';
  {
    std::deque<int> numbers { 2, 4, 6, 8, };

    std::cout << "Second element: "s << numbers[1] << '\n';

    numbers[0] = 5;

    std::cout << "All numbers:"s;
    for (auto i_ : numbers) {
      std::cout << ' ' << i_;
    }
    std::cout << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - front"s << '\n';
  {
    std::deque<char> letters { 'o', 'm', 'g', 'w', 't', 'f', };

    if (!letters.empty()) {
      std::cout << "The first character is '"s << letters.front() << "'.\n"s;
    }

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - back"s << '\n';
  {
    std::deque<char> letters { 'a', 'b', 'c', 'd', 'e', 'f', };

    if (!letters.empty()) {
      std::cout << "The last character is '"s << letters.back() << "'.\n"s;
    }

    std::cout << '\n';
  };

  /// Iterators
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - begin, end, cbegin, cend"s << '\n';
  {
    std::deque<int> nums { 1, 2, 4, 8, 16, };
    std::deque<std::string> fruits { "orange"s, "apple"s, "raspberry"s, };
    std::deque<char> empty;

    // Print deque.
    std::for_each(nums.begin(), nums.end(), [](int const n_) {
      std::cout << n_ << ' ';
    });
    std::cout << '\n';

    // Sums all integers in the deque nums (if any), printing only the result.
    std::cout << "Sum of nums: "s
              << std::accumulate(nums.begin(), nums.end(), 0) << '\n';

    // Prints the first fruit in the deque fruits, checking if there is any.
    if (!fruits.empty()) {
      std::cout << "First fruit: "s << *fruits.begin() << '\n';
    }

    if (empty.begin() == empty.end()) {
      std::cout << "deque 'empty' is indeed empty.\n"s;
    }

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - rbegin, rend, rcbegin, rcend"s << '\n';
  {
    std::deque<int> nums { 1, 2, 4, 8, 16, };
    std::deque<std::string> fruits { "orange"s, "apple"s, "raspberry"s, };
    std::deque<char> empty;

    // Print deque.
    std::for_each(nums.rbegin(), nums.rend(), [](int const n_) {
      std::cout << n_ << ' ';
    });
    std::cout << '\n';

    // Sums all integers in the deque nums (if any), printing only the result.
    std::cout << "Sum of nums: "s
            << std::accumulate(nums.rbegin(), nums.rend(), 0) << '\n';

    // Prints the first fruit in the deque fruits, checking if there is any.
    if (!fruits.empty()) {
      std::cout << "First fruit: "s << *fruits.rbegin() << '\n';
    }

    if (empty.rbegin() == empty.rend()) {
      std::cout << "deque 'empty' is indeed empty.\n"s;
    }

    std::cout << '\n';
  };

  /// Capacity
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - empty"s << '\n';
  {
    std::deque<int> numbers;
    std::cout << std::boolalpha;
    std::cout << "Initially, numbers.empty(): "s << numbers.empty() << '\n';

    numbers.push_back(42);
    numbers.push_back(13'317);
    std::cout << "After adding elements, numbers.empty(): "s << numbers.empty() << '\n';
    std::cout << std::noboolalpha;

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - size"s << '\n';
  {
    std::deque<int> nums { 1, 3, 5, 7 };

    std::cout << "nums contains "s << nums.size() << " elements.\n"s;

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - max_size"s << '\n';
  {
    std::deque<char> chars;
    std::cout << "Maximum size of a 'deque' is "s << chars.max_size() << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - shrink_to_fit"s << '\n';
  {
    /* std::queue has no capacity() function (like std::vector),
     * because of this we use a custom allocator to show
     * the working of shrink_to_fit.  */
    std::cout << "Default-construct deque:\n"s;
    std::deque<int, cdqstf::NAlloc<int>> deq;

    std::cout << "\nAdd 300 elements:\n"s;
    for (int i_ = 1'000; i_ < 1'300; ++i_) {
      deq.push_back(i_);
    }

    std::cout << "\nPop 100 elements:\n"s;
    for (int i_ = 0; i_ < 100; ++i_) {
      deq.pop_front();
    }

    std::cout << "\nRun shrink_to_fit:\n"s;
    deq.shrink_to_fit();

    std::cout << "\nDestroy deque as it goes out of scope:\n"s;

    std::cout << '\n';
  };

  /// Modifiers
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - clear"s << '\n';
  {
    std::deque<int> container { 1, 2, 3, };

    auto print = [](int const & n_) {
      std::cout << ' ' << n_;
    };

    std::cout << "Before clear:"s;
    std::for_each(container.begin(), container.end(), print);
    std::cout << "\nSize="s << container.size() << '\n';

    std::cout << "Clear\n"s;
    container.clear();

    std::cout << "After clear:"s;
    std::for_each(container.begin(), container.end(), print);
    std::cout << "\nSize="s << container.size() << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - insert"s << '\n';
  {
    auto constexpr cc_max(10ul);
    auto cc(0ul);
    auto printq = [&cc](auto const & dq, auto const sw = 0) {
      std::for_each(dq.cbegin(), dq.cend(), [&cc, &sw](auto ql) {
        std::cout << std::setw(sw) << ql
                  << (++cc % cc_max == 0 ? "\n" : "");
      });
      std::cout << '\n';
      cc = 0ul;
    };

    auto tqueue = std::deque {
       5ul, 42ul, 666ul, 99ul,   0ul,  1ul,  2ul,
      22ul,  7ul,  17ul,  4ul, 217ul, 33ul, 21ul,
    };
    auto av(97ul);
    decltype(av) isrt[] { 201ul, 202ul, 203ul, 204ul, };
    auto iq = std::deque { av, av + 1, av + 2, };
    printq(tqueue, 4);
    tqueue.insert(tqueue.cbegin(), 444ul);
    printq(tqueue, 4);
    tqueue.insert(tqueue.cbegin() + 3, 444ul);
    printq(tqueue, 4);
    printq(iq, 4);
    tqueue.insert(tqueue.cbegin() + 3, std::move(iq[0]));
    printq(iq, 4);
    printq(tqueue, 4);
    tqueue.insert(tqueue.cbegin() + 4, 5ul, 101ul);
    printq(tqueue, 4);
    tqueue.insert(tqueue.cbegin(), std::span { isrt }.begin(), std::span { isrt }.end());
    printq(tqueue, 4);
    tqueue.insert(tqueue.cbegin() + 10, { 301ul, 302ul, 303ul, });
    printq(tqueue, 4);

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - emplace"s << '\n';
  {
    struct Aempl {
      std::string str;

      Aempl(std::string str) : str(std::move(str))  {
        std::cout << " constructed\n"s;
      }

      Aempl(const Aempl & other) : str(other.str) {
        std::cout << " copy constructed\n"s;
      }

      Aempl(Aempl && other) : str(std::move(other.str)) {
        std::cout << " move constructed\n"s;
      }

      Aempl & operator=(const Aempl & other) {
        str = other.str;
        std::cout << " copy assigned\n"s;
        return *this;
      }

      Aempl & operator=(Aempl && other) {
        str = std::move(other.str);
        std::cout << " move assigned\n"s;
        return *this;
      }
    };

    std::deque<Aempl> container;

    std::cout << "construct 2 times Aempl:\n"s;
    Aempl two { "two"s };
    Aempl three { "three"s };

    std::cout << "emplace:\n"s;
    container.emplace(container.end(), "one"s);

    std::cout << "emplace with Aempl &:\n"s;
    container.emplace(container.end(), two);

    std::cout << "emplace with Aempl &&:\n"s;
    container.emplace(container.end(), std::move(three));

    std::cout << "content:\n"s;
    for (auto const & obj : container) {
      std::cout << ' ' << obj.str;
    }
    std::cout << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - erase"s << '\n';
  {
    auto print_container = [](std::deque<int> const & container) {
      for (auto & iv : container) {
        std::cout << iv << " ";
      }
      std::cout << '\n';
    };

    std::deque<int> container { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    print_container(container);

    container.erase(container.begin());
    print_container(container);

    container.erase(container.begin() + 2, container.begin() + 5);
    print_container(container);

    // Erase all even numbers (C++11 and later)
    for (auto it = container.begin(); it != container.end(); ) {
      if (*it % 2 == 0) {
        it = container.erase(it);
      }
      else {
        ++it;
      }
    }
    print_container(container);

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - push_back"s << '\n';
  {
    std::deque<std::string> letters;

    letters.push_back("abc"s);
    std::string s_up = "def"s;
    letters.push_back(std::move(s_up));

    std::cout << "deque holds: "s;
    for (auto && ix : letters) {
      std::cout << std::quoted(ix) << ' ';
    }
    std::cout << "\nMoved-from string holds "s << std::quoted(s_up) << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - emplace_back"s << '\n';
  {
    struct President {
      std::string name;
      std::string country;
      int year;

      President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
        std::cout << "I am being constructed.\n"s;
      }

      President(President && other)
        : name(std::move(other.name)),
          country(std::move(other.country)),
          year(other.year) {
        std::cout << "I am being moved.\n"s;
      }

      President & operator=(const President & other) = default;
    };

    std::deque<President> elections;
    std::cout << "emplace_back:\n";
    auto& ref = elections.emplace_back("Nelson Mandela"s, "South Africa"s, 1994);
    assert(ref.year != 1984 && "uses a reference to the created object (C++17)");

    std::deque<President> reElections;
    std::cout << "\npush_back:\n"s;
    reElections.push_back(President("Franklin Delano Roosevelt"s, "the USA"s, 1936));

    std::cout << "\nContents:\n"s;

    for (President const & president : elections) {
      std::cout << president.name << " was elected president of "s
                << president.country << " in "s << president.year << ".\n"s;
    }

    for (President const & president : reElections) {
      std::cout << president.name << " was re-elected president of "s
                << president.country << " in "s << president.year << ".\n"s;
    }

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - pop_front"s << '\n';
  {
    auto print = [](auto const & con) {
      for (auto const & item : con) {
        std::cout << item;
      }
      std::cout << '\n';
    };

    std::deque<char> letters { 'A','B','C','D', };

    for (char ch{letters.back()}; ch != 'H' ;) {
      letters.push_back(++ch);
      print(letters);
      letters.pop_front();
    }

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - resize"s << '\n';
  {
    std::deque<int> container = { 1, 2, 3, };
    std::cout << "The deque holds: "s;
    for(auto & el: container) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
    container.resize(5);
    std::cout << "After resize up to 5: "s;
    for(auto & el: container) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
    container.resize(2);
    std::cout << "After resize down to 2: "s;
    for(auto & el: container) {
      std::cout << el << ' ';
    }
    std::cout << '\n';

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - swap"s << '\n';
  {
    using namespace cdqswp;

    std::deque<int> a1 { 1, 2, 3, }, a2 { 4, 5, };

    auto it1 = std::next(a1.begin());
    auto it2 = std::next(a2.begin());

    int& ref1 = a1.front();
    int& ref2 = a2.front();

    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'

    std::cout << '\n';
  };

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - std::operator==, etc."s << '\n';
  {
    std::deque<int> alice { 1, 2, 3, };
    std::deque<int> bob   { 7, 8, 9, 10, };
    std::deque<int> eve   { 1, 2, 3, };

    std::cout << std::boolalpha;

    // Compare non equal containers
    std::cout << "alice == bob returns "s << (alice == bob) << '\n';
    std::cout << "alice != bob returns "s << (alice != bob) << '\n';
    std::cout << "alice <  bob returns "s << (alice < bob) << '\n';
    std::cout << "alice <= bob returns "s << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns "s << (alice > bob) << '\n';
    std::cout << "alice >= bob returns "s << (alice >= bob) << '\n';

    std::cout << '\n';

    // Compare equal containers
    std::cout << "alice == eve returns "s << (alice == eve) << '\n';
    std::cout << "alice != eve returns "s << (alice != eve) << '\n';
    std::cout << "alice <  eve returns "s << (alice < eve) << '\n';
    std::cout << "alice <= eve returns "s << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns "s << (alice > eve) << '\n';
    std::cout << "alice >= eve returns "s << (alice >= eve) << '\n';

#if (__cplusplus > 201707L)
    //`TODO:  add spaceship operator tests
    auto eq = std::is_eq(alice <=> eve);
    auto nq = std::is_neq(alice <=> eve);
    auto lt = std::is_lt(alice <=> eve);
    auto le = std::is_lteq(alice <=> eve);
    auto gt = std::is_gt(alice <=> eve);
    auto re = std::is_gteq(alice <=> eve);
#endif  /* (__cplusplus > 201707L) */

    std::cout << '\n';
  };

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - std::swap"s << '\n';
  {
    std::deque<int> alice { 1, 2, 3, };
    std::deque<int> bob   { 7, 8, 9, 10, };

    auto print = [](int const & nr) {
      std::cout << ' ' << nr;
    };

    // Print state before swap
    std::cout << "alice:"s;
    std::for_each(alice.begin(), alice.end(), print);
    std::cout << "\n"s "bob  :"s;
    std::for_each(bob.begin(), bob.end(), print);
    std::cout << '\n';

    std::cout << "-- SWAP\n"s;
    std::swap(alice, bob);

    // Print state after swap
    std::cout << "alice:"s;
    std::for_each(alice.begin(), alice.end(), print);
    std::cout << "\n"s "bob  :"s;
    std::for_each(bob.begin(), bob.end(), print);
    std::cout << '\n';

    std::cout << '\n';
  };

#if (__cplusplus > 201707L)
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::deque - std::erase, std::erase_if"s << '\n';
  {
    auto print_container = [](std::string_view comment, const std::deque<char> & ctr)
    {
      std::cout << comment;
      for (auto xl : ctr) {
          std::cout << xl << ' ';
      }
      std::cout << '\n';
    };

    std::deque<char> cnt(10);
    std::iota(cnt.begin(), cnt.end(), '0');
    print_container("Init:\n"s, cnt);

    std::erase(cnt, '3');
    print_container("Erase '3':\n"s, cnt);

    auto erased = std::erase_if(cnt, [](char xl) {
      return (xl - '0') % 2 == 0;
    });
    print_container("Erase all even numbers:\n"s, cnt);
    std::cout << "In all "s << erased << " even numbers were erased.\n"s;

    std::cout << '\n';
  }
#endif  /* (__cplusplus > 201707L) */

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}
