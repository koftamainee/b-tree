#pragma once
#include <utility>

#include "associative_container.h"

template <typename Key, typename Value>
class SearchTree : public AssociativeContainer<Key, Value> {
 public:
  using Base = AssociativeContainer<Key, Value>;
  using typename Base::key_type;
  using typename Base::mapped_type;
  using typename Base::size_type;
  using typename Base::value_type;

  struct iterator_info {
    size_type depth;
    size_type index;
  };

  struct inorder_result {
    value_type& kv;
    iterator_info meta;
  };

  class iterator {
   public:
    virtual ~iterator() = default;
    virtual inorder_result operator*() const = 0;
    virtual iterator& operator++() = 0;
    virtual bool operator==(const iterator& other) const = 0;
    virtual bool operator!=(const iterator& other) const = 0;
  };

  ~SearchTree() override = default;

  virtual iterator* begin() = 0;
  virtual iterator* end() = 0;

  virtual std::pair<iterator*, iterator*> find_in_range(
      const Key& key_low, const Key& key_high) const = 0;
};
