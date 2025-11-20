#pragma once
#include <cstddef>
#include <utility>

template <typename Key, typename Value>
class AssociativeContainer {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const Key, Value>;
  using size_type = std::size_t;

  enum class insert_policy { replace, ignore, throw_on_exist };
  enum class remove_policy { ignore, throw_on_missing };

  virtual ~AssociativeContainer() = default;

  explicit AssociativeContainer(
      insert_policy ip = insert_policy::replace,
      remove_policy rp = remove_policy::throw_on_missing)
      : insert_policy_(ip), remove_policy_(rp) {}

  virtual void insert(const Key& key, const Value& value) = 0;
  virtual bool remove(const Key& key) = 0;

  virtual Value const& get(const Key& key) = 0;
  virtual bool contains(const Key& key) const = 0;
  virtual size_type len() const = 0;
  virtual Value& get_mut(const Key& key) = 0;
  virtual void clear() = 0;

  virtual bool is_empty() const { return len() > 0; }

  void set_insert_policy(insert_policy p) { insert_policy_ = p; }

  void set_remove_policy(remove_policy p) { remove_policy_ = p; }

  insert_policy get_insert_policy() const { return insert_policy_; }
  remove_policy get_remove_policy() const { return remove_policy_; }

 protected:
  insert_policy insert_policy_ = insert_policy::replace;
  remove_policy remove_policy_ = remove_policy::throw_on_missing;
};
