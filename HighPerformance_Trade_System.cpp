#pragma once

#include<memory>
#include<atomic>
#include<functional>
#include<vector>
#include<algorithm>
#include<type_traits>
#include<thread>
#include<ranges>


template <class T, class Compare>
void DeleteOrder(T& levels, Price price, Volume volume, Compare compare){
	auto it = std::ranges::find_if(levels.begin(),levels.end(),price,
		       [comp](const auto& p, Price price){
		       	    return comp(p.first,price);
		       });
	EXPECT(it != levels.end() && it -> first == price);

	it -> second -= volume;
	if(it -> second <= 0){
		levels.erase(it);
	}
}


struct Q
{
	alignas(64) std::atomic<uint64_t> mIndex;
	alignas(64) std::atomic<uint64_t> mPendingIndex;
	alignas(64) uint8_t mData[0];
};

//Simplified code
template <class C> void Q::pop(C readCallback)
{
	if(lastIndex == mIndex) return;

	std::memcpy(&size, mCurrent + sizeof(MessageSize),sizeof(MessageSize));
	uint8_t buffer[size]; // check overflow before using size

	std::memcpy(buffer,mCurrent + sizeof(MessageSize), size);

	readCallback(buffer, mSize);

}