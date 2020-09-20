#pragma once

#include <iostream>
#include <iterator>
#include <fstream>
#include <array>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <string>
#include <algorithm>

template <typename T>
bool IsInRange(const T& val, const T& from, const T& to) {
    return (val >= from) && (val <= to);
}

template <typename T>
bool IsInRange(const T& val, const std::pair<const T&, const T&>& minmax) {
    return (val >= minmax.first) && (val <= minmax.second);
}

template <typename T>
bool IsInsideRange(const T& val, const T& from, const T& to) {
    return (val > from) && (val < to);
}

template <typename T>
bool IsInsideRange(const T& val, const std::pair<const T&, const T&>& minmax) {
    return (val > minmax.first) && (val < minmax.second);
}

template <class T, class U = T>
bool Modify(T& obj, U&& new_value) {
    if (obj != new_value) {
        obj = new_value;
        return true;
    }
    return false;
}

template <class Collection, class T>
void RemoveAll(Collection& c, const T& value) {
    auto itr = std::remove(std::begin(c), std::end(c), value);
    Collection normal (std::distance(std::begin(c), itr));
    std::move(begin(c), itr, begin(normal));
    c = std::move(normal);
}

template <class Collection, class Pred>
void RemoveAllIf(Collection& c, Pred&& predicate) {
    auto itr = std::remove_if(std::begin(c), std::end(c), predicate);
    Collection normal (std::distance(std::begin(c), itr));
    std::move(begin(c), itr, begin(normal));
    c = std::move(normal);
}

template <class Collection, class T>
auto Find(Collection& c, const T& value) {
    return std::find(std::begin(c), std::end(c), value);
}

template <class Collection, class Pred>
auto FindIf(Collection& c, Pred&& predicate) {
    return std::find_if(std::begin(c), std::end(c), predicate);
}

template <class Collection, class T>
bool Contains(const Collection& c, const T& value) {
    if (std::find(std::begin(c), std::end(c), value) == std::end(c))
        return false;
    return true;
}

template <class Collection, class Pred>
bool ContainsIf(const Collection& c, Pred&& predicate) {
    if (std::find_if(std::begin(c), std::end(c), predicate) == std::end(c))
        return false;
    return true;
}

template <class Collection, class Pred>
int CountIf(const Collection& c, Pred&& predicate) {
    return std::count_if(std::begin(c), std::end(c), predicate);
}

template <class T>
const auto& Min(const T& arg) {
    return arg;
}

template <class T, class... Args>
const auto& Min(const T& arg, const Args&... args) {
    return arg < Min(args...) ? arg : Min(args...);
}

template <class T>
const auto& Max(const T& arg) {
    return arg;
}

template <class T, class... Args>
const auto& Max(const T& arg, const Args&... args) {
    return arg > Max(args...) ? arg : Max(args...);
}

template <class Collection>
auto MinElement(const Collection& c) {
    return std::min_element(std::begin(c), std::end(c));
}

template <class Collection>
auto MaxElement(const Collection& c) {
    return std::max_element(std::begin(c), std::end(c));
}

template <class Collection, class Comp>
auto MinElement(const Collection& c, Comp&& comparator) {
    return std::min_element(std::begin(c), std::end(c), comparator);
}

template <class Collection, class Comp>
auto MaxElement(const Collection& c, Comp&& comparator) {
    return std::max_element(std::begin(c), std::end(c), comparator);
}

template <class Collection>
void Sort(Collection& c) {
    std::sort(std::begin(c), std::end(c));
}

template <class Collection, class Comp>
void Sort(Collection& c, Comp&& comparator) {
    std::sort(std::begin(c), std::end(c), comparator);
}

template <class Collection>
void Unique(Collection& c) {
    Sort(c);
    auto itr = std::unique(begin(c), end(c));
    Collection normal (std::distance(std::begin(c), itr));
    std::move(begin(c), itr, begin(normal));
    c = std::move(normal);
}

template <class Collection, class Pred>
void Unique(Collection& c, Pred&& predicate) {
    Sort(c);
    auto itr = std::unique(begin(c), end(c), predicate);
    Collection normal (std::distance(std::begin(c), itr));
    std::move(begin(c), itr, begin(normal));
    c = std::move(normal);    
}

template <class Collection, class Pred>
void ForEach(Collection& c, Pred&& predicate) {
    std::for_each(begin(c), end(c), predicate);
}

template <class Collection, class T>
int IndexOf(const Collection& c, const T& value) {
    return std::distance(begin(c), Find(c, value));
}

template <class Collection, class Pred>
int IndexOfIf(const Collection& c, Pred&& predicate) {
    return std::distance(begin(c), FindIf(c, predicate));
}
