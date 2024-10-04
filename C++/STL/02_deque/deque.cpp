#include <deque>

template <class T, class Allocator = std::allocator<T>>
class deque {
public:
    // 类型定义
    typedef T                                value_type;
    typedef Allocator                        allocator_type;
    typedef size_t                           size_type;
    typedef ptrdiff_t                        difference_type;
    typedef T                               &reference;
    typedef const T                         &const_reference;
    typedef T                               *pointer;
    typedef const T                         *const_pointer;
    typedef std::allocator_traits<Allocator> allocator_traits_type;

    // 迭代器类型
    typedef implementation_defined                iterator;
    typedef implementation_defined                const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // 构造函数和析构函数
    explicit deque(const Allocator & = Allocator());
    explicit deque(size_type n, const Allocator & = Allocator());
    deque(size_type n, const value_type &value,
          const Allocator & = Allocator());
    template <class InputIterator>
    deque(InputIterator first, InputIterator last,
          const Allocator & = Allocator());
    deque(const deque &other);
    deque(deque &&other);
    deque(std::initializer_list<value_type> init,
          const Allocator & = Allocator());
    ~deque();

    // 赋值运算符
    deque &operator=(const deque &other);
    deque &operator=(deque &&other);
    deque &operator=(std::initializer_list<value_type> init);

    // 迭代器
    iterator               begin() noexcept;
    const_iterator         begin() const noexcept;
    iterator               end() noexcept;
    const_iterator         end() const noexcept;
    reverse_iterator       rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator       rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_iterator         cbegin() const noexcept;
    const_iterator         cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // 容量
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void      resize(size_type new_size);
    void      resize(size_type new_size, const value_type &x);

    // 修改器
    void clear() noexcept;
    void push_back(const value_type &value);
    void push_back(T &&value);
    template <class... Args>
    void emplace_back(Args &&...args);
    void push_front(const value_type &value);
    void push_front(T &&value);
    template <class... Args>
    void emplace_front(Args &&...args);
    void pop_back();
    void pop_front();

    // 访问器
    reference       operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference       at(size_type n);
    const_reference at(size_type n) const;
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    // 插入器和移除器
    iterator insert(iterator pos, const value_type &value);
    iterator insert(iterator pos, T &&value);
    template <class... Args>
    iterator emplace(iterator pos, Args &&...args);
    void     insert(iterator pos, size_type n, const value_type &value);
    template <class InputIterator>
    void     insert(iterator pos, InputIterator first, InputIterator last);
    void     insert(iterator pos, std::initializer_list<value_type> ilist);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    // 特殊操作
    void swap(deque &other) noexcept(/* see below */);
};