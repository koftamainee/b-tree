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
  using comparator_t = std::function<int(const Key&, const Key&)>;

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
  size_type size = 0;

 public:
  explicit BTreeBase(size_type t_, comparator_t comp_,
                     std::shared_ptr<logger> lg,
                     std::shared_ptr<allocator> alloc) : SearchTree<Key, Value>(lg, alloc), t(t_), comp(comp_) {}

  ~BTreeBase() noexcept override {}

  void insert(const Key& key, const Value& value) override {}
  bool remove(const Key& key) override { return false; }
  std::pair<iterator, iterator> find_in_range(const Key& left,
                                              const Key& right) const override {
    return {};
  }

  virtual Value const& get(const Key& key) override {}
  bool contains(const Key& key) const override {

  }
  size_type len() const override { return size; }
  Value& get_mut(const Key& key) override {}

  void clear() override {}

  typename SearchTree<Key, Value>::iterator* begin() override {}

  typename SearchTree<Key, Value>::iterator* end() override {}

protected:
  Node* create_node(bool leaf) {
    Node *new_node = allocate_with_guard(sizeof(Node *));
    if (new_node == nullptr) {
      critical_with_guard("Failed to allocate memory for node");
      throw std::bad_alloc();
    }
    allocator::construct(new_node, leaf);
    new_node->children.resize(2 * t - 1);
    new_node->keys.resize(2 * t - 1);
    return new_node;
  }
  void destroy_node(Node* node) {
    if (node == nullptr) {
      return;
    }
    for (auto *child : node->children) {
      destroy_node(child);
    }
    allocator::destruct(node);
    allocator::deallocate(node);
  }

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
