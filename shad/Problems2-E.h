#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

const size_t MAXINT = 1000002;

template <typename InputIterator, typename OutputIterator, typename Compare>
OutputIterator MergeArrays(InputIterator left_beg, InputIterator left_end,
                           InputIterator right_beg, InputIterator right_end,
                           Compare compare, OutputIterator res)
{
    auto ptr_left = left_beg;
    auto ptr_right = right_beg;
    while ((ptr_left != left_end) && (ptr_right != right_end))
    {
        if (compare(*ptr_left, *ptr_right))
        {
            *res = *ptr_left;
            ++res;
            ++ptr_left;
        }
        else
        {
            *res = *ptr_right;
            ++res;
            ++ptr_right;
        }
    }
    while (ptr_left != left_end)
    {
        *res = *ptr_left;
        ++res;
        ++ptr_left;
    }
    while (ptr_right != right_end)
    {
        *res = *ptr_right;
        ++res;
        ++ptr_right;
    }
    return res;
}

template <typename Iterator, typename Compare>
void MergeSort(
    Iterator begin, Iterator end, Compare compare,
    std::vector<typename std::iterator_traits<Iterator>::value_type> &buffer)
{
    if (begin + 1 >= end)
    {
        return;
    }

    // In case of overflow.
    Iterator middle = begin + (end - begin) / 2;

    MergeSort(begin, middle, compare, buffer);
    MergeSort(middle, end, compare, buffer);

    MergeArrays(begin, middle, middle, end, compare, std::back_inserter(buffer));

    std::copy(buffer.begin(), buffer.end(), begin);
    buffer.clear();
}

template <typename Iterator, typename Compare>
void Sort(Iterator begin, Iterator end, Compare compare)
{
    std::vector<typename std::iterator_traits<Iterator>::value_type> buffer;

    MergeSort(begin, end, compare, buffer);
}

class Coin
{
public:
    size_t time;
    size_t coord;
};

bool CompareByCoordinate(const Coin &first_coin, const Coin &second_coin)
{
    return first_coin.coord < second_coin.coord;
}

std::vector<Coin> ReadInput(std::istream &input_stream)
{
    // Speed-up read from stream.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t number_of_coins = 0;
    input_stream >> number_of_coins;

    std::vector<Coin> coins(number_of_coins);
    for (size_t pos = 0; pos < number_of_coins; ++pos)
    {
        input_stream >> coins[pos].coord>> coins[pos].time;
    }

    return coins;
}

void PrintAnswers(std::vector < std::vector<size_t>> &left,
                  std::vector < std::vector< size_t>> &right)
{
    if (std::min(left[0][left.size() - 1], right[0][right.size() - 1]) !=
        MAXINT)
    {
        std::cout << std::min(left[0][left.size() - 1], right[0][right.size() - 1]) << std::endl;
    }
    else
    {
        std::cout << "No solution" << std::endl;
    }
}

void initWalkArray(std::vector < std::vector < size_t>> &arr)
{
    for (size_t pos = 0; pos < arr.size(); ++pos)
    {
        arr[pos].assign(arr.size(), MAXINT);
        arr[pos][pos] = 0;
    }
}

void fillPositionInWalkArray(std::vector < std::vector < size_t>> & left,
                             std::vector < std::vector < size_t>> & right,
                             bool is_update_left, bool is_cum_left,
                             std::vector<Coin> &coins, size_t from, size_t to,
                             size_t time_coord, size_t distance_left,
                             size_t distance_right, size_t left_ptr,
                             size_t right_ptr)
{
    size_t dist = 0;
    if (coins[distance_left].coord > coins[distance_right].coord)
    {
        dist = coins[distance_left].coord - coins[distance_right].coord;
    }
    else
    {
        dist = coins[distance_right].coord - coins[distance_left].coord;
    }

    size_t cum_dist = 0;
    if (is_cum_left)
    {
        if (left[from][to] == MAXINT)
        {
            return;
        }
        cum_dist = left[from][to] + dist;
    }
    else
    {
        if (right[from][to] == MAXINT)
        {
            return;
        }
        cum_dist = right[from][to] + dist;
    }

    if (cum_dist <= coins[time_coord].time)
    {
        if (is_update_left)
        {
            left[left_ptr][right_ptr] = std::min(left[left_ptr][right_ptr], cum_dist);
        }
        else
        {
            right[left_ptr][right_ptr] =
                std::min(right[left_ptr][right_ptr], cum_dist);
        }
    }
}

void Solution(std::vector<Coin> &coins)
{
    Sort(coins.begin(), coins.end(), CompareByCoordinate);

    auto number_of_coins = coins.size();
    std::vector < std::vector < size_t>> left(number_of_coins);
    std::vector < std::vector < size_t>> right(number_of_coins);

    initWalkArray(left);
    initWalkArray(right);

    for (size_t seg_len = 1; seg_len < number_of_coins; ++seg_len)
    {
        for (size_t seg_beg = 0; seg_beg + seg_len < number_of_coins; ++seg_beg)
        {

            fillPositionInWalkArray(left, right, true, true, coins, seg_beg + 1,
                                    seg_beg + seg_len, seg_beg, seg_beg, seg_beg + 1,
                                    seg_beg, seg_beg + seg_len);
            fillPositionInWalkArray(left, right, true, false, coins, seg_beg + 1,
                                    seg_beg + seg_len, seg_beg, seg_beg,
                                    seg_beg + seg_len, seg_beg, seg_beg + seg_len);
            fillPositionInWalkArray(right, right, false, false, coins, seg_beg,
                                    seg_beg + seg_len - 1, seg_beg + seg_len,
                                    seg_beg + seg_len - 1, seg_beg + seg_len, seg_beg,
                                    seg_beg + seg_len);
            fillPositionInWalkArray(left, right, false, true, coins, seg_beg,
                                    seg_beg + seg_len - 1, seg_beg + seg_len, seg_beg,
                                    seg_beg + seg_len, seg_beg, seg_beg + seg_len);
        }
    }

    PrintAnswers(left, right);
}

int compound()
{

    std::vector<Coin> coins = ReadInput(std::cin);

    Sort(coins.begin(), coins.end(), CompareByCoordinate);

    Solution(coins);

    return 0;
}
