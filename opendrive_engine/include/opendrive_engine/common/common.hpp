#ifndef OPENDRIVE_CPP_COMMON_HPP_
#define OPENDRIVE_CPP_COMMON_HPP_

#include <tinyxml2.h>

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace opendrive {
namespace common {

template <typename T>
static T SpeedMPH2KMH(T mph) {
  return mph * 1.60934;
}

template <typename T>
static T SpeedMS2KMH(T ms) {
  return ms * 3.6;
}

template <typename T>
static T SpeedMPH2MS(T mph) {
  return mph * 0.44704;
}

template <typename T>
static T SpeedKMH2MS(T kmh) {
  return kmh * 0.27778;
}

/**
 * @brief 计算偏离点
 *
 * @tparam T element::Point
 * @param point 基准点
 * @param lateral_offset 横向偏离距离
 * @return 偏离点
 */
template <typename T>
static T GetOffsetPoint(const T& point, double lateral_offset) {
  const double x = -std::sin(point.heading());
  const double y = std::cos(point.heading());
  T offset_point = point;
  offset_point.set_x(offset_point.x() + lateral_offset * x);
  offset_point.set_y(offset_point.y() + lateral_offset * y);
  return offset_point;
}

/**
 * @brief 容器排序
 *
 * @tparam T Poloy3派生类
 * @param items Poloy3 vector;
 * @param asc 升序/降序
 */
template <typename T>
static void VectorSortPoloy3(std::vector<T>* items, bool asc = true) {
  std::sort(items->begin(), items->end(), [asc](const T& t1, const T& t2) {
    return asc ? t1.s() < t2.s() : t1.s() > t2.s();
  });
}

/**
 * @brief 获取目标值左边的元素(包括目标值)
 *
 * @tparam T1 element::Poloy3
 * @tparam T2 number
 * @param items ascending sequence
 * @param target target value
 * @return sequence index or -1
 */
template <typename T1, typename T2>
static int GetGeValuePoloy3(const std::vector<T1>& items, T2 target) {
  if (items.empty() || target < items.at(0).s()) return -1;
  for (int i = items.size() - 1; i >= 0; i--) {
    if (target >= items.at(i).s()) return i;
  }
  return -1;
}

/**
 * @brief 获取目标值左边的元素(不包括目标值)
 *
 * @tparam T1 element::Poloy3
 * @tparam T2 number
 * @param items ascending sequence
 * @param target target value
 * @return sequence index or -1
 */
template <typename T1, typename T2>
static int GetGtValuePoloy3(const std::vector<T1>& items, T2 target) {
  if (items.empty() || target < items.at(0).s()) return -1;
  if (target < items.at(0).s()) return -1;
  for (int i = items.size() - 1; i >= 0; i--) {
    if (target > items.at(i).s()) return i;
  }
  return 0;
}

template <typename T1, typename T2>
static int GetGePtrPoloy3(const std::vector<T1>& items, T2 target) {
  if (items.empty() || target < items.at(0)->s()) return -1;
  for (int i = items.size() - 1; i >= 0; i--) {
    if (target >= items.at(i)->s()) return i;
  }
  return -1;
}

template <typename T1, typename T2>
static int GetGtPtrPoloy3(const std::vector<T1>& items, T2 target) {
  if (items.empty() || target < items.at(0)->s()) return -1;
  if (target < items.at(0)->s()) return -1;
  for (int i = items.size() - 1; i >= 0; i--) {
    if (target > items.at(i)->s()) return i;
  }
  return 0;
}

static bool FileExists(const std::string& path) {
  if (FILE* f = fopen(path.c_str(), "r")) {
    fclose(f);
    return true;
  }
  return false;
}

static std::vector<std::string> Split(const std::string& str,
                                      const std::string& delimiter) {
  std::vector<std::string> res;
  size_t pos = 0;
  size_t index = 0;
  std::string token;
  while ((pos = str.find(delimiter, index)) != std::string::npos) {
    token = str.substr(index, pos - index);
    res.emplace_back(token);
    index = pos + delimiter.length();
  }
  token = str.substr(index);
  res.emplace_back(token);
  return res;
}

template <typename T>
static T Clamp(T a, T min = T(0), T max = T(1)) {
  return std::min(std::max(a, min), max);
}

static std::string StrToUpper(const std::string& s) {
  std::string ret = s;
  std::transform(s.begin(), s.end(), ret.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return ret;
}

static std::string StrToLower(const std::string& s) {
  std::string ret = s;
  std::transform(s.begin(), s.end(), ret.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return ret;
}

static bool StrEquals(const std::string& a, const std::string& b) {
  if (a.size() == b.size() && StrToUpper(a) == StrToUpper(b)) {
    return true;
  }
  return false;
}

static tinyxml2::XMLError XmlQueryBoolAttribute(
    const tinyxml2::XMLElement* xml_node, const std::string& name,
    bool& value) {
  tinyxml2::XMLError ret = xml_node->QueryBoolAttribute(name.c_str(), &value);
  return ret;
}

static tinyxml2::XMLError XmlQueryStringAttribute(
    const tinyxml2::XMLElement* xml_node, const std::string& name,
    std::string* value) {
  const char* val = xml_node->Attribute(name.c_str());
  if (nullptr == val) {
    return tinyxml2::XML_NO_ATTRIBUTE;
  }
  *value = val;
  return tinyxml2::XML_SUCCESS;
}

static tinyxml2::XMLError XmlQueryIntAttribute(
    const tinyxml2::XMLElement* xml_node, const std::string& name, int* value) {
  tinyxml2::XMLError ret = xml_node->QueryIntAttribute(name.c_str(), value);
  return ret;
}

static tinyxml2::XMLError XmlQueryFloatAttribute(
    const tinyxml2::XMLElement* xml_node, const std::string& name,
    float* value) {
  tinyxml2::XMLError ret = xml_node->QueryFloatAttribute(name.c_str(), value);
  return ret;
}

static tinyxml2::XMLError XmlQueryDoubleAttribute(
    const tinyxml2::XMLElement* xml_node, const std::string& name,
    double* value) {
  return xml_node->QueryDoubleAttribute(name.c_str(), value);
}

template <typename T>
static tinyxml2::XMLError XmlQueryEnumAttribute(
    const tinyxml2::XMLElement* xml_node, const std::string& name, T* value,
    const std::map<T, std::string>& choices) {
  std::string var;
  tinyxml2::XMLError ret = XmlQueryStringAttribute(xml_node, name, &var);
  if (tinyxml2::XMLError::XML_SUCCESS != ret) {
    return ret;
  }
  ret = tinyxml2::XMLError::XML_ERROR_PARSING_TEXT;
  for (const auto& choice : choices) {
    if (StrEquals(choice.second, var)) {
      *value = choice.first;
      ret = tinyxml2::XMLError::XML_SUCCESS;
      break;
    }
  }
  return ret;
}

static const tinyxml2::XMLElement* XmlNextSiblingElement(
    const tinyxml2::XMLElement* element) {
  return element->NextSiblingElement(element->Name());
}

}  // namespace common
}  // namespace opendrive

#endif  // OPENDRIVE_CPP_COMMON_HPP_
