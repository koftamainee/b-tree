#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "allocator_guardant.h"
#include "logger_guardant.h"
#include "search_tree.h"

template <typename Key, typename Value, typename Derived>
class BTreeBase : public SearchTree<Key, Value>,
                  protected logger_guardant,
                  private allocator_guardant {
 public:
  using size_type = std::size_t;
  using comparator_t = std::function<bool(const Key&, const Key&)>;

 protected:
  struct Node {
    bool leaf;
    std::vector<Key> keys;
    std::vector<Value> values;
    std::vector<Node*> children;

    explicit Node(bool leaf_) : leaf(leaf_) {}
    virtual ~Node() = default;
  };

 public:
  struct iterator;

 protected:
  std::shared_ptr<logger> logger_ptr;
  std::shared_ptr<allocator> allocator_ptr;
  Node* root = nullptr;
  size_type t;
  comparator_t comp;

 public:
  explicit BTreeBase(size_type t_, comparator_t comp_,
                     std::shared_ptr<logger> lg,
                     std::shared_ptr<allocator> alloc) {}

  virtual ~BTreeBase() noexcept {}

  void insert(const Key& key, const Value& value) override {}
  bool remove(const Key& key) override { return false; }
  std::pair<iterator, iterator> find_in_range(const Key& left,
                                              const Key& right) const override {
    return {};
  }

  virtual Value const& get(const Key& key) override {}
  virtual bool contains(const Key& key) override {}
  virtual size_type len() override {}
  virtual Value& get_mut(const Key& key) override {}

  void clear() override {}

  typename SearchTree<Key, Value>::iterator* begin() override {}

  typename SearchTree<Key, Value>::iterator* end() override {}

 protected:
  Node* allocate_node(bool leaf) {}
  void destroy_node(Node* node) {}

  logger* get_logger() const override { return logger_ptr.get(); }
  allocator* get_allocator() const override { return allocator_ptr.get(); }

 public:
  struct iterator {
    using value_pair = std::pair<Key, Value>;

    iterator() {}
    iterator(Node* n, size_type i, size_type d) {}

    iterator& operator++() { return *this; }
    iterator operator++(int) { return *this; }

    bool operator==(const iterator& other) const { return false; }
    bool operator!=(const iterator& other) const { return false; }

    value_pair operator*() const { return {}; }
    size_type depth() const { return 0; }
    size_type index_in_node() const { return 0; }

   protected:
    friend class BTreeBase;
    Node* node_ptr = nullptr;
    size_type index = 0;
    size_type depth_ = 0;
  };
};
