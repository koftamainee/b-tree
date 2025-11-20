#pragma once

#include "btree_base.h"

template <typename TKey, typename TValue>
class BTree : public BTreeBase<TKey, TValue, BTree<TKey, TValue>> {
  using Base = BTreeBase<TKey, TValue, BTree>;
  using Node = typename Base::Node;

 public:
  explicit BTree(size_t t, typename Base::comparator_t comp,
                 std::shared_ptr<logger> lg, std::shared_ptr<allocator> alloc) {
  }

 protected:
  Node* create_leaf_node() override { return nullptr; }
  Node* create_internal_node() override { return nullptr; }

  void prepare_leaf_for_insert(Node* leaf) override {}
  void prepare_internal_for_insert(Node* internal) override {}

  void split_child(Node* parent, size_t idx) override {}
  void handle_overflow(Node* node) override {}

  void find_in_node(Node* node, const TKey& key, TValue& out,
                    bool& found) const override {}
  void find_range_in_node(Node* node, const TKey& left, const TKey& right,
                          typename Base::iterator& begin_it,
                          typename Base::iterator& end_it) const override {}

  void dispose_in_node(Node* node, const TKey& key) override {}
  void destroy_node(Node* node) override {}

 public:
  void insert(const TKey& key, const TValue& value) {}

  template <typename K, typename V>
  void insert(K&& key, V&& value) {}

 private:
  template <typename K, typename V>
  void insert_impl(K&& key, V&& value) {}

  template <typename K, typename V>
  void insert_non_full(Node* node, K&& key, V&& value) {}
};
