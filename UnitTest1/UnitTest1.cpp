#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.13.2/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestAddPrice)
		{
			OpenHashTable hashTable;
			Price priceToAdd = { "TestProduct", "TestShop", 10.5 };
			hashTable.addPrice(priceToAdd);

			Assert::IsTrue(hashTable.searchProductByName("TestProduct"));
		}

		TEST_METHOD(TestDeletePrice)
		{
			OpenHashTable hashTable;
			Price priceToAdd = { "TestProduct", "TestShop", 10.5 };
			hashTable.addPrice(priceToAdd);

			Assert::IsTrue(hashTable.searchProductByName("TestProduct"));

			hashTable.deletePriceByName("TestProduct");

			Assert::IsFalse(hashTable.searchProductByName("TestProduct"));
		}
	};
}
